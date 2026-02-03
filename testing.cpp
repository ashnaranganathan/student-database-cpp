#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Node {
    string firstName;
    string lastName;
    string courseCode;
    double grade;
    Node* next;
};

void printRecord(Node* node, int index) {
    cout << index << ")"
        << node -> firstName << " " << node -> lastName << ", "
        << " | Course: " << node -> courseCode << " | " 
        << "Grade: " << node -> grade << endl;

}

void insertRecord(Node*& head, int position, string fname, string lname, string course, double grade) {
    Node* newNode = new Node();
    newNode->firstName = fname;
    newNode->lastName = lname;
    newNode->courseCode = course;
    newNode->grade = grade;
    newNode->next = nullptr;
    if (position <= 0 || head == nullptr) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* current = head;
    for (int i = 0; i < position - 1 && current->next != nullptr; ++i) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}


void deleteRecord(Node*& head, int position) {
    if (head == nullptr) {
        cout << "Database is empty. Nothing to delete." << endl;
        return;
    }
    if (position <= 0) {
        Node* tempt = head;
        head = head->next;
        delete tempt; 
        cout << "Record at position " << position << " deleted." << endl;
        return;
    }
    Node* current = head;
    int index = 0;
    while (current->next != nullptr && index < position - 1) {
        current = current->next;
        index++;
    }
    if (current->next == nullptr) {
        cout << "Position " << position << " is out of bounds. No record deleted." << endl;
        return;
    }
    Node* tempt = current->next;
    current->next = tempt->next;
    delete tempt;
    cout << "Record at position " << position << " deleted." << endl;
}


void searchByLastName(Node* head, string lname) {
    Node* current = head;
    int index = 0;
    bool found = false;
    while (current != nullptr) {
        if (current->lastName == lname) {
            printRecord(current, index);
            found = true;
        }
        current = current->next;
        index++;
    }
    if (!found) {
        cout << "No records found with last name: " << lname << endl;
    }
}
void printRange(Node* head, int start, int end) {
    if (head == nullptr) {
        cout << "Database is empty." << endl;
        return;
    }
    if (start < 0) start = 0;
    if (end < 0) end = 0;
    Node* current = head;
    int index = 0;
    while (current != nullptr) {
        if (index >= start && index <= end) {
            printRecord(current, index);
        }
        current = current->next;
        index++;
    }
}

void classAverage(Node* head, string course) {
    Node* current = head;
    double total = 0.0;
    int count = 0;
    while (current != nullptr) {
        if (current->courseCode == course) {
            total += current->grade;
            count++;
        }
        current = current->next;
    }
    if (count == 0) {
        cout << "No records found for course: " << course << endl;
    } else {
        double average = total / count;
        cout << fixed << setprecision(2);
        cout << "Class average for course " << course << ": " << average << endl;
    }
}
void printAllRecords(Node* head) {
    if (head == nullptr) {
        cout << "Database is empty." << endl;
        return;
    }
    Node* current = head;
    int index = 0;
    while (current != nullptr) {
        printRecord(current, index);
        current = current->next;
        index++;
    }
}
void clearList (Node*& head) {
    while (head != nullptr) {
        Node* tempt = head;
        head = head->next;
        delete tempt;
    }
}

int main() {
    Node* head = nullptr;   
    int choice;

    cout << "Welcome to the database menu!\n";

    do {
        cout << "\nPress 1 to insert a new record\n";
        cout << "Press 2 to delete a record\n";
        cout << "Press 3 to search the database (by last name)\n";
        cout << "Press 4 to print a range in the database\n";
        cout << "Press 5 to find the class average for a course\n";
        cout << "Press 9 to quit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string fn, ln, cc;
            double gr;
            int pos;

            cout << "Enter position to insert at: ";
            cin >> pos;

            cout << "Enter first name: ";
            cin >> fn;

            cout << "Enter last name: ";
            cin >> ln;

            cout << "Enter course code: ";
            cin >> cc;

            cout << "Enter grade: ";
            cin >> gr;

            insertRecord(head, pos, fn, ln, cc, gr);
            cout << "Record inserted.\n";
        }
        else if (choice == 2) {
            int pos;
            cout << "Enter position to delete: ";
            cin >> pos;
            deleteRecord(head, pos);
        }
        else if (choice == 3) {
            string ln;
            cout << "Enter last name to search: ";
            cin >> ln;
            searchByLastName(head, ln);
        }
        else if (choice == 4) {
            int start, end;
            cout << "Enter start index: ";
            cin >> start;
            cout << "Enter end index: ";
            cin >> end;
            printRange(head, start, end);
        }
        else if (choice == 5) {
            string cc;
            cout << "Enter course code: ";
            cin >> cc;
            classAverage(head, cc);
        }
        else if (choice == 9) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 9);

    clearList(head); 
    return 0;
}



