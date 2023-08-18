################################################################################
##                                                                            ##
##    CONTAINS: Class with H5FlowStage inheritance designed to perform a      ##
##              selection on Bern Module 1 data processed in module0_flow     ##
##              format. Selected events are proton candidates. This code is   ##
##              modeled on https://github.com/DUNE/ndlar_flow/blob/main/src/  ##
##              module0_flow/analysis/stopping_muon_selection.py              ##
##                                                                            ##
################################################################################

import numpy as np
import numpy.ma as ma
import logging
from scipy.interpolate import interp1d, pchip_interpolate
import scipy.integrate as integrate
import scipy.stats as stats
import scipy.ndimage as ndimage
import scipy.optimize as optimize
from copy import deepcopy

from h5flow.core import H5FlowStage
# don't have access to h5flow.core resources because they are now part of ndlar_flow/module0_flow vs. higher level h5flow
from h5flow.data import dereference_chain

import sys
sys.path.append("../../common")
from func import mode, condense_array
import units

class ProtonSelection(H5FlowStage):

    class_version = '0.0.0'

    default_params = dict(
        fid_cut=20, # mm
        cathode_fid_cut=20, # mm
        anode_fid_cut=20, # mm
        profile_dx=22, # mm
        profile_max_range=2000, # mm
        larpix_gain=250, # e/mV
        larpix_noise=500,  # e/mm
        proton_classifier_cut=-1.0,
        muon_classifier_cut=-1.0,
        dqdx_peak_cut=5e3, # e/mm
        profile_search_dx=22, # mm
        remaining_e_cut=85e9, # keV

        curvature_rr_correction=22.6647 / 22,
        density_dx_correction_params=[0.78497819, -3.41826874, 198.93022888],

        hits_dset_name='charge/hits', # '/data' directory may not be necessary ... unclear
        #charge_dset_name='charge/hits/', # TO DO: Calibrate for electron lifetime
        tracklet_dset_name='combined/tracklets', # no merged part?
        t0_dset_name='combined/t0', # 
        ext_trigs_dset_name='charge/ext_trigs',
        path='high_purity_sel/protons') # path within hdf5 file vs. file path

    event_summ_dset_name = 'event_summ_reco'
    event_tracks_dset_name = 'event_tracks_reco'
    #event_hits_dset_name = 'event_hits_reco'

    event_summ_dtype = np.dtype([('sel', 'u1'),
                                 ('event_id', 'f8'),
                                 ('next_trigs', 'f8'),
                                 ('ntracks', 'f8'),
                                 ('nhits', 'f8'), 
                                 ('event_charge', 'f8')])

    event_tracks_dtype = np.dtype([('nhits', 'f8'),
                                   ('length', 'f8'),
                                   ('theta', 'i8'),
                                   ('phi', 'f8'),
                                   ('track_q', 'f8')])
#
    #hit_profile_dtype = np.dtype([('idx','i4'),('rr','f8')])


    def __init__(self, **params):
        super(ProtonSelection, self).__init__(**params)
        
        for key,val in self.default_params.items():
            setattr(self, key, params.get(key, val))

        self.curvature_rr_correction = params.get('curvature_rr_correction', dict())
        self.density_dx_correction_params = params.get('density_dx_correction_params', dict())
        self.larpix_gain = params.get('larpix_gain', dict())


    def init(self, source_name):
        super(ProtonSelection, self).init(source_name)
        
        #self.is_mc = resources['RunData'].is_mc
        correction_key = ('medm')
        #correction_key = ('mc' if self.is_mc
        #                  else 'medm')
        #correction_key = ('high' if (not self.is_mc
       #                             and resources['RunData'].charge_thresholds == 'high')
         #                 else correction_key)
        self.curvature_rr_correction = self.curvature_rr_correction.get(correction_key, self.default_params['curvature_rr_correction'])
        self.density_dx_correction_params = self.density_dx_correction_params.get(correction_key, self.default_params['density_dx_correction_params'])
        self.larpix_gain = self.larpix_gain.get(correction_key, self.default_params['larpix_gain'])

        attrs = dict()
        for key in self.default_params:
            attrs[key] = getattr(self, key)
        #print(attrs)
        self.data_manager.set_attrs(self.path,
                                    classname=self.classname,
                                    class_version=self.class_version,
                                    **attrs)
        self.data_manager.create_dset(f'{self.path}/{self.event_summ_dset_name}',
                                      self.event_summ_dtype)
        #self.data_manager.create_dset(f'{self.path}/{self.event_tracks_dset_name}',
        #                              self.event_tracks_dtype)
        #self.data_manager.create_dset(f'{self.path}/{self.hit_profile_dset_name}',
        #                              self.hit_profile_dtype)
        #self.data_manager.create_ref(f'{self.path}/{self.hit_profile_dset_name}', self.hits_dset_name)
        #if self.is_mc:
        #    self.data_manager.create_dset(f'{self.path}/{self.event_sel_truth_dset_name}',
        #                                  self.event_sel_dtype)

        #self.create_dqdx_profile_templates()
        #self.data_manager.set_attrs(self.path,
        #                            proton_dqdx=self.proton_range_table['dqdx'],
        #                            muon_dqdx=self.muon_range_table['dqdx'],
        #                            proton_dqdx_width=self.proton_range_table['dqdx_width'],
        #                            muon_dqdx_width=self.muon_range_table['dqdx_width'],
        #                            proton_dedx=self.proton_range_table['dedx_mpv'],
        #                            muon_dedx=self.muon_range_table['dedx_mpv'],
        #                            proton_range=self.proton_range_table['range'],
        #                            muon_range=self.muon_range_table['range'],
        #                            proton_recom=self.proton_range_table['recomb'],
        #                            muon_recom=self.muon_range_table['recomb'])

    def finish(self, source_name):
        super(ProtonSelection, self).finish(source_name)
        summ_dset_name = f'{self.path}/{self.event_summ_dset_name}'

        if self.rank == 0:
            total = len(self.data_manager.get_dset(summ_dset_name))
            min_tracks = np.min(self.data_manager.get_dset(summ_dset_name)['ntracks'])
            print("Minimum tracks in an event:", min_tracks)
            max_tracks = np.max(self.data_manager.get_dset(summ_dset_name)['ntracks'])
            print("Maximum tracks in an event:", max_tracks)

            min_hits = np.min(self.data_manager.get_dset(summ_dset_name)['nhits'])
            print("Minimum hits in an event:", min_hits)
            max_hits = np.max(self.data_manager.get_dset(summ_dset_name)['nhits'])
            print("Maximum hits in an event:", max_hits)

            min_charge = np.min(self.data_manager.get_dset(summ_dset_name)['event_charge'])
            print("Minimum charge in an event:", min_charge)
            max_charge = np.max(self.data_manager.get_dset(summ_dset_name)['event_charge'])
            print("Maximum charge in an event:", max_charge)

            min_ext_trigs = np.min(self.data_manager.get_dset(summ_dset_name)['next_trigs'])
            print("Minimum ext_trigs in an event:", min_ext_trigs)
            max_ext_trigs = np.max(self.data_manager.get_dset(summ_dset_name)['next_trigs'])
            print("Maximum ext_trigs in an event:", max_ext_trigs)

            #nstopping = np.sum(self.data_manager.get_dset(sel_dset_name)['stop'])
            nselected = np.sum(self.data_manager.get_dset(summ_dset_name)['sel'])
            #print(f'Stopping: {nstopping} / {total} ({nstopping/total:0.03f})')
            print(f'Selected: {nselected} / {total} ({nselected/total:0.03f})')
            sel_events_mask = self.data_manager.get_dset(summ_dset_name)['sel'] == 1
            sel_events = self.data_manager.get_dset(summ_dset_name)[sel_events_mask]['event_id'][10:20]
            print("Sample events:", sel_events)

            #if self.is_mc:
            #    sel_truth_dset_name = f'{self.path}/{self.event_sel_truth_dset_name}'
            #    true_stopping = np.sum(self.data_manager.get_dset(sel_truth_dset_name)['stop'])
            #    true_stopping_muon = np.sum(self.data_manager.get_dset(sel_truth_dset_name)['sel'])
            #    print(f'True stopping: {true_stopping} / {total} ({true_stopping/total:0.03f})')
            #    print(f'True stopping muons: {true_stopping_muon} / {total} ({true_stopping_muon/total:0.03f})')

            #    correct = np.sum(self.data_manager.get_dset(sel_truth_dset_name)['sel'] &
            #                     self.data_manager.get_dset(sel_dset_name)['sel'])

            #    print(f'Purity: {correct} / {nselected} ({correct/nselected:0.03f})')
            #    print(f'Efficiency: {correct} / {true_stopping_muon} ({correct/true_stopping_muon:0.03f})')


    def run(self, source_name, source_slice, cache):
        super(ProtonSelection, self).run(source_name, source_slice, cache)
        
        # load arrays of event-level, hit-level, and track-level info
        events = cache[source_name]
        t0 = cache[self.t0_dset_name].reshape(cache[source_name].shape)
        hits = ma.array(cache[self.hits_dset_name], shrink=False)
        q = hits['q']
        q.reshape(hits.shape)
        tracks = ma.array(cache[self.tracklet_dset_name], shrink=False)

        if events.shape[0]:

            # prep arrays to write to file
            event_ids = events['id']
            event_next_trigs = events['n_ext_trigs']
            #print("Shape of one event's tracks:", tracks['id'][0].shape)
            #print("One event's tracks's mask:", tracks['id'][0].mask)
            #print("One event's tracks's ids:", tracks['id'][0])
            #print("Number of valid events for one event:", int((~tracks['id'][0].mask).sum()))
            event_ntracks = np.array([int((~tracks['id'][i].mask).sum()) for i in range(len(tracks))])
            event_nhits = events['nhit']
            event_charge = events['q']

            #print("Hits Shape:", hits.shape)

            max_hit_charge = np.array([np.max(hits['q'][i]) for i in range(len(hits))])

            nhits_cut = (event_nhits > 50) & (event_nhits < 5000)
            hit_charge_threshold_cut = (max_hit_charge > 300) 
            external_trigger_cut = (event_next_trigs > 0)
            event_sel = nhits_cut & hit_charge_threshold_cut & external_trigger_cut

            #track_nhits = tracks.ravel()['nhit'][~tracks['nhit'].mask]
            #track_length = tracks.ravel()['length'][~tracks['length'].mask]
            #track_theta = tracks.ravel()['theta'][~tracks['theta'].mask]
            #track_phi = tracks.ravel()['phi'][~tracks['phi'].mask]
            #track_q = tracks.ravel()['q'][~tracks['q'].mask]

            
            
            
            #print("Max Track length:", max_track_length)

        event_summ = np.zeros(len(tracks), dtype=self.event_summ_dtype)

        if len(event_summ):
            event_summ['sel'] = event_sel
            event_summ['event_id'] = event_ids
            event_summ['next_trigs'] = event_next_trigs
            event_summ['ntracks'] = event_ntracks
            event_summ['nhits'] = event_nhits
            event_summ['event_charge'] = event_charge

        #event_tracks = np.zeros(len(track_length), dtype=self.event_tracks_dtype)

        #if len(event_tracks):
        #    event_tracks['nhits'] = track_nhits
        #    event_tracks['length'] = track_length
        #    event_tracks['theta'] = track_theta
        #    event_tracks['phi'] = track_phi
        #    event_tracks['track_q'] = track_q
        #    
        #hit_profile = np.zeros(hits.shape, dtype=self.hit_profile_dtype)
        #if len(hit_profile):
        #    hit_profile['idx'] -= 1
        #    hit_profile['idx'][~hits['id'].mask] = hit_prof_idx[~hits['id'].mask]
        #    hit_profile['rr'][~hits['id'].mask] = hit_prof_rr[~hits['id'].mask]


        # reserve data space
        event_summ_slice = self.data_manager.reserve_data(
            f'{self.path}/{self.event_summ_dset_name}', source_slice)
        #event_tracks_slice = self.data_manager.reserve_data(
        #    f'{self.path}/{self.event_tracks_dset_name}', source_slice)
        #event_hits_slice = self.data_manager.reserve_data(
        #    f'{self.path}/{self.hit_profile_dset_name}', int((~hits['id'].mask).sum()))


        # write
        self.data_manager.write_data(f'{self.path}/{self.event_summ_dset_name}',
                                     event_summ_slice, event_summ)
        #self.data_manager.write_data(f'{self.path}/{self.event_tracks_dset_name}',
        #                             event_tracks_slice, event_tracks)
        #self.data_manager.write_data(f'{self.path}/{self.hit_profile_dset_name}',
        #                             event_hits_slice, hit_profile[~hits['id'].mask])
        #self.data_manager.write_ref(f'{self.path}/{self.hit_profile_dset_name}',
        #        self.hits_dset_name, np.c_[event_hits_slice, hits['id'].compressed()])

            ## calculate hit positions and charge
            #hit_q = self.larpix_gain * q['q'] # convert mV -> ke
#
            ## filter out bad channel ids
            #hit_mask = (hits['px'] != 0.0) & (hits['py'] != 0.0) & ~hit_q.mask & ~hit_drift['t_drift'].mask
            #hit_q.mask = hit_q.mask | ~hit_mask
            #hit_xyz = ma.array(np.concatenate([
            #    hits['px'][..., np.newaxis], hits['py'][..., np.newaxis], 
            #    hit_drift['z'][..., np.newaxis]], axis=-1), shrink=False,\
            #    mask=np.zeros(hits['px'].shape + (3,), dtype=bool) | hit_q.mask[...,np.newaxis] | ~hit_mask[...,np.newaxis])

        #Event charge threshold selection
        #HIP, MIP selection
        #Track fitting
        #PIDA
        #Void analysis
