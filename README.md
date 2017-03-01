# pita
Sorgente: https://genie.weizmann.ac.il/pubs/mir07/mir07_exe.html  

Il codice che si scarica dal sito è forlder-dependent:  
con il comando `make install` si copierà in tutti gli script il full path della cartella.  
Non si potrà quindi spostare il codice in altre cartelle senza prima aver cambiato il path file per file o rieseguendo il Makefile.  

Al fine di eliminare questa dipendenza hard-coded sono stati modificati i sorgenti in modo tale che automaticamente ad ogni esecuzione prendano il path della cartella corrente.  
L'applicazione modificata è stata messa in `64bit_exe_pita_prediction_no_path_dep.tar.gz`.

## Esecuzione Perl e compilazione CPP:
Run PITA:
```
perl pita_prediction.pl -utr input_utr.fa -mir input_microRNAs.fa -prefix <NOME_OUTPUT> [OPZIONI FACOLTATIVE (--help)]
```

RNAddG_compute.cpp:
```
g++  -std=c++11  RNAddG_compute.cpp  -o RNAddG_compute_CPP
```

