#ifndef BILL_H
#define BILL_H

// ============================================================
// Bill.h
// Represents a charge generated from an appointment
// Created automatically when a patient books an appointment
// Stores: bill id, patient id, appointment id,
//         amount, status, date
// Status: unpaid, paid, cancelled
// ============================================================

#include <iostream>
#include <string>
using namespace std;

class Bill {
private:
    int    billId;
    int    patientId;
    int    appointmentId;
    float  amount;
    string status;   // unpaid, paid, cancelled
    string date;     // format: DD-MM-YYYY

public:

    // --------------------------------------------------------
    // Constructors & Destructor
    // --------------------------------------------------------
    Bill();
    Bill(int billId, int patientId, int appointmentId,
        float amount, string status, string date);
    Bill(const Bill& other);
    ~Bill();

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------
    int    getBillId()        const;
    int    getPatientId()     const;
    int    getAppointmentId() const;
    float  getAmount()        const;
    string getStatus()        const;
    string getDate()          const;

    // --------------------------------------------------------
    // Setters
    // --------------------------------------------------------
    void setBillId(int billId);
    void setPatientId(int patientId);
    void setAppointmentId(int appointmentId);
    void setAmount(float amount);
    void setStatus(string status);
    void setDate(string date);
    // needed for Storage<T> compatibility
    int getId() const { return billId; }
    // --------------------------------------------------------
    // Display
    // simple display function for bill info
    // used in patient menu and admin panel
    // --------------------------------------------------------
    void displayInfo() const;
};

#endif