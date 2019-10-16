#include <iostream>
#include "Dir.hpp"
#include "File.hpp"
#include "System.hpp"

using namespace std;

int main() {
	System filesystem;

	string cmd;
	do {
		filesystem.printCore();
		cin >> cmd;
		if (cmd == "mkdir") {
			string dirname;
			cin >> dirname;
            filesystem.mkdir(dirname);
        }
		else if (cmd == "ls") {
			filesystem.ls();
		}
		else if (cmd == "cd") {
			string dirname;
			cin >> dirname;
			if (dirname == "..") {
				filesystem.cdBack();
			}
			else {
                filesystem.cd(dirname);
			}
		}
		else if(cmd=="rm"){
			string second;
			cin >> second;

			if (second == "-rf") {
				string dirname;
				cin >> dirname;
                filesystem.rmrf(dirname);
			} else {
                filesystem.rm(second);
			}
		}
        else if(cmd=="touch") {
            string fname;
            cin>>fname;
            
            filesystem.touch(fname);
        }
		else if (cmd != "exit") {
			cerr << "The command is not valid.\n";
		}
	} while (cmd != "exit");
}
