################################################################################
##                                                                            ##
##    CONTAINS: Method to make cuts on Bern Module Data based on charge       ##
##              threshold and number of hits in event. Returns event ids of   ##
##              passing events.                                               ##
##                                                                            ##
################################################################################

import h5py, glob, argparse
import numpy as np
import sys

def make_charge_thresh_cut(events_passed, events_data, hits_data, thresh):

    print("Starting charge threshold and HIP/MIP cut ...")

    passing_events = events_passed

    events_to_run_over = len(events_data['id'])

    for i in range(events_to_run_over):

        if i%10==0: print("Event "+str(i)+'/'+str(events_to_run_over))

        id = events_data['id'][i]
        # Cut on number of hits in an event
        events_event_id_mask = events_data['id'] == id
        event = events_data[events_event_id_mask]
        if event['nhit'] > 50 and event['nhit'] < 5000: 
            passing_events.append(id)
        else: 
            continue

        # Cut on max charge for a hit in the event
        hits_event_id_mask = hits_data['id'] == id
        event_hits = hits_data[hits_event_id_mask]
        max_charge = np.max(event_hits['q'])
        if max_charge > thresh: 
            passing_events.append(id)
        else:
            continue       

    return passing_events