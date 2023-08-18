#!/bin/bash

################################################################################
##                                                                            ##
##    CONTAINS: Bash script to run proton selection on a single file. Script  ##
##              is based on https://github.com/peter-madigan/                 ##
##              module0_flow_tutorial/blob/main/run_module0_flow_example.sh.  ##
##                                                                            ##
################################################################################

# Runs proton selection on an example file
# (must be run from within h5flow environment and module0_flow_selection/ directory)
# Usage:
#   source run_proton_selection.sh <example file>
# 
# file path in NERSC: /global/cfs/cdirs/dune/www/data/Module1/reco/charge_only/events_2022_02_08_08_54_32_CET.gz.h5

INPUT_FILE=$1
OUTPUT_FILE=/global/cfs/cdirs/dune/users/ehinkle/nd_prototypes_ana/bern_module_selections/proton_selection/module0_flow_selection/test_out.h5

# for running on a login node
H5FLOW_CMD='h5flow'
# for running on a single compute node with 32 cores
#H5FLOW_CMD='srun -n32 h5flow'

export PYTHONPATH=$PYTHONPATH:/global/cfs/cdirs/dune/users/ehinkle/nd_prototypes_ana/bern_module_selections/proton_selection/module0_flow_selection/



# run stages
WORKFLOW1='h5flow_proton_selection_test.yaml'


if [ -e $OUTPUT_FILE ]; then
    rm -i $OUTPUT_FILE
fi

$H5FLOW_CMD --nompi -c $WORKFLOW1 -i $INPUT_FILE -o $OUTPUT_FILE 

echo "Done!"
echo "Output can be found at $OUTPUT_FILE"