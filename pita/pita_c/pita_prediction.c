#include <stdio.h>
#include <assert.h>

#include "helper_string.h"

//corresponding of File::Basename in perl
#include <libgen.h>

//to run a command line on terminal
//use "system()"
#include <stdlib.h>

//to retrieve pid of process
//use "getpid()"
#include <unistd.h>

//to concatenate strings:
//use "char *strcat(char *dest, const char *src)"
#include <string.h>

void printHelp(){
printf("syntax: pita_prediction.pl [OPTIONS]\n\n");
printf("Execute the PITA algorithm for identifying and scoring microRNA target sites.\n\n");
printf("options:\n");
printf("    -utr <filename>:      fasta file containing the UTRs to be scanned\n");
printf("    -mir <filename>:      fasta file containing the microRNA sequences\n");
printf("    -upstream <filename>: fasta file containing the upstream sequence for each UTR. The IDs\n");
printf("                          in should match the IDs found int the UTR file. If less 200 bp are\n");
printf("                          given (or if no file is given), it is padded with Poly-A.\n\n");
printf("    -flank_up <bp>\n");
printf("    -flank_down <bp>:     Flank requirement in basepairs (default: zero for both)\n\n");
printf("    -ddG_context <bp>:    Number of bases upstream and downstream for target site that are\n");
printf("                         taken into account when folding the UTR (default: 70)\n\n\n");
printf("    -prefix <string>:     Add the string as a prefix to the output files (pita_results.tab and ext_utr.stab)\n");
printf("    -gxp:        Produce a gxp (Genomica project file) output file.\n\n");
printf("    Seed matching parameters:\n\n");
printf("    -len <num1-num2>:     Search for seed lengths of num1,...,num2 to the MicroRNA (default: 6-8)\n\n");
printf("    -gu <nums>:           Lengths for which G:U wobbles are allowed and number of allowed wobbles.\n");
printf("                          Format of nums: <length;num G:U>,<length;num G:U>,... (default: 6;0,7;1,8;1)\n\n");
printf("    -mis <nums>:          Lengths for which mismatches are allowed and number of allowed mismatches\n");
printf("                          Format of nums: <length;num mismatches>,<length;num mismatches>,...\n");
printf("                          (default: 6;0,7;0,8;1)\n\n");
printf("    -loop <nums>:         Lengths for which a single loop in either the target or the microrna is allowed\n");
printf("                          Format of nums: <length>,<length>,... (default: none)\n\n");
}


int mainFun(const int argc, const char **argv){
	char *flank_down  = NULL, *loop   = NULL, *utr_fn     = NULL;
        char *flank_up    = NULL, *mir_fn = NULL, *lengths    = NULL;;
        char *upstream_fn = NULL, *gxp    = NULL, *mismatches = NULL;
        char *prefix      = NULL, *gu     = NULL;
	if(checkCmdLineFlag(argc, argv, "help")){
		printHelp();
		return 0;
	}
	if(!getCmdLineArgumentString(argc, argv, "prefix", &prefix)){ 
		printf("Error: must specifiy a prefix for the output file(s) (-prefix)\n");
		return 0;
	}
	if(!getCmdLineArgumentString(argc, argv, "utr", &utr_fn)){
        	printf("Error: must specifiy a UTR file (-utr)\n");
		return 0;
	}
        if(!getCmdLineArgumentString(argc, argv, "mir", &mir_fn)){
        	printf("Error: must specifiy a miRs file (-mir)\n");
		return 0;
	}
	getCmdLineArgumentString(argc, argv, "upstream",   &upstream_fn);
        getCmdLineArgumentString(argc, argv, "flank_up",   &flank_up);
        getCmdLineArgumentString(argc, argv, "flank_down", &flank_down);
        getCmdLineArgumentString(argc, argv, "len",        &lengths);
        getCmdLineArgumentString(argc, argv, "gu",         &gu);
        getCmdLineArgumentString(argc, argv, "mis",        &mismatches);
        getCmdLineArgumentString(argc, argv, "loop",       &loop);
        getCmdLineArgumentString(argc, argv, "gxp",        &gxp);
	
	int pid = getpid();

	char curdir[1000];
	getcwd(curdir, sizeof(curdir));
	char runcmd[2000];

	strcpy(runcmd, curdir);
	char buffer[1000];
	snprintf(buffer, sizeof(buffer), "/lib/pita_run.pl -utr %s -mir %s -prefix %s_ ", utr_fn, mir_fn, prefix);
	strcat(runcmd, buffer);

	if(upstream_fn != NULL && upstream_fn[0] != 0){
		snprintf(buffer, sizeof(buffer), " -upstream %s", upstream_fn);
		strcat(runcmd, buffer);
	}
        if(flank_up != NULL && flank_up[0] != 0){
                snprintf(buffer, sizeof(buffer), " -flank_up %s", flank_up);
                strcat(runcmd, buffer);
        }
        if(flank_down != NULL && flank_down[0] != 0){
                snprintf(buffer, sizeof(buffer), " -flank_down %s", flank_down);
                strcat(runcmd, buffer);
        }
        if(lengths != NULL && lengths[0] != 0){
                snprintf(buffer, sizeof(buffer), " -len %s", lengths);
                strcat(runcmd, buffer);
        }
        if(gu != NULL && gu[0] != 0){
                snprintf(buffer, sizeof(buffer), " -gu %s", gu);
                strcat(runcmd, buffer);
        }
        if(loop != NULL && loop[0] != 0){
                snprintf(buffer, sizeof(buffer), " -loop %s", loop);
                strcat(runcmd, buffer);
        }
        if(mismatches != NULL && mismatches[0] != 0){
                snprintf(buffer, sizeof(buffer), " -mis %s", mismatches);
                strcat(runcmd, buffer);
        }
	printf("## runcmd..\n%s\n\n", runcmd);	
	system(runcmd);
	
	char command1[1000];
	snprintf(command1, sizeof(command1), "rm %s_ext_utr.stab; mv %s_pita_results.tab tmp_%d; head -n 1 tmp_%d | cut -f 1-5,8,10- > %s_pita_results.tab; cat tmp_%d | %s/lib/body.pl 2 -1 | tr -d \'\\r\' | cut -f 1-8,10- | %s/lib/merge_columns.pl -1 4 -2 5 -d ':' | %s/lib/merge_columns.pl -1 4 -2 5 -d ':' | sed 's/Seed:Mismatchs:G:U/Seed/g' | sort -k 13n >> %s_pita_results.tab; rm tmp_%d;", prefix, prefix, pid, pid, prefix, pid, curdir, curdir, curdir, prefix, pid);

	system(command1);

	char command2[1000];
	snprintf(command2, sizeof(command2), "cat %s_pita_results.tab | %s/lib/body.pl 2 -1 | cut -f 1,2,13 | %s/lib/modify_column.pl -c 2 -m '\"-1\"' | %s/lib/average_rows.pl -k 0,1 -losoe -n | %s/lib/cut.pl -f 2,3,1,4 | %s/lib/modify_column.pl -c 3 -m '\"-1\"' | %s/lib/modify_column.pl -c 3 -p 2 | sort -k 4n | %s/lib/cap.pl \"RefSeq,microRNA,Sites,Score\" > %s_pita_results_targets.tab", prefix, curdir, curdir, curdir, curdir, curdir, curdir, curdir, prefix); 

	system(command2);	

	if(gxp != NULL && gxp[0] != 0){
		if(atoi(gxp) == 1){
			printf("Creating gxp file... ");
			char gxp_header[2000];
			strcpy(gxp_header, "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n<GeneXPress>\n\n<TSCRawData>\nUID\tNAME\tGWEIGHT\tE1\nG2\tG2\t1\t1\n</TSCRawData>\n\n<GeneXPressAttributes>\n<Attributes Id=\"0\">\n<Attribute Name=\"g_module\" Id=\"0\" Value=\"1 2\">\n</Attribute>\n</Attributes>\n</GeneXPressAttributes>\n\n<GeneXPressObjects>\n<Objects Type=\"Genes\" URLPrefix=\"genome-www4.stanford.edu/cgi-bin/SGD/locus.pl?locus=\">\n<Gene Id=\"0\" ORF=\"G2\" Desc=\"G2\">\n<Attributes AttributesGroupId=\"0\" Type=\"Full\" Value=\"1\">\n</Attributes>\n</Gene>\n</Objects>\n<Objects Type=\"Experiments\">\n<Experiment Id=\"0\" name=\"E1\">\n</Experiment>\n</Objects>\n</GeneXPressObjects>\n<TSCHierarchyClusterData NumClusters=\"1\">\n<Root ClusterNum=\"0\" NumChildren=\"0\">\n</Root>\n</TSCHierarchyClusterData>\n");

			FILE *file;
			char name_gxp[50];
			snprintf(name_gxp, sizeof(name_gxp), "%s_pita_results.gxp", prefix);			
			
			file=fopen(name_gxp, "w");
			if(file == NULL)
				return -1;
			fprintf(file, "%s", gxp_header);
			fclose(file);
			char command_gxp[1000];
			snprintf(command_gxp, sizeof(command_gxp), "%s/lib/fasta2stab.pl %s | %s/lib/stab2length.pl | %s/lib/lin.pl | %s/lib/add_column.pl -s 0 | %s/lib/cut.pl -f 2,1,4,3 | %s/lib/add_column.pl -s 0 | %s/lib/add_column.pl -s 1 | %s/lib/tab2feature_gxt.pl -n 'UTR Sequences' >> %s", curdir, utr_fn, curdir, curdir, curdir, curdir, curdir, curdir, curdir, name_gxp);

			system(command_gxp);
			
			snprintf(command_gxp, sizeof(command_gxp), "%s/lib/body.pl 2 -1 %s_pita_results.tab | tr -d '\\r' | %s/lib/cut.pl -f 1-4,2,14 | %s/lib/uniquify.pl -c 1 | %s/lib/tab2feature_gxt.pl -n 'PITA Predictions' -c '0,0,255,1'  -lh 50 -l 'Filled box' -minc '0' -maxc '25' >> %s",curdir, prefix, curdir, curdir, curdir, name_gxp);
			
			system(command_gxp);
			file=fopen(name_gxp, "a");
			if(file == NULL)
                                return -1;
                        fprintf(file, "<GeneXPressTable Type=\"ChromosomeTrack\" Name=\"UTR Sequences Track\" TrackNames=\"UTR Sequences\">\n</GeneXPressTable>\n<GeneXPressTable Type=\"ChromosomeTrack\" Name=\"PITA Predictions Track\" TrackNames=\"PITA Predictions\">\n</GeneXPressTable>\n<TableDisplay TableDataModel=\"PITA Predictions Track\">\n</TableDisplay>\n<TableDisplay TableDataModel=\"UTR Sequences Track\">\n</TableDisplay>\n<GeneXPressClusterLists>\n</GeneXPressClusterLists>\n</GeneXPress>\n");
			fclose(file);
			printf(" Done.\n");			
		}
	}
	system("./removeIllegalXMLChars.pl");
	printf("Done.\n\n");
	return 0;
}


int main(int argc, char **argv){
	
	int xxx = mainFun(argc, (const char **)argv);
	return 0;
}


