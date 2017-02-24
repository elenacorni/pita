#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv) {

string test;
test = argv[1];
cout << "test: " << test << "\n";

ifstream file(test);
if(file)
cout << "il file esiste e l'ho aperto!\n";
else
cout << "NON ESISTE!!! o non riesco ad aprirlo!\n";
    string str; 
    while (getline(file, str))
    {
     cout << str << "\n\n";
cout << "altra riga...\n";
       }

return 0;
}
