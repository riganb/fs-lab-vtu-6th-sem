#include <bits/stdc++.h>

using namespace std;

struct Student {
    string usn;
    string name;
    string age;
    string sem;
    string branch;
};

// Function to add a student record
void add(vector<Student>& students) {
    Student newStudent;
    cout << "Enter USN: ";
    cin >> newStudent.usn;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter Age: ";
    cin >> newStudent.age;
    cout << "Enter Semester: ";
    cin >> newStudent.sem;
    cout << "Enter Branch: ";
    cin.ignore();
    getline(cin, newStudent.branch);

    students.push_back(newStudent);
    cout << "Student record added successfully!" << endl;
}

// Function to search for a student record by name
void search(const vector<Student>& students) {
    string searchName;
    cout << "Enter the name to search: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    for (const auto& student : students) {
        if (student.name == searchName) {
            cout << "Student details:" << endl;
            cout << "USN: " << student.usn << endl;
            cout << "Name: " << student.name << endl;
            cout << "Age: " << student.age << endl;
            cout << "Semester: " << student.sem << endl;
            cout << "Branch: " << student.branch << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No student with the given name found!" << endl;
    }
}

// Function to delete a student record by name
void deleteStudent(vector<Student>& students) {
    string deleteName;
    cout << "Enter the name to delete: ";
    cin.ignore();
    getline(cin, deleteName);

    bool deleted = false;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->name == deleteName) {
            students.erase(it);
            deleted = true;
            break;
        }
    }

    if (deleted) {
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "No student with the given name found!" << endl;
    }
}

// Function to display all student records
void display(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records available!" << endl;
        return;
    }

    cout << "Student records:" << endl;
    for (const auto& student : students) {
        cout << "USN: " << student.usn << endl;
        cout << "Name: " << student.name << endl;
        cout << "Age: " << student.age << endl;
        cout << "Semester: " << student.sem << endl;
        cout << "Branch: " << student.branch << endl;
        cout << "------------------------" << endl;
    }
}

// Function to save student records to a file in the order of insertion
void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (const auto& student : students) {
        file << student.usn << "|" << student.name << "|" << student.age << "|"
             << student.sem << "|" << student.branch << endl;
    }

    file.close();
    cout << "Student records saved to " << filename << " successfully!" << endl;
}

// Function to save student records to a file based on the order of USN
void saveToFileByUSN(vector<Student>& students, const string& filename) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.usn < b.usn;
    });

    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (const auto& student : students) {
        file << student.usn << "|" << student.name << "|" << student.age << "|"
             << student.sem << "|" << student.branch << endl;
    }

    file.close();
    cout << "Student records saved to " << filename << " successfully!" << endl;
}

int main() {
    vector<Student> students;
    string insertFile = "insertion_order.txt";
    string usnFile = "usn_order.txt";

    int choice;
    while (true) {
        cout << "\n--- Student Database ---" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Save Records by Insertion Order" << endl;
        cout << "6. Save Records by USN Order" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                add(students);
                break;
            case 2:
                search(students);
                break;
            case 3:
                deleteStudent(students);
                break;
            case 4:
                display(students);
                break;
            case 5:
                saveToFile(students, insertFile);
                break;
            case 6:
                saveToFileByUSN(students, usnFile);
                break;
            case 7:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
