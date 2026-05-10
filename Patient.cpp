#include "Patient.h"

// 
// Patient.cpp
// Definitions for Patient class
// 


// ------------------------------------------------------------
// Default constructor
// initializes everything to safe empty values
// balance starts at 0, age at 0, gender at 'M' as default
// ------------------------------------------------------------
Patient::Patient() : Person() {
    age = 0;
    gender = 'M';
    balance = 0.0f;
}


// ------------------------------------------------------------
// Parametrized constructor
// passes common attributes up to Person via initializer list
// then sets Patient specific attributes
// ------------------------------------------------------------
Patient::Patient(int id, string name, int age, char gender,
    string contact, string password, float balance)
    : Person(id, name, contact, password) {

    this->age = age;
    this->gender = gender;
    this->balance = balance;
}


// ------------------------------------------------------------
// Copy constructor
// passes other up to Person copy constructor
// then copies Patient specific attributes
// ------------------------------------------------------------
Patient::Patient(const Patient& other) : Person(other) {
    this->age = other.age;
    this->gender = other.gender;
    this->balance = other.balance;
}


// ------------------------------------------------------------
// Destructor
// string and primitive types clean themselves up
// nothing extra to free here
// ------------------------------------------------------------
Patient::~Patient() {}


// 
// Getters
// 

int Patient::getAge() const {
    return age;
}

char Patient::getGender() const {
    return gender;
}

float Patient::getBalance() const {
    return balance;
}


// 
// Setters
// 

void Patient::setAge(int age) {
    this->age = age;
}

void Patient::setGender(char gender) {
    this->gender = gender;
}

void Patient::setBalance(float balance) {
    this->balance = balance;
}


// 
// Operator Overloads
// 

// ------------------------------------------------------------
// += operator
// adds amount to patient balance (used in top up and refunds)
// returns *this for chaining
// ------------------------------------------------------------
Patient& Patient::operator+=(float amount) {
    balance += amount;
    return *this;
}


// ------------------------------------------------------------
// -= operator
// deducts amount from patient balance (used in booking/paying)
// returns *this for chaining
// ------------------------------------------------------------
Patient& Patient::operator-=(float amount) {
    balance -= amount;
    return *this;
}


// ------------------------------------------------------------
// == operator
// compares two patients by their ID
// used to find a specific patient in Storage<Patient>
// ------------------------------------------------------------
bool Patient::operator==(const Patient& other) const {
    return this->id == other.id;
}


// ------------------------------------------------------------
// << operator (friend)
// used when displaying patient info on screen
// format matches project requirement
// ------------------------------------------------------------
ostream& operator<<(ostream& output, const Patient& source) {
    output << "----------------------------" << endl;
    output << "Patient ID  : " << source.id << endl;
    output << "Name        : " << source.name << endl;
    output << "Age         : " << source.age << endl;
    output << "Gender      : " << source.gender << endl;
    output << "Contact     : " << source.contact << endl;
    output << "Balance     : PKR " << source.balance << endl;
    output << "----------------------------" << endl;
    return output; // for cascading like cout << p1 << p2
}



// ------------------------------------------------------------
// showMenu()
// displays the patient menu on screen
// actual menu LOGIC will be handled in main via functions
// this just prints the options
// ------------------------------------------------------------
void Patient::showMenu() {
    cout << "\n========================" << endl;
    cout << "Welcome, " << name << endl;
    cout << "Balance: PKR " << balance << endl;
    cout << "========================" << endl;
    cout << "1. Book Appointment" << endl;
    cout << "2. Cancel Appointment" << endl;
    cout << "3. View My Appointments" << endl;
    cout << "4. View My Medical Records" << endl;
    cout << "5. View My Bills" << endl;
    cout << "6. Pay Bill" << endl;
    cout << "7. Top Up Balance" << endl;
    cout << "8. Logout" << endl;
    cout << "========================" << endl;
    cout << "Enter your choice: ";
}


// ------------------------------------------------------------
// displayInfo()
// displays basic patient info — used in admin panel
// ------------------------------------------------------------
void Patient::displayInfo() const {
    cout << left;
    cout << "ID: " << id << " | ";
    cout << "Name: " << name << " | ";
    cout << "Age: " << age << " | ";
    cout << "Gender: " << gender << " | ";
    cout << "Contact: " << contact << " | ";
    cout << "Balance: PKR " << balance << endl;
}