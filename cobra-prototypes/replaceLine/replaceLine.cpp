/*
    * Code/prototype from https://stackoverflow.com/questions/9505085/replace-a-line-in-text-file.

    ! Does not work.
    ? Will be saved for later.
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string strReplace = "editor.theme: Cobra - Light Theme";
    string strNew = "editor.theme: Cobra - Dark Theme";
    ifstream filein("filein.txt"); //File to read from
    ofstream fileout("fileout.txt"); //Temporary file
    if(!filein || !fileout)
    {
        cout << "Error opening files!" << endl;
        return 1;
    }

    string strTemp;
    bool found = false;
    while(filein >> strTemp)
    {
        if(strTemp == strReplace){
            strTemp = strNew;
            found = true;
        }
        fileout << strTemp << '\n';
        if(found) break;
    }
    return 0;
}
