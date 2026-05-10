#ifndef FILEHANDLER_H
#define FILEHANDLER_H

// ============================================================
// FileHandler.h
// The ONLY class permitted to perform file I/O in HealthCare
// Handles: loading, appending, updating, deleting records
// Works with: patients.txt, doctors.txt, admin.txt,
//             appointments.txt, prescriptions.txt,
//             bills.txt, security_log.txt, discharged.txt
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Storage.h"
#include "HospitalException.h"
using namespace std;

class FileHandler {
public:

    // --------------------------------------------------------
    // Loading functions
    // called on startup to load all data from files
    // into Storage<T> objects in memory
    // throws FileNotFoundException if file cant be opened
    // --------------------------------------------------------
    static void loadPatients(Storage<Patient>& storage);
    static void loadDoctors(Storage<Doctor>& storage);
    static void loadAdmin(Admin& admin);
    static void loadAppointments(Storage<Appointment>& storage);
    static void loadBills(Storage<Bill>& storage);
    static void loadPrescriptions(Storage<Prescription>& storage);

    // --------------------------------------------------------
    // Appending functions
    // called when a new record is created
    // adds one new line to the relevant txt file
    // --------------------------------------------------------
    static void appendPatient(const Patient& patient);
    static void appendDoctor(const Doctor& doctor);
    static void appendAppointment(const Appointment& appointment);
    static void appendBill(const Bill& bill);
    static void appendPrescription(const Prescription& prescription);

    // --------------------------------------------------------
    // Updating functions
    // called when an existing record changes
    // rewrites the entire file with updated data
    // --------------------------------------------------------
    static void updatePatient(Storage<Patient>& storage);
    static void updateDoctor(Storage<Doctor>& storage);
    static void updateAppointment(Storage<Appointment>& storage);
    static void updateBill(Storage<Bill>& storage);

    // --------------------------------------------------------
    // Deleting functions
    // removes a specific record by ID
    // rewrites the entire file without that record
    // --------------------------------------------------------
    static void deletePatient(int id, Storage<Patient>& storage);
    static void deleteDoctor(int id, Storage<Doctor>& storage);
    static void deleteAppointment(int id, Storage<Appointment>& storage);
    static void deleteBill(int id, Storage<Bill>& storage);
    static void deletePrescription(int id, Storage<Prescription>& storage);

    // --------------------------------------------------------
    // Security log
    // appends a failed login attempt to security_log.txt
    // --------------------------------------------------------
    static void logSecurityEvent(const string& role,
        const string& enteredId,
        const string& result);

    // --------------------------------------------------------
    // View security log
    // reads and returns contents of security_log.txt
    // --------------------------------------------------------
    static void viewSecurityLog();

    // --------------------------------------------------------
    // Discharge patient
    // copies patient + all their records to discharged.txt
    // then deletes from all active files
    // --------------------------------------------------------
    static void dischargePatient(int patientId,
        Storage<Patient>& patientStorage,
        Storage<Appointment>& appointmentStorage,
        Storage<Bill>& billStorage,
        Storage<Prescription>& prescriptionStorage);

    // --------------------------------------------------------
    // Get current timestamp
    // used for security log entries
    // returns formatted string: DD-MM-YYYY HH:MM:SS
    // --------------------------------------------------------
    static string getCurrentTimestamp();
};

#endif