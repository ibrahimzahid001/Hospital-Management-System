#ifndef PATIENT_H
#define PATIENT_H

// ============================================================
// Patient.h
// Represents a registered patient in HealthCare
// Inherits from Person (id, name, contact, password)
// Adds: age, gender, balance
// Overloads: +=, -=, ==, 
// ============================================================

#include "Person.h"

class Patient : public Person {
private:
    int    age;
    char   gender;   // 'M' or 'F'
    float  balance;

public:

    // --------------------------------------------------------
    // Constructors & Destructor
    // --------------------------------------------------------
    Patient();
    Patient(int id, string name, int age, char gender,
        string contact, string password, float balance);
    Patient(const Patient& other);
    ~Patient();

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------
    int   getAge()     const;
    char  getGender()  const;
    float getBalance() const;

    // --------------------------------------------------------
    // Setters
    // --------------------------------------------------------
    void setAge(int age);
    void setGender(char gender);
    void setBalance(float balance);

    // --------------------------------------------------------
    // Operator Overloads
    // += adds amount to balance (top up)
    // -= deducts amount from balance (booking/paying)
    // == compares two patients by ID
    // << formatted console output
    // --------------------------------------------------------
    Patient& operator+=(float amount);
    Patient& operator-=(float amount);
    bool     operator==(const Patient& other) const;

    friend ostream& operator<<(ostream& output, const Patient& source);

    // --------------------------------------------------------
    // Pure virtual implementations (inherited from Person)
    // --------------------------------------------------------
    void showMenu()       override;
    void displayInfo()    const override;
};

#endif