#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    // Variables
    int menuChoice, itemQuantity, sizeChoiceMultiple;
    char sizeChoice, isMember, tipChoice;
    string itemName, sizeString, notes;
    double basePrice, priceIncrease, itemPrice = 0.0;

    cout << fixed << setprecision(2);

    // Menu
    cout << "----------------------- MENU ----------------------\n";
    cout << left << setw(18) << "Item" << setw(12) << "Small (s)" << setw(12) << "Medium (m)" << setw(12) << "Large (l)\n";
    cout << "---------------------------------------------------\n";
    cout << setw(18) << "1. Muffins"   << setw(12) << "$3.00" << setw(12) << "$5.00" << "$7.00\n";
    cout << setw(18) << "2. Coffee"    << setw(12) << "$1.50" << setw(12) << "$3.00" << "$4.50\n";
    cout << setw(18) << "3. Hashbrowns"<< setw(12) << "$1.00" << setw(12) << "$3.00" << "$5.00\n";
    cout << setw(18) << "4. Cakepops"  << setw(12) << "$0.50" << setw(12) << "$1.50" << "$2.50\n";
    cout << setw(18) << "5. Sandwich"  << setw(12) << "$6.00" << setw(12) << "$8.00" << "$10.00\n";
    cout << "---------------------------------------------------\n";

    // Input
    cout << "Select an item (1-5): ";
    cin >> menuChoice;

    // Item selection
    switch (menuChoice)
    {
        case 1: {
            itemName = "Muffins"; 
            basePrice = 3.00;
            priceIncrease = 2.00;
            break;
        }
        case 2: {
            itemName = "Coffee"; 
            basePrice = 1.50;
            priceIncrease = 1.50;
            break;
        }
        case 3: {
            itemName = "Hashbrowns"; 
            basePrice = 1.00;
            priceIncrease = 2.00;
            break;
        }
        case 4: {
            itemName = "Cakepops"; 
            basePrice = 0.50;
            priceIncrease = 1.00;
            break;
        }
        case 5: {
            itemName = "Sandwich"; 
            basePrice = 6.00;
            priceIncrease = 2.00;
            break;
        }
        default:  {
            itemName = "Unknown"; 
            break;
        }
    }

    cout << "Select a size (s, m, l): ";
    cin >> sizeChoice;

    sizeChoice = tolower(sizeChoice);

    switch (sizeChoice)
    {
        case 's': {
            sizeString = "Small";
            sizeChoiceMultiple = 0;
            break;
        }
        case 'm': {
            sizeString = "Medium";
            sizeChoiceMultiple = 1;
            break;
        }
        case 'l': {
            sizeString = "Large";
            sizeChoiceMultiple = 2;
            break;  
        }
        default: {
            sizeString = "Unknown";
            sizeChoiceMultiple = 0;
            break;
        }
    }

    itemPrice = basePrice + (priceIncrease * sizeChoiceMultiple);

    // Other inputs
    cout << "How many do you want to buy? ";
    cin >> itemQuantity;

    cout << "Is member (y/n): ";
    cin >> isMember;
    cin.ignore();

    cout << "Enter cashier notes: ";
    getline(cin, notes);

    // Calculations
    double subTotal = itemQuantity * itemPrice;
    bool member = (tolower(isMember) == 'y');
    double discount = member ? subTotal * 0.10 : 0.0;
    double discountedSubTotal = subTotal - discount;

    // Taxes
    double stateTax = discountedSubTotal * 0.065;
    double countyTax = discountedSubTotal * 0.005;
    double cityTax = discountedSubTotal * 0.02125;
    double totalTax = stateTax + countyTax + cityTax;

    // Tip options
    double tip15 = discountedSubTotal * 0.15;
    double tip20 = discountedSubTotal * 0.20;
    double tip25 = discountedSubTotal * 0.25;
    double tipAmount = 0.0;

    cout << "\nTip Options:\n";
    cout << "A) 15%  B) 20%  C) 25%  D) Other\n";
    cout << "Choice: ";
    cin >> tipChoice;

    if (tolower(tipChoice) == 'a') {
        tipAmount = tip15;
    } else if (tolower(tipChoice) == 'b') {
        tipAmount = tip20;
    } else if (tolower(tipChoice) == 'c') {
        tipAmount = tip25;
    } else if (tolower(tipChoice) == 'd') {
        cout << "Enter tip amount: $";
        cin >> tipAmount;
    }

    double total = discountedSubTotal + totalTax + tipAmount;

    // Output
    cout << "--------------- RECEIPT ----------------\n";
    cout << left << setw(31) << "Item" << right << setw(10) << "Total\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < itemQuantity; i++) {
        cout << left << setw(25) << itemName << right << setw(10) << "$" << itemPrice << "\n";
    }

    cout << "----------------------------------------\n";
    cout << left << setw(25) << "Subtotal:" << right << setw(10) << "$" << subTotal << "\n";
    cout << left << setw(25) << "Discount:" << right << setw(10) << "-$" << discount << "\n";
    cout << left << setw(25) << "Tax:" << right << setw(10) << "$" << totalTax << "\n";
    cout << left << setw(25) << "Tip:" << right << setw(10) << "$" << tipAmount << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(25) << "TOTAL:" << right << setw(10) << "$" << total << "\n";
    cout << "----------------------------------------\n";
    cout << "Member: " << (member ? "Yes" : "No") << "\n";
    cout << "Notes:  " << notes << "\n";
    cout << "----------------------------------------\n";

    return 0;
}