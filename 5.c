5. Using an array of structures, implement a student database with attributes: roll no, name, department, subject, subject marks.
Write functions for: adding a student, deleting a student, searching a student.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

typedef struct {
    int roll;
    char name[50];
    char department[50];
    char subject[50];
    int marks;
} Student;

Student students[MAX_STUDENTS];
int count = 0;

void read_line(char *buf, int size) {
    if (fgets(buf, size, stdin)) {
        size_t len = strlen(buf);
        if (len && buf[len-1] == '\n') buf[len-1] = '\0';
    }
}

void addStudent() {
    if (count >= MAX_STUDENTS) {
        printf("Database full.\n");
        return;
    }
    Student s;
    printf("Enter roll no: ");
    if (scanf("%d", &s.roll) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }
    while(getchar()!='\n');
    printf("Enter name: ");
    read_line(s.name, sizeof(s.name));
    printf("Enter department: ");
    read_line(s.department, sizeof(s.department));
    printf("Enter subject: ");
    read_line(s.subject, sizeof(s.subject));
    printf("Enter marks: ");
    if (scanf("%d", &s.marks) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }
    while(getchar()!='\n');
    students[count++] = s;
    printf("Student added.\n");
}

void deleteStudent() {
    if (count == 0) { printf("No students to delete.\n"); return; }
    int roll, i, pos = -1;
    printf("Enter roll no to delete: ");
    if (scanf("%d", &roll) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }
    while(getchar()!='\n');
    for (i = 0; i < count; i++) if (students[i].roll == roll) { pos = i; break; }
    if (pos == -1) { printf("Student with roll %d not found.\n", roll); return; }
    for (i = pos; i < count - 1; i++) students[i] = students[i+1];
    count--;
    printf("Student deleted.\n");
}

void searchStudent() {
    if (count == 0) { printf("No students in database.\n"); return; }
    int choice;
    printf("Search by: 1.Roll no  2.Name\nEnter choice: ");
    if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }
    while(getchar()!='\n');
    if (choice == 1) {
        int roll, i, found = 0;
        printf("Enter roll no: ");
        if (scanf("%d", &roll) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }
        while(getchar()!='\n');
        for (i = 0; i < count; i++) {
            if (students[i].roll == roll) {
                printf("Roll: %d\nName: %s\nDepartment: %s\nSubject: %s\nMarks: %d\n",
                       students[i].roll, students[i].name, students[i].department, students[i].subject, students[i].marks);
                found = 1;
                break;
            }
        }
        if (!found) printf("Not found.\n");
    } else if (choice == 2) {
        char name[50];
        int i, found = 0;
        printf("Enter name: ");
        read_line(name, sizeof(name));
        for (i = 0; i < count; i++) {
            if (strcasecmp(students[i].name, name) == 0) {
                printf("Roll: %d\nName: %s\nDepartment: %s\nSubject: %s\nMarks: %d\n\n",
                       students[i].roll, students[i].name, students[i].department, students[i].subject, students[i].marks);
                found = 1;
            }
        }
        if (!found) printf("Not found.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void displayAll() {
    if (count == 0) { printf("No students to display.\n"); return; }
    for (int i = 0; i < count; i++) {
        printf("Record %d:\n", i+1);
        printf("Roll: %d\nName: %s\nDepartment: %s\nSubject: %s\nMarks: %d\n\n",
               students[i].roll, students[i].name, students[i].department, students[i].subject, students[i].marks);
    }
}

int main() {
    int opt;
    while (1) {
        printf("\n1.Add student\n2.Delete student\n3.Search student\n4.Display all\n5.Exit\nEnter option: ");
        if (scanf("%d", &opt) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); continue; }
        while(getchar()!='\n');
        if (opt == 1) addStudent();
        else if
