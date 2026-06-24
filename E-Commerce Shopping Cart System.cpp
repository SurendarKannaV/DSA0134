#include <iostream>
using namespace std;

class Product {
private:
    string productName;
    float price;
    int quantity;

public:
    static int totalProducts;

    void getData() {
        cout<<"\nProduct Name: ";
        cin>>productName;

        cout<<"Price: ";
        cin>>price;

        cout<<"Quantity: ";
        cin>>quantity;

        if(price<0)
            price=0;

        if(quantity<0)
            quantity=0;

        totalProducts++;
    }

    float calculateTotal() {
        return price * quantity;
    }

    void display() {
        cout<<"\nProduct: "<<productName;
        cout<<"\nPrice: "<<price;
        cout<<"\nQuantity: "<<quantity;
        cout<<"\nTotal Cost: "<<calculateTotal()<<endl;
    }
};

int Product::totalProducts=0;

int main() {
    int n;
    float grandTotal=0;

    cout<<"Enter Number of Products: ";
    cin>>n;

    Product p[50];

    for(int i=0;i<n;i++)
        p[i].getData();

    cout<<"\nShopping Cart Details\n";

    for(int i=0;i<n;i++) {
        p[i].display();
        grandTotal += p[i].calculateTotal();
    }

    cout<<"\nTotal Products: "
        <<Product::totalProducts;

    cout<<"\nFinal Bill Amount: "
        <<grandTotal;

    return 0;
}
