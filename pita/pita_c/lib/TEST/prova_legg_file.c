#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv) {

string test;
test = argv[1];
cout << "test: " << test << "\n";

ifstream file("test.txt");
string content;

while(file >> content) {
//cout << content << "\n";
}
return 0;
}
