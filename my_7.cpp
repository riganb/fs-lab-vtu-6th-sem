/*
Author: Rigan Burnwal
Email: therealriganb@gmail.com
Date: 21-06-2023
*/

#include <fstream>
#include <iostream>

using namespace std;

void write_names() {
    string name;
    ofstream a("a.txt"), b("b.txt");
    int nA, nB;
    cout << "Enter number of names for file 1: ";
    cin >> nA;
    cout << "Enter the names (in ascending order): " << endl;
    for(int i = 0; i < nA; i++) {
        cin >> name;
        a << name << endl;
    }
    a.close();
    cout << "Enter number of names for file 2: ";
    cin >> nB;
    cout << "Enter the names (in ascending order): " << endl;
    for(int i = 0; i < nB; i++) {
        cin >> name;
        b << name << endl;
    }
    b.close();
}

int main() {
    write_names();
    string aName, bName;
    ifstream a("a.txt"), b("b.txt");
    ofstream c("c.txt");
    getline(a, aName);
    getline(b, bName);
    while(!a.eof() && !b.eof()) {
        if(aName == bName) {
            c << aName << endl;
            cout << "Common Name: " << aName << endl;
            getline(a, aName);
            getline(b, bName);
            continue;
        } else if(aName < bName)
            getline(a, aName);
        else
            getline(b, bName);
        cout << "Not common!" << endl;
    }
    cin.ignore();
    cin >> aName;
    return 0;
}
