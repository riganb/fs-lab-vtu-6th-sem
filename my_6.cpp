/*
Author: Rigan Burnwal
Email: therealriganb@gmail.com
Date: 18-06-2023
*/

#include <iostream>
#include <fstream>

using namespace std;

string students[100][6];
string headings[5] = {"USN", "Name", "Age", "Sem", "Branch"};
int count_ = 0;

void swap_records(int a, int b) {
    for(int i = 0; i < 6; i++) {
        string temp = students[a][i];
        students[a][i] = students[b][i];
        students[b][i] = temp;
    }
}

void createEmptyFiles() {
    ofstream record("record-6.txt"), usn("usn-6.txt"), name("name-6.txt");
    record.close();
    usn.close();
    name.close();
}

void read() {
    ifstream record("record-6.txt");
    string temp;

    //reading records
    for(int i = 0; i < count_; i++) {
        getline(record, students[i][5], '|');
        for(int j = 0; j < 4; j++) {
            getline(record, students[i][j], '|');
        }
        getline(record, students[i][4], '\n');
    }

    record.close();
}

void save() {
    ofstream record("record-6.txt"), usn("usn-6.txt"), name("name-6.txt");

    // storing records
    for(int k = 0; k < count_; k++) {
        record << k;
        for(int i = 0; i < 5; i++)
            record << "|" << students[k][i];
        record << "\n";
    }
    record.close();

    //sorting records according to usn
    for(int i = 0; i < count_; i++) {
        for(int j = i + 1; j < count_; j++) {
            if(students[i][0] > students[j][0]) {
                swap_records(i, j);
            }
        }
    }

    // storing records according to usn
    for(int k = 0; k < count_; k++)
        usn << students[k][0] << "|" << ((int) students[k][5].c_str()[0]) << "\n";
    usn.close();

    //sorting records according to name
    for(int i = 0; i < count_; i++) {
        for(int j = i + 1; j < count_; j++) {
            if(students[i][1] > students[j][1]) {
                swap_records(i, j);
            }
        }
    }

    // storing records according to name
    for(int k = 0; k < count_; k++)
        name << students[k][1] << "|" << students[k][0] << "|" << ((int) students[k][5].c_str()[0]) << "\n";
    name.close();
}

void add_() {
    read();
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < 5; i++) {
            cout << "Enter Student " << k << "'s " << headings[i] << ": ";
            cin >> students[count_][i];
        }
        count_++;
        cout << "\n";
    }
    save();
}

void display_() {
    read();
    for(int i = 0; i < 5; i++)
        cout << headings[i] << "\t";
    cout << "\n";
    for(int k = 0; k < count_; k++) {
        for(int i = 0; i < 5; i++) {
            cout << students[k][i] << "\t";
        }
        cout << "\n";
    }
}

void search_() {
    read();
    string term;
    cout << "Enter name to search for: ";
    cin >> term;
    int found = 0;
    for(int k = 0; k < count_; k++) {
        if(term == students[k][1]) {
            if(found == 0) {
                cout << "Found record(s) are:\n";
                cout << "Name\tUSN\n";
            }
            found = 1;
            cout << term << "\t" << students[k][0] << endl;
        }
    }
    if(!found) {
        cout << "Name not found!\n";
    } else {
        string usn;
        cout << "Enter usn to search record: ";
        cin >> usn;
        for(int k = 0; k < count_; k++) {
            if(term == students[k][1] && usn == students[k][0]) {
                cout << "Record found at index " << k << "!\n";
                for(int i = 0; i < 5; i++)
                    cout << headings[i] << ": " << students[k][i] << endl;
                return;
            }
        }
        cout << "Wrong USN, not found!\n";
    }
}

void delete_() {
    read();
    string term;
    cout << "Enter name to delete for: ";
    cin >> term;
    int found = 0;
    for(int k = 0; k < count_; k++) {
        if(term == students[k][1]) {
            if(found == 0) {
                cout << "Found record(s) are:\n";
                cout << "Name\tUSN\n";
            }
            found = 1;
            cout << term << "\t" << students[k][0] << endl;
        }
    }
    if(!found) {
        cout << "Name not found!\n";
    } else {
        string usn;
        cout << "Enter usn to delete record: ";
        cin >> usn;
        for(int k = 0; k < count_; k++) {
            if(term == students[k][1] && usn == students[k][0]) {
                for(int x = k + 1; x < count_; x++)
                    for(int i = 0; i < 5; i++)
                        students[x - 1][i] = students[x][i];
                cout << "Record deleted from index " << k << "!\n";
                count_--;
                save();
                return;
            }
        }
        cout << "Wrong USN, not found!\n";
        save();
    }
}

int main() {
    createEmptyFiles();
    int choice;
    for(int i = 0; i < 100; i++)
        students[i][5] = i;
    while(true) {
        cout << "1. Add" << endl;
        cout << "2. Display" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice == 1)
            add_();
        else if(choice == 2)
            display_();
        else if(choice == 3)
            search_();
        else if(choice == 4)
            delete_();
        else if(choice == 5) {
            save();
            return 0;
        }
        cout << "\n";
    }
    return 0;
}