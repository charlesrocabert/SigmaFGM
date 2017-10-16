
# Requirements

First, the execution of our scripts require some dependencies:
* Python
* R software, with the R packages <code>corrplot</code> and <code>ellipse</code>

The code should work properly on Unix and OSX. We do not provide the code for Windows.

# Scripts execution

To reproduce our analysis on yeast data provided by Yvert et al. (2013), please follow the next few steps:

* Download the git repository <code>SigmaFGM</code> ((anonymized))
* Dowload raw yeast data at http://sunlight.k.u-tokyo.ac.jp/wild37noise/index.html. You must convert <code>xls</code> files to <code>csv</code> format, and place the resulting files in the folder <code>SigmaFGM-master/phenomics_analysis/csv</code>
* With your terminal, navigate to the folder <code>SigmaFGM-master/phenomics_analysis</code> using command <code>cd</code>
* Simply run the bash script with this command:

        bash run_phenomics_analysis.sh

* Wait

The resulting data is dispatched in various folders, and the pictures are located in the folder <code>pic</code>.

