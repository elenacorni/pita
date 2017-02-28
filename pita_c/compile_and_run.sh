g++ -std=c++11 lib/cRNA.cpp -o lib/XXXX
perl pita_prediction.pl -utr input_utr.fa -mir input_microRNAs.fa -prefix $1
