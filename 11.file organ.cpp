ASSIGNMENT NO : 11
TITLE: FILE ORGANIZATION USING C++
PROBLEM STATEMENT:
Department maintains a student information. The file contains roll number, name, division and address.
Allow user to add, delete information of student. Display information of particular employee. If record of
student does not exist an appropriate message is displayed. If it is, then the system displays the student
details. Use sequential file to main the data. 





#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Student {
    string roll_no, name, division, address;
};

void add_student() {
    ofstream file("students.txt", ios::app);
    Student s;
    cout << "Enter Roll Number: "; cin >> s.roll_no;
    cout << "Enter Name: "; cin.ignore(); getline(cin, s.name);
    cout << "Enter Division: "; getline(cin, s.division);
    cout << "Enter Address: "; getline(cin, s.address);
    file << s.roll_no << "," << s.name << "," << s.division << "," << s.address << "\n";
    file.close();
    cout << "Student record added successfully!\n";
}

void delete_student() {
    string roll_no, line;
    cout << "Enter Roll Number to delete: "; cin >> roll_no;
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    bool found = false;

    while (getline(file, line)) {
        if (line.substr(0, line.find(",")) != roll_no)
            temp << line << "\n";
        else
            found = true;
    }

    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    cout << (found ? "Student record deleted successfully!\n" : "Student record not found!\n");
}

void search_student() {
    string roll_no, line;
    cout << "Enter Roll Number to search: "; cin >> roll_no;
    ifstream file("students.txt");
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> data;
        string value;

        while (getline(ss, value, ',')) data.push_back(value);

        if (data[0] == roll_no) {
            cout << "Student Record Found:\n";
            cout << "Roll Number: " << data[0] << "\n";
            cout << "Name: " << data[1] << "\n";
            cout << "Division: " << data[2] << "\n";
            cout << "Address: " << data[3] << "\n";
            found = true;
            break;
        }
    }

    file.close();
    if (!found) cout << "Student record not found!\n";
}

void display_students() {
    ifstream file("students.txt");
    string line;
    cout << "Student Records:\n";

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> data;
        string value;
        while (getline(ss, value, ',')) data.push_back(value);

        if (data.size() == 4) {
            cout << "Roll Number: " << data[0]
                 << " | Name: " << data[1]
                 << " | Division: " << data[2]
                 << " | Address: " << data[3] << "\n";
        }
    }

    file.close();
    cout << endl;
}

int main() {
    while (true) {
        cout << "\n1. Add Student\n2. Delete Student\n3. Search Student\n4. Display All Students\n5. Exit\nEnter your choice: ";
        int choice; cin >> choice;
        switch (choice) {
            case 1: add_student(); break;
            case 2: delete_student(); break;
            case 3: search_student(); break;
            case 4: display_students(); break;
            case 5: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Please enter a valid option.\n";
        }
    }
}
