#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <map>

using namespace std;

// ─── Utility ────────────────────────────────────────────────

string currentTime() {
    time_t now = time(0);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void printLine(char ch = '-', int len = 55) {
    cout << string(len, ch) << "\n";
}

void printHeader(const string& title) {
    printLine('=');
    cout << "  " << title << "\n";
    printLine('=');
}

// ─── Transaction Record ─────────────────────────────────────

struct Transaction {
    string type;       // "Recharge" or transit type
    double amount;
    string timestamp;
    string description;
};

// ─── Smart Card ─────────────────────────────────────────────

class SmartCard {
public:
    int    cardId;
    string holderName;
    double balance;
    vector<Transaction> history;

    SmartCard(int id, const string& name, double initialBalance)
        : cardId(id), holderName(name), balance(initialBalance) {
        Transaction t = {"Recharge", initialBalance, currentTime(),
                         "Initial card load"};
        history.push_back(t);
    }

    bool deduct(double amount, const string& type, const string& desc) {
        if (balance < amount) return false;
        balance -= amount;
        Transaction t = {type, -amount, currentTime(), desc};
        history.push_back(t);
        return true;
    }

    void recharge(double amount) {
        balance += amount;
        Transaction t = {"Recharge", amount, currentTime(),
                         "Top-up of Rs." + to_string((int)amount)};
        history.push_back(t);
    }

    void printCard() const {
        cout << "  Card ID   : " << setw(6) << setfill('0') << cardId << "\n";
        cout << "  Holder    : " << holderName << "\n";
        cout << "  Balance   : Rs." << fixed << setprecision(2) << balance << "\n";
        setfill(' ');
    }

    void printHistory() const {
        printHeader("TRANSACTION HISTORY — Card #" + to_string(cardId));
        cout << left << setw(12) << "Type"
             << setw(10) << "Amount"
             << setw(22) << "Date & Time"
             << "Description\n";
        printLine();
        for (const auto& t : history) {
            string amtStr = (t.amount >= 0 ? "+" : "") +
                            to_string((int)t.amount) + ".00";
            cout << left << setw(12) << t.type
                 << setw(10) << amtStr
                 << setw(22) << t.timestamp
                 << t.description << "\n";
        }
        printLine();
        cout << "  Current Balance: Rs." << fixed << setprecision(2) << balance << "\n";
        printLine('=');
    }
};

// ─── Transit Routes ─────────────────────────────────────────

struct Route {
    string name;
    string type;      // Bus / Metro / Train
    double baseFare;
};

// ─── Gateway System ─────────────────────────────────────────

class FareGateway {
    vector<SmartCard> cards;
    vector<Route>     routes;
    int nextCardId = 1001;

    SmartCard* findCard(int id) {
        for (auto& c : cards)
            if (c.cardId == id) return &c;
        return nullptr;
    }

public:
    FareGateway() {
        // Predefined routes
        routes = {
            {"Route 1 - City Center",   "Bus",   15.0},
            {"Route 2 - Airport Link",  "Bus",   40.0},
            {"Route 3 - Blue Line",     "Metro", 25.0},
            {"Route 4 - Green Line",    "Metro", 30.0},
            {"Route 5 - North Express", "Train", 60.0},
            {"Route 6 - South Local",   "Train", 45.0},
        };
    }

    // ── Create Card ──────────────────────────────────────────
    void createCard() {
        printHeader("CREATE SMART CARD");
        string name;
        double initial;

        cout << "  Enter Holder Name    : ";
        cin.ignore();
        getline(cin, name);
        cout << "  Initial Load (Rs.)   : ";
        cin >> initial;

        if (initial < 0) { cout << "  [!] Invalid amount.\n"; return; }

        cards.emplace_back(nextCardId++, name, initial);
        SmartCard& c = cards.back();
        cout << "\n  ✓ Card created successfully!\n";
        printLine();
        c.printCard();
        printLine('=');
    }

    // ── Check Balance ────────────────────────────────────────
    void checkBalance() {
        printHeader("CHECK BALANCE");
        int id;
        cout << "  Enter Card ID: ";
        cin >> id;

        SmartCard* c = findCard(id);
        if (!c) { cout << "  [!] Card not found.\n"; return; }

        printLine();
        c->printCard();
        printLine('=');
    }

    // ── Recharge Card ────────────────────────────────────────
    void rechargeCard() {
        printHeader("RECHARGE CARD");
        int id; double amount;
        cout << "  Enter Card ID      : ";  cin >> id;
        cout << "  Recharge Amount    : Rs."; cin >> amount;

        SmartCard* c = findCard(id);
        if (!c) { cout << "  [!] Card not found.\n"; return; }
        if (amount <= 0) { cout << "  [!] Invalid amount.\n"; return; }

        c->recharge(amount);
        cout << "\n  ✓ Recharge successful!\n";
        cout << "  New Balance: Rs." << fixed << setprecision(2) << c->balance << "\n";
        printLine('=');
    }

    // ── Pay Fare ─────────────────────────────────────────────
    void payFare() {
        printHeader("PAY TRANSIT FARE");

        // Show routes
        cout << "  Available Routes:\n";
        printLine();
        for (int i = 0; i < (int)routes.size(); i++) {
            cout << "  [" << (i + 1) << "] "
                 << left << setw(26) << routes[i].name
                 << " (" << routes[i].type << ")"
                 << "   Rs." << fixed << setprecision(2) << routes[i].baseFare
                 << "\n";
        }
        printLine();

        int choice;
        cout << "  Select Route (1-" << routes.size() << "): ";
        cin >> choice;

        if (choice < 1 || choice > (int)routes.size()) {
            cout << "  [!] Invalid route.\n"; return;
        }

        Route& r = routes[choice - 1];

        int id;
        cout << "  Enter Card ID: ";
        cin >> id;

        SmartCard* c = findCard(id);
        if (!c) { cout << "  [!] Card not found.\n"; return; }

        printLine();
        cout << "  Passenger : " << c->holderName << "\n";
        cout << "  Route     : " << r.name << "\n";
        cout << "  Type      : " << r.type << "\n";
        cout << "  Fare      : Rs." << fixed << setprecision(2) << r.baseFare << "\n";
        cout << "  Balance   : Rs." << fixed << setprecision(2) << c->balance << "\n";
        printLine();

        if (c->balance < r.baseFare) {
            cout << "  [!] Insufficient balance! Please recharge.\n";
            cout << "  Shortfall: Rs." << fixed << setprecision(2)
                 << (r.baseFare - c->balance) << "\n";
            printLine('=');
            return;
        }

        char confirm;
        cout << "  Confirm payment? (y/n): ";
        cin >> confirm;
        if (tolower(confirm) != 'y') { cout << "  Payment cancelled.\n"; return; }

        bool ok = c->deduct(r.baseFare, r.type,
                            r.type + " - " + r.name);
        if (ok) {
            cout << "\n  ✓ Payment successful! Tap card and board " << r.type << ".\n";
            cout << "  Remaining Balance: Rs." << fixed << setprecision(2) << c->balance << "\n";
        }
        printLine('=');
    }

    // ── Journey History ──────────────────────────────────────
    void viewHistory() {
        printHeader("JOURNEY HISTORY");
        int id;
        cout << "  Enter Card ID: ";
        cin >> id;

        SmartCard* c = findCard(id);
        if (!c) { cout << "  [!] Card not found.\n"; return; }

        c->printHistory();
    }

    // ── Admin: All Cards ─────────────────────────────────────
    void adminViewAllCards() {
        printHeader("ADMIN — ALL SMART CARDS");
        if (cards.empty()) { cout << "  No cards registered yet.\n"; return; }

        cout << left << setw(10) << "Card ID"
             << setw(22) << "Holder Name"
             << "Balance\n";
        printLine();
        for (const auto& c : cards) {
            cout << "  " << left << setw(8) << c.cardId
                 << setw(22) << c.holderName
                 << "Rs." << fixed << setprecision(2) << c.balance << "\n";
        }
        printLine('=');
    }

    // ── Main Menu ────────────────────────────────────────────
    void run() {
        int choice;
        do {
            printHeader("PUBLIC TRANSIT FARE PAYMENT GATEWAY");
            cout << "  [1] Create Smart Card\n";
            cout << "  [2] Check Balance\n";
            cout << "  [3] Recharge Card\n";
            cout << "  [4] Pay Transit Fare\n";
            cout << "  [5] View Journey History\n";
            cout << "  [6] Admin — View All Cards\n";
            cout << "  [0] Exit\n";
            printLine();
            cout << "  Select option: ";
            cin >> choice;
            cout << "\n";

            switch (choice) {
                case 1: createCard();        break;
                case 2: checkBalance();      break;
                case 3: rechargeCard();      break;
                case 4: payFare();           break;
                case 5: viewHistory();       break;
                case 6: adminViewAllCards(); break;
                case 0:
                    printLine('=');
                    cout << "  Thank you for using Transit Gateway. Goodbye!\n";
                    printLine('=');
                    break;
                default:
                    cout << "  [!] Invalid option. Try again.\n";
            }
            cout << "\n";

        } while (choice != 0);
    }
};

// ─── Main ───────────────────────────────────────────────────

int main() {
    FareGateway gateway;
    gateway.run();
    return 0;
}
