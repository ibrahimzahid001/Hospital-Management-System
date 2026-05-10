#ifndef STORAGE_H
#define STORAGE_H

// ============================================================
// Storage.h
// Generic template class for storing any type in HealthCare
// Internally uses a fixed array T data[100]
// No vectors allowed as per project requirements
// Used for: Storage<Patient>, Storage<Doctor>,
//           Storage<Appointment>, Storage<Bill>
//           Storage<Prescription>
// NOTE: Template classes must be fully defined in .h file
//       No separate .cpp file for this class
// ============================================================

#include <iostream>
using namespace std;

template <typename T>
class Storage {
private:
    T   data[100]; // fixed array — no vectors allowed
    int count;     // how many items currently stored

public:

    // --------------------------------------------------------
    // Default constructor
    // initializes count to 0
    // array elements use their own default constructors
    // --------------------------------------------------------
    Storage() {
        count = 0;
    }


    // --------------------------------------------------------
    // add()
    // adds a new item to the storage
    // if storage is full prints a message and returns false
    // returns true if added successfully
    // --------------------------------------------------------
    bool add(const T& item) {
        if (count >= 100) {
            cout << "Storage is full. Cannot add more items." << endl;
            return false;
        }
        data[count] = item;
        count++;
        return true;
    }


    // --------------------------------------------------------
    // removeById()
    // removes an item by its ID
    // shifts all items after it one position left
    // to fill the gap — no holes in the array
    // returns true if removed, false if not found
    // --------------------------------------------------------
    bool removeById(int id) {
        int foundIndex = -1;

        // find the item with matching id
        for (int i = 0; i < count; i++) {
            if (data[i].getId() == id) {
                foundIndex = i;
                break;
            }
        }

        // if not found return false
        if (foundIndex == -1) {
            return false;
        }

        // shift everything after foundIndex one step left
        // this fills the gap left by the removed item
        for (int i = foundIndex; i < count - 1; i++) {
            data[i] = data[i + 1];
        }

        count--;
        return true;
    }


    // --------------------------------------------------------
    // findById()
    // searches for an item by its ID
    // returns a pointer to the item if found
    // returns nullptr if not found
    // caller must check for nullptr before using result
    // --------------------------------------------------------
    T* findById(int id) {
        for (int i = 0; i < count; i++) {
            if (data[i].getId() == id) {
                return &data[i]; // return address of found item
            }
        }
        return nullptr; // not found
    }


    // --------------------------------------------------------
    // getAll()
    // returns pointer to the internal data array
    // used when we need to loop through all items
    // e.g. displaying all patients, all appointments etc.
    // --------------------------------------------------------
    T* getAll() {
        return data;
    }


    // --------------------------------------------------------
    // size()
    // returns how many items are currently stored
    // --------------------------------------------------------
    int size() const {
        return count;
    }


    // --------------------------------------------------------
    // updateById()
    // finds item by ID and replaces it with updated item
    // used after loading from file and modifying an object
    // returns true if updated, false if not found
    // --------------------------------------------------------
    bool updateById(int id, const T& updatedItem) {
        for (int i = 0; i < count; i++) {
            if (data[i].getId() == id) {
                data[i] = updatedItem;
                return true;
            }
        }
        return false; // not found
    }


    // --------------------------------------------------------
    // clear()
    // resets the storage to empty
    // used on restart to reload fresh from files
    // --------------------------------------------------------
    void clear() {
        count = 0;
    }
};

#endif