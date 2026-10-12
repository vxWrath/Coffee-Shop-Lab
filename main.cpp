#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
#include <fstream>

using namespace std;

void clearStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    double grandTotalSales = 0.0;
    int totalCustomers = 0;
    char nextCustomer = ' ';

    // Load menu from file: "<name> <small price> <per-size increase> <starting stock>" per line
    string menuItem1, menuItem2, menuItem3, menuItem4, menuItem5;
    double menuItem1Price, menuItem2Price, menuItem3Price, menuItem4Price, menuItem5Price;
    double menuItem1Increase, menuItem2Increase, menuItem3Increase, menuItem4Increase, menuItem5Increase;

    // Stock is the count we started the day with and never changes. Sold accumulates
    // across every customer so that at the end we can report the change and what is left.
    int menuItem1Stock, menuItem2Stock, menuItem3Stock, menuItem4Stock, menuItem5Stock;
    int menuItem1Sold = 0, menuItem2Sold = 0, menuItem3Sold = 0, menuItem4Sold = 0, menuItem5Sold = 0;

    ifstream menuFile("menu.txt");

    if (!menuFile) {
        cout << "Error: could not open menu.txt\n";
        return 1;
    }

    menuFile >> menuItem1 >> menuItem1Price >> menuItem1Increase >> menuItem1Stock;
    menuFile >> menuItem2 >> menuItem2Price >> menuItem2Increase >> menuItem2Stock;
    menuFile >> menuItem3 >> menuItem3Price >> menuItem3Increase >> menuItem3Stock;
    menuFile >> menuItem4 >> menuItem4Price >> menuItem4Increase >> menuItem4Stock;
    menuFile >> menuItem5 >> menuItem5Price >> menuItem5Increase >> menuItem5Stock;

    // Check the reads themselves, not just the open. Without this a malformed file
    // loads empty names and garbage prices and the program runs anyway.
    if (!menuFile) {
        cout << "Error: menu.txt is malformed. Each line needs a name, a price, an increase, and a starting stock.\n";
        return 1;
    }

    menuFile.close();

    cout << fixed << setprecision(2);

    while (true) {
        int menuChoice = 0, itemQuantity = 0, sizeChoiceMultiple = 0;
        char sizeChoice = ' ', isMember = ' ', tipChoice = ' ';
        string customerName, orderSummary = "", itemName = "Unknown", sizeString = "Unknown", notes;
        double basePrice = 0.0, priceIncrease = 0.0, itemPrice = 0.0;
        
        // Accumulator variable to track total cost across multiple items
        double runningSubtotal = 0.0;
        int totalItemsOrdered = 0;

        cout << "------------------- COFFEE SHOP -------------------\n";
        cout << "Welcome to the Coffee Shop. What is your name? ";
        getline(cin, customerName);

        cout << "Hello, " << customerName << "! Press enter to view the menu.";
        cin.get();

        // MAIN ORDERING LOOP
        while (true) {
            cout << "\n----------------------- MENU ----------------------\n";
            cout << left << setw(18) << "Item" << setw(12) << "Small (s)" << setw(12) << "Medium (m)" << setw(12) << "Large (l)" << "\n";
            cout << "---------------------------------------------------\n";
            cout << setw(18) << ("1. " + menuItem1) << "$" << setw(11) << menuItem1Price << "$" << setw(11) << (menuItem1Price + menuItem1Increase) << "$" << (menuItem1Price + menuItem1Increase * 2) << "\n";
            cout << setw(18) << ("2. " + menuItem2) << "$" << setw(11) << menuItem2Price << "$" << setw(11) << (menuItem2Price + menuItem2Increase) << "$" << (menuItem2Price + menuItem2Increase * 2) << "\n";
            cout << setw(18) << ("3. " + menuItem3) << "$" << setw(11) << menuItem3Price << "$" << setw(11) << (menuItem3Price + menuItem3Increase) << "$" << (menuItem3Price + menuItem3Increase * 2) << "\n";
            cout << setw(18) << ("4. " + menuItem4) << "$" << setw(11) << menuItem4Price << "$" << setw(11) << (menuItem4Price + menuItem4Increase) << "$" << (menuItem4Price + menuItem4Increase * 2) << "\n";
            cout << setw(18) << ("5. " + menuItem5) << "$" << setw(11) << menuItem5Price << "$" << setw(11) << (menuItem5Price + menuItem5Increase) << "$" << (menuItem5Price + menuItem5Increase * 2) << "\n";
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

            // Item names and base prices come from the menu file
            switch (menuChoice) {
                case 1: itemName = menuItem1; basePrice = menuItem1Price; priceIncrease = menuItem1Increase; break;
                case 2: itemName = menuItem2; basePrice = menuItem2Price; priceIncrease = menuItem2Increase; break;
                case 3: itemName = menuItem3; basePrice = menuItem3Price; priceIncrease = menuItem3Increase; break;
                case 4: itemName = menuItem4; basePrice = menuItem4Price; priceIncrease = menuItem4Increase; break;
                case 5: itemName = menuItem5; basePrice = menuItem5Price; priceIncrease = menuItem5Increase; break;
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

            // Log the sale against inventory. Size is not a factor here: a small,
            // a medium, and a large each count as one item.
            switch (menuChoice) {
                case 1: menuItem1Sold += itemQuantity; break;
                case 2: menuItem2Sold += itemQuantity; break;
                case 3: menuItem3Sold += itemQuantity; break;
                case 4: menuItem4Sold += itemQuantity; break;
                case 5: menuItem5Sold += itemQuantity; break;
            }

            // Work in whole cents: to_string on a double always prints 6 decimal places
            int orderCostCents = (int)(currentOrderCost * 100 + 0.5);
            string orderCostText = to_string(orderCostCents / 100) + "." + (orderCostCents % 100 < 10 ? "0" : "") + to_string(orderCostCents % 100);

            string itemLine = to_string(itemQuantity) + "x " + sizeString + " " + itemName + " - $" + orderCostText + "\n";
            orderSummary += itemLine;

            cout << "--> Added to order!\n";
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

        // Add loyalty points
        int loyaltyPoints = total / 3.0;
        string stars = "";

        for (int i = 0; i < loyaltyPoints; i++) {
            stars += "*";
        }

        // Output Receipt
        cout << "\n--------------- RECEIPT ----------------\n";
        cout << "Customer: " << customerName << "\n";
        cout << "----------------------------------------\n";
        cout << orderSummary;
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
        cout << "Loyalty Points: " << stars << "\n";
        cout << "----------------------------------------\n";

        fstream receiptFile("receipt.txt");
        receiptFile << "\n\n------------------- RECEIPT -------------------\n";
        receiptFile << "Customer: " << customerName << "\n";
        receiptFile << "----------------------------------------\n";
        receiptFile << orderSummary;
        receiptFile << "----------------------------------------\n";
        receiptFile << left << setw(28) << "Subtotal:" << right << setw(4) << "$" << setw(8) << runningSubtotal << "\n";
        receiptFile << left << setw(28) << "Discount:" << right << setw(4) << "-$" << setw(8) << discount << "\n";
        receiptFile << left << setw(28) << "Tax:" << right << setw(4) << "$" << setw(8) << totalTax << "\n";
        receiptFile << left << setw(28) << "Tip:" << right << setw(4) << "$" << setw(8) << tipAmount << "\n";
        receiptFile << "----------------------------------------\n";
        receiptFile << left << setw(28) << "TOTAL:" << right << setw(4) << "$" << setw(8) << total << "\n";
        receiptFile << "----------------------------------------\n";
        receiptFile << "Member:   " << (member ? "Yes" : "No") << "\n";
        receiptFile << "Notes:    " << notes << "\n";
        receiptFile << "Loyalty Points: " << stars << "\n";
        receiptFile << "----------------------------------------\n";
        receiptFile.close();

        grandTotalSales += total;
        totalCustomers++;

        while (true) {
            cout << "\nIs there another customer? (y/n)";
            cin >> nextCustomer;
            nextCustomer = tolower(nextCustomer);

            if (nextCustomer == 'y' || nextCustomer == 'n') {
                break;
            }

            cout << "Invalid input. Please enter 'y' or 'n'.\n";
            clearStream();
        }

        clearStream();

        if (nextCustomer == 'n') {
            break;
        }
    }

    cout << "\n\nTotal Customers: " << totalCustomers << "\n";
    cout << "Grant Total: " << grandTotalSales << "\n";

    // DAILY INVENTORY: every item on the menu is listed, including ones nobody ordered
    cout << "\nDaily Inventory\n";
    cout << left << setw(20) << "Item" << right << setw(12) << "Start" << setw(12) << "Change" << setw(12) << "End" << "\n";

    cout << left << setw(20) << menuItem1 << right << setw(12) << menuItem1Stock << setw(12) << -menuItem1Sold << setw(12) << (menuItem1Stock - menuItem1Sold) << "\n";
    cout << left << setw(20) << menuItem2 << right << setw(12) << menuItem2Stock << setw(12) << -menuItem2Sold << setw(12) << (menuItem2Stock - menuItem2Sold) << "\n";
    cout << left << setw(20) << menuItem3 << right << setw(12) << menuItem3Stock << setw(12) << -menuItem3Sold << setw(12) << (menuItem3Stock - menuItem3Sold) << "\n";
    cout << left << setw(20) << menuItem4 << right << setw(12) << menuItem4Stock << setw(12) << -menuItem4Sold << setw(12) << (menuItem4Stock - menuItem4Sold) << "\n";
    cout << left << setw(20) << menuItem5 << right << setw(12) << menuItem5Stock << setw(12) << -menuItem5Sold << setw(12) << (menuItem5Stock - menuItem5Sold) << "\n";

    ofstream inventoryFile("inventory.txt");
    inventoryFile << "Daily Inventory\n";
    inventoryFile << left << setw(20) << "Item" << right << setw(12) << "Start" << setw(12) << "Change" << setw(12) << "End" << "\n";

    inventoryFile << left << setw(20) << menuItem1 << right << setw(12) << menuItem1Stock << setw(12) << -menuItem1Sold << setw(12) << (menuItem1Stock - menuItem1Sold) << "\n";
    inventoryFile << left << setw(20) << menuItem2 << right << setw(12) << menuItem2Stock << setw(12) << -menuItem2Sold << setw(12) << (menuItem2Stock - menuItem2Sold) << "\n";
    inventoryFile << left << setw(20) << menuItem3 << right << setw(12) << menuItem3Stock << setw(12) << -menuItem3Sold << setw(12) << (menuItem3Stock - menuItem3Sold) << "\n";
    inventoryFile << left << setw(20) << menuItem4 << right << setw(12) << menuItem4Stock << setw(12) << -menuItem4Sold << setw(12) << (menuItem4Stock - menuItem4Sold) << "\n";
    inventoryFile << left << setw(20) << menuItem5 << right << setw(12) << menuItem5Stock << setw(12) << -menuItem5Sold << setw(12) << (menuItem5Stock - menuItem5Sold) << "\n";
    inventoryFile.close();

    return 0;
}