#include <iostream>
using namespace std;

class Event {
private:
    string eventName;
    string participantName;
    int regID;

public:
    static int totalParticipants;

    void registerParticipant() {
        cout<<"\nEvent Name: ";
        cin>>eventName;

        cout<<"Participant Name: ";
        cin>>participantName;

        cout<<"Registration ID: ";
        cin>>regID;

        totalParticipants++;
    }

    int getRegID() {
        return regID;
    }

    void display() {
        cout<<"\nEvent: "<<eventName;
        cout<<"\nParticipant: "<<participantName;
        cout<<"\nRegistration ID: "<<regID<<endl;
    }
};

int Event::totalParticipants=0;

int main() {
    int n;
    cout<<"Enter Number of Participants: ";
    cin>>n;

    Event e[50];

    for(int i=0;i<n;i++) {
        bool duplicate=false;
        e[i].registerParticipant();

        for(int j=0;j<i;j++) {
            if(e[i].getRegID()==e[j].getRegID())
                duplicate=true;
        }

        if(duplicate)
            cout<<"Duplicate Registration ID!\n";
    }

    cout<<"\nRegistration Details\n";

    for(int i=0;i<n;i++)
        e[i].display();

    cout<<"\nTotal Participants: "
        <<Event::totalParticipants;

    return 0;
}
