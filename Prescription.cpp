#include "Prescription.h"

// Prescription.cpp
// Definitions for Prescription class


// ------------------------------------------------------------
// StrCopy()
// private helper function
// copies source into destination safely
// stops at maxLen to prevent buffer overflow
// same style as StrCopy from your assignments
// ------------------------------------------------------------
void Prescription::StrCopy(char* destination,
    const char* source,
    int maxLen) {
    int i = 0;
    while (i < maxLen - 1 && source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0'; // always null terminate
}


// ------------------------------------------------------------
// Default constructor
// initializes everything to safe empty values
// medicines and notes are char arrays so we null them out
// ------------------------------------------------------------
Prescription::Prescription() {
    prescriptionId = 0;
    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    date = "";
    medicines[0] = '\0';
    notes[0] = '\0';
}


// ------------------------------------------------------------
// Parametrized constructor
// directly sets all attributes from arguments
// StrCopy used for char arrays with size limit
// to prevent buffer overflow as project requires
// ------------------------------------------------------------
Prescription::Prescription(int prescriptionId, int appointmentId,
    int patientId, int doctorId, string date,
    const char* medicines, const char* notes) {
    this->prescriptionId = prescriptionId;
    this->appointmentId = appointmentId;
    this->patientId = patientId;
    this->doctorId = doctorId;
    this->date = date;

    // copy medicines safely — max 500 chars
    StrCopy(this->medicines, medicines, 500);

    // copy notes safely — max 300 chars
    StrCopy(this->notes, notes, 300);
}


// ------------------------------------------------------------
// Copy constructor
// copies all attributes from other Prescription obj
// StrCopy used for char arrays
// ------------------------------------------------------------
Prescription::Prescription(const Prescription& other) {
    this->prescriptionId = other.prescriptionId;
    this->appointmentId = other.appointmentId;
    this->patientId = other.patientId;
    this->doctorId = other.doctorId;
    this->date = other.date;

    StrCopy(this->medicines, other.medicines, 500);
    StrCopy(this->notes, other.notes, 300);
}


// ------------------------------------------------------------
// Destructor
// char arrays are stack allocated — no heap to free
// string handles its own memory
// nothing extra to free here
// ------------------------------------------------------------
Prescription::~Prescription() {}


// 
// Getters
// 

int Prescription::getPrescriptionId() const {
    return prescriptionId;
}

int Prescription::getAppointmentId() const {
    return appointmentId;
}

int Prescription::getPatientId() const {
    return patientId;
}

int Prescription::getDoctorId() const {
    return doctorId;
}

string Prescription::getDate() const {
    return date;
}

const char* Prescription::getMedicines() const {
    return medicines;
}

const char* Prescription::getNotes() const {
    return notes;
}


// 
// Setters
// 

void Prescription::setPrescriptionId(int prescriptionId) {
    this->prescriptionId = prescriptionId;
}

void Prescription::setAppointmentId(int appointmentId) {
    this->appointmentId = appointmentId;
}

void Prescription::setPatientId(int patientId) {
    this->patientId = patientId;
}

void Prescription::setDoctorId(int doctorId) {
    this->doctorId = doctorId;
}

void Prescription::setDate(string date) {
    this->date = date;
}

// copies medicines string safely into our char array
// truncates silently if longer than 499 chars as project requires
void Prescription::setMedicines(const char* medicines) {
    StrCopy(this->medicines, medicines, 500);
}

// copies notes string safely into our char array
// truncates silently if longer than 299 chars as project requires
void Prescription::setNotes(const char* notes) {
    StrCopy(this->notes, notes, 300);
}


// 
// displayInfo()
// shows prescription info in clean formatted way
// used in patient medical records and doctor history view
// 
void Prescription::displayInfo() const {
    cout << "----------------------------" << endl;
    cout << "Prescription ID : " << prescriptionId << endl;
    cout << "Appointment ID  : " << appointmentId << endl;
    cout << "Date            : " << date << endl;
    cout << "Medicines       : " << medicines << endl;
    cout << "Notes           : " << notes << endl;
    cout << "----------------------------" << endl;
}