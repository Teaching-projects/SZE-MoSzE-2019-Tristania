#include <iostream>
#include "Dir.hpp"
#include "File.hpp"
#include "System.hpp"
#include <sstream>

using namespace std;

int main() {
	System filesystem;

	string cmd;
    string tokens[3];
	do {
		filesystem.printCore();
        //cmd tokenize
        getline(cin, cmd);

        stringstream ss(cmd);
        string token;
        int i = 0;
        while (getline(ss, token, ' ')) {
            tokens[i] = token;
            i++;
        }
        
		if (tokens[0] == "mkdir") {
            filesystem.mkdir(tokens[1]);
        }
		else if (tokens[0] == "ls") {
            if (tokens[1].empty()) {
                filesystem.ls("");
            } else {
                filesystem.ls(tokens[1]);
            }
			
		}
		else if (tokens[0] == "cd") {
			if (tokens[1] == "..") {
				filesystem.cdBack();
			}
			else {
                try {
                    filesystem.cd(tokens[1]);
                } catch (NoDirectoryExc e) {
                    cerr << e.getWhat();
                }
			}
		}
		else if(tokens[0]=="rm"){
			if (tokens[1] == "-rf") {

                filesystem.rmrf(tokens[2]);
			} else {
                filesystem.rm(tokens[1]);
			}
		}
        else if(tokens[0]=="touch") {
            filesystem.touch(tokens[1]);
        }
		else if (tokens[0] != "exit") {
			cerr << "The command is not valid.\n";
		}
        
        //reset cmd strings manually
        //TODO: make automatically
        tokens[0].clear();
        tokens[1].clear();
        tokens[2].clear();
	} while (tokens[0] != "exit");
}
