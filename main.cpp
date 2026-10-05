#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

void clearStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    int menuChoice = 0, itemQuantity = 0, sizeChoiceMultiple = 0;
    char sizeChoice = ' ', isMember = ' ', tipChoice = ' ';
    string customerName, itemName = "Unknown", sizeString = "Unknown", notes;
    double basePrice = 0.0, priceIncrease = 0.0, itemPrice = 0.0;
    
    // Accumulator variable to track total cost across multiple items
    double runningSubtotal = 0.0;
    int totalItemsOrdered = 0;

    cout << fixed << setprecision(2);

    cout << "------------------- COFFEE SHOP -------------------\n";
    cout << "Welcome to the Coffee Shop. What is your name? ";
    getline(cin, customerName);

    cout << "Hello, " << customerName << "! Press enter to view the menu.";
    cin.get();

    // MAIN ORDERING LOOP
    while (true) {
        cout << "\n----------------------- MENU ----------------------\n";
        cout << left << setw(18) << "Item" << setw(12) << "Small (s)" << setw(12) << "Medium (m)" << setw(12) << "Large (l)\n";
        cout << "---------------------------------------------------\n";
        cout << setw(18) << "1. Muffins"   << setw(12) << "$3.00" << setw(12) << "$5.00" << "$7.00\n";
        cout << setw(18) << "2. Coffee"    << setw(12) << "$1.50" << setw(12) << "$3.00" << "$4.50\n";
        cout << setw(18) << "3. Hashbrowns"<< setw(12) << "$1.00" << setw(12) << "$3.00" << "$5.00\n";
        cout << setw(18) << "4. Cakepops"  << setw(12) << "$0.50" << setw(12) << "$1.50" << "$2.50\n";
        cout << setw(18) << "5. Sandwich"  << setw(12) << "$6.00" << setw(12) << "$8.00" << "$10.00\n";
        cout << setw(18) << "6. Checkout"  << "\n";
        cout << "---------------------------------------------------\n";

        // Menu Choice Input & Validation (1-6)
        while (true) {
            cout << "Select an item (1-6): ";
            if (cin >> menuChoice && menuChoice >= 1 && menuChoice <= 6) {
                break;
            }
            cout << "Invalid menu choice! Please select 1 through 6.\n";
            clearStream();
        }

        // Option 6: Exit ordering loop to proceed to checkout
        if (menuChoice == 6) {
            if (totalItemsOrdered == 0) {
                cout << "Your cart is empty! Please order at least one item before checking out.\n";
                continue;
            }
            break;
        }

        // Item base prices
        switch (menuChoice) {
            case 1: itemName = "Muffins";    basePrice = 3.00; priceIncrease = 2.00; break;
            case 2: itemName = "Coffee";     basePrice = 1.50; priceIncrease = 1.50; break;
            case 3: itemName = "Hashbrowns"; basePrice = 1.00; priceIncrease = 2.00; break;
            case 4: itemName = "Cakepops";   basePrice = 0.50; priceIncrease = 1.00; break;
            case 5: itemName = "Sandwich";   basePrice = 6.00; priceIncrease = 2.00; break;
        }

        // Size Selection
        while (true) {
            cout << "Select a size for " << itemName << " (s, m, l): ";
            cin >> sizeChoice;
            sizeChoice = tolower(sizeChoice);

            if (sizeChoice == 's' || sizeChoice == 'm' || sizeChoice == 'l') {
                break;
            }
            cout << "Invalid size! Choose 's', 'm', or 'l'.\n";
            clearStream();
        }

        switch (sizeChoice) {
            case 's': sizeString = "Small";  sizeChoiceMultiple = 0; break;
            case 'm': sizeString = "Medium"; sizeChoiceMultiple = 1; break;
            case 'l': sizeString = "Large";  sizeChoiceMultiple = 2; break;
        }

        itemPrice = basePrice + (priceIncrease * sizeChoiceMultiple);

        // Quantity Selection
        while (true) {
            cout << "How many " << sizeString << " " << itemName << "(s) do you want? ";
            if (cin >> itemQuantity && itemQuantity > 0) {
                break;
            }
            cout << "Invalid quantity! Must be greater than 0.\n";
            clearStream();
        }

        // Update total cost and item count accumulator
        double currentOrderCost = itemPrice * itemQuantity;
        runningSubtotal += currentOrderCost;
        totalItemsOrdered += itemQuantity;

        cout << "--> Added " << itemQuantity << "x " << sizeString << " " << itemName 
             << " ($" << currentOrderCost << ") to your order!\n";
    }

    // CHECKOUT PHASE
    cout << "\n------------------- CHECKOUT -------------------\n";

    // Membership
    while (true) {
        cout << "Is member (y/n): ";
        cin >> isMember;
        isMember = tolower(isMember);

        if (isMember == 'y' || isMember == 'n') {
            break;
        }
        cout << "Invalid selection! Enter 'y' or 'n'.\n";
        clearStream();
    }

    clearStream();

    // Notes
    while (true) {
        cout << "Enter cashier notes: ";
        getline(cin, notes);
        if (!notes.empty()) {
            break;
        }
        cout << "Notes cannot be empty. Please try again.\n";
    }

    // Calculations using runningSubtotal
    bool member = (isMember == 'y');
    double discount = member ? (runningSubtotal * 0.10) : 0.0;
    double discountedSubTotal = runningSubtotal - discount;

    // Taxes
    double stateTax = discountedSubTotal * 0.065;
    double countyTax = discountedSubTotal * 0.005;
    double cityTax = discountedSubTotal * 0.02125;
    double totalTax = stateTax + countyTax + cityTax;

    // Tip
    double tipAmount = -1.00;
    while (tipAmount < 0.00) {
        cout << "\nTip Options:\n";
        cout << "A) 15%   B) 20%   C) 25%   D) Other\n";
        cout << "Choice: ";
        cin >> tipChoice;

        switch (tolower(tipChoice)) {
            case 'a': tipAmount = discountedSubTotal * 0.15; break;
            case 'b': tipAmount = discountedSubTotal * 0.20; break;
            case 'c': tipAmount = discountedSubTotal * 0.25; break;
            case 'd':
                while (true) {
                    cout << "Enter tip amount: $";
                    if (cin >> tipAmount && tipAmount >= 0.0) {
                        break;
                    }
                    cout << "Invalid tip! Enter a non-negative number.\n";
                    clearStream();
                }
                break;
            default:
                cout << "Invalid choice! Select A, B, C, or D.\n";
                clearStream();
                break;
        }
    }

    double total = discountedSubTotal + totalTax + tipAmount;

    // Output Receipt
    cout << "\n--------------- RECEIPT ----------------\n";
    cout << "Customer: " << customerName << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(28) << "Total Items Ordered:" << right << setw(12) << totalItemsOrdered << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(28) << "Subtotal:" << right << setw(4) << "$" << setw(8) << runningSubtotal << "\n";
    cout << left << setw(28) << "Discount:" << right << setw(4) << "-$" << setw(8) << discount << "\n";
    cout << left << setw(28) << "Tax:" << right << setw(4) << "$" << setw(8) << totalTax << "\n";
    cout << left << setw(28) << "Tip:" << right << setw(4) << "$" << setw(8) << tipAmount << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(28) << "TOTAL:" << right << setw(4) << "$" << setw(8) << total << "\n";
    cout << "----------------------------------------\n";
    cout << "Member:   " << (member ? "Yes" : "No") << "\n";
    cout << "Notes:    " << notes << "\n";
    cout << "----------------------------------------\n";

    return 0;
}