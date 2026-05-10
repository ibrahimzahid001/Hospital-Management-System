#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include "HospitalException.h"
#include "Person.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Storage.h"
#include "Validator.h"
#include "FileHandler.h"
using namespace std;

// ============================================================
// Global Storage Objects
// all data lives here in memory during runtime
// loaded from files on startup
// ============================================================
Storage<Patient>      patientStorage;
Storage<Doctor>       doctorStorage;
Storage<Appointment>  appointmentStorage;
Storage<Bill>         billStorage;
Storage<Prescription> prescriptionStorage;
Admin                 adminObj;




// ------------------------------------------------------------
// getMaxId()
// finds the maximum ID in a storage to generate next ID
// new ID = max + 1
// used for appointments, bills, prescriptions, doctors
// ------------------------------------------------------------
template <typename T>
int getMaxId(Storage<T>& storage) {
    int  maxId = 0;
    T* all = storage.getAll();
    int  total = storage.size();

    for (int i = 0; i < total; i++) {
        if (all[i].getId() > maxId) {
            maxId = all[i].getId();
        }
    }
    return maxId;
}


// ------------------------------------------------------------
// getCurrentDate()
// returns today's date as DD-MM-YYYY string
// used in doctor menu and report generation
// ------------------------------------------------------------
string getCurrentDate() {
    time_t now = time(0);
    tm* timePtr = localtime(&now);
    char   buffer[11];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", timePtr);
    return string(buffer);
}


// ------------------------------------------------------------
// getDoctorName()
// finds doctor name by ID from storage
// used when displaying appointments with doctor name
// ------------------------------------------------------------
string getDoctorName(int doctorId) {
    Doctor* d = doctorStorage.findById(doctorId);
    if (d != nullptr) {
        return d->getName();
    }
    return "Unknown";
}


// ------------------------------------------------------------
// getPatientName()
// finds patient name by ID from storage
// used when displaying appointments with patient name
// ------------------------------------------------------------
string getPatientName(int patientId) {
    Patient* p = patientStorage.findById(patientId);
    if (p != nullptr) {
        return p->getName();
    }
    return "Unknown";
}


// ------------------------------------------------------------
// sortAppointmentsByDateAsc()
// sorts appointments array by date ascending
// implemented manually using bubble sort as required
// no library sort functions used
// ------------------------------------------------------------
void sortAppointmentsByDateAsc(Appointment* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].getDate() > arr[j + 1].getDate()) {
                Appointment temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


// ------------------------------------------------------------
// sortAppointmentsByDateDesc()
// sorts appointments array by date descending
// most recent first — used for medical records
// ------------------------------------------------------------
void sortAppointmentsByDateDesc(Appointment* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].getDate() < arr[j + 1].getDate()) {
                Appointment temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


// ------------------------------------------------------------
// sortAppointmentsByTimeAsc()
// sorts appointments array by time slot ascending
// used in doctor menu for today's appointments
// ------------------------------------------------------------
void sortAppointmentsByTimeAsc(Appointment* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].getTimeSlot() > arr[j + 1].getTimeSlot()) {
                Appointment temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


// ============================================================
// STARTUP — Load all files into storage
// ============================================================
void loadAllData() {
    system("cd");
    try {
        FileHandler::loadPatients(patientStorage);
    }
    catch (FileNotFoundException& e) {
        cout << e.what() << endl;
    }

    try {
        FileHandler::loadDoctors(doctorStorage);
    }
    catch (FileNotFoundException& e) {
        cout << e.what() << endl;
    }

    try {
        FileHandler::loadAdmin(adminObj);
    }
    catch (FileNotFoundException& e) {
        cout << e.what() << endl;
    }

    try {
        FileHandler::loadAppointments(appointmentStorage);
    }
    catch (FileNotFoundException& e) {
        cout << e.what() << endl;
    }

    try {
        FileHandler::loadBills(billStorage);
    }
    catch (FileNotFoundException& e) {
        cout << e.what() << endl;
    }

    try {
        FileHandler::loadPrescriptions(prescriptionStorage);
    }
    catch (FileNotFoundException& e) {
        cout << e.what() << endl;
    }
}


// ============================================================
// LOGIN SYSTEM
// validates credentials against loaded storage
// locks after 3 consecutive failed attempts
// logs failed attempts to security_log.txt
// ============================================================


// ------------------------------------------------------------
// loginPatient()
// returns pointer to logged in Patient or nullptr if failed
// ------------------------------------------------------------
Patient* loginPatient() {
    int    attempts = 0;
    string enteredId;
    string enteredPass;

    while (attempts < 3) {
        cout << "Enter Patient ID   : ";
        cin >> enteredId;
        cout << "Enter Password     : ";
        cin >> enteredPass;

        // validate id is a number
        int id = 0;
        try {
            id = stoi(enteredId);
        }
        catch (...) {
            attempts++;
            cout << "Invalid ID. Attempts remaining: "
                << 3 - attempts << endl;

            FileHandler::logSecurityEvent("Patient", enteredId, "FAILED");
            continue;
        }

        // find patient in storage
        Patient* p = patientStorage.findById(id);

        if (p != nullptr && p->getPassword() == enteredPass) {
            return p; // login successful
        }
        else {
            attempts++;
            cout << "Invalid ID or Password. Attempts remaining: "
                << 3 - attempts << endl;

            FileHandler::logSecurityEvent("Patient", enteredId, "FAILED");
        }
    }

    // 3 failed attempts — lock account
    cout << "Account locked. Contact admin." << endl;
    return nullptr;
}


// ------------------------------------------------------------
// loginDoctor()
// returns pointer to logged in Doctor or nullptr if failed
// ------------------------------------------------------------
Doctor* loginDoctor() {
    int    attempts = 0;
    string enteredId;
    string enteredPass;

    while (attempts < 3) {
        cout << "Enter Doctor ID    : ";
        cin >> enteredId;
        cout << "Enter Password     : ";
        cin >> enteredPass;

        int id = 0;
        try {
            id = stoi(enteredId);
        }
        catch (...) {
            attempts++;
            cout << "Invalid ID. Attempts remaining: "
                << 3 - attempts << endl;

            FileHandler::logSecurityEvent("Doctor", enteredId, "FAILED");
            continue;
        }

        Doctor* d = doctorStorage.findById(id);

        if (d != nullptr && d->getPassword() == enteredPass) {
            return d;
        }
        else {
            attempts++;
            cout << "Invalid ID or Password. Attempts remaining: "
                << 3 - attempts << endl;

            FileHandler::logSecurityEvent("Doctor", enteredId, "FAILED");
        }
    }

    cout << "Account locked. Contact admin." << endl;
    return nullptr;
}


// ------------------------------------------------------------
// loginAdmin()
// returns true if admin login successful, false if failed
// ------------------------------------------------------------
bool loginAdmin() {
    int    attempts = 0;
    string enteredId;
    string enteredPass;

    while (attempts < 3) {
        cout << "Enter Admin ID     : ";
        cin >> enteredId;
        cout << "Enter Password     : ";
        cin >> enteredPass;

        int id = 0;
        try {
            id = stoi(enteredId);
        }
        catch (...) {
            attempts++;
            cout << "Invalid ID. Attempts remaining: "
                << 3 - attempts << endl;

            FileHandler::logSecurityEvent("Admin", enteredId, "FAILED");
            continue;
        }

        if (adminObj.getId() == id &&
            adminObj.getPassword() == enteredPass) {
            return true;
        }
        else {
            attempts++;
            cout << "Invalid ID or Password. Attempts remaining: "
                << 3 - attempts << endl;

            FileHandler::logSecurityEvent("Admin", enteredId, "FAILED");
        }
    }

    cout << "Account locked. Contact admin." << endl;
    return false;
}


// ============================================================
// PATIENT MENU FUNCTIONS
// ============================================================


// ------------------------------------------------------------
// bookAppointment()
// patient searches by specialization, picks doctor,
// picks date and time slot, balance is checked and deducted
// ------------------------------------------------------------
void bookAppointment(Patient* patient) {
    cout << "\n--- Book Appointment ---" << endl;

    // step 1 — get specialization from patient
    cout << "Enter specialization to search: ";
    string spec;
    cin.ignore();
    getline(cin, spec);

    // convert to lowercase for case insensitive comparison
    string specLower = Validator::toLower(spec);

    // step 2 — find all doctors with that specialization
    Doctor* allDoctors = doctorStorage.getAll();
    int     totalDoctors = doctorStorage.size();

    // collect matching doctors into temp array
    static Doctor matchingDoctors[100];
    int    matchCount = 0;

    for (int i = 0; i < totalDoctors; i++) {
        string docSpec = Validator::toLower(
            allDoctors[i].getSpecialization());
        if (docSpec == specLower) {
            matchingDoctors[matchCount] = allDoctors[i];
            matchCount++;
        }
    }

    if (matchCount == 0) {
        cout << "No doctors available for that specialization." << endl;
        return;
    }

    // display matching doctors
    cout << "\nAvailable Doctors:" << endl;
    cout << "-------------------" << endl;
    for (int i = 0; i < matchCount; i++) {
        cout << "ID: " << matchingDoctors[i].getId()
            << " | Name: Dr. " << matchingDoctors[i].getName()
            << " | Fee: PKR " << matchingDoctors[i].getFee()
            << endl;
    }

    // step 3 — get doctor ID from patient
    cout << "\nEnter Doctor ID: ";
    int doctorId;
    cin >> doctorId;

    Doctor* selectedDoctor = doctorStorage.findById(doctorId);
    if (selectedDoctor == nullptr) {
        cout << "Doctor not found." << endl;
        return;
    }

    // step 4 — get and validate date
    string date;
    int    dateAttempts = 0;

    while (dateAttempts < 3) {
        cout << "Enter date (DD-MM-YYYY): ";
        cin >> date;

        if (Validator::isValidDate(date)) {
            break;
        }
        else {
            cout << "Invalid date. Use format DD-MM-YYYY." << endl;
            dateAttempts++;
            if (dateAttempts == 3) {
                cout << "Too many invalid attempts." << endl;
                return;
            }
        }
    }

    // step 5 — show available time slots for that doctor on that date
    string allSlots[8] = {
        "09:00","10:00","11:00","12:00",
        "13:00","14:00","15:00","16:00"
    };

    // check which slots are taken
    bool slotTaken[8] = { false };

    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getDoctorId() == doctorId &&
            allAppts[i].getDate() == date &&
            allAppts[i].getStatus() != "cancelled") {

            // mark this slot as taken
            for (int j = 0; j < 8; j++) {
                if (allSlots[j] == allAppts[i].getTimeSlot()) {
                    slotTaken[j] = true;
                }
            }
        }
    }

    // display available slots
    cout << "\nAvailable Time Slots:" << endl;
    bool anyAvailable = false;
    for (int i = 0; i < 8; i++) {
        if (!slotTaken[i]) {
            cout << allSlots[i] << " ";
            anyAvailable = true;
        }
    }
    cout << endl;

    if (!anyAvailable) {
        cout << "No slots available for this doctor on this date." << endl;
        return;
    }

    // step 6 — get time slot from patient
    string timeSlot;
    bool   slotBooked = false;

    while (!slotBooked) {
        cout << "Enter time slot (e.g. 09:00): ";
        cin >> timeSlot;

        // validate it is one of the 8 valid slots
        if (!Validator::isValidTimeSlot(timeSlot)) {
            cout << "Invalid time slot." << endl;
            continue;
        }

        // check if slot is taken using == operator on Appointment
        // create a temp appointment to check conflict
        Appointment tempAppt(0, patient->getId(), doctorId,
            date, timeSlot, "pending");

        bool conflict = false;
        for (int i = 0; i < totalAppt; i++) {
            // uses overloaded == operator for conflict detection
            if (allAppts[i] == tempAppt) {
                conflict = true;
                break;
            }
        }

        if (conflict) {
            try {
                throw SlotUnavailableException(
                    "This time slot is already booked. "
                    "Please choose another slot.");
            }
            catch (SlotUnavailableException& e) {
                cout << e.what() << endl;

                // redisplay available slots
                cout << "\nAvailable Time Slots:" << endl;
                for (int i = 0; i < 8; i++) {
                    if (!slotTaken[i]) {
                        cout << allSlots[i] << " ";
                    }
                }
                cout << endl;
            }
        }
        else {
            slotBooked = true;
        }
    }

    // step 7 — check patient balance against doctor fee
    float fee = selectedDoctor->getFee();

    if (patient->getBalance() < fee) {
        try {
            throw InsufficientFundsException(
                "Insufficient balance to book this appointment.");
        }
        catch (InsufficientFundsException& e) {
            cout << e.what() << endl;
            return;
        }
    }

    // step 8 — deduct fee using -= operator
    *patient -= fee;

    // step 9 — generate new appointment ID
    int newApptId = getMaxId(appointmentStorage) + 1;

    // step 10 — create and save appointment
    Appointment newAppt(newApptId, patient->getId(), doctorId,
        date, timeSlot, "pending");
    appointmentStorage.add(newAppt);
    FileHandler::appendAppointment(newAppt);

    // step 11 — generate new bill ID and create bill
    int newBillId = getMaxId(billStorage) + 1;

    Bill newBill(newBillId, patient->getId(),
        newApptId, fee, "unpaid", date);
    billStorage.add(newBill);
    FileHandler::appendBill(newBill);

    // step 12 — update patient balance in file
    patientStorage.updateById(patient->getId(), *patient);
    FileHandler::updatePatient(patientStorage);

    cout << "Appointment booked successfully. "
        << "Appointment ID: " << newApptId << endl;
}


// ------------------------------------------------------------
// cancelAppointment()
// shows pending appointments, patient picks one to cancel
// refunds fee to balance using += operator
// ------------------------------------------------------------
void cancelAppointment(Patient* patient) {
    cout << "\n--- Cancel Appointment ---" << endl;

    // collect pending appointments for this patient
    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    static Appointment pendingAppts[100];
    int         pendingCount = 0;

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getPatientId() == patient->getId() &&
            allAppts[i].getStatus() == "pending") {
            pendingAppts[pendingCount] = allAppts[i];
            pendingCount++;
        }
    }

    if (pendingCount == 0) {
        cout << "You have no pending appointments." << endl;
        return;
    }

    // display pending appointments
    cout << "\nYour Pending Appointments:" << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < pendingCount; i++) {
        cout << "Appointment ID: " << pendingAppts[i].getAppointmentId()
            << " | Doctor: " << getDoctorName(
                pendingAppts[i].getDoctorId())
            << " | Date: " << pendingAppts[i].getDate()
            << " | Time: " << pendingAppts[i].getTimeSlot()
            << endl;
    }

    // get appointment ID to cancel
    cout << "\nEnter Appointment ID to cancel: ";
    int apptId;
    cin >> apptId;

    // validate it belongs to this patient and is pending
    Appointment* appt = appointmentStorage.findById(apptId);

    if (appt == nullptr ||
        appt->getPatientId() != patient->getId() ||
        appt->getStatus() != "pending") {
        cout << "Invalid appointment ID." << endl;
        return;
    }

    // get the fee to refund from the doctor
    float fee = 0.0f;
    Doctor* d = doctorStorage.findById(appt->getDoctorId());
    if (d != nullptr) {
        fee = d->getFee();
    }

    // update appointment status to cancelled
    appt->setStatus("cancelled");
    appointmentStorage.updateById(apptId, *appt);
    FileHandler::updateAppointment(appointmentStorage);

    // refund fee to patient balance using += operator
    *patient += fee;
    patientStorage.updateById(patient->getId(), *patient);
    FileHandler::updatePatient(patientStorage);

    // update corresponding bill status to cancelled
    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getAppointmentId() == apptId) {
            allBills[i].setStatus("cancelled");
            billStorage.updateById(allBills[i].getBillId(),
                allBills[i]);
            FileHandler::updateBill(billStorage);
            break;
        }
    }

    cout << "Appointment cancelled. PKR " << fee
        << " refunded to your balance." << endl;
}


// ------------------------------------------------------------
// viewMyAppointments()
// displays all appointments for this patient
// sorted by date ascending
// ------------------------------------------------------------
void viewMyAppointments(Patient* patient) {
    cout << "\n--- My Appointments ---" << endl;

    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    // collect this patient's appointments
    static Appointment myAppts[100];
    int         myCount = 0;

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getPatientId() == patient->getId()) {
            myAppts[myCount] = allAppts[i];
            myCount++;
        }
    }

    if (myCount == 0) {
        cout << "No appointments found." << endl;
        return;
    }

    // sort by date ascending
    sortAppointmentsByDateAsc(myAppts, myCount);

    // display
    cout << "----------------------------" << endl;
    for (int i = 0; i < myCount; i++) {
        cout << "ID: " << myAppts[i].getAppointmentId()
            << " | Doctor: " << getDoctorName(
                myAppts[i].getDoctorId())
            << " | Date: " << myAppts[i].getDate()
            << " | Time: " << myAppts[i].getTimeSlot()
            << " | Status: " << myAppts[i].getStatus()
            << endl;
    }
}


// ------------------------------------------------------------
// viewMyMedicalRecords()
// displays all prescriptions for this patient
// sorted by date descending (most recent first)
// ------------------------------------------------------------
void viewMyMedicalRecords(Patient* patient) {
    cout << "\n--- My Medical Records ---" << endl;

    Prescription* allPres = prescriptionStorage.getAll();
    int           totalPre = prescriptionStorage.size();

    // collect this patient's prescriptions
    static Prescription myPres[100];
    int          myCount = 0;

    for (int i = 0; i < totalPre; i++) {
        if (allPres[i].getPatientId() == patient->getId()) {
            myPres[myCount] = allPres[i];
            myCount++;
        }
    }

    if (myCount == 0) {
        cout << "No medical records found." << endl;
        return;
    }

    // sort prescriptions by date descending manually
    // bubble sort on date string — works because DD-MM-YYYY
    // sorts correctly as string when compared properly
    // we convert to YYYY-MM-DD for correct string comparison
    for (int i = 0; i < myCount - 1; i++) {
        for (int j = 0; j < myCount - i - 1; j++) {
            // convert DD-MM-YYYY to YYYY-MM-DD for comparison
            string d1 = myPres[j].getDate();
            string d2 = myPres[j + 1].getDate();

            // YYYY-MM-DD format: year(6-9) + month(3-4) + day(0-1)
            string cmp1 = d1.substr(6, 4) + d1.substr(3, 2) + d1.substr(0, 2);
            string cmp2 = d2.substr(6, 4) + d2.substr(3, 2) + d2.substr(0, 2);

            if (cmp1 < cmp2) {
                Prescription temp = myPres[j];
                myPres[j] = myPres[j + 1];
                myPres[j + 1] = temp;
            }
        }
    }

    // display
    cout << "----------------------------" << endl;
    for (int i = 0; i < myCount; i++) {
        cout << "Date     : " << myPres[i].getDate() << endl;
        cout << "Doctor   : " << getDoctorName(
            myPres[i].getDoctorId()) << endl;
        cout << "Medicines: " << myPres[i].getMedicines() << endl;
        cout << "Notes    : " << myPres[i].getNotes() << endl;
        cout << "----------------------------" << endl;
    }
}


// ------------------------------------------------------------
// viewMyBills()
// displays all bills for this patient
// shows total outstanding unpaid amount at bottom
// ------------------------------------------------------------
void viewMyBills(Patient* patient) {
    cout << "\n--- My Bills ---" << endl;

    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    // collect this patient's bills
    static Bill myBills[100];
    int  myCount = 0;

    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getPatientId() == patient->getId()) {
            myBills[myCount] = allBills[i];
            myCount++;
        }
    }

    if (myCount == 0) {
        cout << "No bills found." << endl;
        return;
    }

    // display all bills and track total unpaid
    float totalUnpaid = 0.0f;

    cout << "----------------------------" << endl;
    for (int i = 0; i < myCount; i++) {
        cout << "Bill ID        : " << myBills[i].getBillId() << endl;
        cout << "Appointment ID : " << myBills[i].getAppointmentId() << endl;
        cout << "Amount         : PKR " << myBills[i].getAmount() << endl;
        cout << "Status         : " << myBills[i].getStatus() << endl;
        cout << "Date           : " << myBills[i].getDate() << endl;
        cout << "----------------------------" << endl;

        if (myBills[i].getStatus() == "unpaid") {
            totalUnpaid += myBills[i].getAmount();
        }
    }

    cout << "Total Outstanding: PKR " << totalUnpaid << endl;
}


// ------------------------------------------------------------
// payBill()
// shows unpaid bills, patient picks one to pay
// checks balance, deducts using -= operator
// ------------------------------------------------------------
void payBill(Patient* patient) {
    cout << "\n--- Pay Bill ---" << endl;

    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    // collect unpaid bills for this patient
    static Bill unpaidBills[100];
    int  unpaidCount = 0;

    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getPatientId() == patient->getId() &&
            allBills[i].getStatus() == "unpaid") {
            unpaidBills[unpaidCount] = allBills[i];
            unpaidCount++;
        }
    }

    if (unpaidCount == 0) {
        cout << "No unpaid bills." << endl;
        return;
    }

    // display unpaid bills
    cout << "\nYour Unpaid Bills:" << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < unpaidCount; i++) {
        cout << "Bill ID: " << unpaidBills[i].getBillId()
            << " | Amount: PKR " << unpaidBills[i].getAmount()
            << " | Date: " << unpaidBills[i].getDate()
            << endl;
    }

    // get bill ID to pay
    cout << "\nEnter Bill ID to pay: ";
    int billId;
    cin >> billId;

    // validate it belongs to this patient and is unpaid
    Bill* bill = billStorage.findById(billId);

    if (bill == nullptr ||
        bill->getPatientId() != patient->getId() ||
        bill->getStatus() != "unpaid") {
        cout << "Invalid bill ID." << endl;
        return;
    }

    // check balance
    if (patient->getBalance() < bill->getAmount()) {
        try {
            throw InsufficientFundsException(
                "Insufficient balance to pay this bill.");
        }
        catch (InsufficientFundsException& e) {
            cout << e.what() << endl;
            return;
        }
    }

    // deduct amount using -= operator
    *patient -= bill->getAmount();

    // update bill status to paid
    bill->setStatus("paid");
    billStorage.updateById(billId, *bill);
    FileHandler::updateBill(billStorage);

    // update patient balance in file
    patientStorage.updateById(patient->getId(), *patient);
    FileHandler::updatePatient(patientStorage);

    cout << "Bill paid successfully. "
        << "Remaining balance: PKR "
        << patient->getBalance() << endl;
}


// ------------------------------------------------------------
// topUpBalance()
// patient adds money to their balance
// validates positive amount, max 3 attempts
// uses += operator
// ------------------------------------------------------------
void topUpBalance(Patient* patient) {
    cout << "\n--- Top Up Balance ---" << endl;

    int   attempts = 0;
    float amount = 0.0f;

    while (attempts < 3) {
        cout << "Enter amount to add (PKR): ";
        cin >> amount;

        if (!Validator::isValidFloat(amount)) {
            try {
                throw InvalidInputException(
                    "Amount must be a positive number greater than 0.");
            }
            catch (InvalidInputException& e) {
                cout << e.what() << endl;
                attempts++;
                if (attempts == 3) {
                    cout << "Too many invalid attempts." << endl;
                    return;
                }
            }
        }
        else {
            break;
        }
    }

    // add amount using += operator
    *patient += amount;

    // update patient balance in file
    patientStorage.updateById(patient->getId(), *patient);
    FileHandler::updatePatient(patientStorage);

    cout << "Balance updated. New balance: PKR "
        << patient->getBalance() << endl;
}


// ------------------------------------------------------------
// runPatientMenu()
// runs the full patient menu loop until logout
// ------------------------------------------------------------
void runPatientMenu(Patient* patient) {
    int choice = 0;

    while (true) {
        patient->showMenu();
        cin >> choice;

        if (!Validator::isValidMenuChoice(choice, 1, 8)) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (choice == 1) bookAppointment(patient);
        else if (choice == 2) cancelAppointment(patient);
        else if (choice == 3) viewMyAppointments(patient);
        else if (choice == 4) viewMyMedicalRecords(patient);
        else if (choice == 5) viewMyBills(patient);
        else if (choice == 6) payBill(patient);
        else if (choice == 7) topUpBalance(patient);
        else if (choice == 8) {
            cout << "Logging out..." << endl;
            break;
        }
    }
}


// ============================================================
// DOCTOR MENU FUNCTIONS
// ============================================================


// ------------------------------------------------------------
// viewTodaysAppointments()
// shows all appointments for today for this doctor
// sorted by time slot ascending
// ------------------------------------------------------------
void viewTodaysAppointments(Doctor* doctor) {
    cout << "\n--- Today's Appointments ---" << endl;

    string       today = getCurrentDate();
    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    // collect today's appointments for this doctor
    static Appointment todayAppts[100];
    int         todayCount = 0;

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getDoctorId() == doctor->getId() &&
            allAppts[i].getDate() == today) {
            todayAppts[todayCount] = allAppts[i];
            todayCount++;
        }
    }

    if (todayCount == 0) {
        cout << "No appointments scheduled for today." << endl;
        return;
    }

    // sort by time slot ascending
    sortAppointmentsByTimeAsc(todayAppts, todayCount);

    // display
    cout << "----------------------------" << endl;
    for (int i = 0; i < todayCount; i++) {
        cout << "Appointment ID : "
            << todayAppts[i].getAppointmentId() << endl;
        cout << "Patient        : "
            << getPatientName(todayAppts[i].getPatientId()) << endl;
        cout << "Time Slot      : "
            << todayAppts[i].getTimeSlot() << endl;
        cout << "Status         : "
            << todayAppts[i].getStatus() << endl;
        cout << "----------------------------" << endl;
    }
}


// ------------------------------------------------------------
// markAppointmentComplete()
// doctor marks a pending appointment as completed
// ------------------------------------------------------------
void markAppointmentComplete(Doctor* doctor) {
    cout << "\n--- Mark Appointment Complete ---" << endl;

    string today = getCurrentDate();

    // show today's pending appointments for this doctor
    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    bool anyPending = false;
    cout << "Today's Pending Appointments:" << endl;
    cout << "----------------------------" << endl;

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getDoctorId() == doctor->getId() &&
            allAppts[i].getDate() == today &&
            allAppts[i].getStatus() == "pending") {

            cout << "Appointment ID : "
                << allAppts[i].getAppointmentId() << endl;
            cout << "Patient        : "
                << getPatientName(allAppts[i].getPatientId()) << endl;
            cout << "Time Slot      : "
                << allAppts[i].getTimeSlot() << endl;
            cout << "----------------------------" << endl;
            anyPending = true;
        }
    }

    if (!anyPending) {
        cout << "No pending appointments for today." << endl;
        return;
    }

    cout << "Enter Appointment ID: ";
    int apptId;
    cin >> apptId;

    // validate it belongs to this doctor, is pending and is today
    Appointment* appt = appointmentStorage.findById(apptId);

    if (appt == nullptr ||
        appt->getDoctorId() != doctor->getId() ||
        appt->getStatus() != "pending" ||
        appt->getDate() != today) {
        cout << "Invalid appointment ID." << endl;
        return;
    }

    // update status to completed
    appt->setStatus("completed");
    appointmentStorage.updateById(apptId, *appt);
    FileHandler::updateAppointment(appointmentStorage);

    cout << "Appointment marked as completed." << endl;
}


// ------------------------------------------------------------
// markAppointmentNoShow()
// doctor marks a pending appointment as noshow
// bill is also cancelled — no refund issued
// ------------------------------------------------------------
void markAppointmentNoShow(Doctor* doctor) {
    cout << "\n--- Mark Appointment No-Show ---" << endl;

    string today = getCurrentDate();

    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    bool anyPending = false;
    cout << "Today's Pending Appointments:" << endl;
    cout << "----------------------------" << endl;

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getDoctorId() == doctor->getId() &&
            allAppts[i].getDate() == today &&
            allAppts[i].getStatus() == "pending") {

            cout << "Appointment ID : "
                << allAppts[i].getAppointmentId() << endl;
            cout << "Patient        : "
                << getPatientName(allAppts[i].getPatientId()) << endl;
            cout << "Time Slot      : "
                << allAppts[i].getTimeSlot() << endl;
            cout << "----------------------------" << endl;
            anyPending = true;
        }
    }

    if (!anyPending) {
        cout << "No pending appointments for today." << endl;
        return;
    }

    cout << "Enter Appointment ID: ";
    int apptId;
    cin >> apptId;

    Appointment* appt = appointmentStorage.findById(apptId);

    if (appt == nullptr ||
        appt->getDoctorId() != doctor->getId() ||
        appt->getStatus() != "pending" ||
        appt->getDate() != today) {
        cout << "Invalid appointment ID." << endl;
        return;
    }

    // update appointment status to noshow
    appt->setStatus("noshow");
    appointmentStorage.updateById(apptId, *appt);
    FileHandler::updateAppointment(appointmentStorage);

    // update corresponding bill to cancelled — no refund
    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getAppointmentId() == apptId) {
            allBills[i].setStatus("cancelled");
            billStorage.updateById(allBills[i].getBillId(),
                allBills[i]);
            FileHandler::updateBill(billStorage);
            break;
        }
    }

    cout << "Appointment marked as no-show." << endl;
}


// ------------------------------------------------------------
// writePrescription()
// doctor writes prescription for a completed appointment
// validates appointment belongs to doctor and is completed
// checks no prescription already exists for this appointment
// ------------------------------------------------------------
void writePrescription(Doctor* doctor) {
    cout << "\n--- Write Prescription ---" << endl;

    cout << "Enter Appointment ID: ";
    int apptId;
    cin >> apptId;

    // validate appointment belongs to this doctor and is completed
    Appointment* appt = appointmentStorage.findById(apptId);

    if (appt == nullptr ||
        appt->getDoctorId() != doctor->getId() ||
        appt->getStatus() != "completed") {
        cout << "Invalid appointment ID." << endl;
        return;
    }

    // check if prescription already exists for this appointment
    Prescription* allPres = prescriptionStorage.getAll();
    int           totalPre = prescriptionStorage.size();

    for (int i = 0; i < totalPre; i++) {
        if (allPres[i].getAppointmentId() == apptId) {
            cout << "Prescription already written "
                << "for this appointment." << endl;
            return;
        }
    }

    // get medicines — max 499 chars
    char medicines[500];
    cout << "Enter medicines "
        << "(e.g. Paracetamol 500mg;Amoxicillin 250mg): ";
    cin.ignore();
    cin.getline(medicines, 500);

    // get notes — max 299 chars
    char notes[300];
    cout << "Enter notes (max 300 chars): ";
    cin.getline(notes, 300);

    // generate new prescription ID
    int newPresId = getMaxId(prescriptionStorage) + 1;

    // create and save prescription
    Prescription newPres(newPresId, apptId,
        appt->getPatientId(), doctor->getId(),
        appt->getDate(), medicines, notes);

    prescriptionStorage.add(newPres);
    FileHandler::appendPrescription(newPres);

    cout << "Prescription saved." << endl;
}


// ------------------------------------------------------------
// viewPatientMedicalHistory()
// doctor views prescriptions they wrote for a patient
// patient must have at least one completed appointment
// with this doctor — access denied otherwise
// ------------------------------------------------------------
void viewPatientMedicalHistory(Doctor* doctor) {
    cout << "\n--- View Patient Medical History ---" << endl;

    cout << "Enter Patient ID: ";
    int patientId;
    cin >> patientId;

    // validate patient exists
    Patient* p = patientStorage.findById(patientId);
    if (p == nullptr) {
        cout << "Access denied. You can only view records "
            << "of your own patients." << endl;
        return;
    }

    // validate patient has at least one completed appointment
    // with this doctor
    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    bool hasCompleted = false;
    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getPatientId() == patientId &&
            allAppts[i].getDoctorId() == doctor->getId() &&
            allAppts[i].getStatus() == "completed") {
            hasCompleted = true;
            break;
        }
    }

    if (!hasCompleted) {
        cout << "Access denied. You can only view records "
            << "of your own patients." << endl;
        return;
    }

    // collect prescriptions written by this doctor for this patient
    Prescription* allPres = prescriptionStorage.getAll();
    int           totalPre = prescriptionStorage.size();

    Prescription myPres[100];
    int          myCount = 0;

    for (int i = 0; i < totalPre; i++) {
        if (allPres[i].getPatientId() == patientId &&
            allPres[i].getDoctorId() == doctor->getId()) {
            myPres[myCount] = allPres[i];
            myCount++;
        }
    }

    if (myCount == 0) {
        cout << "No prescriptions found for this patient." << endl;
        return;
    }

    // sort by date descending
    for (int i = 0; i < myCount - 1; i++) {
        for (int j = 0; j < myCount - i - 1; j++) {
            string d1 = myPres[j].getDate();
            string d2 = myPres[j + 1].getDate();
            string cmp1 = d1.substr(6, 4) + d1.substr(3, 2) + d1.substr(0, 2);
            string cmp2 = d2.substr(6, 4) + d2.substr(3, 2) + d2.substr(0, 2);

            if (cmp1 < cmp2) {
                Prescription temp = myPres[j];
                myPres[j] = myPres[j + 1];
                myPres[j + 1] = temp;
            }
        }
    }

    // display
    cout << "----------------------------" << endl;
    for (int i = 0; i < myCount; i++) {
        cout << "Date     : " << myPres[i].getDate() << endl;
        cout << "Medicines: " << myPres[i].getMedicines() << endl;
        cout << "Notes    : " << myPres[i].getNotes() << endl;
        cout << "----------------------------" << endl;
    }
}


// ------------------------------------------------------------
// runDoctorMenu()
// runs the full doctor menu loop until logout
// ------------------------------------------------------------
void runDoctorMenu(Doctor* doctor) {
    int choice = 0;

    while (true) {
        doctor->showMenu();
        cin >> choice;

        if (!Validator::isValidMenuChoice(choice, 1, 6)) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (choice == 1) viewTodaysAppointments(doctor);
        else if (choice == 2) markAppointmentComplete(doctor);
        else if (choice == 3) markAppointmentNoShow(doctor);
        else if (choice == 4) writePrescription(doctor);
        else if (choice == 5) viewPatientMedicalHistory(doctor);
        else if (choice == 6) {
            cout << "Logging out..." << endl;
            break;
        }
    }
}


// ============================================================
// ADMIN MENU FUNCTIONS
// ============================================================


// ------------------------------------------------------------
// addDoctor()
// admin adds a new doctor to the system
// validates all fields using Validator
// ------------------------------------------------------------
void addDoctor() {
    cout << "\n--- Add Doctor ---" << endl;

    string name;
    string specialization;
    string contact;
    string password;
    float  fee = 0.0f;

    cin.ignore();

    // get name
    cout << "Enter name (max 50 chars): ";
    getline(cin, name);
    if (name.length() > 50) {
        name = name.substr(0, 50);
    }

    // get specialization
    cout << "Enter specialization (max 50 chars): ";
    getline(cin, specialization);
    if (specialization.length() > 50) {
        specialization = specialization.substr(0, 50);
    }

    // get and validate contact
    cout << "Enter contact (11 digits): ";
    cin >> contact;

    if (!Validator::isValidContact(contact)) {
        cout << "Invalid contact number." << endl;
        return;
    }

    // get and validate password
    cout << "Enter password (min 6 chars): ";
    cin >> password;

    if (!Validator::isValidPassword(password)) {
        cout << "Password must be at least 6 characters." << endl;
        return;
    }

    // get and validate fee
    cout << "Enter consultation fee (PKR): ";
    cin >> fee;

    if (!Validator::isValidFloat(fee)) {
        cout << "Fee must be a positive number." << endl;
        return;
    }

    // generate new doctor ID
    int newDoctorId = getMaxId(doctorStorage) + 1;

    // create and save doctor
    Doctor newDoctor(newDoctorId, name, specialization,
        contact, password, fee);
    doctorStorage.add(newDoctor);
    FileHandler::appendDoctor(newDoctor);

    cout << "Doctor added successfully. ID: " << newDoctorId << endl;
}


// ------------------------------------------------------------
// removeDoctor()
// admin removes a doctor from the system
// checks no pending appointments exist for this doctor
// ------------------------------------------------------------
void removeDoctor() {
    cout << "\n--- Remove Doctor ---" << endl;

    // display all doctors
    Doctor* allDoctors = doctorStorage.getAll();
    int     totalDoctor = doctorStorage.size();

    if (totalDoctor == 0) {
        cout << "No doctors in the system." << endl;
        return;
    }

    cout << "All Doctors:" << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < totalDoctor; i++) {
        cout << "ID: " << allDoctors[i].getId()
            << " | Name: Dr. " << allDoctors[i].getName()
            << " | Spec: " << allDoctors[i].getSpecialization()
            << " | Fee: PKR " << allDoctors[i].getFee()
            << endl;
    }

    cout << "Enter Doctor ID to remove: ";
    int doctorId;
    cin >> doctorId;

    // check if doctor has pending appointments
    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getDoctorId() == doctorId &&
            allAppts[i].getStatus() == "pending") {
            cout << "Cannot remove doctor with pending appointments. "
                << "Cancel or reassign them first." << endl;
            return;
        }
    }

    // delete doctor
    FileHandler::deleteDoctor(doctorId, doctorStorage);
    cout << "Doctor removed." << endl;
}


// ------------------------------------------------------------
// viewAllPatients()
// displays all patients with count of unpaid bills
// ------------------------------------------------------------
void viewAllPatients() {
    cout << "\n--- All Patients ---" << endl;

    Patient* allPatients = patientStorage.getAll();
    int      totalPatient = patientStorage.size();

    if (totalPatient == 0) {
        cout << "No patients in the system." << endl;
        return;
    }

    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    cout << "----------------------------" << endl;
    for (int i = 0; i < totalPatient; i++) {

        // count unpaid bills for this patient
        int unpaidCount = 0;
        for (int j = 0; j < totalBill; j++) {
            if (allBills[j].getPatientId() == allPatients[i].getId() &&
                allBills[j].getStatus() == "unpaid") {
                unpaidCount++;
            }
        }

        cout << "ID: " << allPatients[i].getId()
            << " | Name: " << allPatients[i].getName()
            << " | Age: " << allPatients[i].getAge()
            << " | Gender: " << allPatients[i].getGender()
            << " | Contact: " << allPatients[i].getContact()
            << " | Balance: PKR " << allPatients[i].getBalance()
            << " | Unpaid Bills: " << unpaidCount
            << endl;
    }
}


// ------------------------------------------------------------
// viewAllDoctors()
// displays all doctors in the system
// ------------------------------------------------------------
void viewAllDoctors() {
    cout << "\n--- All Doctors ---" << endl;

    Doctor* allDoctors = doctorStorage.getAll();
    int     totalDoctor = doctorStorage.size();

    if (totalDoctor == 0) {
        cout << "No doctors in the system." << endl;
        return;
    }

    cout << "----------------------------" << endl;
    for (int i = 0; i < totalDoctor; i++) {
        cout << "ID: " << allDoctors[i].getId()
            << " | Name: Dr. " << allDoctors[i].getName()
            << " | Spec: " << allDoctors[i].getSpecialization()
            << " | Contact: " << allDoctors[i].getContact()
            << " | Fee: PKR " << allDoctors[i].getFee()
            << endl;
    }
}


// ------------------------------------------------------------
// viewAllAppointments()
// displays all appointments sorted by date descending
// ------------------------------------------------------------
void viewAllAppointments() {
    cout << "\n--- All Appointments ---" << endl;

    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    if (totalAppt == 0) {
        cout << "No appointments in the system." << endl;
        return;
    }

    // copy into temp array for sorting
    static Appointment tempAppts[100];
    for (int i = 0; i < totalAppt; i++) {
        tempAppts[i] = allAppts[i];
    }

    // sort by date descending
    for (int i = 0; i < totalAppt - 1; i++) {
        for (int j = 0; j < totalAppt - i - 1; j++) {
            string d1 = tempAppts[j].getDate();
            string d2 = tempAppts[j + 1].getDate();
            string cmp1 = d1.substr(6, 4) + d1.substr(3, 2) + d1.substr(0, 2);
            string cmp2 = d2.substr(6, 4) + d2.substr(3, 2) + d2.substr(0, 2);

            if (cmp1 < cmp2) {
                Appointment temp = tempAppts[j];
                tempAppts[j] = tempAppts[j + 1];
                tempAppts[j + 1] = temp;
            }
        }
    }

    cout << "----------------------------" << endl;
    for (int i = 0; i < totalAppt; i++) {
        cout << "ID: " << tempAppts[i].getAppointmentId()
            << " | Patient: " << getPatientName(
                tempAppts[i].getPatientId())
            << " | Doctor: " << getDoctorName(
                tempAppts[i].getDoctorId())
            << " | Date: " << tempAppts[i].getDate()
            << " | Time: " << tempAppts[i].getTimeSlot()
            << " | Status: " << tempAppts[i].getStatus()
            << endl;
    }
}


// ------------------------------------------------------------
// viewUnpaidBills()
// displays all unpaid bills across all patients
// appends [OVERDUE] if bill is more than 7 days old
// ------------------------------------------------------------
void viewUnpaidBills() {
    cout << "\n--- Unpaid Bills ---" << endl;

    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    bool anyUnpaid = false;

    // get today's time for overdue check
    time_t now = time(0);

    cout << "----------------------------" << endl;
    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getStatus() != "unpaid") continue;

        anyUnpaid = true;

        // parse bill date DD-MM-YYYY into time_t for difftime
        string date = allBills[i].getDate();
        int    day = stoi(date.substr(0, 2));
        int    mon = stoi(date.substr(3, 2));
        int    yr = stoi(date.substr(6, 4));

        tm billTime = {};
        billTime.tm_mday = day;
        billTime.tm_mon = mon - 1;  // tm_mon is 0 based
        billTime.tm_year = yr - 1900; // tm_year is years since 1900
        time_t billDate = mktime(&billTime);

        // difftime returns difference in seconds
        double diffSeconds = difftime(now, billDate);
        double diffDays = diffSeconds / (60 * 60 * 24);

        string overdueTag = "";
        if (diffDays > 7) {
            overdueTag = " [OVERDUE]";
        }

        cout << "Bill ID  : " << allBills[i].getBillId() << endl;
        cout << "Patient  : " << getPatientName(
            allBills[i].getPatientId()) << endl;
        cout << "Amount   : PKR " << allBills[i].getAmount() << endl;
        cout << "Date     : " << allBills[i].getDate() << overdueTag << endl;
        cout << "----------------------------" << endl;
    }

    if (!anyUnpaid) {
        cout << "No unpaid bills." << endl;
    }
}


// ------------------------------------------------------------
// dischargePatient()
// admin discharges a patient
// checks no unpaid bills or pending appointments
// archives all records to discharged.txt
// ------------------------------------------------------------
void dischargePatientAdmin() {
    cout << "\n--- Discharge Patient ---" << endl;

    cout << "Enter Patient ID: ";
    int patientId;
    cin >> patientId;

    // validate patient exists
    Patient* p = patientStorage.findById(patientId);
    if (p == nullptr) {
        cout << "Patient not found." << endl;
        return;
    }

    // check for unpaid bills
    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getPatientId() == patientId &&
            allBills[i].getStatus() == "unpaid") {
            cout << "Cannot discharge patient with unpaid bills." << endl;
            return;
        }
    }

    // check for pending appointments
    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getPatientId() == patientId &&
            allAppts[i].getStatus() == "pending") {
            cout << "Cannot discharge patient "
                << "with pending appointments." << endl;
            return;
        }
    }

    // discharge — archive and delete all records
    try {
        FileHandler::dischargePatient(patientId,
            patientStorage,
            appointmentStorage,
            billStorage,
            prescriptionStorage);
        cout << "Patient discharged and archived successfully." << endl;
    }
    catch (FileNotFoundException& e) {
        cout << e.what() << endl;
    }
}


// ------------------------------------------------------------
// generateDailyReport()
// generates a report for today's activity
// no separate file created — all derived from existing files
// ------------------------------------------------------------
void generateDailyReport() {
    cout << "\n--- Daily Report ---" << endl;

    string today = getCurrentDate();
    cout << "Date: " << today << endl;
    cout << "----------------------------" << endl;

    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    // count appointments by status for today
    int totalToday = 0;
    int pendingCount = 0;
    int completedCount = 0;
    int noshowCount = 0;
    int cancelledCount = 0;

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getDate() == today) {
            totalToday++;
            if (allAppts[i].getStatus() == "pending") pendingCount++;
            else if (allAppts[i].getStatus() == "completed") completedCount++;
            else if (allAppts[i].getStatus() == "noshow") noshowCount++;
            else if (allAppts[i].getStatus() == "cancelled") cancelledCount++;
        }
    }

    cout << "Total appointments today: " << totalToday << endl;
    cout << "(Pending: " << pendingCount
        << " Completed: " << completedCount
        << " No-show: " << noshowCount
        << " Cancelled: " << cancelledCount << ")" << endl;

    // revenue collected today from paid bills
    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    float revenueToday = 0.0f;
    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getDate() == today &&
            allBills[i].getStatus() == "paid") {
            revenueToday += allBills[i].getAmount();
        }
    }

    cout << "\nRevenue collected today: PKR " << revenueToday << endl;

    // patients with outstanding unpaid bills
    cout << "\nPatients with outstanding unpaid bills:" << endl;
    cout << "----------------------------" << endl;

    Patient* allPatients = patientStorage.getAll();
    int      totalPatient = patientStorage.size();

    for (int i = 0; i < totalPatient; i++) {
        float totalOwed = 0.0f;

        for (int j = 0; j < totalBill; j++) {
            if (allBills[j].getPatientId() == allPatients[i].getId() &&
                allBills[j].getStatus() == "unpaid") {
                totalOwed += allBills[j].getAmount();
            }
        }

        if (totalOwed > 0) {
            cout << "Patient: " << allPatients[i].getName()
                << " | Total Owed: PKR " << totalOwed << endl;
        }
    }

    // doctor wise summary for today
    cout << "\nDoctor-wise Summary for Today:" << endl;
    cout << "----------------------------" << endl;

    Doctor* allDoctors = doctorStorage.getAll();
    int     totalDoctor = doctorStorage.size();

    for (int i = 0; i < totalDoctor; i++) {
        int docCompleted = 0;
        int docPending = 0;
        int docNoshow = 0;

        for (int j = 0; j < totalAppt; j++) {
            if (allAppts[j].getDoctorId() == allDoctors[i].getId() &&
                allAppts[j].getDate() == today) {

                if (allAppts[j].getStatus() == "completed") docCompleted++;
                else if (allAppts[j].getStatus() == "pending") docPending++;
                else if (allAppts[j].getStatus() == "noshow") docNoshow++;
            }
        }

        // only show doctors who had activity today
        if (docCompleted + docPending + docNoshow > 0) {
            cout << "Dr. " << allDoctors[i].getName()
                << " | Completed: " << docCompleted
                << " | Pending: " << docPending
                << " | No-show: " << docNoshow
                << endl;
        }
    }
}


// ------------------------------------------------------------
// runAdminMenu()
// runs the full admin menu loop until logout
// ------------------------------------------------------------
void runAdminMenu() {
    int choice = 0;

    while (true) {
        adminObj.showMenu();
        cin >> choice;

        if (!Validator::isValidMenuChoice(choice, 1, 10)) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (choice == 1)  addDoctor();
        else if (choice == 2)  removeDoctor();
        else if (choice == 3)  viewAllPatients();
        else if (choice == 4)  viewAllDoctors();
        else if (choice == 5)  viewAllAppointments();
        else if (choice == 6)  viewUnpaidBills();
        else if (choice == 7)  dischargePatientAdmin();
        else if (choice == 8)  FileHandler::viewSecurityLog();
        else if (choice == 9)  generateDailyReport();
        else if (choice == 10) {
            cout << "Logging out..." << endl;
            break;
        }
    }
}


// MAIN FUNCTION
// just a sequence of function calls as required
int main() {
    // load all data from files on startup
    loadAllData();

    int choice = 0;

    while (true) {

        // display startup menu
        cout << "\n=======================================" << endl;
        cout << "Welcome to HealthCare Hospital Management System" << endl;
        cout << "=======================================" << endl;
        cout << "Login as:" << endl;
        cout << "1. Patient" << endl;
        cout << "2. Doctor" << endl;
        cout << "3. Admin" << endl;
        cout << "4. Exit" << endl;
        cout << "=======================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (!Validator::isValidMenuChoice(choice, 1, 4)) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (choice == 1) {
            // patient login
            Patient* patient = loginPatient();
            if (patient != nullptr) {
                runPatientMenu(patient);
            }
        }
        else if (choice == 2) {
            // doctor login
            Doctor* doctor = loginDoctor();
            if (doctor != nullptr) {
                runDoctorMenu(doctor);
            }
        }
        else if (choice == 3) {
            // admin login
            bool success = loginAdmin();
            if (success) {
                runAdminMenu();
            }
        }
        else if (choice == 4) {
            cout << "Thank you for using HealthCare. Goodbye!" << endl;
            break;
        }
    }

    return 0;
}