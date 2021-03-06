#include <iostream>
#include <exception>
#include <cstdio>
#include "brute.h"
using namespace std;

int main(int argc, char* argv[]) {
    //Checks input parameters
    //Standard use: given filename to edit
    if(argc == 2 && argv[1][0] != '-') {
        string fileName = argv[1];
        try {
            //Creates window pane to open fileName
            pane mainScreen(fileName);

            //Initializes window to interact with
            mainScreen.initialize();

            //Gives mainScreen control of typing
            mainScreen.take_control();

            //Ends the window so we can use terminal
            endwin();
            return 0;
        }
        catch (err &e) {
            endwin();
            cerr << e.what() << endl;
            return 2;
        }
    }
    //Saving a syntax style
    if((argc == 3 || argc == 4) && argv[1][0] == '-' && argv[1][1] == 's' && argv[2][0] != '-') {
        string fileName = argv[2];
        string ext;
        ofstream f;
        f.open((path + "sfiles/types.txt").c_str(), ios::app);
        if(!f.is_open()) {
            cout << "Could not add syntax style" << endl;
            cout << "Could not open types.txt" << endl;
            return 1;
        }
        else {
            //If the user specified the extensions in the command, add them to the file
            if(argc == 4) {
                f << argv[3];
            }
            //If not, we prompt the user for them
            else {
                cout << "Add file extensions: ";
                cin >> ext;
                f << ext;
            }
            f << " fileType:" << argv[2] << endl;
            f.close();
            //Copy the document specified into the sfiles directory
            ifstream original;
            string copy;
            string line;
            
            //Copy the document 
            original.open(argv[2]);
            if(original.is_open()) {
                while(!original.eof()) {
                    getline(original, line);
                    copy += line + '\n';
                }
                original.close();
            }
            else {
                cout << "Could not open " << argv[2] << endl;
                cout << "Did not copy " << argv[2] << " to sfiles directory." << endl;
                return 1;
            }

            //Write it into another file in the new directory
            string filename(argv[2]);
            f.open((path + "sfiles/" + filename).c_str());
            f << copy;
            cout << "Successfully added syntax highlighting file" << endl;
            f.close();
            return 0;
        }
    }
    //Printing all syntax file names
    if(argc == 2 && argv[1][0] == '-' && argv[1][1] == 'l') {
        fstream f;
        string s;
        const string indicator = "fileType:";
        f.open((path + "sfiles/types.txt").c_str());
        while(f.is_open() && !f.eof()) {
            getline(f, s);
            int index = s.find(indicator);
            if(index != string::npos)
                cout << s.substr(index+indicator.size()) << endl;
        }
        f.close();
        return 0;
    }
    //Deleting syntax files
    if(argc == 3 && argv[1][0] == '-' && argv[1][1] == 'r' && argv[2][0] != '-') {
        string fname(argv[2]);

        //Check that there was a reasonable input
        int i = fname.find(".txt");
        if(i == string::npos) {
            cout << "Could not delete " << fname << endl;
            return 1;
        }

        //Remove file
        if(remove((path + "sfiles/"+fname).c_str()) != 0) {
            cout << "Could not delete " << fname << endl;
            return 2;
        }

        //Remove the link to the file in types.txt
        fstream copy;
        string str;
        string newFile;
        copy.open((path + "sfiles/types.txt").c_str());
        while(!copy.eof()) {
            getline(copy, str);
            i = str.find(fname);
            if(i == string::npos) {
                newFile += (str + '\n');
            }
        }
        copy.close();

        ofstream copyWithoutLinks;
        copyWithoutLinks.open((path + "sfiles/types.txt").c_str());
        copyWithoutLinks << newFile;
        copyWithoutLinks.close();
        cout << "Deleted file successfully" << endl;
        return 0;
    }

    //Help Function
    if(argc == 2 && argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'h') {
        cout << "Usage: " << argv[0] << " [FILENAME]" << endl;
        cout << "Simple text editor for simple files" << endl << endl;
        cout << "Commands and interpretation:" << endl;
        cout << "  -s    Stores a syntax file specified by the user" << endl;   
        cout << "  -l    Lists the syntax files being used by the text editor" << endl;
        cout << "  -r    Removes syntax file from the text editor's file system" << endl << endl;

        cout << "When adding syntax files, specify the path to the syntax file, " << endl;
        cout << "and specify the extensions that the syntax file will be used for." << endl; 
        cout << "If adding multiple files, use double quotes." << endl;
        cout << "Example: " << argv[0] << " -s c++.txt \".h .cpp\"" << endl;
    return 0;
    }

    //If we did not recognize an output, we tell the user the default use, and refer them to the help function
    cerr << "Usage: " << argv[0] << " [FILENAME]" << endl;
    cerr << "Try '" << argv[0] << " --help' for more information" << endl;
    return 1;
}

