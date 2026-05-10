#include "Bill.h"

// 
// Bill.cpp
// Definitions for Bill class
// 


// ------------------------------------------------------------
// Default constructor
// initializes everything to safe empty values
// status defaults to unpaid since every new
// bill starts as unpaid
// ------------------------------------------------------------
Bill::Bill() {
    billId = 0;
    patientId = 0;
    appointmentId = 0;
    amount = 0.0f;
    status = "unpaid";
    date = "";
}


// ------------------------------------------------------------
// Parametrized constructor
// directly sets all attributes from arguments
// ------------------------------------------------------------
Bill::Bill(int billId, int patientId, int appointmentId,
    float amount, string status, string date) {
    this->billId = billId;
    this->patientId = patientId;
    this->appointmentId = appointmentId;
    this->amount = amount;
    this->status = status;
    this->date = date;
}


// ------------------------------------------------------------
// Copy constructor
// copies all attributes from other Bill obj
// ------------------------------------------------------------
Bill::Bill(const Bill& other) {
    this->billId = other.billId;
    this->patientId = other.patientId;
    this->appointmentId = other.appointmentId;
    this->amount = other.amount;
    this->status = other.status;
    this->date = other.date;
}


// ------------------------------------------------------------
// Destructor
// string handles its own memory
// nothing extra to free here
// ------------------------------------------------------------
Bill::~Bill() {}


// 
// Getters
// 

int Bill::getBillId() const {
    return billId;
}

int Bill::getPatientId() const {
    return patientId;
}

int Bill::getAppointmentId() const {
    return appointmentId;
}

float Bill::getAmount() const {
    return amount;
}

string Bill::getStatus() const {
    return status;
}

string Bill::getDate() const {
    return date;
}


// 
// Setters
// 

void Bill::setBillId(int billId) {
    this->billId = billId;
}

void Bill::setPatientId(int patientId) {
    this->patientId = patientId;
}

void Bill::setAppointmentId(int appointmentId) {
    this->appointmentId = appointmentId;
}

void Bill::setAmount(float amount) {
    this->amount = amount;
}

void Bill::setStatus(string status) {
    this->status = status;
}

void Bill::setDate(string date) {
    this->date = date;
}


// 
// displayInfo()
// displays bill info in a clean formatted way
// used in patient menu (view bills) and admin panel
// shows OVERDUE tag if needed — that logic is in main
// 
void Bill::displayInfo() const {
    cout << "----------------------------" << endl;
    cout << "Bill ID        : " << billId << endl;
    cout << "Appointment ID : " << appointmentId << endl;
    cout << "Amount         : PKR " << amount << endl;
    cout << "Status         : " << status << endl;
    cout << "Date           : " << date << endl;
    cout << "----------------------------" << endl;
}