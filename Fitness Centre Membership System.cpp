#include <iostream>
using namespace std;

class Member {
private:
    int memberID;
    string name, planType;
    float fee;

public:
    static int activeMembers;

    void input() {
        cout << "\nMember ID: ";
        cin >> memberID;

        cout << "Name: ";
        cin >> name;

        cout << "Plan (Basic/Premium/VIP): ";
        cin >> planType;

        assignPlan();
        activeMembers++;
    }

    void assignPlan() {
        if(planType=="Basic")
            fee=1000;
        else if(planType=="Premium")
            fee=2000;
        else if(planType=="VIP")
            fee=3000;
        else {
            fee=0;
            cout<<"Invalid Plan\n";
        }
    }

    void display() {
        cout<<"\nID: "<<memberID;
        cout<<"\nName: "<<name;
        cout<<"\nPlan: "<<planType;
        cout<<"\nFee: "<<fee<<endl;
    }
};

int Member::activeMembers=0;

int main() {
    int n;
    cout<<"Enter Number of Members: ";
    cin>>n;

    Member m[50];

    for(int i=0;i<n;i++)
        m[i].input();

    cout<<"\nMembership Details\n";

    for(int i=0;i<n;i++)
        m[i].display();

    cout<<"\nTotal Active Members: "
        <<Member::activeMembers;

    return 0;
}
