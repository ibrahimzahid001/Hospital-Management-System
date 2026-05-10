#include "Doctor.h"

// 
// Doctor.cpp
// Definitions for Doctor class
// 


// ------------------------------------------------------------
// Default constructor
// initializes everything to safe empty values
// fee starts at 0.0
// ------------------------------------------------------------
Doctor::Doctor() : Person() {
    specialization = "";
    fee = 0.0f;
}


// ------------------------------------------------------------
// Parametrized constructor
// passes common attributes up to Person via initializer list
// then sets Doctor specific attributes
// ------------------------------------------------------------
Doctor::Doctor(int id, string name, string specialization,
    string contact, string password, float fee)
    : Person(id, name, contact, password) {

    this->specialization = specialization;
    this->fee = fee;
}


// ------------------------------------------------------------
// Copy constructor
// passes other up to Person copy constructor
// then copies Doctor specific attributes
// ------------------------------------------------------------
Doctor::Doctor(const Doctor& other) : Person(other) {
    this->specialization = other.specialization;
    this->fee = other.fee;
}


// ------------------------------------------------------------
// Destructor
// string and float clean themselves up
// nothing extra to free here
// ------------------------------------------------------------
Doctor::~Doctor() {}


// 
// Getters
// 

string Doctor::getSpecialization() const {
    return specialization;
}

float Doctor::getFee() const {
    return fee;
}


// 
// Setters
// 

void Doctor::setSpecialization(string specialization) {
    this->specialization = specialization;
}

void Doctor::setFee(float fee) {
    this->fee = fee;
}


// 
// Operator Overloads
// 


bool Doctor::operator==(const Doctor& other) const {
    return this->id == other.id;
}


// ------------------------------------------------------------
// << operator (friend)
// formatted console output for a Doctor object
// used when displaying doctor info on screen
// ------------------------------------------------------------
ostream& operator<<(ostream& output, const Doctor& source) {
    output << "----------------------------" << endl;
    output << "Doctor ID      : " << source.id << endl;
    output << "Name           : " << source.name << endl;
    output << "Specialization : " << source.specialization << endl;
    output << "Contact        : " << source.contact << endl;
    output << "Fee            : PKR " << source.fee << endl;
    output << "----------------------------" << endl;
    return output; // for cascading like cout << d1 << d2
}




// ------------------------------------------------------------
// showMenu()
// displays the doctor menu on screen
// actual menu LOGIC will be handled in main via functions
// this just prints the options
// ------------------------------------------------------------
void Doctor::showMenu() {
    cout << "\n================================================" << endl;
    cout << "Welcome, Dr. " << name << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "================================================" << endl;
    cout << "1. View Today's Appointments" << endl;
    cout << "2. Mark Appointment Complete" << endl;
    cout << "3. Mark Appointment No-Show" << endl;
    cout << "4. Write Prescription" << endl;
    cout << "5. View Patient Medical History" << endl;
    cout << "6. Logout" << endl;
    cout << "================================================" << endl;
    cout << "Enter your choice: ";
}


// ------------------------------------------------------------
// displayInfo()
// displays basic doctor info — used in admin panel
// and when patient searches by specialization
// ------------------------------------------------------------
void Doctor::displayInfo() const {
    cout << "ID: " << id << " | ";
    cout << "Name: Dr. " << name << " | ";
    cout << "Specialization: " << specialization << " | ";
    cout << "Contact: " << contact << " | ";
    cout << "Fee: PKR " << fee << endl;
}