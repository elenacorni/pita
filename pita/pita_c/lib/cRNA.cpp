
/* ******************************************** *
 *  TRADUZIONE DELLO SCRIPT: RNAddG_compute.pl  *
 * ******************************************** */

#include <stdio.h>
#include <assert.h>
#include <libgen.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include "../helper_string.h"

using namespace std;

char const* const RNAHYBRID_EXE_DIR = "Bin/RNAHybrid/RNAhybrid-2.1/src";
char const* const RNAddG_EXE_DIR  = "Bin/ViennaRNA/ViennaRNA-1.6/Progs/";

//#############################################################################
vector<string> extract_sequence(int start, int end, int us, int ds, string sequence);
vector<string> getddG(vector<string> vIn, int downstream_rest);
vector<string> getdGduplexes(vector<string> vIn);
vector<string> split(const string &s, char delim);
void join_and_push(vector<string> vIn, char delimit, vector<string> &vOut);
void loadArg(int argc, const char **argv, const char *flag, int& var);
void printHelp();
string GetStdoutFromCommand(string cmd);


//##############################################################################
int main(int argc, char **argv){
  if(checkCmdLineFlag(argc, (const char**)argv, "help")){
	printHelp();
  	return 0;
  }
/*  
  string file_ref;
  string file = argv[1];
  ifstream fl(file);
  if(!fl.is_open()){
	cout << "Could not open file " << file << "\n";
  }
*/  
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
  
  //Load arg from command line..
  loadArg(argc,(const char **)argv, "tl",              FULL_TL);
  loadArg(argc,(const char **)argv, "dgtl",            DDG_OPEN);
  loadArg(argc,(const char **)argv, "3max",            include_3max);
  loadArg(argc,(const char **)argv, "ddG_v4",          include_ddG_v4);
  loadArg(argc,(const char **)argv, "upstream_rest",   upstream_rest);
  loadArg(argc,(const char **)argv, "downstream_rest", downstream_rest);
  loadArg(argc,(const char **)argv, "noforce",         no_force);
  getCmdLineArgumentString(argc,(const char **)argv, "components", &components);
  
  //Step over all Locations
  int done       = 0;
  int bunch_size = 1000;

  //cout << "# 5\n";
//int contatore = 0;
//  while(!done){
//cout << "#* n.giro nel while: " << contatore << "\n";
//
  vector<string> dGduplexesInputArray;
  vector<string> ddGInputArray;
  vector<string> headerInputArray;
//  string record;
  cout << "#* a\n";

//string file_ref;
string file = argv[1];
cout << "file: " << file << "\n";

ifstream fl(file);

/*
if(fl)
cout << "IL FILE ESISTE E RIESCO AD APRIRLO\n\n";
else 
cout << "NON ESISTE!!!!!! o NON RIESCO AD APRIRLO!!\n\n\n";
*/

string record;
//if(!fl.is_open()){
  //  cout << "Could not open file " << file << "\n";
//}
//else
// cout << "il file è aperto!!!\n\n";

//    int nlines;
//    for(nlines=0; nlines<bunch_size; nlines++){
cout << "---------------------------------inizio WHILE-------------------------------------\n";
    // trasformo il for in un while..
  while(getline(fl, record)){

cout << "\n\n >> RIGA...\n";
  cout << record << "\n\n";
/*      if(!(fl >> record)){
	done = 1;
	break;
      }*/
cout << "#*  > 1\n";	
      //chomp function:
      vector<string> row = split(record, '\t');
cout << "#*  > 2\n";
      int endpos = stoi(row[2]);
      string miRNA  = row[8];
      string utr    = row[11];
      string force_binding_i = "";
      string force_binding_j = "";
cout << "#*  > 3\n";
      if(!no_force){
	force_binding_i = row[9];
	force_binding_i = row[10];
      }
cout << "#*  > 4\n";
      //Calculate begining of target but make sure we're still in the UTR
      int startpos = max(endpos - FULL_TL + 1,1);
      cout << "#*  > 5\n";
      int maxtargetLen = endpos - startpos +1;
      string target = utr.substr(startpos -1, maxtargetLen);
      int real_start = max(endpos - DDG_OPEN +1,1);
cout << "#*  > 6\n";
      char del = '\t';
     //push(@headerInputArray,join ("\t", splice(@row, 0, 8))); si traduce in:
      //splice:
      vector<string> el_elim;
      auto it = next(row.begin(), 8);
      move(row.begin(), it, back_inserter(el_elim));
      join_and_push(el_elim, del, headerInputArray); 
cout << "#*  > 7\n";


      //join:
  //    ostringstream oss;
      //Convert all but the last element to avoid a trailing "\t"
    //  copy(el_elim.begin(), el_elim.end()-1, ostream_iterator<string>(oss, "\t"));
     // oss << el_elim.back(); //Now add the last element with no delimiter
     // string vec2string = oss.str();
      //push:
    //  headerInputArray.push_back(vec2string);

/* >>>>>>>>>>>>> SBAGLIATO: il problema è che force_binding_j è smepre zero!! <<<<<<<<<<<<<<<<<<<<<  */
      //push(@dGduplexesInputArray, join ("\t", $miRNA, $target, $force_binding_i, $force_binding_j));   
      cout << "#***  miRNA:  " << miRNA  << "  - target:  " <<  target << " - force_binding_i:  " << force_binding_i << " -  force_binding_j:  " << force_binding_j << "\n";
      vector<string> vectTmp = {miRNA, target, force_binding_i, force_binding_j};
      join_and_push(vectTmp, del, dGduplexesInputArray);
cout << "#*  > 8\n";
      //push(@ddGInputArray, join ("\t", $miRNA, $utr, $real_start, $endpos, $upstream_rest, $downstream_rest, $ddG_area));
      vector<string> vectTmp1 = {miRNA, utr, to_string(real_start), to_string(endpos), to_string(upstream_rest), to_string(downstream_rest), to_string(ddG_area)};
      join_and_push(vectTmp1, del, ddGInputArray);
cout << "#*  > 9 (in fondo al while)\n";
    }//fine while read_rows
cout << "---------------------------------fine WHILE-------------------------------------\n";

  int arraySize = headerInputArray.size();
  cout << "\nComputing " << arraySize << " results: ";

  vector<string> dGduplexesOutputArray = getdGduplexes(dGduplexesInputArray);
  vector<string> ddGOutputArray        = getddG(ddGInputArray, downstream_rest);
cout << "#* b\n";
  int i;
  char del = '\t';
  for(i=0; i<arraySize; i++){
      vector<string> v1 = split(dGduplexesOutputArray[i], del);
      vector<string> v2 = split(ddGOutputArray[i], del);
cout << "#* c\n";
      //$ddGall = $dGall + ($dG1 - $dG0);
      v2[0] = to_string( (stoi(v1[1]) + (stoi(v2[2]) - stoi(v2[1]))) );
cout << "#* d\n";
      int ddG_v4 = 0;
      int dG3max = 0;
      int dG3ratio = 0;
cout << "#* e (in fondo al while)\n";
      cout << headerInputArray[i] << "\t" << v1[0] << "\t" <<  v1[1] <<  "\t" <<  v1[2] << "\t" <<  v1[3] <<  "\t" << v2[0] << "\t"  <<  v2[1] <<  "\t" <<  v2[2] <<  "\t" <<  ddG_v4 <<  "\t" <<  dG3max <<  "\t" <<  dG3ratio << "\n";
  }
//contatore ++;
//  }//fine while
  cout << " Done.\n";
  cout << "\n###################################################################\n";
  cout << "\n##                       FINE cRNA.cpp                              ##\n";
  cout << "\n###################################################################\n";
  return 0;
}

//#############################################################################
vector<string> getddG(vector<string> vIn, int downstream_rest){
    vector<string> vOut;
    string upstream_rest;
    vector<string> seq_area;

    ofstream myfile("tmp_seqfile2");
    if(myfile.is_open()){
      int i;
      char del = '\t';
      for(i=0; i<vIn.size(); i++){
        string oneTarget = vIn[i];
	vector<string> vSplit = split(oneTarget, del);
	//Extract area around sequence
	int arg3 = stoi(vSplit[5]) + stoi(vSplit[6]);
	int arg4 = stoi(vSplit[4]) + stoi(vSplit[6]);
	seq_area = extract_sequence(stoi(vSplit[2]),stoi(vSplit[3]),arg3,arg4,vSplit[1]);
	myfile << seq_area[2] << "\n";
      }
      myfile.close();
    }
    else cout << "Could not open temporary sequence file.\n";

/*
    if(upstream_res.compare("0") != 0){
       //$upstream_rest =~ s/^0//; manca un *
       // Because we're gonna call C with this argument and
       // sscanf is problematic with leading zeros
       while(upstream_res[0] == '0'){
           upstream_res.erase(0,1);
       }
    }
*/
    string seq = seq_area[2];
    string bindStart = seq_area[0];
    string bindEnd   = seq_area[1];

    int target_len = stoi(bindEnd) - stoi(bindStart) + 1 + downstream_rest;

    std::stringstream cmd;
    cmd << " " << RNAddG_EXE_DIR << "/RNAddG4 -u " << upstream_rest << " -s " << bindEnd << " -f " << to_string(target_len) << " -t " << to_string(target_len) << " < tmp_seqfile2";

    int ii;
    cout <<  "Calling RNAddG with " << vIn.size() << " targets... \n";

    //my @resArray = split (/\n/, `$cmd`);
 
 /*   cmd << " > tmp_output_cmdLine1.txt";
    system(cmd.str().c_str());
    ifstream file("tmp_output_cmdLine1.txt");
    string str;
    string result_of_cmd;
    while(getline(file, str)){
      result_of_cmd += str;
      result_of_cmd.push_back('\n');
    }
    */
    string result_of_cmd = GetStdoutFromCommand(cmd.str());
    vector<string> resArray = split(result_of_cmd, '\n');

    for(ii=0; ii<resArray.size(); ii++){
      string resline = resArray[ii];
      vector<string> ddG_values = split(resline, '\n');
      vector<string> small = {ddG_values[6],ddG_values[3],ddG_values[4]};
      join_and_push(small, '\t', vOut);
    }

    return vOut;
}
//.............................................................................
vector<string> extract_sequence(int start, int end, int us, int ds, string sequence){
    int us_start = (start > us ? start - us : 1);
    int ds_end   = ((end + ds)< sequence.length() ? end + ds : sequence.length());
    int actual_start = start - us_start + 1;
    string string1 = sequence.substr(us_start -1, (ds_end - us_start) + 1);
    int actual_end = actual_start + abs(end - start);
    vector<string> result = {to_string(actual_start), to_string(actual_end), string1};

    return result;
}
//.............................................................................
vector<string> getdGduplexes(vector<string> vIn){
    vector<string> vOut;
    int insize = vIn.size();
/*
    int j;
    for(j=0; j<vIn.size(); j++){
       cout << "#_.-> vIn[" << j << "] = " << vIn[j] << "\n";
    }
*/
    ofstream myfile("tmp_seqfile1");
    if(myfile.is_open()){
      int i;
      char del = '\t';
      for(i=0; i<insize; i++){
        string oneTarget = vIn[i];
	vector<string> vSplit = split(oneTarget, del);
	int j;
	for(j=0; j<vSplit.size(); j++){
	   myfile << vSplit[j] << "\n";
	}
      }
      myfile.close();
    }
    else cout << "Could not open temporary sequence file.\n";

    //Call RNAduplex and extract result dGs and length
    int ii;
    std::stringstream cmd;
 //   cmd << " " <<  RNAddG_EXE_DIR << "RNAduplex -5 0 < tmp_seqfile1  | > tmp_output_cmdLine.txt";
 
    cmd << " " <<  RNAddG_EXE_DIR << "/RNAduplex -5 0 < tmp_seqfile1";

    cout << "Calling RNAduplex with " << insize << " targets... ";

    //my $result_of_cmd = `$cmd`;
 //  cmd << " | > tmp_output_cmdLine.txt";
 //   system(cmd.str().c_str());
    
/*    ifstream file("tmp_output_cmdLine.txt");
    string str;
    string result_of_cmd;
    while(getline(file, str)){
       result_of_cmd += str;
       result_of_cmd.push_back('\n');
    }
*/
    string result_of_cmd = GetStdoutFromCommand(cmd.str());
    vector<string> resArray = split(result_of_cmd, '\n');

    int outsize = resArray.size();

    if(insize != outsize)
       cout << "RNAduplex failure. Result was " << result_of_cmd << "\n";

    for(ii=0; ii<outsize; ii++){
       string resline = resArray[ii];
       vector<string> items  = split(resline, '\t');
       vector<string> small = {items[6], items[7], items[8], items[9]};
       join_and_push(small, '\t', vOut);
    }

    return vOut;
}
//.............................................................................
void join_and_push(vector<string> vIn, char delimit, vector<string> &vOut){
    ostringstream oss;
    string d ;
    d += delimit;
    //Convert all but the last element to avoid a trailing "delimit"
    copy(vIn.begin(), vIn.end()-1, ostream_iterator<string>(oss, d.c_str()));
    oss<< vIn.back(); //Now add the last element with no delimiter
    string vec2string = oss.str();
    //push:
    vOut.push_back(vec2string);
}
//.............................................................................
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
//.............................................................................
void loadArg(int argc, const char **argv, const char *flag, int &var){
  if(checkCmdLineFlag(argc, argv, flag)){
    var = getCmdLineArgumentInt(argc, argv, flag);
  }
}
//............................................................................
string GetStdoutFromCommand(string cmd) {
  string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");
 
  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
    if(fgets(buffer, max_buffer, stream) != NULL)
       data.append(buffer);
    pclose(stream);
  }

  return data;
}
//.............................................................................
void printHelp(){
printf("Usage: RNAddG_compute.pl <file>\n\n");
printf("	Compute the dG energies of potential target sites whose seed is given in the external\n");
printf("	tab file.\n\n");
printf("	Output consists of the input ID, followed by the following:\n\n");
printf("        Type         miRNA coordinates           Target coordinates\n");
printf("        ====         =================           ==================\n");
printf("        target_length\n");
printf("        dG all       nt 1 and up                 nt 1-FULL_TL\n");
printf("        dG 5'        nt 1-9                      computed\n");
printf("        dG 3'        nt 10 and up                computed\n");
printf("        dG0\n");
printf("        dG1\n");
printf("        ddG_v4\n");
printf("        dG 3' max    nt 10 and up                Reverse complement of\n");
printf("                                                 miRNA bases 10 and up\n");
printf("        dG 3' ratio\n\n");
printf("    -tl <num>:           Maximal target length (default: 50)\n");
printf("    -dgtl <num>:         Target length when opening for ddG calculation (default: 25)\n");
printf("    -ddgarea <num>:      Area upstream and downstream around target to fold (default: 70) \n");
printf("    -no3max:             Do not compute 3' max value and ratio (saves time)\n");
printf("    -components <file>:  Print the components of the ddG calculation into the given file.\n");
}
//.............................................................................


