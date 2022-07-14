#include<iostream>
#include<cmath>
#include<string>
#include<fstream>

using namespace std;
int main()
{
std::ifstream t;
int length;
t.open("file.txt");      // open input file
t.seekg(0, std::ios::end);    // go to the end
length = t.tellg();           // report location (this is the length)
t.seekg(0, std::ios::beg);    // go back to the beginning
char* buffer = new char[length];    // allocate memory for a buffer of appropriate dimension
t.read(buffer, length);       // read the whole file into the buffer
t.close();

cout << buffer << endl;
}