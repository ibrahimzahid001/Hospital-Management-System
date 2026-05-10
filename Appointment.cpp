#include "Appointment.h"

// 
// Appointment.cpp
// Definitions for Appointment class
// 


// ------------------------------------------------------------
// Default constructor
// initializes everything to safe empty values
// status defaults to pending since every new 
// appointment starts as pending
// ------------------------------------------------------------
Appointment::Appointment() {
    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    date = "";
    timeSlot = "";
    status = "pending";
}


// ------------------------------------------------------------
// Parametrized constructor
// directly sets all attributes from arguments
// ------------------------------------------------------------
Appointment::Appointment(int appointmentId, int patientId, int doctorId,
    string date, string timeSlot, string status) {
    this->appointmentId = appointmentId;
    this->patientId = patientId;
    this->doctorId = doctorId;
    this->date = date;
    this->timeSlot = timeSlot;
    this->status = status;
}


// ------------------------------------------------------------
// Copy constructor
// copies all attributes from other Appointment obj
// ------------------------------------------------------------
Appointment::Appointment(const Appointment& other) {
    this->appointmentId = other.appointmentId;
    this->patientId = other.patientId;
    this->doctorId = other.doctorId;
    this->date = other.date;
    this->timeSlot = other.timeSlot;
    this->status = other.status;
}


// ------------------------------------------------------------
// Destructor
// string handles its own memory
// nothing extra to free here
// ------------------------------------------------------------
Appointment::~Appointment() {}


// ============================================================
// Getters
// ============================================================

int Appointment::getAppointmentId() const {
    return appointmentId;
}

int Appointment::getPatientId() const {
    return patientId;
}

int Appointment::getDoctorId() const {
    return doctorId;
}

string Appointment::getDate() const {
    return date;
}

string Appointment::getTimeSlot() const {
    return timeSlot;
}

string Appointment::getStatus() const {
    return status;
}


// 
// Setters
// 

void Appointment::setAppointmentId(int appointmentId) {
    this->appointmentId = appointmentId;
}

void Appointment::setPatientId(int patientId) {
    this->patientId = patientId;
}

void Appointment::setDoctorId(int doctorId) {
    this->doctorId = doctorId;
}

void Appointment::setDate(string date) {
    this->date = date;
}

void Appointment::setTimeSlot(string timeSlot) {
    this->timeSlot = timeSlot;
}

void Appointment::setStatus(string status) {
    this->status = status;
}


// 
// Operator Overloads
// 


bool Appointment::operator==(const Appointment& other) const {
    // if either appointment is cancelled — no conflict
    if (this->status == "cancelled" || other.status == "cancelled") {
        return false;
    }

    // all three must match for a conflict to exist
    return (this->doctorId == other.doctorId &&
        this->date == other.date &&
        this->timeSlot == other.timeSlot);
}


// ------------------------------------------------------------
// << operator (friend)
// formatted console output for an Appointment object
// used in patient menu, doctor menu and admin panel
// ------------------------------------------------------------
ostream& operator<<(ostream& output, const Appointment& source) {
    output << "----------------------------" << endl;
    output << "Appointment ID : " << source.appointmentId << endl;
    output << "Patient ID     : " << source.patientId << endl;
    output << "Doctor ID      : " << source.doctorId << endl;
    output << "Date           : " << source.date << endl;
    output << "Time Slot      : " << source.timeSlot << endl;
    output << "Status         : " << source.status << endl;
    output << "----------------------------" << endl;
    return output; // for cascading like cout << a1 << a2
}