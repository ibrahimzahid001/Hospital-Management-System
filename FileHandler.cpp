#define _CRT_SECURE_NO_WARNINGS
#include "FileHandler.h"
#include <ctime>    // for time(), localtime(), strftime()


// FileHandler.cpp
// Definitions for FileHandler class
// ALL file I/O happens here and nowhere else


// getCurrentTimestamp()
// used for security log entries
string FileHandler::getCurrentTimestamp() {
    time_t now = time(0);
    tm* timePtr = localtime(&now);
    char   buffer[30];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timePtr);
    return string(buffer);
}





// ------------------------------------------------------------
// loadPatients()
// reads patients.txt line by line
// format: patient_id,name,age,gender,contact,password,balance
// ------------------------------------------------------------
void FileHandler::loadPatients(Storage<Patient>& storage) {
    ifstream file("patients.txt");
    // throw exception if file cant be opened
    if (!file.is_open()) {
        throw FileNotFoundException("Error: patients.txt could not be opened.");
    }

    string line;
    while (getline(file, line)) {

        // skip empty lines
        if (line.empty()) continue;

        stringstream ss(line);
        string token;

        // parse each comma separated field
        int    id;
        string name;
        int    age;
        char   gender;
        string contact;
        string password;
        float  balance;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); age = stoi(token);
        getline(ss, token, ','); gender = token[0];
        getline(ss, contact, ',');
        getline(ss, password, ',');
        getline(ss, token, ','); balance = stof(token);

        // create Patient object and add to storage
        Patient p(id, name, age, gender, contact, password, balance);
        storage.add(p);
    }

    file.close();
}


// ------------------------------------------------------------
// loadDoctors()
// reads doctors.txt line by line
// format: doctor_id,name,specialization,contact,password,fee
// ------------------------------------------------------------
void FileHandler::loadDoctors(Storage<Doctor>& storage) {
    ifstream file("doctors.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: doctors.txt could not be opened.");
    }

    string line;
    while (getline(file, line)) {

        if (line.empty()) continue;

        stringstream ss(line);
        string token;

        int    id;
        string name;
        string specialization;
        string contact;
        string password;
        float  fee;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, specialization, ',');
        getline(ss, contact, ',');
        getline(ss, password, ',');
        getline(ss, token, ','); fee = stof(token);

        Doctor d(id, name, specialization, contact, password, fee);
        storage.add(d);
    }

    file.close();
}


// ------------------------------------------------------------
// loadAdmin()
// reads admin.txt — only one admin exists
// format: admin_id,name,password
// ------------------------------------------------------------
void FileHandler::loadAdmin(Admin& admin) {
    ifstream file("admin.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: admin.txt could not be opened.");
    }

    string line;
    if (getline(file, line)) {

        if (!line.empty()) {
            stringstream ss(line);
            string token;

            int    id;
            string name;
            string password;

            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, password, ',');

            // contact is not in admin.txt so we pass empty string
            admin = Admin(id, name, "", password);
        }
    }

    file.close();
}


// ------------------------------------------------------------
// loadAppointments()
// reads appointments.txt line by line
// format: appointment_id,patient_id,doctor_id,
//         date,time_slot,status
// ------------------------------------------------------------
void FileHandler::loadAppointments(Storage<Appointment>& storage) {
    ifstream file("appointments.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: appointments.txt could not be opened.");
    }

    string line;
    while (getline(file, line)) {

        if (line.empty()) continue;

        stringstream ss(line);
        string token;

        int    appointmentId;
        int    patientId;
        int    doctorId;
        string date;
        string timeSlot;
        string status;

        getline(ss, token, ','); appointmentId = stoi(token);
        getline(ss, token, ','); patientId = stoi(token);
        getline(ss, token, ','); doctorId = stoi(token);
        getline(ss, date, ',');
        getline(ss, timeSlot, ',');
        getline(ss, status, ',');

        Appointment a(appointmentId, patientId, doctorId,
            date, timeSlot, status);
        storage.add(a);
    }

    file.close();
}


// ------------------------------------------------------------
// loadBills()
// reads bills.txt line by line
// format: bill_id,patient_id,appointment_id,amount,status,date
// ------------------------------------------------------------
void FileHandler::loadBills(Storage<Bill>& storage) {
    ifstream file("bills.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: bills.txt could not be opened.");
    }

    string line;
    while (getline(file, line)) {

        if (line.empty()) continue;

        stringstream ss(line);
        string token;

        int    billId;
        int    patientId;
        int    appointmentId;
        float  amount;
        string status;
        string date;

        getline(ss, token, ','); billId = stoi(token);
        getline(ss, token, ','); patientId = stoi(token);
        getline(ss, token, ','); appointmentId = stoi(token);
        getline(ss, token, ','); amount = stof(token);
        getline(ss, status, ',');
        getline(ss, date, ',');

        Bill b(billId, patientId, appointmentId, amount, status, date);
        storage.add(b);
    }

    file.close();
}


// ------------------------------------------------------------
// loadPrescriptions()
// reads prescriptions.txt line by line
// format: prescription_id,appointment_id,patient_id,
//         doctor_id,date,medicines,notes
// ------------------------------------------------------------
void FileHandler::loadPrescriptions(Storage<Prescription>& storage) {
    ifstream file("prescriptions.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: prescriptions.txt could not be opened.");
    }

    string line;
    while (getline(file, line)) {

        if (line.empty()) continue;

        stringstream ss(line);
        string token;

        int    prescriptionId;
        int    appointmentId;
        int    patientId;
        int    doctorId;
        string date;
        string medicines;
        string notes;

        getline(ss, token, ','); prescriptionId = stoi(token);
        getline(ss, token, ','); appointmentId = stoi(token);
        getline(ss, token, ','); patientId = stoi(token);
        getline(ss, token, ','); doctorId = stoi(token);
        getline(ss, date, ',');
        getline(ss, medicines, ',');
        getline(ss, notes, ',');

        Prescription p(prescriptionId, appointmentId, patientId,
            doctorId, date,
            medicines.c_str(), notes.c_str());
        storage.add(p);
    }

    file.close();
}





// ------------------------------------------------------------
// appendPatient()
// format: patient_id,name,age,gender,contact,password,balance
// ------------------------------------------------------------
void FileHandler::appendPatient(const Patient& patient) {
    ofstream file("patients.txt", ios::app);

    if (!file.is_open()) {
        throw FileNotFoundException("Error: patients.txt could not be opened.");
    }

    file << patient.getId() << ","
        << patient.getName() << ","
        << patient.getAge() << ","
        << patient.getGender() << ","
        << patient.getContact() << ","
        << patient.getPassword() << ","
        << patient.getBalance() << "\n";

    file.close();
}


// ------------------------------------------------------------
// appendDoctor()
// format: doctor_id,name,specialization,contact,password,fee
// ------------------------------------------------------------
void FileHandler::appendDoctor(const Doctor& doctor) {
    ofstream file("doctors.txt", ios::app);

    if (!file.is_open()) {
        throw FileNotFoundException("Error: doctors.txt could not be opened.");
    }

    file << doctor.getId() << ","
        << doctor.getName() << ","
        << doctor.getSpecialization() << ","
        << doctor.getContact() << ","
        << doctor.getPassword() << ","
        << doctor.getFee() << "\n";

    file.close();
}


// ------------------------------------------------------------
// appendAppointment()
// format: appointment_id,patient_id,doctor_id,
//         date,time_slot,status
// ------------------------------------------------------------
void FileHandler::appendAppointment(const Appointment& appointment) {
    ofstream file("appointments.txt", ios::app);

    if (!file.is_open()) {
        throw FileNotFoundException("Error: appointments.txt could not be opened.");
    }

    file << appointment.getAppointmentId() << ","
        << appointment.getPatientId() << ","
        << appointment.getDoctorId() << ","
        << appointment.getDate() << ","
        << appointment.getTimeSlot() << ","
        << appointment.getStatus() << "\n";

    file.close();
}


// ------------------------------------------------------------
// appendBill()
// format: bill_id,patient_id,appointment_id,amount,status,date
// ------------------------------------------------------------
void FileHandler::appendBill(const Bill& bill) {
    ofstream file("bills.txt", ios::app);

    if (!file.is_open()) {
        throw FileNotFoundException("Error: bills.txt could not be opened.");
    }

    file << bill.getBillId() << ","
        << bill.getPatientId() << ","
        << bill.getAppointmentId() << ","
        << bill.getAmount() << ","
        << bill.getStatus() << ","
        << bill.getDate() << "\n";

    file.close();
}


// ------------------------------------------------------------
// appendPrescription()
// format: prescription_id,appointment_id,patient_id,
//         doctor_id,date,medicines,notes
// ------------------------------------------------------------
void FileHandler::appendPrescription(const Prescription& prescription) {
    ofstream file("prescriptions.txt", ios::app);

    if (!file.is_open()) {
        throw FileNotFoundException("Error: prescriptions.txt could not be opened.");
    }

    file << prescription.getPrescriptionId() << ","
        << prescription.getAppointmentId() << ","
        << prescription.getPatientId() << ","
        << prescription.getDoctorId() << ","
        << prescription.getDate() << ","
        << prescription.getMedicines() << ","
        << prescription.getNotes() << "\n";

    file.close();
}




// ------------------------------------------------------------
// updatePatient()
// rewrites patients.txt with all current patient data
// ------------------------------------------------------------
void FileHandler::updatePatient(Storage<Patient>& storage) {
    ofstream file("patients.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: patients.txt could not be opened.");
    }

    Patient* all = storage.getAll();
    int      total = storage.size();

    for (int i = 0; i < total; i++) {
        file << all[i].getId() << ","
            << all[i].getName() << ","
            << all[i].getAge() << ","
            << all[i].getGender() << ","
            << all[i].getContact() << ","
            << all[i].getPassword() << ","
            << all[i].getBalance() << "\n";
    }

    file.close();
}


// ------------------------------------------------------------
// updateDoctor()
// rewrites doctors.txt with all current doctor data
// ------------------------------------------------------------
void FileHandler::updateDoctor(Storage<Doctor>& storage) {
    ofstream file("doctors.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: doctors.txt could not be opened.");
    }

    Doctor* all = storage.getAll();
    int     total = storage.size();

    for (int i = 0; i < total; i++) {
        file << all[i].getId() << ","
            << all[i].getName() << ","
            << all[i].getSpecialization() << ","
            << all[i].getContact() << ","
            << all[i].getPassword() << ","
            << all[i].getFee() << "\n";
    }

    file.close();
}


// ------------------------------------------------------------
// updateAppointment()
// rewrites appointments.txt with all current appointment data
// ------------------------------------------------------------
void FileHandler::updateAppointment(Storage<Appointment>& storage) {
    ofstream file("appointments.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: appointments.txt could not be opened.");
    }

    Appointment* all = storage.getAll();
    int          total = storage.size();

    for (int i = 0; i < total; i++) {
        file << all[i].getAppointmentId() << ","
            << all[i].getPatientId() << ","
            << all[i].getDoctorId() << ","
            << all[i].getDate() << ","
            << all[i].getTimeSlot() << ","
            << all[i].getStatus() << "\n";
    }

    file.close();
}


// ------------------------------------------------------------
// updateBill()
// rewrites bills.txt with all current bill data
// ------------------------------------------------------------
void FileHandler::updateBill(Storage<Bill>& storage) {
    ofstream file("bills.txt");

    if (!file.is_open()) {
        throw FileNotFoundException("Error: bills.txt could not be opened.");
    }

    Bill* all = storage.getAll();
    int   total = storage.size();

    for (int i = 0; i < total; i++) {
        file << all[i].getBillId() << ","
            << all[i].getPatientId() << ","
            << all[i].getAppointmentId() << ","
            << all[i].getAmount() << ","
            << all[i].getStatus() << ","
            << all[i].getDate() << "\n";
    }

    file.close();
}





// ------------------------------------------------------------
// deletePatient()
// removes patient from storage then rewrites patients.txt
// ------------------------------------------------------------
void FileHandler::deletePatient(int id, Storage<Patient>& storage) {
    storage.removeById(id);
    updatePatient(storage);
}


// ------------------------------------------------------------
// deleteDoctor()
// removes doctor from storage then rewrites doctors.txt
// ------------------------------------------------------------
void FileHandler::deleteDoctor(int id, Storage<Doctor>& storage) {
    storage.removeById(id);
    updateDoctor(storage);
}


// ------------------------------------------------------------
// deleteAppointment()
// removes appointment from storage then rewrites appointments.txt
// ------------------------------------------------------------
void FileHandler::deleteAppointment(int id, Storage<Appointment>& storage) {
    storage.removeById(id);
    updateAppointment(storage);
}


// ------------------------------------------------------------
// deleteBill()
// removes bill from storage then rewrites bills.txt
// ------------------------------------------------------------
void FileHandler::deleteBill(int id, Storage<Bill>& storage) {
    storage.removeById(id);
    updateBill(storage);
}


// ------------------------------------------------------------
// deletePrescription()
// removes prescription from storage
// then rewrites prescriptions.txt
// ------------------------------------------------------------
void FileHandler::deletePrescription(int id,
    Storage<Prescription>& storage) {
    storage.removeById(id);

    // rewrite prescriptions.txt without deleted record
    ofstream file("prescriptions.txt");

    if (!file.is_open()) {
        throw FileNotFoundException(
            "Error: prescriptions.txt could not be opened.");
    }

    Prescription* all = storage.getAll();
    int           total = storage.size();

    for (int i = 0; i < total; i++) {
        file << all[i].getPrescriptionId() << ","
            << all[i].getAppointmentId() << ","
            << all[i].getPatientId() << ","
            << all[i].getDoctorId() << ","
            << all[i].getDate() << ","
            << all[i].getMedicines() << ","
            << all[i].getNotes() << "\n";
    }

    file.close();
}



// logSecurityEvent()
// appends a failed login attempt to security_log.txt
// format: timestamp,role,entered_id,result

void FileHandler::logSecurityEvent(const string& role,
    const string& enteredId,
    const string& result) {
    ofstream file("security_log.txt", ios::app);

    if (!file.is_open()) {
        return; // silently fail for log — dont crash the program
    }

    file << getCurrentTimestamp() << ","
        << role << ","
        << enteredId << ","
        << result << "\n";

    file.close();
}



// viewSecurityLog()
// reads and displays security_log.txt line by line

void FileHandler::viewSecurityLog() {
    ifstream file("security_log.txt");

    if (!file.is_open()) {
        cout << "No security events logged." << endl;
        return;
    }

    string line;
    bool   empty = true;

    while (getline(file, line)) {
        if (!line.empty()) {
            cout << line << endl;
            empty = false;
        }
    }

    if (empty) {
        cout << "No security events logged." << endl;
    }

    file.close();
}


// 
// dischargePatient()
// copies patient + all their records to discharged.txt
// then deletes from all active files
// 
void FileHandler::dischargePatient(int patientId,
    Storage<Patient>& patientStorage,
    Storage<Appointment>& appointmentStorage,
    Storage<Bill>& billStorage,
    Storage<Prescription>& prescriptionStorage) {

    // open discharged.txt in append mode
    ofstream discharged("discharged.txt", ios::app);

    if (!discharged.is_open()) {
        throw FileNotFoundException(
            "Error: discharged.txt could not be opened.");
    }

    // --------------------------------------------------------
    // write patient record to discharged.txt
    // --------------------------------------------------------
    Patient* p = patientStorage.findById(patientId);
    if (p != nullptr) {
        discharged << p->getId() << ","
            << p->getName() << ","
            << p->getAge() << ","
            << p->getGender() << ","
            << p->getContact() << ","
            << p->getPassword() << ","
            << p->getBalance() << "\n";
    }

    // --------------------------------------------------------
    // write all appointments for this patient to discharged.txt
    // --------------------------------------------------------
    Appointment* allAppts = appointmentStorage.getAll();
    int          totalAppt = appointmentStorage.size();

    for (int i = 0; i < totalAppt; i++) {
        if (allAppts[i].getPatientId() == patientId) {
            discharged << allAppts[i].getAppointmentId() << ","
                << allAppts[i].getPatientId() << ","
                << allAppts[i].getDoctorId() << ","
                << allAppts[i].getDate() << ","
                << allAppts[i].getTimeSlot() << ","
                << allAppts[i].getStatus() << "\n";
        }
    }

    // --------------------------------------------------------
    // write all bills for this patient to discharged.txt
    // --------------------------------------------------------
    Bill* allBills = billStorage.getAll();
    int   totalBill = billStorage.size();

    for (int i = 0; i < totalBill; i++) {
        if (allBills[i].getPatientId() == patientId) {
            discharged << allBills[i].getBillId() << ","
                << allBills[i].getPatientId() << ","
                << allBills[i].getAppointmentId() << ","
                << allBills[i].getAmount() << ","
                << allBills[i].getStatus() << ","
                << allBills[i].getDate() << "\n";
        }
    }

    // --------------------------------------------------------
    // write all prescriptions for this patient to discharged.txt
    // --------------------------------------------------------
    Prescription* allPres = prescriptionStorage.getAll();
    int           totalPre = prescriptionStorage.size();

    for (int i = 0; i < totalPre; i++) {
        if (allPres[i].getPatientId() == patientId) {
            discharged << allPres[i].getPrescriptionId() << ","
                << allPres[i].getAppointmentId() << ","
                << allPres[i].getPatientId() << ","
                << allPres[i].getDoctorId() << ","
                << allPres[i].getDate() << ","
                << allPres[i].getMedicines() << ","
                << allPres[i].getNotes() << "\n";
        }
    }

    discharged.close();

    // --------------------------------------------------------
    // now delete patient records from all active storages
    // and rewrite all files
    // --------------------------------------------------------

    // delete all appointments for this patient
    Appointment* appts = appointmentStorage.getAll();
    int          apptTotal = appointmentStorage.size();

    for (int i = apptTotal - 1; i >= 0; i--) {
        if (appts[i].getPatientId() == patientId) {
            appointmentStorage.removeById(appts[i].getAppointmentId());
        }
    }
    updateAppointment(appointmentStorage);

    // delete all bills for this patient
    Bill* bills = billStorage.getAll();
    int   billTotal = billStorage.size();

    for (int i = billTotal - 1; i >= 0; i--) {
        if (bills[i].getPatientId() == patientId) {
            billStorage.removeById(bills[i].getBillId());
        }
    }
    updateBill(billStorage);

    // delete all prescriptions for this patient
    Prescription* pres = prescriptionStorage.getAll();
    int           preTotal = prescriptionStorage.size();

    for (int i = preTotal - 1; i >= 0; i--) {
        if (pres[i].getPatientId() == patientId) {
            prescriptionStorage.removeById(
                pres[i].getPrescriptionId());
        }
    }

    // rewrite prescriptions.txt without deleted records
    ofstream presFile("prescriptions.txt");
    Prescription* presAll = prescriptionStorage.getAll();
    int           presTotal = prescriptionStorage.size();

    for (int i = 0; i < presTotal; i++) {
        presFile << presAll[i].getPrescriptionId() << ","
            << presAll[i].getAppointmentId() << ","
            << presAll[i].getPatientId() << ","
            << presAll[i].getDoctorId() << ","
            << presAll[i].getDate() << ","
            << presAll[i].getMedicines() << ","
            << presAll[i].getNotes() << "\n";
    }

    presFile.close();

    // finally delete the patient record itself
    deletePatient(patientId, patientStorage);
}