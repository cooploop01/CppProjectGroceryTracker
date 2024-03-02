//  GroceryTracker
//
//  Cooper Ring
//
//  2/25/24
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;  // To store item frequencies
    
    void askToGoBackToMenu() {
        char choice;
        cout << "\nDo you want to go back to the menu? (Y/N): ";  // To make the visuals not as repetitive
        cin >> choice;

        if (toupper(choice) == 'N') { // n or N will work as an exit. Any other character or int will take user back to the menu
            saveDataToFile();
            cout << "\nData saved. Exiting program.\n";
            cout << "Goodbye!\n";
            exit(0);
        }
    }

public:
    void readDataFromFile() {
        // Read data from the input file and populate itemFrequency map
        ifstream inputFile("CS210_Project_Three_Input_File.txt");
        string itemName;

        while (inputFile >> itemName) {
            itemFrequency[itemName]++;
        }

        inputFile.close();
    }

    void menuOptionOne() {
        // Prompt user to input the item and return its frequency
        cout << "\nEnter the item you wish to search for: ";
        string userInput;
        cin.ignore();  // Ignore any lingering newline characters
        getline(cin, userInput);

        auto it = itemFrequency.find(userInput);
        if (it != itemFrequency.end()) {
            cout << "\nFrequency of " << userInput << ": " << it->second << " times\n";
        } else {
            cout << "\nItem not found.\n";
        }
        askToGoBackToMenu();
    }


    void menuOptionTwo() {
        // Print the list with numbers that represent the frequency of all items
        for (const auto& entry : itemFrequency) {
            cout << entry.first << " " << entry.second << endl;
        }
        askToGoBackToMenu();
    }

    void menuOptionThree() {
        // Print the frequency information in the form of a histogram
        for (const auto& entry : itemFrequency) {
            cout << entry.first << " ";
            for (int i = 0; i < entry.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
        askToGoBackToMenu();
    }

    void saveDataToFile() {
        // Save the item frequencies to the backup file (frequency.dat)
        ofstream outputFile("frequency.dat");

        for (const auto& entry : itemFrequency) {
            outputFile << entry.first << " " << entry.second << endl;
        }

        outputFile.close();
    }
};

int main() {
    GroceryTracker tracker;
    tracker.readDataFromFile();

    int choice;

    do {
        // Display menu options
        cout << "\nWelcome to Corner Grocer Item Tracking System\n"; // User-friendly Formatting
        cout << "--------------------------------------------\n";
        cout << "Menu:\n";
        cout << "1. Search for an item\n";
        cout << "2. Display item frequencies\n";
        cout << "3. Display item frequencies as a histogram\n";
        cout << "4. Exit\n";
        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                tracker.menuOptionOne();
                break;
            case 2:
                tracker.menuOptionTwo();
                break;
            case 3:
                tracker.menuOptionThree();
                break;
            case 4:
                tracker.saveDataToFile();
                cout << "\nData saved. Exiting program.\n";
                cout << "Goodbye!\n";  // Goodbye message
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}

