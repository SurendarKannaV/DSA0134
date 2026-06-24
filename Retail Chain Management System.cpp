#include <iostream>
using namespace std;

class Product {
private:
    string name;
    float price;
    int quantity;

public:
    static float overallSales;

    void input() {
        cout << "Enter product name: ";
        cin >> name;

        cout << "Enter price: ";
        cin >> price;

        cout << "Enter quantity sold: ";
        cin >> quantity;

        if (price < 0) price = 0;
        if (quantity < 0) quantity = 0;
    }

    float productSales() {
        return price * quantity;
    }

    string getName() {
        return name;
    }

    void display() {
        cout << "\nProduct Name: " << name;
        cout << "\nPrice: " << price;
        cout << "\nQuantity Sold: " << quantity;
        cout << "\nSales: " << productSales() << endl;
    }
};

float Product::overallSales = 0;

class Store {
private:
    Product products[100];
    int productCount;
    int storeNo;

public:
    void input(int s) {
        storeNo = s;

        cout << "\nEnter number of products in Store " << storeNo << ": ";
        cin >> productCount;

        for (int i = 0; i < productCount; i++) {
            cout << "\nProduct " << i + 1 << endl;
            products[i].input();
        }
    }

    float calculateStoreSales() {
        float total = 0;

        for (int i = 0; i < productCount; i++) {
            total += products[i].productSales();
        }

        return total;
    }

    Product getTopProduct() {
        int index = 0;

        for (int i = 1; i < productCount; i++) {
            if (products[i].productSales() > products[index].productSales()) {
                index = i;
            }
        }

        return products[index];
    }

    void display() {
        cout << "\n\nStore " << storeNo << " Details";

        for (int i = 0; i < productCount; i++) {
            products[i].display();
        }

        cout << "Total Store Sales: " << calculateStoreSales() << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of stores: ";
    cin >> n;

    Store stores[20];

    for (int i = 0; i < n; i++) {
        stores[i].input(i + 1);
    }

    int bestStore = 0;
    Product topProduct;
    bool firstProduct = true;

    for (int i = 0; i < n; i++) {
        stores[i].display();

        float sales = stores[i].calculateStoreSales();
        Product::overallSales += sales;

        if (sales > stores[bestStore].calculateStoreSales()) {
            bestStore = i;
        }

        Product p = stores[i].getTopProduct();

        if (firstProduct || p.productSales() > topProduct.productSales()) {
            topProduct = p;
            firstProduct = false;
        }
    }

    cout << "\nOverall Sales: " << Product::overallSales;
    cout << "\nBest Performing Store: Store " << bestStore + 1;
    cout << "\nBest Selling Product: " << topProduct.getName();
    cout << "\nProduct Sales: " << topProduct.productSales() << endl;

    return 0;
}
