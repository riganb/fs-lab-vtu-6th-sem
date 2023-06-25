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

void save() {
    ofstream record("record-5.txt"), usn("usn-5.txt");

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
}

void add_() {
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

int find_index(string usn) {
    for(int k = 0; k < count_; k++)
        if(usn == students[k][0])
            return k;
    return -1;
}

void search_() {
    string term;
    cout << "Enter USN to search for: ";
    cin >> term;
    int idx = find_index(term);
    if(idx == -1)
        cout << "USN not found!\n";
    else {
        cout << "Student found at index " << idx << "!\n\n";
            for(int i = 0; i < 5; i++)
                cout << headings[i] << ": " << students[idx][i] << "\n";
    }
}

void swap_records(int a, int b) {
    for(int i = 0; i < 6; i++) {
        string temp = students[a][i];
        students[a][i] = students[b][i];
        students[b][i] = temp;
    }
}

void delete_() {
    string term;
    cout << "Enter USN to delete: ";
    cin >> term;
    int idx = find_index(term);
    if(idx == -1)
        cout << "USN not found!\n";
    else {
        for(int k = idx + 1; k < count_; k++)
            for(int i = 0; i < 5; i++)
                students[k - 1][i] = students[k][i];
        count_--;
        cout << "Record deleted.\n";
        save();
    }
}

int main() {
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