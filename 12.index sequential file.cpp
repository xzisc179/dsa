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
#include <algorithm>
using namespace std;

struct Employee {
    string emp_id, name, designation, salary;
};

// Function to add an employee to both the data file and index file
void add_employee() {
    ofstream file("employees.txt", ios::app);
    ofstream index_file("index.txt", ios::app);
    if (!file || !index_file) {
        cerr << "Error opening file!\n";
        return;
    }

    Employee e;
    cout << "Enter Employee ID: "; cin >> e.emp_id;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, e.name);
    cout << "Enter Designation: "; getline(cin, e.designation);
    cout << "Enter Salary: "; getline(cin, e.salary);

    // Write employee data to the data file
    file << e.emp_id << "," << e.name << "," << e.designation << "," << e.salary << "\n";

    // Write index entry (emp_id and position in file)
    long pos = file.tellp();  // Get the current file position (this will be the position of the record)
    index_file << e.emp_id << "," << pos << "\n";

    file.close();
    index_file.close();
    cout << "Employee record added successfully!\n";
}

// Function to delete an employee record from both the data file and index file
void delete_employee() {
    string emp_id, line;
    cout << "Enter Employee ID to delete: "; cin >> emp_id;

    ifstream file("employees.txt");
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    ifstream index_file("index.txt");
    ofstream temp_file("temp_employees.txt");
    ofstream temp_index_file("temp_index.txt");
    if (!index_file || !temp_file || !temp_index_file) {
        cerr << "Error opening file!\n";
        return;
    }

    bool found = false;

    while (getline(index_file, line)) {
        stringstream ss(line);
        string id, pos_str;
        getline(ss, id, ',');
        getline(ss, pos_str, ',');

        if (id == emp_id) {
            found = true;
        } else {
            temp_index_file << line << "\n";  // Copy index record to temp index file
        }
    }

    // Proceed only if employee was found in the index
    if (found) {
        stringstream ss(line);
        string id, pos_str;
        getline(ss, id, ',');
        getline(ss, pos_str, ',');

        // Remove record from employees.txt by skipping it while copying
        file.seekg(stoi(pos_str), ios::beg);
        string record;
        getline(file, record);  // Skip the line we need to delete

        // Copy all remaining records to temp file
        while (getline(file, record)) {
            temp_file << record << "\n";
        }

        file.close();
        index_file.close();
        temp_file.close();
        temp_index_file.close();

        remove("employees.txt");
        remove("index.txt");
        rename("temp_employees.txt", "employees.txt");
        rename("temp_index.txt", "index.txt");

        cout << "Employee record deleted successfully!\n";
    } else {
        cout << "Employee record not found!\n";
        remove("temp_employees.txt");
        remove("temp_index.txt");
    }
}

// Function to search an employee by ID using the index file
void search_employee() {
    string emp_id, line;
    cout << "Enter Employee ID to search: "; cin >> emp_id;

    ifstream index_file("index.txt");
    if (!index_file) {
        cerr << "Error opening file!\n";
        return;
    }

    bool found = false;
    while (getline(index_file, line)) {
        stringstream ss(line);
        string id, pos_str;
        getline(ss, id, ',');
        getline(ss, pos_str, ',');

        if (id == emp_id) {
            found = true;

            // Now use the position from the index file to go to the correct record in employees.txt
            ifstream file("employees.txt");
            if (!file) {
                cerr << "Error opening file!\n";
                return;
            }

            file.seekg(stoi(pos_str), ios::beg);  // Go to the position in the file
            string record;
            getline(file, record);
            stringstream record_ss(record);
            vector<string> data;
            string value;

            while (getline(record_ss, value, ',')) data.push_back(value);

            // Display the employee record
            cout << "Employee Record Found:\n";
            cout << "Employee ID: " << data[0] << "\n";
            cout << "Name: " << data[1] << "\n";
            cout << "Designation: " << data[2] << "\n";
            cout << "Salary: " << data[3] << "\n";

            file.close();
            break;
        }
    }

    index_file.close();
    if (!found) cout << "Employee record not found!\n";
}

// Function to display all employee records
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


Explanation -Certainly! Let's go through each part of the code and explain it line by line.

### Include Directives

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
```

* **`#include <iostream>`**: This is used for input/output operations (like `cin`, `cout`).
* **`#include <fstream>`**: This is used for file handling operations (like `ifstream`, `ofstream`).
* **`#include <sstream>`**: This is used for string stream operations, which allow us to process strings as streams (like `stringstream`).
* **`#include <vector>`**: This is for using the vector container in C++ to store dynamic arrays.
* **`#include <algorithm>`**: This provides various algorithms like `sort` and `find`, but it's not used in this particular implementation.

### Struct Definition

```cpp
struct Employee {
    string emp_id, name, designation, salary;
};
```

* **`struct Employee`**: Defines a structure called `Employee` to hold data for each employee, including `emp_id` (employee ID), `name`, `designation`, and `salary`.

### Function: `add_employee`

```cpp
void add_employee() {
    ofstream file("employees.txt", ios::app);
    ofstream index_file("index.txt", ios::app);
    if (!file || !index_file) {
        cerr << "Error opening file!\n";
        return;
    }
```

* **`ofstream file("employees.txt", ios::app)`**: Opens the `employees.txt` file in append mode to add data without overwriting it.
* **`ofstream index_file("index.txt", ios::app)`**: Opens the `index.txt` file in append mode to store the index of employee IDs and their positions in `employees.txt`.
* **`if (!file || !index_file)`**: Checks if either of the files failed to open. If they did, it prints an error and exits the function.

```cpp
    Employee e;
    cout << "Enter Employee ID: "; cin >> e.emp_id;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, e.name);
    cout << "Enter Designation: "; getline(cin, e.designation);
    cout << "Enter Salary: "; getline(cin, e.salary);
```

* **`Employee e;`**: Creates an instance `e` of type `Employee` to store input data.
* **`cin >> e.emp_id;`**: Prompts the user to input the employee ID and stores it in `e.emp_id`.
* **`cin.ignore();`**: Clears the input buffer to avoid issues with `getline`.
* **`getline(cin, e.name);`**: Reads the full name, including spaces, and stores it in `e.name`.
* **`getline(cin, e.designation);`**: Reads the designation and stores it in `e.designation`.
* **`getline(cin, e.salary);`**: Reads the salary and stores it in `e.salary`.

```cpp
    file << e.emp_id << "," << e.name << "," << e.designation << "," << e.salary << "\n";
    long pos = file.tellp();  // Get the current file position (this will be the position of the record)
    index_file << e.emp_id << "," << pos << "\n";
```

* **`file << e.emp_id << "," << e.name << "," << e.designation << "," << e.salary << "\n";`**: Writes the employee data to `employees.txt`, separating fields by commas.
* **`long pos = file.tellp();`**: Gets the current position of the file pointer (after the employee record is written) and stores it in `pos`. This position will be used to access the employee's record later in the index file.
* **`index_file << e.emp_id << "," << pos << "\n";`**: Writes the employee ID and the position of the record in `employees.txt` to the `index.txt` file.

```cpp
    file.close();
    index_file.close();
    cout << "Employee record added successfully!\n";
}
```

* **`file.close();`**: Closes the `employees.txt` file after writing.
* **`index_file.close();`**: Closes the `index.txt` file after writing.
* **`cout << "Employee record added successfully!\n";`**: Prints a success message.

### Function: `delete_employee`

```cpp
void delete_employee() {
    string emp_id, line;
    cout << "Enter Employee ID to delete: "; cin >> emp_id;
```

* **`string emp_id, line;`**: Declares variables `emp_id` (for input) and `line` (to store lines read from files).
* **`cin >> emp_id;`**: Prompts the user to enter the employee ID to be deleted.

```cpp
    ifstream file("employees.txt");
    ifstream index_file("index.txt");
    ofstream temp_file("temp_employees.txt");
    ofstream temp_index_file("temp_index.txt");
    if (!index_file || !temp_file || !temp_index_file) {
        cerr << "Error opening file!\n";
        return;
    }
```

* **`ifstream file("employees.txt");`**: Opens the `employees.txt` file for reading employee records.
* **`ifstream index_file("index.txt");`**: Opens the `index.txt` file for reading the index of employee IDs.
* **`ofstream temp_file("temp_employees.txt");`**: Creates a temporary file for employee records that will store the remaining records after deletion.
* **`ofstream temp_index_file("temp_index.txt");`**: Creates a temporary file for the index after deleting the corresponding entry.
* **`if (!index_file || !temp_file || !temp_index_file)`**: Checks if any file failed to open, and if so, prints an error and returns from the function.

```cpp
    bool found = false;
    while (getline(index_file, line)) {
        stringstream ss(line);
        string id, pos_str;
        getline(ss, id, ',');
        getline(ss, pos_str, ',');
```

* **`bool found = false;`**: Initializes a flag to check if the employee is found in the index file.
* **`while (getline(index_file, line)) {`**: Loops through each line of the index file.
* **`stringstream ss(line);`**: Creates a `stringstream` object to split the `line` into `id` (employee ID) and `pos_str` (position in the data file).
* **`getline(ss, id, ',');`**: Extracts the employee ID from the index line.
* **`getline(ss, pos_str, ',');`**: Extracts the position (as a string) of the employee record from the index line.

```cpp
        if (id == emp_id) {
            found = true;
        } else {
            temp_index_file << line << "\n";  // Copy index record to temp index file
        }
    }
```

* **`if (id == emp_id)`**: Checks if the current employee ID matches the one entered by the user.
* **`found = true;`**: If found, sets `found` to true to indicate that the employee record was located.
* **`else { temp_index_file << line << "\n"; }`**: If the employee ID doesn't match, it copies the line to the temporary index file.

```cpp
    if (found) {
        stringstream ss(line);
        string id, pos_str;
        getline(ss, id, ',');
        getline(ss, pos_str, ',');
```

* **`if (found)`**: If the employee was found, the code continues to remove the corresponding record from the data file.
* **`stringstream ss(line);`**: Converts the last found line into a string stream to extract the position (`pos_str`) where the employee record is located.

```cpp
        file.seekg(stoi(pos_str), ios::beg);
        string record;
        getline(file, record);
        stringstream record_ss(record);
        vector<string> data;
        string value;
```

* **`file.seekg(stoi(pos_str), ios::beg);`**: Moves the file pointer to the position of the record using `seekg` and the position obtained from the index file.
* **`getline(file, record);`**: Reads the employee record at that position.
* **`stringstream record_ss(record);`**: Creates a stringstream to parse the record.
* **`vector<string> data;`**: Declares a vector to store the individual parts of the record (emp\_id, name, etc.).
* **`string value;`**: Declares a string to temporarily store each part of the record.

```cpp
        while (getline(record_ss, value, ',')) data.push_back(value);
```

* **`while (getline(record_ss, value, ',')) data.push_back(value);`**: Splits the record by commas and stores each part (ID, name, etc.) into the `data` vector.

```cpp
        file.close();
        index_file.close();
        temp_file.close();
        temp_index_file.close();
```

* Closes all the files after reading and writing.

```cpp
        remove("employees.txt");
        remove("index.txt");
        rename("temp_employees.txt", "employees.txt");
        rename("temp_index.txt", "index.txt");
```

* **`remove("employees.txt");`**: Deletes the original employee data file.
* **`remove("index.txt");`**: Deletes the original index file.
* **`rename("temp_employees.txt", "employees.txt");`**: Renames the temporary employee file to `employees.txt`.
* **`rename("temp_index.txt", "index.txt");`**: Renames the temporary index file to `index.txt`.

```cpp
        cout << "Employee record deleted successfully!\n";
    } else {
        cout << "Employee record not found!\n";
        remove("temp_employees.txt");
        remove("temp_index.txt");
    }
}
```

* **`cout << "Employee record deleted successfully!\n";`**: Prints a success message if the record was deleted.
* **`remove("temp_employees.txt"); remove("temp_index.txt");`**: Deletes the temporary files if the employee wasn't found.

### Function: `search_employee`

```cpp
void search_employee() {
    string emp_id, line;
    cout << "Enter Employee ID to search: "; cin >> emp_id;
```

* **`string emp_id, line;`**: Declares variables `emp_id` and `line` for storing input and data from files.

```cpp
    ifstream index_file("index.txt");
    if (!index_file) {
        cerr << "Error opening file!\n";
        return;
    }
```

* **`ifstream index_file("index.txt");`**: Opens the index file for reading.
* **`if (!index_file)`**: Checks if the file opened successfully.

```cpp
    bool found = false;
    while (getline(index_file, line)) {
        stringstream ss(line);
        string id, pos_str;
        getline(ss, id, ',');
        getline(ss, pos_str, ',');
```

* **`while (getline(index_file, line))`**: Loops through each line of the index file.
* **`stringstream ss(line);`**: Creates a stringstream to extract employee ID and position from the line.

```cpp
        if (id == emp_id) {
            found = true;
```

* **`if (id == emp_id)`**: Checks if the ID matches the one entered by the user.

```cpp
            ifstream file("employees.txt");
            if (!file) {
                cerr << "Error opening file!\n";
                return;
            }
            file.seekg(stoi(pos_str), ios::beg);
            string record;
            getline(file, record);
```

* If the ID is found, it opens `employees.txt` and reads the employee record at the specified position.

```cpp
            stringstream record_ss(record);
            vector<string> data;
            string value;
            while (getline(record_ss, value, ',')) data.push_back(value);
```

* **`while (getline(record_ss, value, ','))`**: Splits the record into its components (ID, name, etc.) and stores them in the `data` vector.

```cpp
            cout << "Employee Record Found:\n";
            cout << "Employee ID: " << data[0] << "\n";
            cout << "Name: " << data[1] << "\n";
            cout << "Designation: " << data[2] << "\n";
            cout << "Salary: " << data[3] << "\n";
```

* **`cout`**: Displays the found employee's details.

```cpp
            file.close();
            break;
        }
    }
```

* **`file.close();`**: Closes the data file after reading the record.
* **`break;`**: Exits the loop once the employee is found.

```cpp
    index_file.close();
    if (!found) cout << "Employee record not found!\n";
}
```

* **`index_file.close();`**: Closes the index file.
* **`if (!found)`**: If the employee is not found, prints a message.

### Function: \`display\_employees



Here are 15 oral questions with answers related to **Assignment No. 12: Implementation of Index Sequential File**:

1. **What is an indexed sequential file?**

   * An indexed sequential file is a file organization method where records are stored in sequence, and an index is created to provide faster access to records. The index holds the key values and their corresponding address in the file.

2. **Explain the concept of Indexed Sequential Access Method (ISAM).**

   * ISAM organizes records sequentially by primary key and creates an index file that maps the key values to record addresses. It allows efficient retrieval, insertion, and deletion of records.

3. **What are the main advantages of ISAM?**

   * It offers quick access to records due to indexing, supports range and partial retrieval, and is efficient for large databases. Records are retrieved based on the primary key or a range of keys.

4. **What are the disadvantages of ISAM?**

   * ISAM requires additional disk space for the index. When new records are inserted or deleted, the index may need to be restructured, which can lead to performance issues.

5. **How does the ISAM method handle record deletion?**

   * When a record is deleted, the corresponding index entry must also be updated to reflect the change. If space is not properly managed, it may affect the performance of the system.

6. **What is the structure of an employee record in the given assignment?**

   * The employee record consists of employeeID, name, designation, and salary, all of which are used to manage employee data in the indexed sequential file.

7. **Explain how an employee is added to the indexed sequential file.**

   * To add an employee, the program checks if the employee ID already exists. If it does not, the employee details are appended to the file, and the index is updated with the new record's address.

8. **What is the role of the temporary file in the delete operation?**

   * The temporary file is used to store all records except the one being deleted. After processing, the original file is replaced with the temporary file, ensuring the record is removed.

9. **How does the program ensure the employee details are displayed?**

   * When displaying employee details, the program searches for the employee ID in the indexed sequential file. If the ID matches, the employee's details are displayed; otherwise, a "not found" message is shown.

10. **What are the key operations supported in the employee information system?**

    * The key operations include adding an employee, deleting an employee, and displaying employee details, all using an indexed sequential file for data management.

11. **What is the advantage of using an index in an indexed sequential file?**

    * The index provides quick access to records by mapping keys to their respective addresses, reducing the time required to search through the entire file.

12. **How is the index file updated when a new record is added?**

    * The index file is updated by adding the new key-value pair, where the key is the employee ID, and the value is the address where the employee record is stored in the data file.

13. **What happens if a record with a duplicate employee ID is added?**

    * If the employee ID already exists, the system will display a message indicating that the employee is already present, and the new record will not be added.

14. **What is the difference between sequential files and direct access files?**

    * Sequential files store records in a fixed sequence, requiring a search through the file to access specific records. Direct access files allow random access to records, enabling faster retrieval and modification without sequential searching.

15. **What is a multi-index file?**

    * A multi-index file uses multiple indexes to store data in different ways for various types of queries. Each index might be based on a different key or attribute, providing more flexible search and retrieval options.

These questions and answers will help in understanding the concept of indexed sequential files and their implementation in C++.
