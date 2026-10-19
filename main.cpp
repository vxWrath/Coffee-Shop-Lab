#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

// Clears the cin fail state and discards the rest of the input line.
// Takes no parameters; returns nothing.
void clearStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads one menu item's name, price, size increase, and stock from menuFile.
bool loadMenuItem(ifstream &menuFile, string &name, double &price, double &increase, int &stock) {
    menuFile >> name >> price >> increase >> stock;
    return true;
}

// Shows the shop banner, asks for the customer's name, and waits for Enter.
// Takes no parameters; returns the customer's name.
string askCustomerName() {
    cout << "------------------- COFFEE SHOP -------------------\n";
    cout << "Welcome to the Coffee Shop. What is your name? ";

    string customerName;
    getline(cin, customerName);

    cout << "Hello, " << customerName << "! Press enter to view the menu.";
    cin.get();

    return customerName;
}

// Asks for a menu choice until the user enters a number from 1 to 6.
// Takes no parameters; returns the valid choice.
int getMenuChoice() {
    int menuChoice = 0;

    while (true) {
        cout << "Select an item (1-6): ";
        if (cin >> menuChoice && menuChoice >= 1 && menuChoice <= 6) {
            return menuChoice;
        }

        cout << "Invalid menu choice! Please select 1 through 6.\n";
        clearStream();
    }
}

// Asks for a size until the user enters s, m, or l.
// itemName is used in the prompt; returns the chosen size as a lowercase char.
char getSize(const string &itemName) {
    char sizeChoice = ' ';

    while (true) {
        cout << "Select a size for " << itemName << " (s, m, l): ";
        cin >> sizeChoice;
        sizeChoice = tolower(sizeChoice);

        if (sizeChoice == 's' || sizeChoice == 'm' || sizeChoice == 'l') {
            return sizeChoice;
        }

        cout << "Invalid size! Choose 's', 'm', or 'l'.\n";
        clearStream();
    }
}

// Converts a validated size character into its display name.
// Takes the size char; returns "Small", "Medium", or "Large".
string getSizeName(char size) {
    switch (size) {
        case 'm': return "Medium";
        case 'l': return "Large";
        default:  return "Small";
    }
}

// Asks how many of an item the customer wants until the value is above zero.
// sizeName and itemName are used in the prompt; returns the valid quantity.
int getQuantity(const string &sizeName, const string &itemName) {
    int itemQuantity = 0;

    while (true) {
        cout << "How many " << sizeName << " " << itemName << "(s) do you want? ";
        if (cin >> itemQuantity && itemQuantity > 0) {
            return itemQuantity;
        }

        cout << "Invalid quantity! Must be greater than 0.\n";
        clearStream();
    }
}

// Asks a yes/no question until the user enters y or n, then clears the line.
// prompt is shown; invalidMessage is used for bad input; returns true for yes.
bool askYesNo(const string &prompt, const string &invalidMessage) {
    char answer = ' ';

    while (true) {
        cout << prompt;
        cin >> answer;
        answer = tolower(answer);

        if (answer == 'y' || answer == 'n') {
            clearStream();
            return answer == 'y';
        }

        cout << invalidMessage << "\n";
        clearStream();
    }
}

// Reads cashier notes, repeating until the customer enters something.
// Takes no parameters; returns the non-empty notes text.
string getNotes() {
    string notes;

    while (true) {
        cout << "Enter cashier notes: ";
        getline(cin, notes);

        if (!notes.empty()) {
            return notes;
        }

        cout << "Notes cannot be empty. Please try again.\n";
    }
}

// Converts a dollar amount to text with exactly two decimal places.
// Takes the amount; returns text such as "12.00".
string formatMoney(double amount) {
    // Work in whole cents because to_string(double) always prints six decimals.
    int cents = (int)(amount * 100 + 0.5);
    string moneyText = to_string(cents / 100) + ".";

    if (cents % 100 < 10) {
        moneyText += "0";
    }

    moneyText += to_string(cents % 100);
    return moneyText;
}

// Formats one row of the menu table.
// Takes the item number, name, small price, and size increase; returns the row.
string formatMenuItem(int number, const string &name, double price, double increase) {
    ostringstream itemLine;

    itemLine << left << fixed << setprecision(2);
    itemLine << setw(18) << (to_string(number) + ". " + name);
    itemLine << "$" << setw(11) << price;
    itemLine << "$" << setw(11) << (price + increase);
    itemLine << "$" << (price + increase * 2);
    itemLine << "\n";

    return itemLine.str();
}

// Builds the complete printable menu from the five menu items.
// Parameters are (name, price, increase) per item, in menu order; returns the
// menu text.
string buildMenuText(
    const string &name1, double price1, double increase1,   // item 1
    const string &name2, double price2, double increase2,   // item 2
    const string &name3, double price3, double increase3,   // item 3
    const string &name4, double price4, double increase4,   // item 4
    const string &name5, double price5, double increase5    // item 5
) {
    ostringstream menu;

    menu << "\n----------------------- MENU ----------------------\n";
    menu << left << setw(18) << "Item";
    menu << setw(12) << "Small (s)";
    menu << setw(12) << "Medium (m)";
    menu << setw(12) << "Large (l)";
    menu << "\n";
    menu << "---------------------------------------------------\n";

    menu << formatMenuItem(1, name1, price1, increase1);
    menu << formatMenuItem(2, name2, price2, increase2);
    menu << formatMenuItem(3, name3, price3, increase3);
    menu << formatMenuItem(4, name4, price4, increase4);
    menu << formatMenuItem(5, name5, price5, increase5);

    menu << setw(18) << "6. Checkout" << "\n";
    menu << "---------------------------------------------------\n";

    return menu.str();
}

// Prints a menu that was already built by buildMenuText.
// Takes the menu text; returns nothing.
void displayMenu(const string &menuText) {
    cout << menuText;
}

// Adds one ordered item to the receipt's order summary.
// Updates orderSummary from quantity, sizeName, itemName, and cost; returns
// nothing.
void addOrderLine(string &orderSummary, int quantity, const string &sizeName, const string &itemName, double cost) {
    orderSummary += to_string(quantity);
    orderSummary += "x " + sizeName;
    orderSummary += " " + itemName;
    orderSummary += " - $" + formatMoney(cost) + "\n";
}

// Calculates the price of one item at the chosen size.
// Takes basePrice, increase, and size; returns the price.
double calculateItemPrice(double basePrice, double increase, char size) {
    switch (size) {
        case 'm': return basePrice + increase;
        case 'l': return basePrice + increase * 2;
        default:  return basePrice;
    }
}

// Adds a sale quantity to the matching item's sold counter.
// menuChoice and quantity choose the amount; the five counters are updated by
// reference; returns nothing.
void recordSale(
    int menuChoice, int quantity,
    int &sold1, int &sold2, int &sold3, int &sold4, int &sold5
) {
    switch (menuChoice) {
        case 1: sold1 += quantity; break;
        case 2: sold2 += quantity; break;
        case 3: sold3 += quantity; break;
        case 4: sold4 += quantity; break;
        case 5: sold5 += quantity; break;
    }
}

// Calculates the member discount.
// Takes the subtotal and membership flag; returns 10% or 0.
double calculateDiscount(double subtotal, bool member) {
    return member ? subtotal * 0.10 : 0.0;
}

// Calculates the combined state, county, and city tax.
// Takes the discounted subtotal; returns the total tax.
double calculateTax(double discountedSubtotal) {
    double stateTax = discountedSubtotal * 0.065;
    double countyTax = discountedSubtotal * 0.005;
    double cityTax = discountedSubtotal * 0.02125;

    return stateTax + countyTax + cityTax;
}

// Displays tip options and returns the chosen tip amount.
// Takes the discounted subtotal; repeats until the input is valid.
double getTip(double discountedSubtotal) {
    char tipChoice = ' ';
    double tipAmount = -1.0;

    while (tipAmount < 0.0) {
        cout << "\nTip Options:\n";
        cout << "A) 15%   B) 20%   C) 25%   D) Other\n";
        cout << "Choice: ";
        cin >> tipChoice;

        switch (tolower(tipChoice)) {
            case 'a': tipAmount = discountedSubtotal * 0.15; break;
            case 'b': tipAmount = discountedSubtotal * 0.20; break;
            case 'c': tipAmount = discountedSubtotal * 0.25; break;
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

    return tipAmount;
}

// Calculates loyalty points from the order total.
// Takes the total; returns one point for every full $3.00.
int calculateLoyaltyPoints(double total) {
    return total / 3.0;
}

// Builds the loyalty star display, one star per point.
// Takes the point count; returns stars wrapped every 40 and aligned under the
// "Loyalty Points:" label.
string buildStars(int points) {
    const int STARS_PER_LINE = 40;
    string stars;

    for (int i = 0; i < points; i++) {
        if (i > 0 && i % STARS_PER_LINE == 0) {
            stars += "\n                ";
        }
        stars += "*";
    }

    return stars;
}

// Formats one aligned money line for the receipt.
// Takes the label, sign ("$" or "-$"), and amount; returns the line.
string formatReceiptLine(const string &label, const string &sign, double amount) {
    ostringstream line;

    line << left << setw(28) << label;
    line << right << setw(4) << sign;
    line << setw(8) << fixed << setprecision(2) << amount;

    return line.str();
}

// Builds the complete receipt text so the screen and file share one output.
// Takes the customer, order, money amounts, membership, notes, and stars;
// returns the receipt text.
string buildReceipt(
    const string &customerName, const string &orderSummary,   // customer and order
    double subtotal, double discount, double tax,             // money before total
    double tip, double total,                                 // final money
    bool member, const string &notes, const string &stars    // receipt details
) {
    ostringstream receipt;

    receipt << "\n--------------- RECEIPT ----------------\n";
    receipt << "Customer: " << customerName << "\n";
    receipt << "----------------------------------------\n";
    receipt << orderSummary;
    receipt << "----------------------------------------\n";
    receipt << formatReceiptLine("Subtotal:", "$", subtotal) << "\n";
    receipt << formatReceiptLine("Discount:", "-$", discount) << "\n";
    receipt << formatReceiptLine("Tax:", "$", tax) << "\n";
    receipt << formatReceiptLine("Tip:", "$", tip) << "\n";
    receipt << "----------------------------------------\n";
    receipt << formatReceiptLine("TOTAL:", "$", total) << "\n";
    receipt << "----------------------------------------\n";
    receipt << "Member:   " << (member ? "Yes" : "No") << "\n";
    receipt << "Notes:    " << notes << "\n";
    receipt << "Loyalty Points: " << stars << "\n";
    receipt << "----------------------------------------\n";

    return receipt.str();
}

// Writes text to a file, either appending or replacing its contents.
// Takes fileName, text, and append; returns true if the write succeeded.
bool printToFile(const string &fileName, const string &text, bool append) {
    ofstream file(fileName, append ? ios::app : ios::trunc);

    if (!file) {
        return false;
    }

    file << text;

    if (!file) {
        return false;
    }

    file.close();
    return true;
}

// Runs checkout for one customer: reads membership and notes, calculates the
// discount, tax, tip, and total, prints the receipt, and appends it to
// receipt.txt. Takes customerName, orderSummary, and subtotal; returns the
// final total.
double checkoutCustomer(const string &customerName, const string &orderSummary, double subtotal) {
    cout << "\n------------------- CHECKOUT -------------------\n";

    bool member = askYesNo("Is member (y/n): ", "Invalid selection! Enter 'y' or 'n'.");
    string notes = getNotes();

    double discount = calculateDiscount(subtotal, member);
    double discountedSubtotal = subtotal - discount;
    double totalTax = calculateTax(discountedSubtotal);
    double tipAmount = getTip(discountedSubtotal);
    double total = discountedSubtotal + totalTax + tipAmount;

    int loyaltyPoints = calculateLoyaltyPoints(total);
    string stars = buildStars(loyaltyPoints);

    string receipt = buildReceipt(
        customerName, orderSummary,                    // customer and order
        subtotal, discount, totalTax,                  // money before total
        tipAmount, total,                              // final money
        member, notes, stars                           // receipt details
    );

    cout << receipt;

    if (!printToFile("receipt.txt", receipt, true)) {
        cout << "Warning: could not open receipt.txt. Receipt was not saved.\n";
    }

    return total;
}

// Formats one row of the daily inventory report.
// Takes the item name, starting stock, and amount sold; returns the row.
string formatInventoryLine(const string &name, int stock, int sold) {
    ostringstream line;

    line << left << setw(20) << name;
    line << right << setw(12) << stock;
    line << setw(12) << -sold;
    line << setw(12) << (stock - sold);
    line << "\n";

    return line.str();
}

// Builds the complete daily inventory report for all five items.
// Parameters are (name, stock, sold) per item, in menu order; returns the
// report text.
string buildInventoryReport(
    const string &name1, int stock1, int sold1,   // item 1
    const string &name2, int stock2, int sold2,   // item 2
    const string &name3, int stock3, int sold3,   // item 3
    const string &name4, int stock4, int sold4,   // item 4
    const string &name5, int stock5, int sold5    // item 5
) {
    ostringstream report;

    report << "Daily Inventory\n";
    report << left << setw(20) << "Item";
    report << right << setw(12) << "Start";
    report << setw(12) << "Change";
    report << setw(12) << "End";
    report << "\n";

    report << formatInventoryLine(name1, stock1, sold1);
    report << formatInventoryLine(name2, stock2, sold2);
    report << formatInventoryLine(name3, stock3, sold3);
    report << formatInventoryLine(name4, stock4, sold4);
    report << formatInventoryLine(name5, stock5, sold5);

    return report.str();
}

// Runs the coffee shop: loads the menu, serves each customer, then prints the
// daily totals and inventory report. Takes no parameters; returns 0 on
// success, 1 if menu.txt cannot be opened or is malformed.
int main()
{
    // Menu data from menu.txt: name, small price, per-size increase, and stock.
    string menuItem1, menuItem2, menuItem3, menuItem4, menuItem5;
    double menuItem1Price = 0.0, menuItem2Price = 0.0, menuItem3Price = 0.0, menuItem4Price = 0.0, menuItem5Price = 0.0;
    double menuItem1Increase = 0.0, menuItem2Increase = 0.0, menuItem3Increase = 0.0, menuItem4Increase = 0.0, menuItem5Increase = 0.0;
    int menuItem1Stock = 0, menuItem2Stock = 0, menuItem3Stock = 0, menuItem4Stock = 0, menuItem5Stock = 0;

    // Sold counts accumulate across all customers for the inventory report.
    int menuItem1Sold = 0, menuItem2Sold = 0, menuItem3Sold = 0, menuItem4Sold = 0, menuItem5Sold = 0;

    ifstream menuFile("menu.txt");

    if (!menuFile) {
        cout << "Error: could not open menu.txt\n";
        return 1;
    }

    // All five items must load, or the menu file is malformed.
    bool menuLoaded =
        loadMenuItem(menuFile, menuItem1, menuItem1Price, menuItem1Increase, menuItem1Stock) &&
        loadMenuItem(menuFile, menuItem2, menuItem2Price, menuItem2Increase, menuItem2Stock) &&
        loadMenuItem(menuFile, menuItem3, menuItem3Price, menuItem3Increase, menuItem3Stock) &&
        loadMenuItem(menuFile, menuItem4, menuItem4Price, menuItem4Increase, menuItem4Stock) &&
        loadMenuItem(menuFile, menuItem5, menuItem5Price, menuItem5Increase, menuItem5Stock);

    menuFile.close();

    if (!menuLoaded) {
        cout << "Error: menu.txt is malformed. Each line needs a name, a price, an increase, and a starting stock.\n";
        return 1;
    }

    cout << fixed << setprecision(2);

    // The menu never changes during the run, so build its text once.
    string menuText = buildMenuText(
        menuItem1, menuItem1Price, menuItem1Increase,   // item 1
        menuItem2, menuItem2Price, menuItem2Increase,   // item 2
        menuItem3, menuItem3Price, menuItem3Increase,   // item 3
        menuItem4, menuItem4Price, menuItem4Increase,   // item 4
        menuItem5, menuItem5Price, menuItem5Increase    // item 5
    );

    double grandTotalSales = 0.0;
    int totalCustomers = 0;

    while (true) {
        string customerName = askCustomerName();
        string orderSummary;
        double runningSubtotal = 0.0;
        int totalItemsOrdered = 0;

        // MAIN ORDERING LOOP
        while (true) {
            displayMenu(menuText);

            int menuChoice = getMenuChoice();

            if (menuChoice == 6) {
                if (totalItemsOrdered == 0) {
                    cout << "Your cart is empty! Please order at least one item before checking out.\n";
                    continue;
                }
                break;
            }

            // Choose this item's data based on the menu choice.
            string itemName;
            double basePrice = 0.0;
            double priceIncrease = 0.0;

            switch (menuChoice) {
                case 1: itemName = menuItem1; basePrice = menuItem1Price; priceIncrease = menuItem1Increase; break;
                case 2: itemName = menuItem2; basePrice = menuItem2Price; priceIncrease = menuItem2Increase; break;
                case 3: itemName = menuItem3; basePrice = menuItem3Price; priceIncrease = menuItem3Increase; break;
                case 4: itemName = menuItem4; basePrice = menuItem4Price; priceIncrease = menuItem4Increase; break;
                case 5: itemName = menuItem5; basePrice = menuItem5Price; priceIncrease = menuItem5Increase; break;
            }

            char sizeChoice = getSize(itemName);
            string sizeName = getSizeName(sizeChoice);
            int itemQuantity = getQuantity(sizeName, itemName);
            double itemCost = calculateItemPrice(basePrice, priceIncrease, sizeChoice) * itemQuantity;

            runningSubtotal += itemCost;
            totalItemsOrdered += itemQuantity;

            // Record the sale and add the item to the receipt summary.
            recordSale(
                menuChoice, itemQuantity,
                menuItem1Sold, menuItem2Sold, menuItem3Sold,
                menuItem4Sold, menuItem5Sold
            );
            addOrderLine(orderSummary, itemQuantity, sizeName, itemName, itemCost);

            cout << "--> Added to order!\n";
        }

        double total = checkoutCustomer(customerName, orderSummary, runningSubtotal);

        grandTotalSales += total;
        totalCustomers++;

        if (!askYesNo("\nIs there another customer? (y/n)",
                      "Invalid input. Please enter 'y' or 'n'.")) {
            break;
        }
    }

    cout << "\n\nTotal Customers: " << totalCustomers << "\n";
    cout << "Grand Total: " << grandTotalSales << "\n";

    // Every menu item is listed, including ones nobody ordered.
    string inventoryReport = buildInventoryReport(
        menuItem1, menuItem1Stock, menuItem1Sold,   // item 1
        menuItem2, menuItem2Stock, menuItem2Sold,   // item 2
        menuItem3, menuItem3Stock, menuItem3Sold,   // item 3
        menuItem4, menuItem4Stock, menuItem4Sold,   // item 4
        menuItem5, menuItem5Stock, menuItem5Sold    // item 5
    );

    cout << "\n" << inventoryReport;

    if (!printToFile("inventory.txt", inventoryReport, false)) {
        cout << "Warning: could not open inventory.txt. Inventory was not saved.\n";
    }

    return 0;
}
