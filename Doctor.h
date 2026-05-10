#ifndef DOCTOR_H
#define DOCTOR_H

// ============================================================
// Doctor.h
// Represents a doctor in HealthCare hospital system
// Inherits from Person (id, name, contact, password)
// Adds: specialization, fee
// Overloads: ==, 
// ============================================================

#include "Person.h"

class Doctor : public Person {
private:
    string specialization;
    float  fee;            // consultation fee in PKR

public:

    // --------------------------------------------------------
    // Constructors & Destructor
    // --------------------------------------------------------
    Doctor();
    Doctor(int id, string name, string specialization,
        string contact, string password, float fee);
    Doctor(const Doctor& other);
    ~Doctor();

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------
    string getSpecialization() const;
    float  getFee()            const;

    // --------------------------------------------------------
    // Setters
    // --------------------------------------------------------
    void setSpecialization(string specialization);
    void setFee(float fee);

    // --------------------------------------------------------
    // Operator Overloads
    // == compares two doctors by ID
    // << formatted console output
    // --------------------------------------------------------
    bool operator==(const Doctor& other) const;

    friend ostream& operator<<(ostream& output, const Doctor& source);

    // --------------------------------------------------------
    // Pure virtual implementations (inherited from Person)
    // --------------------------------------------------------
    void showMenu()         override;
    void displayInfo() const override;
};

#endif