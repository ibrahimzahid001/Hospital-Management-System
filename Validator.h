#ifndef VALIDATOR_H
#define VALIDATOR_H

// ============================================================
// Validator.h
// The ONLY class permitted to contain input validation logic
// All methods are static — call as Validator::methodName()
// No object instantiation needed
// Validates: dates, time slots, contacts, passwords,
//            floats, menu choices, IDs
// ============================================================

#include <iostream>
#include <string>
using namespace std;

class Validator {
public:

    // --------------------------------------------------------
    // isValidDate()
    // validates date in DD-MM-YYYY format
    // day must be 01-31, month 01-12
    // year must be current year or later
    // returns true if valid, false if not
    // --------------------------------------------------------
    static bool isValidDate(const string& date);


    // --------------------------------------------------------
    // isValidTimeSlot()
    // checks if given slot is one of the 8 fixed daily slots:
    // 09:00 10:00 11:00 12:00 13:00 14:00 15:00 16:00
    // returns true if valid, false if not
    // --------------------------------------------------------
    static bool isValidTimeSlot(const string& slot);


    // --------------------------------------------------------
    // isValidContact()
    // contact must be exactly 11 digits, all numeric
    // returns true if valid, false if not
    // --------------------------------------------------------
    static bool isValidContact(const string& contact);


    // --------------------------------------------------------
    // isValidPassword()
    // password must be minimum 6 characters
    // returns true if valid, false if not
    // --------------------------------------------------------
    static bool isValidPassword(const string& password);


    // --------------------------------------------------------
    // isValidFloat()
    // checks if value is a positive float greater than 0
    // returns true if valid, false if not
    // --------------------------------------------------------
    static bool isValidFloat(float value);


    // --------------------------------------------------------
    // isValidMenuChoice()
    // checks if choice is within valid range (min to max)
    // returns true if valid, false if not
    // --------------------------------------------------------
    static bool isValidMenuChoice(int choice, int min, int max);


    // --------------------------------------------------------
    // isValidId()
    // checks if ID is a positive integer greater than 0
    // returns true if valid, false if not
    // --------------------------------------------------------
    static bool isValidId(int id);


    // --------------------------------------------------------
    // toLower()
    // converts a string to lowercase manually
    // uses tolower() on each character as project requires
    // used for case-insensitive specialization search
    // --------------------------------------------------------
    static string toLower(const string& str);


    // --------------------------------------------------------
    // getCurrentYear()
    // gets current year using ctime
    // used inside isValidDate() for year validation
    // --------------------------------------------------------
    static int getCurrentYear();
};

#endif