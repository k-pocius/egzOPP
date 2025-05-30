#include "lib.h"

int main() {

    map<string, int> wordCount;
    map<string, set<int>> wordLine;
    vector <string> URL;

    ifstream fd("duom.txt");
    string line;

    int lineNumber = 0;

    while(getline(fd, line)) {
        lineNumber++;
        istringstream iss(line);
        string a;        
        while(iss >> a){

            // ar yra nuoroda
            bool isURL = false;
            if(a.find("http://") == 0 || a.find("https://") == 0 || a.find("www.") == 0) {
                isURL = true;
                URL.push_back(a);
            }

            //remove punctuation
            if(!isURL){
                for(int i = 0, len = a.size(); i < len; i++) {
                    if(ispunct(a[i])){
                        a.erase(i--, 1);
                        len = a.size();
                    }
                }
            }

            //to lower case
            for(char &c : a) {
                c = tolower(c);
            }

            //irasom zodzius
            //randam eilutes nr
            if(!a.empty()){
                wordCount[a]++;
                wordLine[a].insert(lineNumber);
            }
        }

    }

    ofstream fr("wordCount.txt");
    for(auto &a : wordCount){
        if(a.second > 1){
            fr << a.first << ": " << a.second << endl;
        }
    }
    fr.close();

    ofstream fe("wordLine.txt");
    for(auto &a : wordLine){
        if(wordCount[a.first] > 1){
            fe << a.first << ": ";
            for(auto &lineNum : a.second){
                fe << lineNum << " ";
            }
            fe << endl;
        }
    }
    fe.close();

    ofstream ff("URL.txt");
    for(auto &url : URL){
        ff << url << endl;
    }
    ff.close();


    return 0;
}
