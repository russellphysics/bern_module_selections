#!/usr/local/bin/python3.8
######
#
# This code generates root file from evd file
#
######

from array import array
import glob
import h5py
import math
from math import sqrt
from math import pow
import os
import ROOT
from ROOT import TCanvas, TFile, TProfile, TNtuple, TH1F, TH1D, TH2F, TH2D, TH1, TLine, TF1, TRandom3
from ROOT import gROOT, gBenchmark, gRandom, gSystem, gStyle
import sys
import argparser

def main(input_files, output_dir, argv=None):

    # ============================================================
    # Set paths
    # ============================================================

    print(' Input files: ', input_files)

    print(' Output dir: ', output_dir)

    #VD=0.100  # 0.00
    #VD=0.441  # 0.05
    #VD=0.535 # 0.10
    #VD=0.734  # 0.15
    #VD=0.933  # 0.20
    #VD=1.081  # 0.25
    #VD=1.230  # 0.30
    #VD=1.345  # 0.35
    #VD=1.461  # 0.40
    #VD=1.554  # 0.45
    VD=1.648  # 0.50
    #VD=1.727  # 0.55
    #VD=1.806  # 0.60
    #VD=1.876  # 0.65
    #VD=1.941  # 0.70
    #VD=2.000  # 0.75
    #VD=2.060  # 0.80
    #VD=2.098  # 0.85
    #VD=2.147  # 0.90
    #VD=2.192  # 0.95
    #VD=2.238  # 1.00

    VD_array=[0.933,1.081,1.230,1.345,1.461,1.554,1.648,1.727,1.806,1.876,1.941,2.000,2.060,2.098,2.147,2.192,2.238]  #0.2 - 1.00

    #files = [
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt20_kVcm_datalog_2021_04_08_19_54_08_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt25_kVcm_datalog_2021_04_08_19_17_38_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt30_kVcm_datalog_2021_04_08_18_42_39_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt35_kVcm_datalog_2021_04_08_17_54_11_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt40_kVcm_datalog_2021_04_08_17_22_02_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt45_kVcm_datalog_2021_04_08_16_43_54_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt50_kVcm_datalog_2021_04_08_15_55_15_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt55_kVcm_datalog_2021_04_08_15_21_33_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt60_kVcm_datalog_2021_04_08_14_40_33_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt65_kVcm_datalog_2021_04_08_13_41_37_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt70_kVcm_datalog_2021_04_08_13_07_58_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt75_kVcm_datalog_2021_04_08_12_35_50_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt80_kVcm_datalog_2021_04_08_11_50_48_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt85_kVcm_datalog_2021_04_08_10_41_33_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt90_kVcm_datalog_2021_04_08_10_10_37_CEST_evd.h5",
#"/data/rdiurbaData/SingleModule0_HVScan_h5Files/0pt95_kVcm_datalog_2021_04_08_09_33_03_CEST_evd.h5"
#    ]

    #f = h5py.File(os.path.join(datapath,fname),'r')
    fnum=0;
    
    for fname in input_files:
        
        VD=VD_array[fnum]
        fnum=fnum+1;
        f = h5py.File(os.path.join(datapath,fname),'r')
        print(' Processing file', fname)

        #print('File has keys: ', [key for key in f.keys()])
        events    = f['events']
        hits      = f['hits']
        info      = f['info']
        tracks    = f['tracks']
        ext_trigs = f['ext_trigs']

        print(' file keys: ', f.keys())
        print(' n events:    ', len(events))
        print(' n hits:      ', len(hits))
        print(' n tracks:    ', len(tracks))
        print(' n ext_trigs: ', len(ext_trigs))

        # fill tree

        outFileName = fname[:-3] + '.root'
        print('output file : ', output_dir + '' + outFileName )

        output_file = ROOT.TFile((output_dir + '' + outFileName), "RECREATE")
        output_tree = ROOT.TTree("events", "events")
        track_tree = ROOT.TTree("tracks", "tracks")

        #branches
        MAXHITS = f['events']['nhit'].max()
        MAXTRACKS = f['tracks']['nhit'].max()
        MAXTRIGS = f['events']['n_ext_trigs'].max()
        #print('test MAXTRIGS : ', f['events']['n_ext_trigs'].max())


        # Event informations
        eventID              = array('i',[0])           # event ID [-]
        event_start_t        = array('i',[0])           # event timestamp start [UNITS?]
        event_end_t          = array('i',[0])           # event timestamp end [UNITS?]
        event_duration       = array('i',[0])           # event timestamp end - start [UNITS?]
        event_unix_ts        = array('i',[0])           # event unix timestamp [UNITS?]
        event_nhits          = array('i',[0])           # number of hits in the event [-]
        event_q              = array('f',[0.])          # total deposited charge [ke]
        event_q_raw          = array('f',[0.])          # total deposited raw charge [ke]
        event_ntracks        = array('i',[0])           # number of tracks [-]
        event_n_ext_trigs    = array('i',[0])           # number of external triggers [-]
        event_hits_x         = array('f',[0.]*MAXHITS)  # events hit coordinates (x)
        event_hits_y         = array('f',[0.]*MAXHITS)  # events hit coordinates (y)
        event_hits_z         = array('f',[0.]*MAXHITS)  # events hit coordinates (z)
        event_hits_ts        = array('i',[0]*MAXHITS)   # events hit coordinates (timestamp)
        event_hits_q         = array('f',[0.]*MAXHITS)  # events hit charge (ke)
        event_hits_io_group  = array('i',[0]*MAXHITS)   # event hit io group (TPC 1, 2)
        event_hits_chipid    = array('i',[0]*MAXHITS)   # event hit chipid
        event_hits_channelid = array('i',[0]*MAXHITS)   # event hit channelid
        event_hits_io_channel= array('i',[0]*MAXHITS)   # event hit io channel
        event_hits_global_id  = array('i',[0]*MAXHITS)   # event hit global id

        # Track informations
        trackID              = array('i',[0])		# track ID [-]
        track_eventID	     = array('i',[0])		# parent event id [-]
        track_event_start_t  = array('i',[0])
        track_no_in_event    = array('i',[0])
        track_nhits          = array('i',[0])           # number of hits in the track [-]
        track_start_pos_x    = array('f',[0.])          # start position x of the track [mm]
        track_start_pos_y    = array('f',[0.])          # start position y of the track [mm]
        track_start_pos_z    = array('f',[0.])          # start position z of the track [mm]
        track_start_pos_t    = array('f',[0.])          # start position t of the track [0.1 us]
        track_end_pos_x      = array('f',[0.])          # end   position x of the track [mm]
        track_end_pos_y      = array('f',[0.])          # end   position y of the track [mm]
        track_end_pos_z      = array('f',[0.])          # end   position z of the track [mm]
        track_end_pos_t      = array('f',[0.])          # end   position t of the track [0.1 us]
        track_dx             = array('f',[0.])
        track_dy             = array('f',[0.])          #  [0.1 us]
        track_dz             = array('f',[0.])          #  [mm]
        track_length         = array('f',[0.])          # length of the track [mm]
        track_nhits          = array('i',[0])           # number of hits in the track [-]
        track_q              = array('f',[0.])          # total deposited charge [ke]
        track_q_raw          = array('f',[0.])          # total deposited raw charge [ke]
        track_theta          = array('f',[0.])          # track theta
        track_phi            = array('f',[0.])          # track phi
        track_residual_x     = array('f',[0.])          # track residual x
        track_residual_y     = array('f',[0.])          # track residual y
        track_residual_z     = array('f',[0.])          # track residual z
        #track_hits_x         = array('f',[0.]*MAXHITS)  # tracks hit coordinates (x)
        #track_hits_y         = array('f',[0.]*MAXHITS)  # tracks hit coordinates (y)
        #track_hits_z         = array('f',[0.]*MAXHITS)  # tracks hit coordinates (z)
        #track_hits_ts        = array('i',[0]*MAXHITS)   # tracks hit coordinates (timestamp)
       
        track_hits_x=ROOT.std.vector('float')();
        track_hits_y=ROOT.std.vector('float')();
        track_hits_z=ROOT.std.vector('float')();
        track_hits_ts=ROOT.std.vector('int')();
        track_space_x=ROOT.std.vector('float')();
        track_space_y=ROOT.std.vector('float')();
        track_space_z=ROOT.std.vector('float')();
        track_space_ts=ROOT.std.vector('int')();




        #track_hits_q         = array('f',[0.]*MAXHITS)  # tracks hit charge (ke)
        #track_hits_dr        = array('f',[0.]*MAXHITS)  # hit distance from start of track
        #track_hits_Dt        = array('f',[0.]*MAXHITS)
        #track_hits_global_id = array('i',[0]*MAXHITS)   # hit global pixel id
        track_hits_dqdx         =  ROOT.std.vector('float')();# tracks hit charge (ke)
        track_hits_qSum        = ROOT.std.vector('float')();  # hit distance from start of track
        track_hits_res       = ROOT.std.vector('float')();
                
        track_hits_q         =  ROOT.std.vector('float')();# tracks hit charge (ke)
        track_hits_dr        = ROOT.std.vector('float')();  # hit distance from start of track
        track_hits_Dt        = ROOT.std.vector('float')();
        track_hits_global_id = array('i',[0]*MAXHITS)   # hit global pixel id

        # External Trigger informations
        trigID               = array('i',[0]*MAXTRIGS)     # trigger ID
        trig_type            = array('i',[0]*MAXTRIGS)     # trigger type (1-normal ; 2-external; 3-cross ; 4-periodic # TODO: IS THIS TRUE?)
        trig_ts		     = array('f',[0.]*MAXTRIGS)	    # trigger time
        trig_eventID         = array('i',[0]*MAXTRIGS)      # trigger eventid

        # Event
        output_tree.Branch("eventID"           ,eventID           ,"eventID/I")
        output_tree.Branch("event_start_t"     ,event_start_t     ,"event_start_t/I")     # 32 bit timestamp (2^32-1 = 2.147483647e9)
        output_tree.Branch("event_end_t"       ,event_end_t       ,"event_end_t/I")       # 32 bit timestamp (2^32-1 = 2.147483647e9)
        output_tree.Branch("event_duration"    ,event_duration    ,"event_duration/I")
        output_tree.Branch("event_unix_ts"     ,event_unix_ts     ,"event_unix_ts/I")
        output_tree.Branch("event_nhits"       ,event_nhits       ,"event_nhits/I")
        output_tree.Branch("event_q"           ,event_q           ,"event_q/F")
        output_tree.Branch("event_q_raw"       ,event_q_raw       ,"event_q_raw/F")
        output_tree.Branch("event_ntracks"     ,event_ntracks     ,"event_ntracks/I")
        output_tree.Branch("event_n_ext_trigs" ,event_n_ext_trigs ,"event_n_ext_trigs/I")
        output_tree.Branch("event_hits_x"      ,event_hits_x      ,"event_hits_x[event_nhits]/F")
        output_tree.Branch("event_hits_y"      ,event_hits_y      ,"event_hits_y[event_nhits]/F")
        output_tree.Branch("event_hits_z"      ,event_hits_z      ,"event_hits_z[event_nhits]/F")
        output_tree.Branch("event_hits_ts"     ,event_hits_ts     ,"event_hits_ts[event_nhits]/I")
        output_tree.Branch("event_hits_q"      ,event_hits_q      ,"event_hits_q[event_nhits]/F")
        output_tree.Branch("event_hits_io_group"  ,event_hits_io_group  ,"event_hits_io_group[event_nhits]/I")
        output_tree.Branch("event_hits_chipid"    ,event_hits_chipid    ,"event_hits_chipid[event_nhits]/I")
        output_tree.Branch("event_hits_channelid" ,event_hits_channelid ,"event_hits_channelid[event_nhits]/I")
        output_tree.Branch("event_hits_io_channel" ,event_hits_io_channel ,"event_hits_io_channel[event_nhits]/I")
        output_tree.Branch("event_hits_global_id" ,event_hits_global_id ,"event_hits_global_id[event_nhits]/I")



        # Tracks
        track_tree.Branch("trackID"          ,trackID          ,"trackID/I")
        track_tree.Branch("track_eventID"    ,track_eventID    ,"track_eventID/I")
        track_tree.Branch("track_event_start_t"    ,track_event_start_t    ,"track_event_start_t/I")
        track_tree.Branch("track_no_in_event"    ,track_no_in_event    ,"track_no_in_event/I")
        track_tree.Branch("track_nhits"      ,track_nhits      ,"track_nhits/I")
        track_tree.Branch("track_start_pos_x",track_start_pos_x,"track_start_pos_x/F")
        track_tree.Branch("track_start_pos_y",track_start_pos_y,"track_start_pos_y/F")
        track_tree.Branch("track_start_pos_z",track_start_pos_z,"track_start_pos_z/F")
        track_tree.Branch("track_start_pos_t",track_start_pos_t,"track_start_pos_t/I")
        track_tree.Branch("track_end_pos_x"  ,track_end_pos_x  ,"track_end_pos_x/F")
        track_tree.Branch("track_end_pos_y"  ,track_end_pos_y  ,"track_end_pos_y/F")
        track_tree.Branch("track_end_pos_z"  ,track_end_pos_z  ,"track_end_pos_z/F")
        track_tree.Branch("track_end_pos_t"  ,track_end_pos_t  ,"track_end_pos_t/I")
        track_tree.Branch("track_dx"  ,track_dx  ,"track_dx/F")
        track_tree.Branch("track_dy"  ,track_dy  ,"track_dy/F")
        track_tree.Branch("track_dz"  ,track_dz  ,"track_dz/F")

        track_tree.Branch("track_length"     ,track_length     ,"track_length/F")
        track_tree.Branch("track_nhits"      ,track_nhits      ,"track_nhits/I")
        track_tree.Branch("track_q"          ,track_q          ,"track_q/F")
        track_tree.Branch("track_q_raw"      ,track_q_raw      ,"track_q_raw/F")
        track_tree.Branch("track_theta"      ,track_theta      ,"track_theta/F")
        track_tree.Branch("track_phi"        ,track_phi        ,"track_phi/F")
        track_tree.Branch("track_residual_x" ,track_residual_x ,"track_residual_x/F")
        track_tree.Branch("track_residual_y" ,track_residual_y ,"track_residual_y/F")
        track_tree.Branch("track_residual_z" ,track_residual_z ,"track_residual_z/F")
        #track_tree.Branch("track_hits_x"     ,track_hits_x     ,"track_hits_x[track_nhits]/F")
        #track_tree.Branch("track_hits_y"     ,track_hits_y     ,"track_hits_y[track_nhits]/F")
        #track_tree.Branch("track_hits_z"     ,track_hits_z     ,"track_hits_z[track_nhits]/F")
        #track_tree.Branch("track_hits_ts"    ,track_hits_ts    ,"track_hits_ts[track_nhits]/I")
        track_tree.Branch("track_hits_x"     ,track_hits_x     )
        track_tree.Branch("track_hits_y"     ,track_hits_y    )
        track_tree.Branch("track_hits_z"     ,track_hits_z   )
        track_tree.Branch("track_hits_ts"    ,track_hits_ts  )
        #track_tree.Branch("track_hits_q"     ,track_hits_q     ,"track_hits_q[track_nhits]/F")
        #track_tree.Branch("track_hits_Dt"    ,track_hits_Dt    ,"track_hits_Dt[track_nhits]/F")
        #track_tree.Branch("track_hits_dr"    ,track_hits_dr    ,"track_hits_dr[track_nhits]/F")
        track_tree.Branch("track_hits_q"     ,track_hits_q    )
        track_tree.Branch("track_hits_Dt"    ,track_hits_Dt  )
        track_tree.Branch("track_hits_dr"    ,track_hits_dr )
        track_tree.Branch("track_space_x"     ,track_space_x     )
        track_tree.Branch("track_space_y"     ,track_space_y    )
        track_tree.Branch("track_space_z"     ,track_space_z   )
        track_tree.Branch("track_space_ts"    ,track_space_ts  )      
        
        track_tree.Branch("track_hits_dqdx"     ,track_hits_dqdx    )
        track_tree.Branch("track_hits_res"    ,track_hits_res )
        track_tree.Branch("track_hits_qSum"    ,track_hits_qSum )
        
        
        track_tree.Branch("track_hits_global_id" ,track_hits_global_id ,"track_hits_global_id[track_nhits]/I")

        # External Triggers
        output_tree.Branch("trigID"           	,trigID           ,"trigID[event_n_ext_trigs]/I")
        output_tree.Branch("trig_type"        	,trig_type        ,"trig_type[event_n_ext_trigs]/I")
        output_tree.Branch("trig_time"		,trig_ts	,"trig_time[event_n_ext_trigs]/I")
        output_tree.Branch("trig_eventID"          ,trig_eventID        ,"trig_eventID[event_n_ext_trigs]/I")

        print('Tree branches are created.')

        for ev_index in range(len(f['events'])):
            #if ev_index>=100:
            #    break
            #print('ev index of loop',ev_index ,end='\r')

            event = f['events'][ev_index]
            tracks = f['tracks'][event['track_ref']]
            hits = f['hits'][event['hit_ref']]
            trigs = f['ext_trigs'][event['ext_trig_ref']]

            #print('event number : ', event['evid'])
            #print('N tracks', len(tracks))
            #print('N hits', len(hits))
            #print('N trigs', len(trigs))
            #if len(trigs) <1:
            #    continue
            #print('trig ', trigs['type'][0] )
            #if trigs['type'][0] != 2:
            #    print('not an external trigger.')
            #    continue

            eventID[0]           = event['evid']
            event_start_t[0]     = event['ts_start']
            event_end_t[0]       = event['ts_end']
            event_duration[0]    = event['ts_end'] - event['ts_start']
            event_unix_ts[0]     = event['unix_ts']
            event_nhits[0]       = event['nhit']
            event_q[0]           = event['q']
            event_q_raw[0]       = event['q_raw']
            event_ntracks[0]     = event['ntracks']
            event_n_ext_trigs[0] = event['n_ext_trigs']
            for hit in range(len(hits)):
                event_hits_x[hit]  = hits['px'][hit]
                event_hits_y[hit]  = hits['py'][hit]
                if hits['iogroup'][hit] == 1 :
                    event_hits_z[hit]  = -320 +(hits['ts'][hit] - event['ts_start'])*(VD/10)
                if hits['iogroup'][hit] == 2 :
                    event_hits_z[hit]  = 320 - (hits['ts'][hit] - event['ts_start'])*(VD/10)
                event_hits_ts[hit]  = hits['ts'][hit]
                event_hits_q[hit]  = hits['q'][hit]
                event_hits_io_group[hit] = hits['iogroup'][hit]
                event_hits_chipid[hit] = hits['chipid'][hit]
                event_hits_channelid[hit] = hits['channelid'][hit]
                event_hits_io_channel[hit] = hits['iochannel'][hit]
                event_hits_global_id[hit] = ((hits['iogroup'][hit]*256+hits['iochannel'][hit])*256+ hits['chipid'][hit])*64 + hits['channelid'][hit]
            # end for hit
            for i in range(len(tracks)):
                track_hits_x.clear()
                track_hits_y.clear()
                track_hits_ts.clear()
                track_hits_q.clear()
                track_hits_z.clear()
                track_hits_Dt.clear()
                track_hits_dr.clear()
                track_space_x.clear()
                track_space_y.clear()
                track_space_z.clear()
                track_space_ts.clear()
    
                track_hits_res.clear()
                track_hits_qSum.clear()
                track_hits_dqdx.clear()
                trackID[0]		= tracks[i]['track_id']
                track_eventID[0]	= event['evid']
                track_event_start_t[0] = event['ts_start']
                track_no_in_event[0]   = event['ntracks']
                track_nhits[0]  	= tracks[i]['nhit']
                track_start_pos_x[0]= tracks[i]['start'][0]
                track_start_pos_y[0]= tracks[i]['start'][1]
                track_start_pos_z[0]	= tracks[i]['start'][2]
                track_start_pos_t[0]	= tracks[i]['start'][3]
                track_end_pos_x[0]	= tracks[i]['end'][0]
                track_end_pos_y[0]	= tracks[i]['end'][1]
                track_end_pos_z[0]	= tracks[i]['end'][2]
                track_end_pos_t[0]	= tracks[i]['end'][3]
                track_dx[0]         = tracks[i]['end'][0] - tracks[i]['start'][0]
                track_dy[0]         = tracks[i]['end'][1] - tracks[i]['start'][1]
                track_dz[0]         = tracks[i]['end'][2] - tracks[i]['start'][2]

                track_length[0]	    = tracks[i]['length']
                track_theta[0]       	= tracks[i]['theta']
                track_phi[0]         	= tracks[i]['phi']
                track_residual_x[0]  	= tracks[i]['residual'][0]
                track_residual_y[0]  	= tracks[i]['residual'][1]
                track_residual_z[0]  	= tracks[i]['residual'][2]
                track_nhits[0]       	= tracks[i]['nhit']
                track_q[0]           	= tracks[i]['q']
                track_q_raw[0]       	= tracks[i]['q_raw']


                track_hits = f['hits'][tracks[i]['hit_ref']]
                #print('track hits :', len(track_hits))

                for hit in range(len(track_hits)):

                    track_hits_x.push_back(track_hits[hit]['px'])
                    track_hits_y.push_back(track_hits[hit]['py'])
                    if track_hits[hit]['iogroup']==1 :
                        track_hits_z.push_back(-320 + (track_hits[hit]['ts']-event['ts_start'])*(VD/10))
                    if track_hits[hit]['iogroup']==2 :
                        track_hits_z.push_back( 320 - (track_hits[hit]['ts']-event['ts_start'])*(VD/10))
                    track_hits_ts.push_back(int(track_hits[hit]['ts']))
                    track_hits_q.push_back(track_hits[hit]['q'])
                    track_hits_Dt.push_back(track_hits[hit]['ts'] - event['ts_start'])
                    track_hits_dr.push_back( sqrt(pow(track_hits_z[hit]-track_start_pos_z[0] ,2) \
                                        + pow(track_hits_y[hit]-track_start_pos_y[0] ,2) \
                                        + pow(track_hits_x[hit]-track_start_pos_x[0] ,2)))
                    track_hits_global_id[hit] = ((track_hits['iogroup'][hit]*256+track_hits['iochannel'][hit])*256+ track_hits['chipid'][hit])*64 + track_hits['channelid'][hit]
                k=0
                nseg=int(track_length[0]/10)
                segMin=0
                segMax=10
                while k<nseg:
                    j=0
                    qSum=0
                    dqdx=0
                    res=track_length[0]-(10*i)
                    segMax=segMax+10
                    segMin=segMin+10
                    count=0
                    trackX=0
                    trackY=0
                    trackZ=0
                    trackT=0
                    while j<len(track_hits_dr):
                         if(track_hits_dr[j]>segMax or track_hits_dr[j]<segMin):
                            j=j+1
                            continue
                         qSum=track_hits_q[j]+qSum
                         trackX=track_hits_x[j]+trackX
                         trackY=track_hits_y[j]+trackY
                         trackZ=track_hits_z[j]+trackZ
                         trackT=track_hits_ts[j]+trackT
                         j=j+1
                         count=count+1
                    """
                    if (qSum<=0):
                        track_hits_res.push_back(-9999)
                        track_hits_qSum.push_back(-9999)
                        track_hits_dqdx.push_back(-9999)
                        track_space_x.push_back(-9999)
                        track_space_y.push_back(-9999)
                        track_space_z.push_back(-9999)
                        track_space_ts.push_back(-9999)
                        i=i+1
                        continue
                    """
                    if (count<2):
                        k=k+1
                        continue
                    track_hits_res.push_back(res)
                    track_hits_qSum.push_back(qSum)
                    track_hits_dqdx.push_back(qSum)
                    track_space_x.push_back(trackX/count)
                    track_space_y.push_back(trackY/count)
                    track_space_z.push_back(trackZ/count)
                    track_space_ts.push_back(int(trackT/count))
                    k=k+1

                track_tree.Fill()
            #end track loop

            for t in range(len(trigs)):
                trigID[t]               = trigs[t]['trig_id']
                trig_type[t]            = trigs[t]['type']
                trig_ts[t]	        = trigs[t]['ts']
                trig_eventID[t]         = event['evid']

            output_tree.Fill()

        #end event loop

        #create indexx
        output_tree.BuildIndex("event_unix_ts","event_start_t")

        #####
        # Write output_tree
        # --------------------------------------------------------
        output_file.cd()
        output_tree.Write()
        track_tree.Write()

        print('\n Data has been written to %s ' %(output_dir + '/' + outFileName))
    #end file loop
    print("end of code")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--input_files','-i',required=True,type=str)
    parser.add_argument('--output_dir', '-o',required=True,type=str)
    args = parser.parse_args()
    main(**vars(args))
