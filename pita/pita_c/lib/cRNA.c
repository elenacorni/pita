#include <stdio.h>
#include <assert.h>
#include <libgen.h>
#include <string.h>

#include "helper_string.h"

void loadArg(int argc, const char **argv, char flag, int var){
  if(checkCmdLineFlag(argc, argv, flag)){
    var = getCmdLineArgumentInt(argc, argv, flag);
  }
}

int main(int argc, char **argv){
  const char *RNAHYBRID_EXE_DIR = "Bin/RNAHybrid/RNAhybrid-2.1/src";
  const char *$RNAddG_EXE_DIR 	= "Bin/ViennaRNA/ViennaRNA-1.6/Progs/";
 
  //Define variable and set default
  int ddG_area        = 70;
  int FULL_TL         = 50;
  int DDG_OPEN        = 25;
  int include_3max    = 0;
  int include_ddG_v4  = 0;
  char *components    = NULL;
  
  int upstream_rest   = 0;
  int downstream_rest = 0;
  int no_force        = 0;
  
  char *file_ref, *file;
  
  //Load arg from command line..
  //loadArg(argc, argv, flag, var);
  
  getCmdLineArgumentString(argc,(const char **)argv, "file",     &file);
  getCmdLineArgumentString(argc,(const char **)argv, "file_ref", &file_ref);
  
  loadArg(argc,(const char **)argv, "ddgarea",         &ddG_area);
  loadArg(argc,(const char **)argv, "tl",              &FULL_TL);
  loadArg(argc,(const char **)argv, "dgtl",            &DDG_OPEN);
  loadArg(argc,(const char **)argv, "3max",            &include_3max);
  loadArg(argc,(const char **)argv, "ddG_v4",          &include_ddG_v4);
  loadArg(argc,(const char **)argv, "upstream_rest",   &upstream_rest);
  loadArg(argc,(const char **)argv, "downstream_rest", &downstream_rest);
  loadArg(argc,(const char **)argv, "noforce",         &no_force);
/*  
  if(checkCmdLineFlag(argc, (const char **)argv, "ddgarea")){
    ddG_area = getCmdLineArgumentInt(argc, (const char **)argv, "ddgarea");
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "tl")){
    FULL_TL = getCmdLineArgumentInt(argc, (const char **)argv, "tl");
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "dgtl")){
    DDG_OPEN = getCmdLineArgumentInt(argc, (const char **)argv, "dgtl");
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "3max")){
    include_3max = getCmdLineArgumentInt(argc, (const char **)argv, "3max");
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "ddG_v4")){
    include_ddG_v4 = getCmdLineArgumentInt(argc, (const char **)argv, "ddG_v4");
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "upstream_rest")){
    upstream_rest = getCmdLineArgumentInt(argc, (const char **)argv, "upstream_rest");
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "downstream_rest")){
    downstream_rest = getCmdLineArgumentInt(argc, (const char **)argv, "downstream_rest");
  }
  if(checkCmdLineFlag(argc, (const char **)argv, "noforce")){
    no_force = getCmdLineArgumentInt(argc, (const char **)argv, "noforce");
  }*/
  getCmdLineArgumentString(argc,(const char **)argv, "components", &components);
  
  //Step over all Locations
  int done       = 0;
  int bunch_size = 1000;
  
  while(!done){
    char *dGduplexesInputArray;
    char *ddGInputArray;
    char *headerInputArray;
    int record;
    
    int nlines;
    for(nlines=0; nlines<bunch_size, nlines++){
      
    }
    
  }
  return 0;
}














