// Joshua Baron
// CovidDB.cpp

#include "CovidDB.h"
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Compares dateOne with dateTwo returns true 
// if dateOne happens later than dateTwo
bool compareDates(string dateOne, string dateTwo);

// Uses the hash function to hash the country name.
int CovidDB::hashData(string country) {
    int sum = 0;
    // Computes the index using the hash function.
    for (int i = 0; i < (int)country.length(); i++) {
        sum += (i * (int(country[i])));
    }
    sum = sum % size;
    return sum;
}

// Adds a data entry to the hash table
bool CovidDB::add(DataEntry entry) {
    // Hash the entry using the country name.
    int hash = hashData(entry.getCountry());
    bool alreadyInTable = false; // says if the entry is already in the table.

    /*
    Checks if the country is already in the table
    If it is compare the dates of the new entry and old entry
    and add the new cases and deaths to the old
    */
    for (int i = 0; i < (int)table[hash].size(); i++) {
        if (table[hash][i].getCountry() == entry.getCountry()) {
            alreadyInTable = true;
            if (compareDates(entry.getDate(), table[hash][i].getDate())) {
                table[hash][i].setDate(entry.getDate());
            }
            table[hash][i].setCases(table[hash][i].getCases() + entry.getCases());
            table[hash][i].setDeaths(table[hash][i].getDeaths() + entry.getDeaths());
        }
    }
    // If the entry is not in the table 
    // Push the entry into the back of the vector.
    if (alreadyInTable != true) {
        table[hash].push_back(entry);
    }
    return alreadyInTable;
}

// Finds a country in the hash table.
// Returns nullptr if not found.
DataEntry* CovidDB::get(string country) {
    DataEntry *getData = nullptr;
    // Hashes the country input
    int hash = hashData(country);
    // Searches through the table for the country
    // If found, return the data entry for the country.
    for (int i = 0; i < (int)table[hash].size(); i++) {
        if (table[hash][i].getCountry() == country) {
            getData = &table[hash][i];
        }
    }
    return getData;
}

// Removes a country from the hash table
void CovidDB::remove(string country) {
    // Hashes the country input
    int hash = hashData(country);
    // Looks through the table for the country
    // If found, erase the data entry from the table.
    for (int i = 0; i < (int)table[hash].size(); i++) {
        if (table[hash][i].getCountry() == country) {
            table[hash].erase(table[hash].begin() + i);
            cout << country << " has been deleted." << endl << endl;
            return;
        }
    }
    cout << country << " was not found in hash table" << endl << endl;
}

// Prints the contents of the hash table.
void CovidDB::print() {
    for (int i = 0; i < (int)table.size(); i++) {
        for (int j = 0; j < (int)table[i].size(); j++) {
            cout << "Date: " << table[i][j].getDate() << " Country: " << table[i][j].getCountry();
            cout << " Cases: " << table[i][j].getCases() << " Deaths: " << table[i][j].getDeaths() << endl;
        }
    }
    cout << endl;
}

// Compares two dates
bool compareDates(string dateOne, string dateTwo) {
    bool isGreater = false;
    int monthOne; // Month of first date
    int dayOne; // Day of first date
    int yearOne; // Year of first date
    int monthTwo; // Month of second date
    int dayTwo; // Day of second date
    int yearTwo; // Year of second date
    vector<string> splitDate; // Vector to store the string splits
    string split; // String to store the string split
    stringstream strOne(dateOne); // String stream for first date
    stringstream strTwo(dateTwo); // String stream for second date
  
    // Splits dateOne into month, day, year by '/'
    while (getline(strOne, split, '/')) {
        splitDate.push_back(split);
    }
    monthOne = stoi(splitDate[0]);
    dayOne = stoi(splitDate[1]);
    yearOne = stoi(splitDate[2]);

    splitDate.clear();
    
    // Splits dateTwo into month, day, year by '/'
    while (getline(strTwo, split, '/')) {
        splitDate.push_back(split);
    }
    monthTwo = stoi(splitDate[0]);
    dayTwo = stoi(splitDate[1]);
    yearTwo = stoi(splitDate[2]);

    // Compares the dates first checking year then
    // checking month, and lastly checking day.
    if (yearOne > yearTwo) {
        isGreater = true;
    } else if (yearTwo == yearOne) {
        if (monthOne > monthTwo) {
            isGreater = true;
        } else if (monthOne == monthTwo) {
            if (dayOne > dayTwo) {
                isGreater = true;
            }
        }
    }
    return isGreater;
}
