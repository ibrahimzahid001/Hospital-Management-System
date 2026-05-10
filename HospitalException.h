#ifndef HOSPITALEXCEPTION_H
#define HOSPITALEXCEPTION_H

// ============================================================
// HospitalException.h
// Base exception class + all custom exceptions for HealthCare
// All exceptions inherit from HospitalException
// ============================================================

class HospitalException {
protected:
    char message[200]; // stores the error message

public:
    // default constructor — empty message
    HospitalException();

    // parametrized constructor — sets the message
    HospitalException(const char* msg);

    // virtual so derived classes can override it
    // returns the error message
    virtual const char* what() const;

    // virtual destructor — good practice for base classes
    virtual ~HospitalException();
};


// ============================================================
// Thrown when a required .txt file cannot be opened on startup
// ============================================================
class FileNotFoundException : public HospitalException {
public:
    FileNotFoundException();
    FileNotFoundException(const char* msg);
};


// ============================================================
// Thrown when patient balance is less than required amount
// ============================================================
class InsufficientFundsException : public HospitalException {
public:
    InsufficientFundsException();
    InsufficientFundsException(const char* msg);
};


// ============================================================
// Thrown when user input fails validation checks
// ============================================================
class InvalidInputException : public HospitalException {
public:
    InvalidInputException();
    InvalidInputException(const char* msg);
};


// ============================================================
// Thrown when patient tries to book an already occupied slot
// ============================================================
class SlotUnavailableException : public HospitalException {
public:
    SlotUnavailableException();
    SlotUnavailableException(const char* msg);
};

#endif