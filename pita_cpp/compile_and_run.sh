g++  -std=c++11  lib/RNAddG_compute.cpp  -o lib/RNAddG_compute_CPP
perl pita_prediction.pl -utr input_utr.fa -mir input_microRNAs.fa -prefix $1
