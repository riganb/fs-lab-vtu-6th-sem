#include <iostream>
#include <fstream>

using namespace std;

string headings[] = {"name", "usn", "age", "sem", "branch"};
string records[100][5];
int count = 0;

bool saveRecords(int n) {
	ofstream file("my4.txt");
	for(int k = 0; k < n + 1; k++) {
		string line;
		for(int i = 0; i < 5; i++)
			line += records[k][i] + (i == 4? '!': '|');
		file << line + '\n';
	}
	file.close();
	return true;
}

void readRecords() {
	fstream file("my4.txt", ios::in);
	int temp = 0;
	char tempRecord[5][25];
	while(!file.eof()) {
		for(int i = 0; i < 5; i++) {
			file.getline(tempRecord[i], 25, (i == 4? '!': '|'));
			records[temp][i] = tempRecord[i];
		}
		temp++;
	}
}

void addRecord() {
    readRecords();
	for(int i = 0; i < 5; i++) {
		cout << "Enter student's " << headings[i] << ": ";
		cin >> records[count][i];
	}
	count += saveRecords(count)? 1: 0;
}

void displayRecords() {
	readRecords();
	cout << "RRN" << '\t';
	for(int i = 0; i < 5; i++)
		cout << headings[i] << '\t';
	cout << endl;
	for(int i = 0; i < count; i++) {
		cout << i << '\t';
		for(int j = 0; j < 5; j++)
			cout << records[i][j] << '\t';
		cout << endl;
	}
}

void search() {
	readRecords();
	int rrn;
	cout << "Enter RRN: ";
	cin >> rrn;
	cout << "RRN: " << rrn << endl;
	if(rrn < count)
		for(int i = 0; i < 5; i++)
			cout << headings[i] << ": " << records[rrn][i] << endl;
	else
		cout << "Record doesn't exist for given RRN!\n";
}

int main() {
	saveRecords(-1);
	int ch = 1;
	while(ch) {
		cout << endl << "\n0. Exit\n";
		cout << "1. Write to file\n";
		cout << "2. Display the file\n";
		cout << "3. Search a record\n\n";
		cout << "Enter a choice: ";
		cin >> ch;
		if(ch == 1)
			addRecord();
		else if(ch == 2)
			displayRecords();
		else if(ch == 3)
			search();
	}
	return 0;
}