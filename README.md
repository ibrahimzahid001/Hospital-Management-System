# Hospital-Management-System
# HealthCore Hospital Management System

## Student Information
- Name: Ibrahim Zahid
- Roll Number: 25L-2556
- Course: Object Oriented Programming (OOP)
- Section: BCS-2A
- Semester: Spring 2026

## About the Project
A Hospital Management System built in C++ using Object Oriented 
Programming concepts. Supports three types of users: Patients, 
Doctors and Admin. Manages appointments, prescriptions, billing 
and medical records. All data is stored in .txt files and persists 
between program restarts. Built using core OOP concepts including 
inheritance, operator overloading, templates, file handling and 
custom exception handling.

## How to Compile
- Open Visual Studio 2022
- Create a new Empty C++ Project
- Add all uploaded .h files to Header Files folder
- Add all uploaded .cpp files to Source Files folder
- Place all .txt files in the project folder
- Build → Rebuild Solution

## Default Login Credentials

### Admin
- ID: 1
- Password: admin123

### Doctors
| ID | Password |
|----|----------|
| 1  | doc123   |
| 2  | doc456   |
| 3  | doc789   |
| 4  | doc321   |
| 5  | doc654   |

### Patients
| ID | Password |
|----|----------|
| 1  | pass123  |
| 2  | pass456  |
| 3  | pass789  |
| 4  | pass321  |
| 5  | pass654  |

## Features
- Login system with account lockout after 3 failed attempts
- Security log for failed login attempts
- Patient: Book and cancel appointments, view medical records,
  pay bills, top up balance
- Doctor: View appointments, write prescriptions, mark 
  appointments complete or no-show
- Admin: Add and remove doctors, discharge patients, 
  view reports, view security log
- All data persists in .txt files between sessions
- Custom exception handling for insufficient funds, 
  invalid input and slot conflicts
- Operator overloading throughout all major classes
- Generic template based Storage class for all data types

## GitHub Repository
https://github.com/ibrahimzahid001/Hospital-Management-System

## How to Run the Project
1. Download all files from this repository
2. Open Visual Studio 2022
3. Create a new Empty C++ Project
4. Add all .h files to Header Files folder
5. Add all .cpp files to Source Files folder
6. Place all .txt files in the project folder
7. Set Working Directory to $(ProjectDir) in project Properties
8. Build and run with Ctrl + F5
