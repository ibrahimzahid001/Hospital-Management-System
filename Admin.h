#ifndef ADMIN_H
#define ADMIN_H

// ============================================================
// Admin.h
// Represents the system administrator in HealthCare
// Inherits from Person (id, name, contact, password)
// Only one admin exists — loaded from admin.txt on startup
// No operator overloads needed for Admin
// ============================================================

#include "Person.h"

class Admin : public Person {
public:

    // --------------------------------------------------------
    // Constructors & Destructor
    // Admin is simpler than Patient/Doctor
    // no extra private attributes needed
    // --------------------------------------------------------
    Admin();
    Admin(int id, string name, string contact, string password);
    Admin(const Admin& other);
    ~Admin();

    // --------------------------------------------------------
    // Pure virtual implementations (inherited from Person)
    // --------------------------------------------------------
    void showMenu()          override;
    void displayInfo() const override;
};

#endif