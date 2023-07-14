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
// you can change fixed record length to your choice
int count = 0, fixedLength = 69;

void saveRecords() {
    ofstream record("record-2.txt");
    for(int i = 0; i < count; i++) {
        string temp = "";
        for(int j = 0; j < 5; j++) {
            temp += students[i][j] + "|";
        }
        while(temp.length() < fixedLength)
            temp += "|";
        record << temp << "\n";
    }
    record.close();
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

    record.close();
}

void writeRecord() {
    readRecords();
    for(int i = 0; i < 5; i++) {
        cout << "Enter " << headings[i] << ": ";
        cin >> students[count][i];
    }
    count++;
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
    string usn;
    cout << "Enter the USN to modify details for: ";
    cin >> usn;
    for(int i = 0; i < count; i++) {
        if(students[i][0] == usn) {
            cout << "Student found, enter new data:\n";
            for(int j = 0; j < 5; j++) {
                cout << headings[j] << ": ";
                cin >> students[i][j];
            }
            saveRecords();
            return;
        }
    }
    cout << "Student not found!\n";
}

void searchRecord() {
    readRecords();
    string usn;
    cout << "Enter the USN to search for: ";
    cin >> usn;
    for(int i = 0; i < count; i++) {
        if(students[i][0] == usn) {
            cout << "Student found!\n";
            for(int j = 0; j < 5; j++) {
                cout << headings[j] << ": " << students[i][j] << endl;
            }
            return;
        }
    }
    cout << "Student not found!\n";
}

int main() {
    saveRecords();
    int choice;
    while(true) {
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
