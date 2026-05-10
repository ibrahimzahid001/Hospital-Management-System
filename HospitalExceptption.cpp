#include "HospitalException.h"

// 
// HospitalException.cpp
// Definitions for all exception classes
// 


// ------------------------------------------------------------
// SafeCopy()
// private helper to copy msg into message char array
// manual copy — no strncpy needed
// same style as StrCopy from your assignments
// ------------------------------------------------------------
static void SafeCopy(char* destination, const char* source, int maxLen) {
    int i = 0;
    while (i < maxLen - 1 && source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0'; // always null terminate
}


// 
// HospitalException — Base class definitions
// 

// default constructor — blank message
HospitalException::HospitalException() {
    message[0] = '\0';
}

// parametrized constructor
// safely copies msg into our char array using SafeCopy
// no strncpy — no warnings
HospitalException::HospitalException(const char* msg) {
    SafeCopy(message, msg, 200);
}

// returns the stored message
// virtual so derived classes can override if needed
const char* HospitalException::what() const {
    return message;
}

// virtual destructor — nothing to free
HospitalException::~HospitalException() {}


// 
// FileNotFoundException — definitions
// 

FileNotFoundException::FileNotFoundException()
    : HospitalException("Error: Required file could not be opened.") {
}

FileNotFoundException::FileNotFoundException(const char* msg)
    : HospitalException(msg) {
}


// 
// InsufficientFundsException — definitions
// 

InsufficientFundsException::InsufficientFundsException()
    : HospitalException("Error: Insufficient balance to complete this transaction.") {
}

InsufficientFundsException::InsufficientFundsException(const char* msg)
    : HospitalException(msg) {
}


// 
// InvalidInputException — definitions
// 

InvalidInputException::InvalidInputException()
    : HospitalException("Error: Invalid input provided.") {
}

InvalidInputException::InvalidInputException(const char* msg)
    : HospitalException(msg) {
}


// 
// SlotUnavailableException — definitions
// 

SlotUnavailableException::SlotUnavailableException()
    : HospitalException("Error: This time slot is already booked.") {
}

SlotUnavailableException::SlotUnavailableException(const char* msg)
    : HospitalException(msg) {
}