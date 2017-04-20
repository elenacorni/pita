# pita
Sorgente: https://genie.weizmann.ac.il/pubs/mir07/mir07_exe.html  

Il codice che si scarica dal sito è forlder-dependent:  
con il comando `make install` si copierà in tutti gli script il full path della cartella.  
Non si potrà quindi spostare il codice in altre cartelle senza prima aver cambiato il path file per file o rieseguendo il Makefile.  

Al fine di eliminare questa dipendenza hard-coded sono stati modificati i sorgenti in modo tale che automaticamente ad ogni esecuzione prendano il path della cartella corrente.  
L'applicazione modificata è stata messa in `64bit_exe_pita_prediction_no_path_dep.tar.gz`.

### Esecuzione Perl e compilazione CPP:
Run PITA:
```
perl pita_prediction.pl -utr input_utr.fa -mir input_microRNAs.fa -prefix <NOME_OUTPUT> [OPZIONI FACOLTATIVE (--help)]
```

RNAddG_compute.cpp:
```
g++  -std=c++11  RNAddG_compute.cpp  -o RNAddG_compute_CPP
```
### Troubleshouting:
Durante l'esecuzione di `pita_prediction.pl`:
```diff
- Errore:
Calling RNAduplex with 0 targets... Unescaped left brace in regex is deprecated, passed through in regex; marked by <-- HERE in m/\${ <-- HERE HOME}/ at /home/elena/Desktop/pita/pita_c/lib/libfile.pl line 379.
Unescaped left brace in regex is deprecated, passed through in regex; marked by <-- HERE in m/\${ <-- HERE HOME}/ at /home/elena/Desktop/pita/pita_c/lib/libfile.pl line 379.
+ Soluzione:
Nel file libfile.pl line 379:
Cambiare:
$file =~ s/\${HOME}/$home/ge;
in:
$file =~ s/\$\{HOME\}/$home/ge;
.................................................
- Errore:
Can't use 'defined(@array)' (Maybe you should just omit the defined()?) at /home/elena/Desktop/pita/pita_c/lib/join.pl line 205.
+ Soluzione:
Nel file join.pl line 205:
Cambiare:
if(define(@fill_lines) and $#fill_lines>=0)
in:
if(@fill_lines and $#fill_lines>=0)

```
---
# Compilare libreria ViennaRNA-1.6
Quickstart: Usually you'll just have to type:
```sh
./configure (CFLAGS="-std=gnu89 -g -O2 -fPIC")
make
# and (as root)
make install
```
Per compilare `RNAddG4.c`:
```sh
# guardare quali sono i comandi per compilare gli altri codici dall'output del make:
grep --color -Hr "RNAplfold" output_make.txt 
out_make.txt:if gcc -DHAVE_CONFIG_H -I. -I. -I.. -I../H    -std=gnu89 -g -O2 -fPIC -MT RNAplfold.o -MD -MP -MF ".deps/RNAplfold.Tpo" -c -o RNAplfold.o RNAplfold.c; \
out_make.txt:then mv -f ".deps/RNAplfold.Tpo" ".deps/RNAplfold.Po"; else rm -f ".deps/RNAplfold.Tpo"; exit 1; fi
out_make.txt:gcc  -std=gnu89 -g -O2 -fPIC   -o RNAplfold  RNAplfold.o ../lib/libRNA.a -lm 

# quindi fare...
gcc -DHAVE_CONFIG_H -I. -I. -I.. -I../H    -std=gnu89 -g -O2 -fPIC -MT RNAddG4.o -MD -MP -MF ".deps/RNAddG4.Po" -c -o RNAddG4.o RNAddG4.c
gcc  -std=gnu89 -g -O2 -fPIC   -o RNAddG4  RNAddG4.o ../lib/libRNA.a -lm
```

### Troubleshouting:

```diff
- Errore:
../lib/libRNA.a(subopt.o): In function `repeat':
/home/elena/Desktop/pita/pita_c/Bin/ViennaRNA/ViennaRNA-1.6/lib/subopt.c:855: undefined reference to `LoopEnergy'
/home/elena/Desktop/pita/pita_c/Bin/ViennaRNA/ViennaRNA-1.6/lib/subopt.c:914: undefined reference to `HairpinE'
/home/elena/Desktop/pita/pita_c/Bin/ViennaRNA/ViennaRNA-1.6/lib/subopt.c:828: undefined reference to `LoopEnergy'
collect2: error: ld returned 1 exit status
Makefile:320: recipe for target 'RNAsubopt' failed
make[2]: *** [RNAsubopt] Error 1
make[2]: Leaving directory '/home/elena/Desktop/pita/pita_c/Bin/ViennaRNA/ViennaRNA-1.6/Progs'
Makefile:268: recipe for target 'all-recursive' failed
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory '/home/elena/Desktop/pita/pita_c/Bin/ViennaRNA/ViennaRNA-1.6'
Makefile:187: recipe for target 'all' failed
make: *** [all] Error 2
.................................................
+ Soluzione:
>> ./configure CFLAGS="-std=gnu89 -g -O2 -fPIC"
```

```diff
- Errore:
rna_algebra.h: In member function ‘virtual int IntDistRNA_Algebra::worst_score() const’:
rna_algebra.h:168:12: error: ‘INT_MAX’ was not declared in this scope
     return INT_MAX;
            ^~~~~~~
rna_algebra.h: In member function ‘virtual int RIBOSUM8560::replace(RNA_Alphabet, int, RNA_Alphabet, int) const’:
rna_algebra.h:203:14: error: ‘INT_MIN’ was not declared in this scope
       return INT_MIN/4;
.................................................
+ Soluzione:
>> Aggiungere a "rna_algebra.h" : #include <limits.h>
```

```diff
- Errore:
ppforestsz.t.cpp:43:9: error: ‘memcpy’ was not declared in this scope
   memcpy(m_lml,ppf.m_lml,sizeof(Uint)*m_size);
   ~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ppforestsz.t.cpp:44:9: error: ‘memcpy’ was not declared in this scope, and no declarations were found by argument-dependent lookup at the point of instantiation [-fpermissive]
   memcpy(m_keyroot,ppf.m_keyroot,sizeof(bool)*m_size);
   ~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ppforestsz.t.cpp:43:9: note: ‘memcpy’ declared here, later in the translation unit
   memcpy(m_lml,ppf.m_lml,sizeof(Uint)*m_size);

o...
rna_profile_alignment.cpp:306:44: error: ‘memset’ was not declared in this scope
.................................................
+ Soluzione:
>> Nel file indicato aggiungere: #include <string.h>
```

```diff
- Errore:
ppforestbase.h:98:20: error: extra qualification ‘PPForestBase::’ on member ‘getMaxLength’ [-fpermissive]
   inline size_type PPForestBase::getMaxLength(size_type i) const
                    ^~~~~~~~~~~~
.................................................
+ Soluzione:
Nel file indicato:
prima...
inline size_type PPForestBase::getMaxLength(size_type i) const
    {
      assert(m_isSumUpCSFValid);

      if(j==0)
        return 0;
      else
        return m_sumUpCSF[i]+j-1;
    }

dopo...
inline size_type getMaxLength(size_type i) const
    {
      assert(m_isSumUpCSFValid);

      if(j==0)
        return 0;
      else
        return m_sumUpCSF[i]+j-1;
    }
```

```diff
- Errore:
main.c:30:14: error: conflicting types for ‘getline’
 static char *getline(FILE *fp);
.................................................
+ Soluzione:
>> This is because the stdio.h have a getline() function.
>> So a simple thing to make this work would be to rename your function to my_getline()
```
---
