#include <iostream>
#include "Dir.h"
#include "System.h"

using namespace std;

int main(){
	System filesystem;
	
	string cmd;
	do {
		filesystem.printCore();
		cin >>cmd;
		if (cmd == "mkdir") {
			string dirname;
			cin >>dirname;
			filesystem.mkdir(dirname, filesystem.getCurrent());
		} else if (cmd == "ls"){
			filesystem.ls();
		} else if (cmd == "cd") {
			string dirname;
			cin >>dirname;
			if (dirname == ".."){
				filesystem.cdBack();
			} else filesystem.cd(dirname);
		} else if (cmd != "exit"){
			cerr << "The command is not valid.\n";
		}
	} while (cmd != "exit");
}