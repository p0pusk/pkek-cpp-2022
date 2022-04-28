#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <cmath>

using namespace std;


void make_indent(ofstream& fout, int n) {
    for (int i = 0; i < n; i++) {
        fout << " ";
    }
}

void write_line(ofstream& fout, vector<string> words, int indent) {
    make_indent(fout, indent);
    for (auto& f: words) {
        fout << f;
        if (f != words.back() || indent > 1) {
            fout << " ";
        }
    }
    make_indent(fout, indent-1);
    fout << endl;
}


int main(int argc, char* argv[]) {
    fstream file;
    ofstream fout("../output.txt");
    int len;
    if (argc > 2) {
        file.open(argv[1]);
        string kek;
        len = atoi(argv[2]);
    }
    else {
        cout << "Not enough arguments\n";
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        istream_iterator<string> line_it(iss);
        istream_iterator<string> eos;
        vector<string> words;
        while (line_it != eos) {
            words.push_back(*line_it);
            line_it++;
        }

        int left = len;
        vector<string> fit;
        int indent;
        for (int i = 0; i < words.size(); i++) {
            if (words[i].size() <= left) {
                fit.push_back(words[i]);
                left -= words[i].size();
                left -= left > 0 ? 1 : 0;
            }
            else {
                if (fit.empty()) {
                    fout << words[i].substr(0, len) << endl;
                    words[i].erase(0, len);
                    i--;
                    left = len;
                }
                else {
                    indent = ceil(left / 2);
                    write_line(fout, fit, indent);
                    fit.clear();
                    left = len;
                    i--;
                }
            }
        }
        left += 1;
        indent = left / 2;
        write_line(fout, fit, indent);
        fit.clear();
    }

    return 0;
}
