#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    /* Variables */
    int menuChoice;
    char sizeChoice;
    string itemName;
    string itemSize;
    int itemQuantity;
    double itemPrice = 0.0;
    char isMember;
    string notes;

    /* Display Menu */
    cout << fixed << setprecision(2);
    cout << "----------------------- MENU ----------------------" << endl;
    cout << left << setw(18) << "Item"
         << setw(12) << "Small (s)"
         << setw(12) << "Medium (m)"
         << setw(12) << "Large (l)" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(18) << "1. Muffins" << setw(12) << "$2.00" << setw(12) << "$5.00" << setw(12) << "$7.00" << endl;
    cout << left << setw(18) << "2. Coffee" << setw(12) << "$1.50" << setw(12) << "$3.00" << setw(12) << "$4.50" << endl;
    cout << left << setw(18) << "3. Hashbrowns" << setw(12) << "$1.00" << setw(12) << "$3.00" << setw(12) << "$5.00" << endl;
    cout << left << setw(18) << "4. Cakepops" << setw(12) << "$0.50" << setw(12) << "$1.50" << setw(12) << "$2.50" << endl;
    cout << left << setw(18) << "5. Sandwich" << setw(12) << "$6.00" << setw(12) << "$8.00" << setw(12) << "$12.00" << endl;
    cout << "---------------------------------------------------" << endl;

    /* Input */
    cout << "Select an item (1-5): ";
    cin >> menuChoice;

    cout << "Select a size (s, m, l): ";
    cin >> sizeChoice;

    /* Get food and price */
    switch (menuChoice) {
        case 1:
            itemName = "Muffins";

            if (sizeChoice == 's' || sizeChoice == 'S') {
                itemPrice = 2.00;
            }
            else if (sizeChoice == 'm' || sizeChoice == 'M') {
                itemPrice = 5.00;
            }
            else if (sizeChoice == 'l' || sizeChoice == 'L') {
                itemPrice = 7.00;
            }
            break;
        case 2:
            itemName = "Coffee";

            if (sizeChoice == 's' || sizeChoice == 'S') {
                itemPrice = 1.50;
            }
            else if (sizeChoice == 'm' || sizeChoice == 'M') {
                itemPrice = 3.00;
            }
            else if (sizeChoice == 'l' || sizeChoice == 'L') {
                itemPrice = 4.50;
            }
            break;
        case 3:
            itemName = "Hashbrowns";

            if (sizeChoice == 's' || sizeChoice == 'S') {
                itemPrice = 1.00;
            }
            else if (sizeChoice == 'm' || sizeChoice == 'M') {
                itemPrice = 3.00;
            }
            else if (sizeChoice == 'l' || sizeChoice == 'L') {
                itemPrice = 5.00;
            }
            break;
        case 4:
            itemName = "Cakepops";

            if (sizeChoice == 's' || sizeChoice == 'S') {
                itemPrice = 0.50;
            }
            else if (sizeChoice == 'm' || sizeChoice == 'M') {
                itemPrice = 1.50;
            }
            else if (sizeChoice == 'l' || sizeChoice == 'L') {
                itemPrice = 2.50;
            }
            break;
        case 5:
            itemName = "Sandwich";

            if (sizeChoice == 's' || sizeChoice == 'S') {
                itemPrice = 6.00;
            }
            else if (sizeChoice == 'm' || sizeChoice == 'M') {
                itemPrice = 8.00;
            }
            else if (sizeChoice == 'l' || sizeChoice == 'L') {
                itemPrice = 12.00;
            }
            break;
        default:
            itemName = "Unknown Item";
            itemPrice = 0.0;
            break;
    }

    /* Convert size to string */
    string sizeString;
    if (sizeChoice == 's' || sizeChoice == 'S') {
        sizeString = "Small";
    }
    else if (sizeChoice == 'm' || sizeChoice == 'M') {
        sizeString = "Medium";
    }
    else if (sizeChoice == 'l' || sizeChoice == 'L') {
        sizeString = "Large";
    }
    else {
        sizeString = "Unknown";
    }

    /* Other inputs */
    cout << "How many do you want to buy? ";
    cin >> itemQuantity;

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

    // Phase 5: Individual Taxes
    double stateTax = discountedSubTotal * 0.065;      // 6.5%
    double countyTax = discountedSubTotal * 0.005;     // 0.5%
    double cityTax = discountedSubTotal * 0.02125;     // 2.125%
    double totalTax = stateTax + countyTax + cityTax;

    // Phase 5: Tip Menu
    double tip15 = discountedSubTotal * 0.15;
    double tip20 = discountedSubTotal * 0.20;
    double tip25 = discountedSubTotal * 0.25;

    cout << "\n=================== TIP MENU ===================" << endl;
    cout << left << setw(20) << "Tip Selection" << "Amount" << endl;
    cout << "--------------------------------------------" << endl;
    cout << left << setw(20) << "A. 15%" << "$" << tip15 << endl;
    cout << left << setw(20) << "B. 20%" << "$" << tip20 << endl;
    cout << left << setw(20) << "C. 25%" << "$" << tip25 << endl;
    cout << left << setw(20) << "D. Other Amount" << endl;
    cout << "============================================" << endl;

    char tipChoice;
    double tipAmount = 0.0;

    cout << "What tip do you choose? ";
    cin >> tipChoice;

    if (tipChoice == 'A' || tipChoice == 'a') {
        tipAmount = tip15;
    } else if (tipChoice == 'B' || tipChoice == 'b') {
        tipAmount = tip20;
    } else if (tipChoice == 'C' || tipChoice == 'c') {
        tipAmount = tip25;
    } else if (tipChoice == 'D' || tipChoice == 'd') {
        cout << "How much would you like to tip? $";
        cin >> tipAmount;
    }

    // Final Total Calculation
    double total = discountedSubTotal + totalTax + tipAmount;

    /* Output */
    cout << fixed << setprecision(2) << "--------------------- RECEIPT ---------------------" << endl;
    cout << right << setw(15) << "Item Name: " << itemName << endl;
    cout << right << setw(15) << "Item Size: " << sizeString << endl;
    cout << right << setw(15) << "Item Quantity: " << itemQuantity << endl;
    cout << right << setw(15) << "Item Price: " << "$" << itemPrice << endl;

    cout << "---------------------------------------------------" << endl;

    cout << right << setw(15) << "Is Member: ";
    if (member)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    cout << "---------------------------------------------------" << endl;

   cout << right << setw(20) << "Sub Total: " << "$" << subTotal << endl;
    cout << right << setw(20) << "Discount: " << "$" << discount << endl;
    
    cout << "\n--- TAX BREAKDOWN ---" << endl;
    cout << left << setw(22) << "AR State Tax (6.5%):" << "$" << stateTax << endl;
    cout << left << setw(22) << "Faulkner Co Tax (0.5%):" << "$" << countyTax << endl;
    cout << left << setw(22) << "Conway Tax (2.125%):" << "$" << cityTax << endl;
    cout << left << setw(22) << "Total Tax:" << "$" << totalTax << endl;

    cout << "-------------------" << endl;
    cout << left << setw(22) << "Tip:" << "$" << tipAmount << endl;
    cout << left << setw(22) << "Total:" << "$" << total << endl;

    cout << "---------------------------------------------------" << endl;
    cout << right << setw(15) << "Notes: " << notes << endl;

    cout << "----------------- INVENTORY AUDIT -----------------" << endl;
    cout << left << setw(15) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;

    cout << left << setw(15) << itemName << setw(10) << itemQuantity << setw(10) << itemPrice << endl;
    
    return 0;
}
