// Joshua Baron

// Purpose: The purpose of this program is to create an
// implementation of a hash table.

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "CovidDB.h"

using namespace std;

// Function to read the file.
void readFile(CovidDB &hashTable);

// Main function 
int main() {
    CovidDB hashTable(17); // Initialize the hash table
    string date, country; // string to store the date and country
    DataEntry tempEntry; // Temporary data entry
    DataEntry* getEntry; // Stores a pointer to a data entry
    int cases, deaths; // Ints to store the number of cases and deaths.
    int choice; // Choice for the interface
    bool exit = false; // Boolean to exit interface

    // Prints the interface
    while (exit == false) {
        cout << "Covid Tracker" << endl;
        cout << "Please choose the operation you want:" << endl;
        cout << "(1) Create the initial hash table" << endl;
        cout << "(2) Add a new data entry" << endl;
        cout << "(3) Get a data entry" << endl;
        cout << "(4) Remove a data entry" << endl;
        cout << "(5) Display the hash table" << endl;
        cout << "(0) Exit the system" << endl;
        cin >> choice;
        cout << endl;
        
        // Switch statement for the choices
        switch (choice) {
            case 1:
                // Creates hash table, and reads the file.
                readFile(hashTable); 
                break;
            case 2:
                // Adds a new data entry to the table
                cout << "Adding a new data entry..." << endl;
                cout << "Enter the date: ";
                cin >> date;
                cout << "Enter the country: ";
                cin >> country;
                cout << "Enter the cases: ";
                cin >> cases;
                cout << "Enter the deaths: ";
                cin >> deaths;
                tempEntry.setDate(date);
                tempEntry.setCountry(country);
                tempEntry.setCases(cases);
                tempEntry.setDeaths(deaths);
                hashTable.add(tempEntry);
                cout << endl;
                break;
            case 3:
                // Finds a country in the hash table
                cout << "Which country do you want from the table? ";
                cin >> country;
                getEntry = hashTable.get(country);
                if (getEntry == nullptr) {
                    cout << country << " not found in hash table" << endl << endl;
                    break;
                }
                cout << endl;
                cout << "Country " << getEntry->getCountry() << " Date: " << getEntry->getDate() << endl;
                cout << "Cases: " << getEntry->getCases() << " Deaths: " << getEntry->getDeaths() << endl << endl;
                break;
            case 4:
                // Removes a entry from the hash table
                cout << "Which country do you want to remove from the table? ";
                cin >> country;
                hashTable.remove(country);
                break;
            case 5:
                // Prints the hash table
                hashTable.print();
                break;
            case 0:
                // Exits the interface
                exit = true;
                break;
        }
    }
    return 0;
}

// Function to read the file and create
// the initial hash table
void readFile(CovidDB &hashTable) {
    vector<string> separateLine; // Vector to store string split
    string readLine; // String that stores the line in the file
    string dataString; // Stores the split string
    string date, country; // Strings that store the date and country
    int cases, deaths; // Integers that stores the cases and deaths
    DataEntry newEntry; // Stores a data entry
    fstream file; // fstream for the file

    // Opens the file
    file.open("WHO-COVID-data.csv");

    // If the file exists read it and create hash table
    if (file) {
        // While there are lines to read in the file extract 
        // the data from the lines and place in hash table.
        while (getline(file, readLine)) {
            vector<string> separateLine;
            stringstream str(readLine);
            // Splits the file line by commas to extract the data
            while (getline(str, dataString, ',')) {
                separateLine.push_back(dataString);
            }
            if (separateLine.size() > 1) {
                date = separateLine[0];
                country = separateLine[1];
                cases = stoi(separateLine[2]);
                deaths = stoi(separateLine[3]);
                newEntry.setDate(date);
                newEntry.setCountry(country);
                newEntry.setCases(cases);
                newEntry.setDeaths(deaths);
                hashTable.add(newEntry);
            }
        }
    } else {
        cout << "File did not open" << endl;
    } 
    file.close();  
}
