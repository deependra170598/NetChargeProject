# NetChargeProject
Net charge distribution study in simulated data for pp collision.

## To see these project files in order to execute follow table below accordingly.


 | S.N.| input file | .cpp file | output file |
 | --- | ----- | ---- | ------ |
 | 1.|MeanpT_7TeV_CR_0_RH_off.root | readfile.cpp | Netcharge_and_multiplicity.root|
 | 2.|Netcharge_and_multiplicity.root | percentile.cpp | percentile.txt |
 | 3.|Array from percentile.txt | Netcharge_and_multiplicity_with_percentile.cpp | Netcharge_and_multiplicity_with_percentile.root |
 | 4.|Netcharge_and_multiplicity_with_percentile.root | plot_Netcharge_vs_mean_multiplicity.cpp | plot.root |

## Steps
1. readfile.cpp file is run to get Netcharge_and_multiplicity.root file which contains net charge distribution with |eta|<0.8 and multiplicity distrbution with V0M cut.
2. percentile.cpp file is run with input file as Netcharge_and_multiplicity.root to get the corresponding cut for each percentile bin on multiplicity distribution with V0M cut.
3. From percentile.txt array of percentile cut is taken as input to Netcharge_and_multiplicity_with_percentile.cpp and is run to get net charge distribution and multiplicity distribution for different percentile bins.
4. To plot net charge vs mean multiplicity marco plot_Netcharge_vs_mean_multiplicity.cpp is run with inputfile Netcharge_and_multiplicity_with_percentile.root and at last plot is obtained in plot.root file.
