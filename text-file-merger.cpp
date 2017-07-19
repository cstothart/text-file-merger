#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

// This is the merged file.
ofstream g_new_file;

void PrintFile(string file_location) {
    string line;
    ifstream file;
    file.open(file_location);
    getline(file, line);
    while (!file.eof()) {
        getline(file, line);
        g_new_file << line << "\n";
    }
    file.close();
}

vector<string> CreateFileList(string dir) {
    vector<string> fnames;
    path p(dir);
    directory_iterator di(p);
    directory_iterator di_end;
    while(di != di_end) {
        fnames.push_back(di->path().string());
        ++di;
    }
    return fnames;
}

int main() {
    ifstream first_file;
    string header;
    string dir;
    cout << "Please enter the path of the folder that contains all of the text files\n"
            "that you would like to merge.\n\n"
            "Example: c:/users/cary/desktop/text_files\n\nPath: ";
    cin >> dir;
    cout << "\nThe files are being merged.  Please wait...";
    vector<string> file_list = CreateFileList(dir);
    g_new_file.open("merged_file.txt");
    first_file.open(file_list[0]);
    getline(first_file, header);
    g_new_file << header << "\n";
    for (string i : file_list) {
        PrintFile(i);
    }
    g_new_file.close();
    cout << "\n\n" << file_list.size() << " files were merged.\n\n";
    system("pause");
    return 0;
}