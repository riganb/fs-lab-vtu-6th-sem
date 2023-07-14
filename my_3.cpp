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
// no need of fixed length size variable since it is variable length record program
int count = 0;

// this function is being used to save the records
void pack() {
    ofstream record("record-2.txt");
    for(int i = 0; i < count; i++) {
        string temp = "";
        for(int j = 0; j < 5; j++) {
            temp += students[i][j] + "|";
        }
        record << temp << "\n";
    }
    record.close();
}

// this function is being used to read the records
void unpack() {
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

// this function is being used to add a record
void write() {
    unpack();
    for(int i = 0; i < 5; i++) {
        cout << "Enter " << headings[i] << ": ";
        cin >> students[count][i];
    }
    count++;
    pack();
}

// this function is being used to display all the records
void display() {
    unpack();
    cout << "USN\t" << "Name\t" << "Age\t" << "Sem\t" << "Branch\n";
    for(int i = 0; i < count; i++) {
        for(int j = 0; j < 5; j++) {
            cout << students[i][j] << "\t";
        }
        cout << "\n";
    }
}

// this function is being used to modify a record
void modify() {
    unpack();
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
            pack();
            return;
        }
    }
    cout << "Student not found!\n";
}

// this function is being used to search a record
void search() {
    unpack();
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
    pack();
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
            write();
        else if(choice == 2)
            display();
        else if(choice == 3)
            modify();
        else if(choice == 4)
            search();
        else if(choice == 5) {
            return 0;
        }
        cout << "\n";
    }
    return 0;
}
