#include <iostream>
#include <fstream>

using namespace std;

string inputSuffix = "-file.txt", outputSuffix = "-inter.txt";
string tempContent;

void merge(int in1, int in2, int out) {
    ifstream inputFile1(to_string(in1) + inputSuffix);
    ifstream inputFile2(to_string(in2) + inputSuffix);
    ofstream outputFile(to_string(out) + outputSuffix);
    string content1, content2;
    bool read1 = true, read2 = true;
    while(!inputFile1.eof() && !inputFile2.eof()) {
        if(read1) getline(inputFile1, content1, '|');
        if(read2) getline(inputFile2, content2, '|');
        if(content1 == content2) {
            outputFile << content1 << '|';
        } else if(content1 < content2) {
            outputFile << content1 << '|';
            read1 = true;
            read2 = false;
        } else {
            outputFile << content2 << '|';
            read1 = false;
            read2 = true;
        }
    }
    if(inputFile1.eof())
        while(!inputFile2.eof()) {
            getline(inputFile2, content2, '|');
            outputFile << content2 << '|';
        }
    else if(inputFile2.eof())
        while(!inputFile1.eof()) {
            getline(inputFile1, content1, '|');
            outputFile << content1 << '|';
        }
}

int main() {
    int k = 8, n;
    for(int i = 0; i < k; i++) {
        ofstream file(to_string(i) + inputSuffix);
        cout << "Number of records for file " << (i + 1) << ": ";
        cin >> n;
        if(n) cout << "Enter contents in ascending order:\n";
        for(int j = 0; j < n; j++) {
            cin >> tempContent;
            file << tempContent << "|";
        }
        file.close();
    }
    while(k != 1) {
        for(int i = 0; i < k / 2; i++)
            merge(i * 2, i * 2 + 1, i);
        k = k / 2;
        inputSuffix = outputSuffix;
        outputSuffix = to_string(k) + inputSuffix;
    }
    return 0;
}