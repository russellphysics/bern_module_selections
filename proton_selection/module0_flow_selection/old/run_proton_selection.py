################################################################################
##                                                                            ##
##    CONTAINS: Script to make full cuts for proton selection on Bern Module  ##
##              Data. Makes use of methods in other files in directory.       ##
##                                                                            ##
################################################################################

import h5py, glob, argparse
import numpy as np
import sys
import charge_threshold_cut as ct_cut
sys.path.append('../../common')
import file_parsing

def main(data_file):

    #for data_file in glob.glob(file_dir+'/*'): # Loop over data files

        #if (test_count % 5 == 0):
        #    print("Processing file: ", str(test_count), "/", str(n_files_processed))

    data_h5 = h5py.File(data_file,'r')
    file_parsing.print_keys_attributes(data_h5)

    events_data, hits_data = file_parsing.get_charge_datasets(data_h5)
    print("Number of Events Before Cuts:", len(events_data['id']))

    max_charge_threshold = 300
    print("Max Charge Threshold for Selection:", max_charge_threshold)

    # Get event IDs for events which pass max threshold and and no. of hits cuts: 
    ct_cut_passing_events = ct_cut.make_charge_thresh_cut([], events_data, hits_data, max_charge_threshold)
    print("Number of Events Passing Charge Threshold Cut:", len(ct_cut_passing_events))





if __name__=='__main__':
    parser = argparse.ArgumentParser()
    #parser.add_argument('-d', '--file_dir', default=None, required=True, type=str, \
    #                    help='''string corresponding to the path of the directory containing data files to be considered''')
    parser.add_argument('-f', '--data_file', default=None, required=True, type=str, \
                        help='''string corresponding to the path of the data file to be considered''')
    args = parser.parse_args()
    main(**vars(args))