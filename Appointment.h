#ifndef APPOINTMENT_H
#define APPOINTMENT_H

// ============================================================
// Appointment.h
// Represents a single appointment in HealthCare
// Stores: appointment id, patient id, doctor id,
//         date, time slot, status
// Overloads: == (conflict detection), 
// ============================================================

#include <iostream>
#include <string>
using namespace std;

class Appointment {
private:
    int    appointmentId;
    int    patientId;
    int    doctorId;
    string date;      // format: DD-MM-YYYY
    string timeSlot;  // one of 8 fixed slots: 09:00 to 16:00
    string status;    // pending, completed, cancelled, noshow

public:

    // --------------------------------------------------------
    // Constructors & Destructor
    // --------------------------------------------------------
    Appointment();
    Appointment(int appointmentId, int patientId, int doctorId,
        string date, string timeSlot, string status);
    Appointment(const Appointment& other);
    ~Appointment();

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------
    int    getAppointmentId() const;
    int    getPatientId()     const;
    int    getDoctorId()      const;
    string getDate()          const;
    string getTimeSlot()      const;
    string getStatus()        const;

    // --------------------------------------------------------
    // Setters
    // --------------------------------------------------------
    void setAppointmentId(int appointmentId);
    void setPatientId(int patientId);
    void setDoctorId(int doctorId);
    void setDate(string date);
    void setTimeSlot(string timeSlot);
    void setStatus(string status);
    // needed for Storage<T> compatibility
    int getId() const { return appointmentId; }

    // --------------------------------------------------------
    // Operator Overloads
    // == checks if two appointments conflict
    //    same doctor + same date + same time slot
    //    AND neither appointment is cancelled
    // << formatted console output
    // --------------------------------------------------------
    bool operator==(const Appointment& other) const;

    friend ostream& operator<<(ostream& output, const Appointment& source);
};

#endif