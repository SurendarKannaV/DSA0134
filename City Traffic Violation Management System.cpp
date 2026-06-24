#include <iostream>
using namespace std;

class Violation {
private:
    string vehicleNo, ownerName, violationType;
    float fineAmount;

public:
    static int totalViolations;

    void input() {
        cout << "\nVehicle Number: ";
        cin >> vehicleNo;

        cout << "Owner Name: ";
        cin >> ownerName;

        cout << "Violation Type (Signal/Helmet/Speed): ";
        cin >> violationType;

        calculateFine();
        totalViolations++;
    }

    void calculateFine() {
        if (violationType == "Signal")
            fineAmount = 1000;
        else if (violationType == "Helmet")
            fineAmount = 500;
        else if (violationType == "Speed")
            fineAmount = 1500;
        else {
            fineAmount = 0;
            cout << "Invalid Violation Type\n";
        }
    }

    void display() {
        cout << "\nVehicle No: " << vehicleNo;
        cout << "\nOwner Name: " << ownerName;
        cout << "\nViolation Type: " << violationType;
        cout << "\nFine Amount: " << fineAmount << endl;
    }
};

int Violation::totalViolations = 0;

int main() {
    int n;
    cout << "Enter Number of Violations: ";
    cin >> n;

    Violation v[50];

    for(int i=0;i<n;i++)
        v[i].input();

    cout << "\nViolation Reports\n";

    for(int i=0;i<n;i++)
        v[i].display();

    cout << "\nTotal Violations: "
         << Violation::totalViolations;

    return 0;
}
