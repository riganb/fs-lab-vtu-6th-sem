/*
Author: Rigan Burnwal
Email: therealriganb@gmail.com
Date: 14-07-2023
*/

#include <iostream>
#include <fstream>

using namespace std;

string students[100][5];
string headings[5] = {"USN", "Name", "Age", "Sem", "Branch"};
int count = 0, fixedLength = 100;

void saveRecords() {
    ofstream record("record-2.txt");
}

void readRecords() {
    ifstream record("record-2.txt");
    string temp;

    //reading records
    for(int i = 0; i < count; i++) {
        for(int j = 0; j < 5; j++) {
            getline(record, students[i][j], '|');
        }
        getline(record, temp, '\n');
    }
}

void writeRecord() {
    readRecords();
    saveRecords();
}

void displayRecords() {
    readRecords();
    cout << "USN\t" << "Name\t" << "Age\t" << "Sem\t" << "Branch\n";
    for(int i = 0; i < count; i++) {
        for(int j = 0; j < 5; j++) {
            cout << students[i][j] << "\t";
        }
        cout << "\n";
    }
}

void modifyRecord() {
    readRecords();
    saveRecords();
}

void searchRecord() {
    readRecords();
}

int main() {
    saveRecords();
    int choice;
    while(true) {
        // you can use "\n" in the place of endl
        cout << endl;
        cout << "1. Write" << endl;
        cout << "2. Display" << endl;
        cout << "3. Modify" << endl;
        cout << "4. Search" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice == 1)
            writeRecord();
        else if(choice == 2)
            displayRecords();
        else if(choice == 3)
            modifyRecord();
        else if(choice == 4)
            searchRecord();
        else if(choice == 5) {
            return 0;
        }
        cout << "\n";
    }
    return 0;
}
