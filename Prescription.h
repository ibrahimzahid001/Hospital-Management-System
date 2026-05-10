#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

// ============================================================
// Prescription.h
// Represents medicines and notes written by a doctor
// for a completed appointment in HealthCare
// Stores: prescription id, appointment id, patient id,
//         doctor id, date, medicines, notes
// ============================================================

#include <iostream>
#include <string>
using namespace std;

class Prescription {
private:
    int    prescriptionId;
    int    appointmentId;
    int    patientId;
    int    doctorId;
    string date;           // format: DD-MM-YYYY
    char   medicines[500]; // format: Medicine Dosage;Medicine Dosage
    char   notes[300];     // doctor notes for the patient

    // private helper — safe char array copy
    // same style as StrCopy from your assignments
    void StrCopy(char* destination, const char* source, int maxLen);

public:

    // --------------------------------------------------------
    // Constructors & Destructor
    // --------------------------------------------------------
    Prescription();
    Prescription(int prescriptionId, int appointmentId, int patientId,
        int doctorId, string date,
        const char* medicines, const char* notes);
    Prescription(const Prescription& other);
    ~Prescription();

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------
    int         getPrescriptionId() const;
    int         getAppointmentId()  const;
    int         getPatientId()      const;
    int         getDoctorId()       const;
    string      getDate()           const;
    const char* getMedicines()      const;
    const char* getNotes()          const;

    // needed for Storage<T> compatibility
    int getId() const { return prescriptionId; }

    // --------------------------------------------------------
    // Setters
    // --------------------------------------------------------
    void setPrescriptionId(int prescriptionId);
    void setAppointmentId(int appointmentId);
    void setPatientId(int patientId);
    void setDoctorId(int doctorId);
    void setDate(string date);
    void setMedicines(const char* medicines);
    void setNotes(const char* notes);

    // --------------------------------------------------------
    // Display
    // shows prescription info in a clean formatted way
    // used in patient medical records and doctor history view
    // --------------------------------------------------------
    void displayInfo() const;
};

#endif