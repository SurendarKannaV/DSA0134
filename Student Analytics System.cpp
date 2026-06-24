#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int marks;

public:
    void input() {
        cout << "Enter student name: ";
        cin >> name;
        cout << "Enter marks: ";
        cin >> marks;
    }

    string getName() {
        return name;
    }

    int getMarks() {
        return marks;
    }

    bool isPass() {
        return marks >= 40;
    }
};

class Department {
private:
    string deptName;
    Student students[100];
    int count;

public:
    void input() {
        cout << "\nEnter department name: ";
        cin >> deptName;

        cout << "Enter number of students: ";
        cin >> count;

        if (count < 0) count = 0;

        for (int i = 0; i < count; i++) {
            cout << "\nStudent " << i + 1 << endl;
            students[i].input();
        }
    }

    void displayResult() {
        if (count == 0) {
            cout << "\nDepartment " << deptName << " has no students.\n";
            return;
        }

        int topIndex = 0;
        int passCount = 0;

        for (int i = 0; i < count; i++) {
            if (students[i].getMarks() > students[topIndex].getMarks()) {
                topIndex = i;
            }

            if (students[i].isPass()) {
                passCount++;
            }
        }

        cout << "\nDepartment: " << deptName;
        cout << "\nDepartment Topper: " << students[topIndex].getName();
        cout << "\nMarks: " << students[topIndex].getMarks();
        cout << "\nPass Percentage: " << (passCount * 100.0 / count) << "%\n";
    }

    Student getTopper() {
        int topIndex = 0;

        for (int i = 1; i < count; i++) {
            if (students[i].getMarks() > students[topIndex].getMarks()) {
                topIndex = i;
            }
        }

        return students[topIndex];
    }

    int getCount() {
        return count;
    }
};

int main() {
    int n;
    cout << "Enter number of departments: ";
    cin >> n;

    Department dept[20];

    for (int i = 0; i < n; i++) {
        dept[i].input();
    }

    Student overallTopper;
    bool found = false;

    for (int i = 0; i < n; i++) {
        dept[i].displayResult();

        if (dept[i].getCount() > 0) {
            Student temp = dept[i].getTopper();

            if (!found || temp.getMarks() > overallTopper.getMarks()) {
                overallTopper = temp;
                found = true;
            }
        }
    }

    if (found) {
        cout << "\nOverall University Topper: " << overallTopper.getName();
        cout << "\nMarks: " << overallTopper.getMarks() << endl;
    } else {
        cout << "\nNo students available.\n";
    }

    return 0;
}
