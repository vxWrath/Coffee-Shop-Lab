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
    string notes;

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
    cin.ignore();
    cout << "Enter cashier notes: ";
    getline(cin, notes);

    cout << endl;

    /* Calculations */
    double subTotal = itemQuantity * itemPrice;

    bool member = (isMember == 'Y' || isMember == 'y');

    double discount = 0.0;
    if (member) {
        discount = subTotal * 0.10;
    }

    double discountedSubTotal = subTotal - discount;
    double tax = discountedSubTotal * 0.10;
    double total = discountedSubTotal + tax;

    /* Output */
    cout << fixed << setprecision(2) << "----- RECEIPT -----" << endl;
    cout << right << setw(15) << "Item Name: " << itemName << endl;
    cout << right << setw(15) << "Item Code: " << itemCode << endl;
    cout << right << setw(15) << "Item Quantity: " << itemQuantity << endl;
    cout << right << setw(15) << "Item Price: " << "$" << itemPrice << endl;

    cout << "-------------------" << endl;

    cout << right << setw(15) << "Is Member: ";
    if (member) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
    cout << "-------------------" << endl;

    cout << right << setw(15) << "Sub Total: " << "$" << subTotal << endl;
    cout << right << setw(15) << "Discount: " << "$" << discount << endl;
    cout << right << setw(15) << "Tax: " << "$" << tax << endl;
    cout << right << setw(15) << "Total: " << "$" << total << endl;

    cout << "-------------------" << endl;
    cout << right << setw(15) << "Notes: " << notes << endl;
    cout << "-------------------" << endl;
    
    cout << "\n\n----- INVENTORY AUDIT -----" << endl;
    cout << left << setw(15) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;

    cout << left << setw(15) << itemName << setw(10) << itemQuantity << setw(10) << itemPrice << endl;

    return 0;
}
