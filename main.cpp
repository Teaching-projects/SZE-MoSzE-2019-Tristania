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
			if (!filesystem.alreadyExists(dirname)) {
				filesystem.mkdir(dirname);
			} else cerr <<"This directory name already taken. Please try again with another name!" << endl;
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
				if (!filesystem.alreadyExists(dirname)) {
					cerr << "No directory found with the given name. Please try again with another name!\n";
				}
				else {
					filesystem.cd(dirname);
				}
			}
		}
		else if(cmd=="rm"){
			string second;
			cin >> second;

			if (second == "-rf") {
				string dirname;
				cin >> dirname;
				if (!filesystem.alreadyExists(dirname)) {
					cerr << "No directory found with the given name. Please try again with another name!\n";
				}else {
					filesystem.rmrf(dirname);
				}
			} else {
				if (!filesystem.alreadyExists(second)) {
					cerr << "No directory found with the given name. Please try again with another name!\n";
				}
				else {
					filesystem.rm(second);
				}
			}
		}
        else if(cmd=="touch") {
            string fname;
            cin>>fname;

            filesystem.touch(fname);
        }
        else if(cmd=="echo"){
            std::string fname;
            std::string content;
            cin>>fname;
            cin>>content;
            filesystem.echo(fname,content);
        }
		else if (cmd != "exit") {
			cerr << "The command is not valid.\n";
		}
	} while (cmd != "exit");
}
