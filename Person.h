#ifndef PERSON_H
#define PERSON_H

// ============================================================
// Person.h
// Abstract base class for all user types in HealthCare
// Patient, Doctor and Admin all inherit from this class
// Cannot be instantiated directly because of pure virtual funcs
// ============================================================

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    // common attributes shared by Patient, Doctor and Admin
    int    id;
    string name;
    string contact;
    string password;

public:

    // default constructor
    Person();

    // parametrized constructor
    Person(int id, string name, string contact, string password);

    // copy constructor
    Person(const Person& other);

    // virtual destructor — must be virtual in abstract base class
    // so that when we delete a derived obj through base pointer
    // the correct destructor runs (no memory leaks)
    virtual ~Person();

    // --------------------------------------------------------
    // Getters — const because they dont modify the object
    // --------------------------------------------------------
    int    getId()       const;
    string getName()     const;
    string getContact()  const;
    string getPassword() const;

    // --------------------------------------------------------
    // Setters
    // --------------------------------------------------------
    void setId(int id);
    void setName(string name);
    void setContact(string contact);
    void setPassword(string password);

    // --------------------------------------------------------
    // Pure Virtual Functions — makes Person abstract
    // Every derived class MUST implement these
    // --------------------------------------------------------

    // for displaying the user's main menu
    virtual void showMenu() = 0;

    // for displaying basic info of the person
    virtual void displayInfo() const = 0;
};

#endif