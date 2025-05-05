ASSIGNMENT NO: 10
TITLE :IMPLEMENT THE PRIORITY QUEUE USING ARRAY
PROBLEM STATEMENT:
Consider a scenario for Hospital to cater services to different kinds of patients as Serious (top priority), b)
non-serious (medium priority), c) General Checkup (Least priority). Implement the priority queue to cater
services to the patients. 




#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int SERIOUS = 1;
const int NON_SERIOUS = 2;
const int GENERAL_CHECKUP = 3;

struct Patient {
    string id;
    string name;
    int priority;

    bool operator<(const Patient& p) const {
        return priority > p.priority; // Lower number = higher priority
    }
};

string get_priority_name(int priority) {
    switch (priority) {
        case SERIOUS: return "Serious";
        case NON_SERIOUS: return "Non-Serious";
        case GENERAL_CHECKUP: return "General Checkup";
        default: return "Unknown";
    }
}

priority_queue<Patient> pq;
vector<Patient> patient_list;

// Rebuild the priority queue from the patient list
void rebuild_queue() {
    while (!pq.empty()) pq.pop();
    for (const auto& p : patient_list) {
        pq.push(p);
    }
}

void add_patient() {
    Patient p;
    cout << "Enter Patient ID: ";
    cin >> p.id;
    cout << "Enter Patient Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Priority (1 - Serious, 2 - Non-Serious, 3 - General Checkup): ";
    cin >> p.priority;
    pq.push(p);
    patient_list.push_back(p);
    cout << "Patient added successfully!\n";
}

void serve_patient() {
    if (pq.empty()) {
        cout << "No patients in queue!\n";
        return;
    }
    Patient p = pq.top();
    pq.pop();
    cout << "Serving Patient: " << p.id << " - " << p.name << " (Priority: " << get_priority_name(p.priority) << ")\n";

    auto it = remove_if(patient_list.begin(), patient_list.end(), [&p](const Patient& pat) {
        return pat.id == p.id;
    });
    patient_list.erase(it, patient_list.end());
}

void delete_patient() {
    if (patient_list.empty()) {
        cout << "No patients to delete!\n";
        return;
    }
    string id;
    cout << "Enter Patient ID to delete: ";
    cin >> id;

    auto it = remove_if(patient_list.begin(), patient_list.end(), [&id](const Patient& p) {
        return p.id == id;
    });

    if (it == patient_list.end()) {
        cout << "Patient not found!\n";
    } else {
        patient_list.erase(it, patient_list.end());
        rebuild_queue();  // Sync priority queue
        cout << "Patient record deleted successfully!\n";
    }
}

void search_patient() {
    if (patient_list.empty()) {
        cout << "No patients in queue!\n";
        return;
    }
    string id;
    cout << "Enter Patient ID to search: ";
    cin >> id;

    bool found = false;
    for (const auto& p : patient_list) {
        if (p.id == id) {
            cout << "Patient Found: " << p.id << " - " << p.name << " (Priority: " << get_priority_name(p.priority) << ")\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Patient not found!\n";
}

void display_patients() {
    if (pq.empty()) {
        cout << "No patients in queue!\n";
        return;
    }
    priority_queue<Patient> temp = pq;
    cout << "Patients in Queue:\n";
    while (!temp.empty()) {
        Patient p = temp.top();
        temp.pop();
        cout << "ID: " << p.id << " | Name: " << p.name << " | Priority: " << get_priority_name(p.priority) << "\n";
    }
}

int main() {
    while (true) {
        cout << "\n1. Add Patient\n2. Serve Patient\n3. Delete Patient\n4. Search Patient\n5. Display All Patients\n6. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: add_patient(); break;
            case 2: serve_patient(); break;
            case 3: delete_patient(); break;
            case 4: search_patient(); break;
            case 5: display_patients(); break;
            case 6: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Please enter a valid option.\n";
        }
    }
}


Explanation - Let's go through the code step by step to understand how the Priority Queue is implemented for managing hospital patients.

### Header Files and Constants:

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int SERIOUS = 1;
const int NON_SERIOUS = 2;
const int GENERAL_CHECKUP = 3;
```

* **`#include <iostream>`**: For standard input/output operations.

* **`#include <queue>`**: To use the `priority_queue` container.

* **`#include <vector>`**: To use the `vector` container to store patient data.

* **`#include <algorithm>`**: For algorithms like `remove_if` to remove elements from containers.

* **`#include <string>`**: To use the `string` class for patient names and IDs.

* **Priority Constants**:

  * **`SERIOUS`**: Assigned a value of 1 (highest priority).
  * **`NON_SERIOUS`**: Assigned a value of 2 (medium priority).
  * **`GENERAL_CHECKUP`**: Assigned a value of 3 (least priority).

### Patient Struct:

```cpp
struct Patient {
    string id;
    string name;
    int priority;

    bool operator<(const Patient& p) const {
        return priority > p.priority; // Lower number = higher priority
    }
};
```

* **`struct Patient`**: Defines the structure to hold patient details.

  * **`id`**: The patient's unique identifier.
  * **`name`**: The patient's name.
  * **`priority`**: The patient's priority (1 for serious, 2 for non-serious, and 3 for general checkup).
* **`operator<`**: The priority queue in C++ is a max-heap by default, meaning it pops the largest element. By overloading the `<` operator, the code makes it so that a smaller priority value (1 for serious) is considered "greater" in the priority queue, ensuring that the highest priority patient is always served first.

### Helper Function to Get Priority Name:

```cpp
string get_priority_name(int priority) {
    switch (priority) {
        case SERIOUS: return "Serious";
        case NON_SERIOUS: return "Non-Serious";
        case GENERAL_CHECKUP: return "General Checkup";
        default: return "Unknown";
    }
}
```

* **`get_priority_name`**: Converts the priority value (1, 2, or 3) into a readable string for display purposes (e.g., "Serious", "Non-Serious", "General Checkup").

### Priority Queue and Patient List:

```cpp
priority_queue<Patient> pq;
vector<Patient> patient_list;
```

* **`priority_queue<Patient> pq`**: A priority queue that stores patients and ensures that the highest priority patient (lowest priority number) is always at the top.
* **`vector<Patient> patient_list`**: A vector to store all patients. This is used for operations like searching and deleting patients, which are not efficiently handled by the priority queue itself.

### Rebuild Queue Function:

```cpp
void rebuild_queue() {
    while (!pq.empty()) pq.pop();
    for (const auto& p : patient_list) {
        pq.push(p);
    }
}
```

* **`rebuild_queue`**: Clears the current priority queue (`pq`) and rebuilds it from the `patient_list` to ensure synchronization between the two.

### Add Patient Function:

```cpp
void add_patient() {
    Patient p;
    cout << "Enter Patient ID: ";
    cin >> p.id;
    cout << "Enter Patient Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Priority (1 - Serious, 2 - Non-Serious, 3 - General Checkup): ";
    cin >> p.priority;
    pq.push(p);
    patient_list.push_back(p);
    cout << "Patient added successfully!\n";
}
```

* **`add_patient`**: Prompts the user to input a patient's ID, name, and priority.

  * The patient is then added to both the priority queue (`pq`) and the `patient_list`.
  * **`cin.ignore()`** is used to discard the leftover newline character after reading the integer for priority, ensuring that `getline` works properly for reading the name.

### Serve Patient Function:

```cpp
void serve_patient() {
    if (pq.empty()) {
        cout << "No patients in queue!\n";
        return;
    }
    Patient p = pq.top();
    pq.pop();
    cout << "Serving Patient: " << p.id << " - " << p.name << " (Priority: " << get_priority_name(p.priority) << ")\n";

    auto it = remove_if(patient_list.begin(), patient_list.end(), [&p](const Patient& pat) {
        return pat.id == p.id;
    });
    patient_list.erase(it, patient_list.end());
}
```

* **`serve_patient`**: Serves the patient with the highest priority (top of the priority queue).

  * The top patient is removed from the priority queue (`pq`), and the patient's details are displayed.
  * The patient is also removed from the `patient_list` using `remove_if` and `erase`.

### Delete Patient Function:

```cpp
void delete_patient() {
    if (patient_list.empty()) {
        cout << "No patients to delete!\n";
        return;
    }
    string id;
    cout << "Enter Patient ID to delete: ";
    cin >> id;

    auto it = remove_if(patient_list.begin(), patient_list.end(), [&id](const Patient& p) {
        return p.id == id;
    });

    if (it == patient_list.end()) {
        cout << "Patient not found!\n";
    } else {
        patient_list.erase(it, patient_list.end());
        rebuild_queue();  // Sync priority queue
        cout << "Patient record deleted successfully!\n";
    }
}
```

* **`delete_patient`**: Deletes a patient from the `patient_list` by their ID.

  * If the patient is found, they are removed from the list, and the priority queue is rebuilt to ensure consistency between the list and the queue.

### Search Patient Function:

```cpp
void search_patient() {
    if (patient_list.empty()) {
        cout << "No patients in queue!\n";
        return;
    }
    string id;
    cout << "Enter Patient ID to search: ";
    cin >> id;

    bool found = false;
    for (const auto& p : patient_list) {
        if (p.id == id) {
            cout << "Patient Found: " << p.id << " - " << p.name << " (Priority: " << get_priority_name(p.priority) << ")\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Patient not found!\n";
}
```

* **`search_patient`**: Searches for a patient by their ID in the `patient_list`.

  * If the patient is found, their details are displayed; otherwise, a message indicating that the patient was not found is shown.

### Display All Patients Function:

```cpp
void display_patients() {
    if (pq.empty()) {
        cout << "No patients in queue!\n";
        return;
    }
    priority_queue<Patient> temp = pq;
    cout << "Patients in Queue:\n";
    while (!temp.empty()) {
        Patient p = temp.top();
        temp.pop();
        cout << "ID: " << p.id << " | Name: " << p.name << " | Priority: " << get_priority_name(p.priority) << "\n";
    }
}
```

* **`display_patients`**: Displays all patients in the priority queue.

  * A temporary priority queue (`temp`) is used to avoid modifying the original priority queue while displaying its contents.

### Main Function:

```cpp
int main() {
    while (true) {
        cout << "\n1. Add Patient\n2. Serve Patient\n3. Delete Patient\n4. Search Patient\n5. Display All Patients\n6. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: add_patient(); break;
            case 2: serve_patient(); break;
            case 3: delete_patient(); break;
            case 4: search_patient(); break;
            case 5: display_patients(); break;
            case 6: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Please enter a valid option.\n";
        }
    }
}
```

* The `main` function displays a menu of options, allowing the user to add a patient, serve a patient, delete a patient, search for a patient, display all patients, or exit the program.
* The program will continue to run in a loop until the user chooses to exit.

### Summary:

This program models a hospital system that uses a **priority queue** to manage patients based on their severity. Patients with **Serious** conditions are given the highest priority, followed by **Non-Serious** and **General Checkup** patients. The priority queue ensures that patients with higher priority are served first.


    ### Oral Questions with Answers:

1. **What is a priority queue?**

   * A priority queue is an abstract data type where each element is associated with a priority. Elements with higher priority are dequeued before those with lower priority, regardless of the order of their arrival.

2. **What are the main operations on a priority queue?**

   * The main operations are:

     1. `insertWithPriority`: Adds an element to the queue with an associated priority.
     2. `getNext`: Removes and returns the element with the highest priority.
     3. `peekAtNext` (optional): Returns the element with the highest priority without removing it.

3. **How does a priority queue differ from a regular queue?**

   * In a regular queue (FIFO), elements are dequeued in the order they arrive. In a priority queue, elements with higher priority are dequeued before those with lower priority, regardless of their arrival order.

4. **What is the time complexity of inserting an element in a priority queue using an ordered array?**

   * The time complexity of insertion in an ordered array is O(n) because the queue needs to maintain the order, and finding the correct position for the new element requires scanning through the queue.

5. **What is the time complexity of dequeue and peek operations in a priority queue using an unordered array?**

   * The time complexity of both dequeue and peek operations in an unordered array is O(n) because you need to search for the element with the highest priority.

6. **How does a priority queue work in a hospital scenario?**

   * In a hospital, patients are categorized by their condition (e.g., serious, non-serious, general checkup) with corresponding priorities. A priority queue can be used to manage patient service, ensuring that the most critical patients (highest priority) are served first.

7. **What is the advantage of using a binary heap for implementing a priority queue?**

   * A binary heap allows the insertion, deletion, and peek operations to be performed in O(log n) time, making it more efficient than using arrays or linked lists, where operations can take O(n) time.

8. **What are the different ways to implement a priority queue?**

   * A priority queue can be implemented using:

     1. **Ordered Array**: Elements are inserted in sorted order.
     2. **Unordered Array**: Elements are inserted without sorting, and the highest-priority element is searched when needed.
     3. **Linked List**: Can be ordered or unordered.
     4. **Binary Heap**: Efficient implementation using a binary tree structure.

9. **What is the worst-case time complexity of the enqueue operation in an unordered array?**

   * The time complexity of the enqueue operation in an unordered array is O(1), as the element is simply added at the end of the array without maintaining any order.

10. **What is the worst-case time complexity of the dequeue operation in an ordered array?**

    * The dequeue operation in an ordered array has a time complexity of O(1), as the highest-priority element is always at the last position of the array.

11. **Explain the role of comparison functions in priority queues.**

    * Comparison functions determine how elements are prioritized in the queue. For example, in a hospital, a comparison function might prioritize patients based on their medical condition (e.g., serious > non-serious > general checkup).

12. **Why is a priority queue useful in managing hospital patients?**

    * A priority queue ensures that patients are served based on the severity of their condition, rather than the order in which they arrive, which helps in providing timely treatment to critical patients.

13. **What is the time complexity of dequeue and peek operations in a priority queue using a binary heap?**

    * Both the dequeue and peek operations in a binary heap take O(log n) time, as the heap structure allows for efficient extraction of the element with the highest priority.

14. **How would you handle tie-breaking in a priority queue?**

    * Tie-breaking can be handled by adding additional factors like arrival time or other attributes (e.g., urgency of the case) to the comparison function, ensuring that elements with the same priority are ordered based on these factors.

15. **What is the difference between a priority queue and a regular queue in terms of service order?**

    * In a regular queue, the service order follows a First-In-First-Out (FIFO) rule, while in a priority queue, the service order is determined by the priority assigned to each element, with the highest-priority element served first, regardless of when it arrived.
