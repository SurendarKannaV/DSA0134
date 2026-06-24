#include <iostream>
using namespace std;

class Warehouse {
private:
    int itemID, quantity;
    string name, location;

public:
    static int totalItems;

    void addItem() {
        cout<<"\nItem ID: ";
        cin>>itemID;

        cout<<"Item Name: ";
        cin>>name;

        cout<<"Quantity: ";
        cin>>quantity;

        cout<<"Location: ";
        cin>>location;

        if(quantity<0)
            quantity=0;

        totalItems+=quantity;
    }

    void updateStock() {
        int newQty;
        cout<<"Enter New Quantity: ";
        cin>>newQty;

        if(newQty>=0)
            quantity=newQty;
    }

    void display() {
        cout<<"\nItem ID: "<<itemID;
        cout<<"\nName: "<<name;
        cout<<"\nQuantity: "<<quantity;
        cout<<"\nLocation: "<<location<<endl;
    }
};

int Warehouse::totalItems=0;

int main() {
    int n;

    cout<<"Enter Number of Items: ";
    cin>>n;

    Warehouse w[50];

    for(int i=0;i<n;i++)
        w[i].addItem();

    cout<<"\nInventory Details\n";

    for(int i=0;i<n;i++)
        w[i].display();

    cout<<"\nTotal Items Stored: "
        <<Warehouse::totalItems;

    return 0;
}
