#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv) {

string test;
test = argv[1];
cout << "test: " << test << "\n";


ifstream file(test);
string str;
string file_contents;
while (std::getline(file, str))
{
  file_contents += str;
  file_contents.push_back('\n');
}  

cout << "file_contents: " << file_contents << "\n";









/*
ifstream file(test);
string content;

while(file >> content) {
cout << content << "\n";
}
*/
return 0;
}
