#!/bin/bash

#python 1_save_strain_names.py
#python 2_xls_to_csv.py
python 3_merge_data.py
python 4_compute_interstrain_means.py
python 5_correct_data.py
python 6_center_and_scale_data.py
mkdir pic
path=$(pwd)
Rscript 7_analysis.R $path
