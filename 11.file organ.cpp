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


Explanation -Sure! Let’s go through the code line by line to understand what each part does.

### **Includes and Setup:**

```cpp
#include <iostream>     // For input/output operations
#include <fstream>      // For file input/output operations
#include <sstream>      // For stringstream, useful to parse strings
#include <vector>       // To use vector containers
using namespace std;    // To avoid the need to use `std::` before standard library functions
```

* These are the necessary header files. `iostream` for input/output, `fstream` for file handling, `sstream` for string parsing, and `vector` for using dynamic arrays.

### **Student Structure:**

```cpp
struct Student {
    string roll_no, name, division, address;
};
```

* This is a structure that holds the student's information: `roll_no`, `name`, `division`, and `address`. These will be used to store individual student records.

### **Add Student Function:**

```cpp
void add_student() {
    ofstream file("students.txt", ios::app);  // Open the file in append mode
    Student s;
    cout << "Enter Roll Number: "; cin >> s.roll_no;  // Input roll number
    cout << "Enter Name: "; cin.ignore(); getline(cin, s.name);  // Input name, ignores extra newline left by previous input
    cout << "Enter Division: "; getline(cin, s.division);  // Input division
    cout << "Enter Address: "; getline(cin, s.address);  // Input address
    file << s.roll_no << "," << s.name << "," << s.division << "," << s.address << "\n";  // Write data to file in CSV format
    file.close();  // Close the file after writing
    cout << "Student record added successfully!\n";
}
```

* **`ofstream file("students.txt", ios::app);`**: Opens the file `students.txt` in append mode to ensure new student records are added to the end of the file without overwriting existing data.
* **`cin >> s.roll_no;`**: Reads the roll number from the user.
* **`cin.ignore(); getline(cin, s.name);`**: `cin.ignore()` clears the input buffer, allowing `getline()` to properly read the student's name (with spaces).
* **`file << ...`**: Writes the student's details into the file in CSV format, followed by a newline character (`\n`).
* **`file.close();`**: Closes the file after writing the data.

### **Delete Student Function:**

```cpp
void delete_student() {
    string roll_no, line;
    cout << "Enter Roll Number to delete: "; cin >> roll_no;  // Get the roll number to delete
    ifstream file("students.txt");  // Open the file for reading
    ofstream temp("temp.txt");      // Open a temporary file to store modified records
    bool found = false;  // Flag to track if student is found

    while (getline(file, line)) {  // Read the file line by line
        if (line.substr(0, line.find(",")) != roll_no)  // If the roll number in the line is not the one to delete
            temp << line << "\n";  // Write the line to the temp file
        else
            found = true;  // Student is found, set the flag
    }

    file.close();  // Close the original file
    temp.close();  // Close the temporary file
    remove("students.txt");  // Delete the original file
    rename("temp.txt", "students.txt");  // Rename the temp file to replace the original file

    cout << (found ? "Student record deleted successfully!\n" : "Student record not found!\n");
}
```

* **`ifstream file("students.txt");`**: Opens the original file `students.txt` for reading.
* **`ofstream temp("temp.txt");`**: Opens a temporary file `temp.txt` for writing the modified data.
* **`getline(file, line)`**: Reads each line of the file one by one.
* **`line.substr(0, line.find(",")) != roll_no`**: Extracts the roll number (part before the first comma) and checks if it matches the one to be deleted. If not, it writes the line to the temporary file.
* **`remove("students.txt"); rename("temp.txt", "students.txt");`**: Deletes the original file and renames the temporary file to `students.txt`, effectively removing the student record.

### **Search Student Function:**

```cpp
void search_student() {
    string roll_no, line;
    cout << "Enter Roll Number to search: "; cin >> roll_no;  // Input roll number to search
    ifstream file("students.txt");  // Open file to read
    bool found = false;  // Flag to track if student is found

    while (getline(file, line)) {  // Loop through each line in the file
        stringstream ss(line);  // Create stringstream object to parse line
        vector<string> data;  // Vector to hold parsed fields (roll_no, name, etc.)
        string value;

        while (getline(ss, value, ',')) data.push_back(value);  // Split by commas and store values in vector

        if (data[0] == roll_no) {  // If the first value (roll number) matches the searched roll number
            cout << "Student Record Found:\n";
            cout << "Roll Number: " << data[0] << "\n";  // Print student details
            cout << "Name: " << data[1] << "\n";
            cout << "Division: " << data[2] << "\n";
            cout << "Address: " << data[3] << "\n";
            found = true;  // Set flag to true if student is found
            break;
        }
    }

    file.close();  // Close the file
    if (!found) cout << "Student record not found!\n";  // If not found, print message
}
```

* **`stringstream ss(line);`**: Creates a stringstream to parse each line of the student record.
* **`getline(ss, value, ',')`**: Reads each value separated by commas from the stringstream and stores it in the `data` vector.
* **`if (data[0] == roll_no)`**: Checks if the first element (roll number) matches the one the user is searching for. If found, prints the student's details.

### **Display Students Function:**

```cpp
void display_students() {
    ifstream file("students.txt");  // Open file for reading
    string line;
    cout << "Student Records:\n";

    while (getline(file, line)) {  // Loop through each line in the file
        stringstream ss(line);  // Create a stringstream object to parse the line
        vector<string> data;  // Vector to hold parsed values
        string value;

        while (getline(ss, value, ',')) data.push_back(value);  // Split the line by commas

        if (data.size() == 4) {  // Ensure that there are exactly 4 values (roll_no, name, division, address)
            cout << "Roll Number: " << data[0]
                 << " | Name: " << data[1]
                 << " | Division: " << data[2]
                 << " | Address: " << data[3] << "\n";  // Print student details
        }
    }

    file.close();  // Close the file
    cout << endl;
}
```

* Similar to the search function, this one reads each student record, parses it, and displays the details of each student in the file.

### **Main Function:**

```cpp
int main() {
    while (true) {
        cout << "\n1. Add Student\n2. Delete Student\n3. Search Student\n4. Display All Students\n5. Exit\nEnter your choice: ";
        int choice; cin >> choice;  // Get the user's menu choice
        switch (choice) {
            case 1: add_student(); break;  // Call add_student function
            case 2: delete_student(); break;  // Call delete_student function
            case 3: search_student(); break;  // Call search_student function
            case 4: display_students(); break;  // Call display_students function
            case 5: cout << "Exiting program...\n"; return 0;  // Exit the program
            default: cout << "Invalid choice! Please enter a valid option.\n";  // Handle invalid input
        }
    }
}
```

* The main function displays a menu and allows the user to select an operation to add, delete, search, or display student records, or exit the program.

### Summary

This program handles basic file operations like reading, writing, and updating student records using sequential file handling in C++. It uses file operations (`fstream`), string parsing (`stringstream`), and vector data structures to manage and display records efficiently.



    Here are 15 oral questions with answers related to **Assignment No. 11: File Organization Using C++**:

1. **What is file organization?**

   * File organization refers to the arrangement of records in a file. It determines how records are stored and accessed, impacting the performance and efficiency of file operations.

2. **Explain sequential file organization with an example.**

   * In sequential file organization, records are stored in a sequence, one after another. For example, a student record file where student information is stored based on roll number in order.

3. **What are the main operations in sequential file organization?**

   * The main operations include:

     1. Insertion: Adding new records to the file.
     2. Deletion: Removing records from the file.
     3. Searching: Finding a record based on a key.
     4. Updating: Modifying existing records.

4. **What are the advantages of sequential file organization?**

   * It is simple to implement, easy to maintain, and efficient for reading the entire file or appending records. It is inexpensive in terms of storage.

5. **What are the disadvantages of sequential file organization?**

   * Searching for specific records can be slow, especially if the file is large. Updates and deletions also require rewrites of large portions of the file.

6. **What is the difference between sequential file organization and direct access file organization?**

   * Sequential file organization stores records in a fixed sequence, while direct access allows records to be accessed directly without sequential searching, improving efficiency.

7. **How is a new record inserted in sequential file organization?**

   * In sequential files, a new record is typically inserted at the end of the file, and if using sorted files, the file is re-sorted to maintain order.

8. **How do you delete a record in sequential file organization?**

   * A record is deleted by copying all other records to a temporary file, except the one to be deleted, and then replacing the original file with the temporary file.

9. **What is the purpose of a temporary file when deleting records?**

   * The temporary file is used to store all records except the one to be deleted. Once the deletion is complete, the original file is replaced with the temporary file.

10. **What is the role of the "seek" operation in sequential file organization?**

    * The "seek" operation is used to find a specific position within the file for reading or writing records. However, in sequential files, this operation is limited as records are accessed in sequence.

11. **What is the importance of sorting in sequential file organization?**

    * Sorting records (based on a key) helps in maintaining order and can make searching, updating, and deleting records more efficient.

12. **How is student information stored in a sequential file in the given scenario?**

    * The student information is stored in a file with attributes like roll number, name, division, and address. The records are written one after another in a sequence.

13. **What are the key operations supported by a student information system in this assignment?**

    * The key operations include adding a student, deleting a student, and displaying a student's information based on their roll number.

14. **What happens if a student record does not exist when trying to delete or display it?**

    * If the record does not exist, an appropriate message is displayed to inform the user that the student record could not be found.

15. **Explain the algorithm for adding a student in the system.**

    * To add a student, the system opens the file in append mode, accepts student details, writes them to the file, and closes the file after successfully adding the record.

These questions and answers will help in understanding the concept of file organization and sequential file handling using C++.
