#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <libgen.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

int  main(){

string xx = "aaa\tbbb\tttt\tccc\tdddt\tee\tfff\tgg\thhh\tuuuu\tkkkkkk\tt\tbuxc";
const string string_test(xx);
vector<string> string_splitted = split(string_test, '\t');

cout <<"\n"<< xx <<"\n\n";
for(int i =0 ; i < string_splitted.size() ; ++i)
        cout << string_splitted[i] <<endl;

//splice:
vector<string> el_elim;

auto it = next(string_splitted.begin(), 8);
move(string_splitted.begin(), it, back_inserter(el_elim));
//string_splitted.erase(string_splitted.begin(), it);

cout << "dopo l'operazione:\n> string_splitted: ";
for(int i =0 ; i < string_splitted.size() ; ++i)
        cout << string_splitted[i] << " ";

cout << "\n> el_elim: ";
for(int i =0 ; i < el_elim.size() ; ++i)
        cout << el_elim[i] << " ";

cout << "\n\n";

//join:
ostringstream oss;
//Strip off the trailing comma
// Convert all but the last element to avoid a trailing ","
copy(el_elim.begin(), el_elim.end()-1, ostream_iterator<string>(oss, "\t"));
// Now add the last element with no delimiter
oss << el_elim.back();

string vec2string = oss.str();

cout << "\n vec2string  > " << vec2string << endl;

vector<string> vettore_string;
vettore_string.push_back(vec2string);

for(int i =0 ; i < vettore_string.size() ; ++i)
        cout << vettore_string[i] << " ## ";








return 0;
}

