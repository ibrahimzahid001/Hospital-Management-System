#include "Admin.h"

// ============================================================
// Admin.cpp
// Definitions for Admin class
// ============================================================


// ------------------------------------------------------------
// Default constructor
// Person() default constructor handles everything
// Admin has no extra attributes to initialize
// ------------------------------------------------------------
Admin::Admin() : Person() {}


// ------------------------------------------------------------
// Parametrized constructor
// passes everything up to Person via initializer list
// Admin has no extra attributes so nothing extra to set
// ------------------------------------------------------------
Admin::Admin(int id, string name, string contact, string password)
    : Person(id, name, contact, password) {
}


// ------------------------------------------------------------
// Copy constructor
// Person copy constructor handles everything
// ------------------------------------------------------------
Admin::Admin(const Admin& other) : Person(other) {}


// ------------------------------------------------------------
// Destructor
// Person destructor handles everything
// nothing extra to free here
// ------------------------------------------------------------
Admin::~Admin() {}


// ============================================================
// Pure Virtual Implementations
// ============================================================

// ------------------------------------------------------------
// showMenu()
// displays the admin panel menu on screen
// actual menu LOGIC will be handled in main via functions
// this just prints the options
// ------------------------------------------------------------
void Admin::showMenu() {
    cout << "\n==========================" << endl;
    cout << "Admin Panel -- HealthCare" << endl;
    cout << "Welcome, " << name << endl;
    cout << "==========================" << endl;
    cout << "1.  Add Doctor" << endl;
    cout << "2.  Remove Doctor" << endl;
    cout << "3.  View All Patients" << endl;
    cout << "4.  View All Doctors" << endl;
    cout << "5.  View All Appointments" << endl;
    cout << "6.  View Unpaid Bills" << endl;
    cout << "7.  Discharge Patient" << endl;
    cout << "8.  View Security Log" << endl;
    cout << "9.  Generate Daily Report" << endl;
    cout << "10. Logout" << endl;
    cout << "==========================" << endl;
    cout << "Enter your choice: ";
}


// ------------------------------------------------------------
// displayInfo()
// displays basic admin info
// kept simple since only one admin exists
// ------------------------------------------------------------
void Admin::displayInfo() const {
    cout << "----------------------------" << endl;
    cout << "Admin ID  : " << id << endl;
    cout << "Name      : " << name << endl;
    cout << "Contact   : " << contact << endl;
    cout << "----------------------------" << endl;
}