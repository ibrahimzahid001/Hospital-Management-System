#define _CRT_SECURE_NO_WARNINGS
#include "Validator.h"
#include <ctime>    // for time(), localtime() — to get current year
#include <cctype>   // for tolower(), isdigit()


// Definitions for Validator class
// All methods are static


// ------------------------------------------------------------
// getCurrentYear()
// gets the current year using ctime
// used inside isValidDate() for year validation
// ------------------------------------------------------------
int Validator::getCurrentYear() {
    time_t now = time(0);       // get current time as time_t
    tm* timePtr = localtime(&now); // convert to local time struct
    return 1900 + timePtr->tm_year;   // tm_year is years since 1900
}


// ------------------------------------------------------------
// isValidDate()
// validates date string in DD-MM-YYYY format
// checks:
//   - correct length (10 chars)
//   - correct format with dashes at positions 2 and 5
//   - day between 01 and 31
//   - month between 01 and 12
//   - year is current year or later
// ------------------------------------------------------------
bool Validator::isValidDate(const string& date) {
    // must be exactly 10 characters: DD-MM-YYYY
    if (date.length() != 10) {
        return false;
    }

    // dashes must be at positions 2 and 5
    if (date[2] != '-' || date[5] != '-') {
        return false;
    }

    // all other positions must be digits
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // skip dashes
        if (!isdigit(date[i])) {
            return false;
        }
    }

    // extract day, month, year as integers
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // validate ranges
    if (day < 1 || day > 31) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (year < getCurrentYear()) {
        return false;
    }

    return true;
}


// ------------------------------------------------------------
// isValidTimeSlot()
// checks if given slot matches one of the 8 fixed daily slots
// 09:00 10:00 11:00 12:00 13:00 14:00 15:00 16:00
// ------------------------------------------------------------
bool Validator::isValidTimeSlot(const string& slot) {
    // all 8 valid time slots stored in array
    string validSlots[8] = {
        "09:00", "10:00", "11:00", "12:00",
        "13:00", "14:00", "15:00", "16:00"
    };

    // check against each valid slot
    for (int i = 0; i < 8; i++) {
        if (slot == validSlots[i]) {
            return true;
        }
    }
    return false;
}


// ------------------------------------------------------------
// isValidContact()
// contact must be exactly 11 digits, all numeric
// no spaces, no dashes, no letters allowed
// ------------------------------------------------------------
bool Validator::isValidContact(const string& contact) {
    // must be exactly 11 characters
    if (contact.length() != 11) {
        return false;
    }

    // every character must be a digit
    for (int i = 0; i < (int)contact.length(); i++) {
        if (!isdigit(contact[i])) {
            return false;
        }
    }

    return true;
}


// ------------------------------------------------------------
// isValidPassword()
// password must be at least 6 characters long
// ------------------------------------------------------------
bool Validator::isValidPassword(const string& password) {
    if (password.length() < 6) {
        return false;
    }
    return true;
}


// ------------------------------------------------------------
// isValidFloat()
// value must be a positive float greater than 0
// used for consultation fee and top up amount validation
// ------------------------------------------------------------
bool Validator::isValidFloat(float value) {
    if (value <= 0.0f) {
        return false;
    }
    return true;
}


// ------------------------------------------------------------
// isValidMenuChoice()
// checks if choice falls within valid range (min to max)
// used for all menu input validation
// ------------------------------------------------------------
bool Validator::isValidMenuChoice(int choice, int min, int max) {
    if (choice < min || choice > max) {
        return false;
    }
    return true;
}


// ------------------------------------------------------------
// isValidId()
// ID must be a positive integer greater than 0
// ------------------------------------------------------------
bool Validator::isValidId(int id) {
    if (id <= 0) {
        return false;
    }
    return true;
}


// ------------------------------------------------------------
// toLower()
// converts string to lowercase manually
// uses tolower() on each character one by one
// as project requires — case insensitive specialization search
// e.g. "Cardiology" and "cardiology" both match
// ------------------------------------------------------------
string Validator::toLower(const string& str) {
    string result = str;
    for (int i = 0; i < (int)result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}