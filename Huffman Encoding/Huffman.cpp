//compile using -std=c++11
#include <iostream>
#include <string>
#include <fstream>
#include "adaptiveHuffman.h"
#include <stdlib.h>
using namespace std;

int main(int argc, char const *argv[])
{
	if(argc != 4)
	{
		 // Invalid number of files
		cout << "Invald number of command line arguments" << endl;
		return 1;
	}
	string *alphabet_file_name = new string(argv[1]);
	string *message_file_name = new string(argv[2]);
	string *operation = new string(argv[3]);
	string alphabet;
    string message;
	ifstream infile;
	infile.open(alphabet_file_name->c_str());
	while(!infile.eof())
	{
		getline(infile, alphabet);
	}
    infile.close();
    infile.clear();
    infile.open(message_file_name->c_str());
    while(!infile.eof())
    {
        getline(infile, message);
    }
	string * alph = new string(alphabet);

    string * msg = new string(message);

	AdaptiveHuffman ADH(alph);
    ADH.populateList(alph);
    ADH.printList();

    if(*operation == "encode")
    {
        ADH.encode(msg);
    }
	if(*operation == "decode")
	{
		ADH.decode(msg);
	}
	return 0;
}