#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    /* Variables */
    string itemName;
    char itemCode;
    int itemQuantity;
    double itemPrice;
    char isMember;

    /* Input */
    cout << "Item name: ";
    getline(cin, itemName);

    cout << "Item code: ";
    cin >> itemCode;

    cout << "Item quantity: ";
    cin >> itemQuantity;

    cout << "Item price: ";
    cin >> itemPrice;

    cout << "Is member: ";
    cin >> isMember;

    cout << endl;

    /* Calculations */
    double subTotal = itemQuantity * itemPrice;
    double tax = subTotal * 0.10;
    double total = subTotal + tax;

    /* Output */
    cout << fixed << setprecision(2) << "----- RECEIPT -----" << endl;
    cout << right << setw(15) << "Item Name: " << itemName << endl;
    cout << right << setw(15) << "Item Code: " << itemCode << endl;
    cout << right << setw(15) << "Item Quantity: " << itemQuantity << endl;
    cout << right << setw(15) << "Item Price: " << "$" << itemPrice << endl;

    cout << "-------------------" << endl;

    cout << right << setw(15) << "Is Member: ";
    if (isMember == 'y' || isMember == 'Y') {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
    cout << "-------------------" << endl;

    cout << right << setw(15) << "Sub Total: " << "$" << subTotal << endl;
    cout << right << setw(15) << "Tax: " << "$" << tax << endl;
    cout << right << setw(15) << "Total: " << "$" << total << endl;

    return 0;
}