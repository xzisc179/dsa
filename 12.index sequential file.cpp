ASSIGNMENT NO : 12
TITLE: IMPLEMENTATION OF INDEX SEQUENTIAL FILE
PROBLEM STATEMENT:
Company maintains employee information as employee ID, name, designation and salary. Allow user to
add, delete information of employee. Display information of particular employee. If employee does not
exist an appropriate message is displayed. If it is, then the system displays the employee details. Use
index sequential file to maintain the data




#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Employee {
    string emp_id, name, designation, salary;
};

void add_employee() {
    ofstream file("employees.txt", ios::app);
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    Employee e;
    cout << "Enter Employee ID: "; cin >> e.emp_id;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, e.name);
    cout << "Enter Designation: "; getline(cin, e.designation);
    cout << "Enter Salary: "; getline(cin, e.salary);

    file << e.emp_id << "," << e.name << "," << e.designation << "," << e.salary << "\n";
    file.close();
    cout << "Employee record added successfully!\n";
}

void delete_employee() {
    string emp_id, line;
    cout << "Enter Employee ID to delete: "; cin >> emp_id;

    ifstream file("employees.txt");
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    ofstream temp("temp.txt");
    bool found = false;

    while (getline(file, line)) {
        if (line.substr(0, line.find(",")) != emp_id)
            temp << line << "\n";
        else
            found = true;
    }

    file.close();
    temp.close();

    if (found) {
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
        cout << "Employee record deleted successfully!\n";
    } else {
        remove("temp.txt");
        cout << "Employee record not found!\n";
    }
}

void search_employee() {
    string emp_id, line;
    cout << "Enter Employee ID to search: "; cin >> emp_id;

    ifstream file("employees.txt");
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> data;
        string value;

        while (getline(ss, value, ',')) data.push_back(value);

        if (data[0] == emp_id) {
            cout << "Employee Record Found:\n";
            cout << "Employee ID: " << data[0] << "\n";
            cout << "Name: " << data[1] << "\n";
            cout << "Designation: " << data[2] << "\n";
            cout << "Salary: " << data[3] << "\n";
            found = true;
            break;
        }
    }

    file.close();
    if (!found) cout << "Employee record not found!\n";
}

void display_employees() {
    ifstream file("employees.txt");
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    string line;
    cout << "Employee Records:\n";

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> data;
        string value;

        while (getline(ss, value, ',')) data.push_back(value);

        if (data.size() == 4) {
            cout << "Employee ID: " << data[0]
                 << " | Name: " << data[1]
                 << " | Designation: " << data[2]
                 << " | Salary: " << data[3] << "\n";
        }
    }

    file.close();
    cout << endl;
}

int main() {
    while (true) {
        cout << "\n1. Add Employee\n2. Delete Employee\n3. Search Employee\n4. Display All Employees\n5. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: add_employee(); break;
            case 2: delete_employee(); break;
            case 3: search_employee(); break;
            case 4: display_employees(); break;
            case 5: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Please enter a valid option.\n";
        }
    }
}
