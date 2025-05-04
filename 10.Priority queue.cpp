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
