#include "Person.h"

// 
// Person.cpp
// Definitions for Person abstract base class
// 


// ------------------------------------------------------------
// Default constructor
// initializes everything to safe empty values
// ------------------------------------------------------------
Person::Person() {
    id = 0;
    name = "";
    contact = "";
    password = "";
}


// ------------------------------------------------------------
// Parametrized constructor
// directly sets all 4 attributes from arguments
// ------------------------------------------------------------
Person::Person(int id, string name, string contact, string password) {
    this->id = id;
    this->name = name;
    this->contact = contact;
    this->password = password;
}


// ------------------------------------------------------------
// Copy constructor
// copies all attributes from other Person obj
// ------------------------------------------------------------
Person::Person(const Person& other) {
    this->id = other.id;
    this->name = other.name;
    this->contact = other.contact;
    this->password = other.password;
}


// ------------------------------------------------------------
// Virtual destructor
// nothing to free here (string handles its own memory)
// but must exist as virtual for proper derived class cleanup
// ------------------------------------------------------------
Person::~Person() {}



int Person::getId() const {
    return id;
}

string Person::getName() const {
    return name;
}

string Person::getContact() const {
    return contact;
}

string Person::getPassword() const {
    return password;
}


// 
// Setters
// 

void Person::setId(int id) {
    this->id = id;
}

void Person::setName(string name) {
    this->name = name;
}

void Person::setContact(string contact) {
    this->contact = contact;
}

void Person::setPassword(string password) {
    this->password = password;
}

// 
// showMenu() and displayInfo() are pure virtual
// so they have NO definition here in Person.cpp
// They MUST be defined in Patient.cpp, Doctor.cpp, Admin.cpp
// 