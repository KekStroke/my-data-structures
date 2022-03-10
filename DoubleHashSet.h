//
// Created by Anvar on 1/29/2022.
//

#ifndef PROJECT1_DOUBLEHASHSET_H
#define PROJECT1_DOUBLEHASHSET_H

#include <iostream>
#include <memory>
#include <sstream>
#include <bitset>

int DEFAULT_CAPACITY = 7687;

// create enum to represent statuses of array cells is hashset
enum class SetMarker {DELETED, OCCUPIED, EMPTY};

// DoubleHashSet implementation of set
template <class T>
class DoubleHashSet {

    int cap;            // maximum capacity
    int setsize;        // amount of elements

    unique_ptr<T[]> data;           // array of actual values stored
    unique_ptr<SetMarker[]> status; // array of statuses of values

public:

    // default constructor
    explicit DoubleHashSet() {
        cap = DEFAULT_CAPACITY;
        setsize = 0;
        // initialize array filled by null values
        // to recognize empty cells from filled ones
        data = unique_ptr<T[]>(new T[cap] {});
        status = unique_ptr<SetMarker[]>(new SetMarker[cap] {SetMarker::EMPTY});
    };

    // copy constructor
    // O(n) since we need to copy each element of the array
    DoubleHashSet(const DoubleHashSet& other)
    {
        cap = other.cap;
        setsize = other.setsize;

        // allocate new memory for data & status
        data = unique_ptr<T[]>(new T[cap]{});
        status = unique_ptr<SetMarker[]>(new SetMarker[cap]{SetMarker::EMPTY});

        // make deep copy of data and status
        for (int i = 0; i < cap; i++) {
            data[i] = other.data[i];
            status[i] = other.status[i];
        }
    }

    // assign operator overloading
    // O(n) since we need to copy each element of the array
    DoubleHashSet& operator=(const DoubleHashSet& other)
    {
        cap = other.cap;
        setsize = other.cap;

        // allocate new memory for data & status
        data = unique_ptr<T[]>(new T[cap]{});
        status = unique_ptr<SetMarker[]>(new SetMarker[cap]{SetMarker::EMPTY});

        // make deep copy of data and status
        for (int i = 0; i < cap; i++) {
            data[i] = other.data[i];
            status[i] = other.status[i];
        }

        return *this;
    }

    // add item to the set
    // O(1/(1-a)) - unsuccessful search
    // O( 1/a * log(1/(1-a)) ) - successful search
    // where a = (number of deleted elements + number of elements) / capacity of set
    // Since it uses getIndexToAdd function
    void add(T item) {

        // if item is already in the set return
        if (contains(item)) {
            return;
        }

        // get index of first empty or deleted cell
        int index = getIndexToAdd(item);

        // if there are no such elements
        if (index == -1) {
            cout << "Unable to add: Such element does not exist";
            return;
        }

        // add item to free (or deleted) position
        data[index] = item;
        // mark status as OCCUPIED
        status[index] = SetMarker::OCCUPIED;
        setsize++;
    }

    // O(1/(1-a)) - unsuccessful search
    // O( 1/a * log(1/(1-a)) ) - successful search
    // where a = (number of deleted elements + number of elements) / capacity of set
    // Since it uses getIndex function
    void remove(T item) {
        // get index of free cell or index of existing item
        int index = getIndex(item);

        // if such element does not exist in set, throw an error
        if (index == -1 || status[index] != SetMarker::OCCUPIED) {
            cout << endl << "Unable to delete: Such element does not exist" << endl;
            return;
        }

        setsize--;

        // mark array as deleted
        status[index] = SetMarker::DELETED;
    }

    // return True if element exists in the set
    // return False if not
    // O(1/(1-a)) - unsuccessful search
    // O( 1/a * log(1/(1-a)) ) - successful search
    // where a = (number of deleted elements + number of elements) / capacity of set
    // Since it uses getIndex function
    bool contains(T item) {
        auto index = getIndex(item);

        // if index was found, return True
        return (index != -1 && status[index] == SetMarker::OCCUPIED);
    }

    // O(1)
    int size() {
        return setsize;
    }

    // O(1)
    bool isEmpty() {
        return setsize == 0;
    }

    // function to print all elements in the set
    // O(n) since we go through every element
    void printSet() {

        // go through each cell in the set
        for (int i = 0; i < cap; i++) {
            if (status[i] != SetMarker::EMPTY && (status[i] != SetMarker::DELETED)) {
                // if cell is occupied, print it
                cout << data[i] << " ";
            }
        }
        cout << endl;
    }

private:

    // inplementation of second hash function
    // polynomial accumulation
    unsigned int hashcode2(T value)
    {
        // define result of hash function and initial value of polynomial of base 2
        unsigned int hash_result = 0;
        unsigned int polynom = 1;

        // push value to input stream (assumed that value is string)
        // but I'm not sure. I did not check that with other data types
        std::stringstream input;
        input << value;
        // second time because in doesn't convert values correctly from the first time
        input << value;


        // declare our key (bit representation of value)
        unsigned char key;

        // read value as key
        while (input >> key) {

            // while key is positive
            while (key > 0) {

                // add last 8 bits
                hash_result += (key & 255);   // use bitmasks

                hash_result %= cap;        // make sure that value is not too big

                // multiply by polynomial of 2
                hash_result *= polynom;

                key = key >> 8;            // shift right to remove last 8 bits

                polynom *= 2;       // shift right polynomial by 1 is equivalent to taking next power of 2
                polynom %= cap;     // make sure that polynomial is not too large
            }
        }

        return hash_result;
    }

    // helper function to get index of cell occupied by the item
    // O(1/(1-a)) - unsuccessful search
    // O( 1/a * log(1/(1-a)) ) - successful search
    // where a = (number of deleted elements + number of elements) / capacity of set
    int getIndex(T item) {

        // introduce two hash functions
        auto hashfunc = hash<T>();

        // assign hashing functions
        int h1 = (hashfunc(item));

        // h2 is dependent from h1, however due to % operation we can be sure that
        // we cannot get h1 from h1, and h2 will be different for different h1
        // int h2 = 1+(h1%(cap-2));

        int h2 = hashcode2(item);

        // iterative variable for double hashing
        for (int i = 0; i < cap; i++) {

            // get index using double hashing
            int index = abs(h1 + i*h2) % cap;

            // if cell is empty, return -1 meaning that element does not exist
            if (status[index] == SetMarker::EMPTY) {
                return -1;
            } if (item == (data[index])) {
                // if cell is not empty and item is on the position
                // return position index
                return index;
            }

        }

        // if item was not found, return -1
        return -1;

    }

    // helper function to get indexes of next free or deleted
    // cells to insert items on their positions
    // O(1/(1-a)) - unsuccessful search
    // O( 1/a * log(1/(1-a)) ) - successful search
    // where a = (number of deleted elements + number of elements) / capacity of set
    int getIndexToAdd(T item) {

        // introduce two hash functions
        auto hashfunc = hash<T>();
        // auto hashfunc2 = hash<T>();

        // assign hashing functions
        int h1 = hashfunc(item);
    // int h2 = 1+(h1%(cap-2));

        int h2 = hashcode2(item);

        // iterative variable for double hashing
        for (int i = 0; i < cap; i++) {

            // get index using double hashing
            int index = abs(h1 + i * h2) % cap;

            // if cell is empty or was deleted, return its index
            if (status[index] == SetMarker::EMPTY || (status[index] == SetMarker::DELETED)) {
                return index;
            } else if (status[index] == SetMarker::OCCUPIED && data[index] == item) {
                // if cell is occupied and value there is corresponded to item
                // return -1 meaning that that value already exist and no need to add
                return -1;
            }

        }

        // return -1 if all cells are occupied
        return -1;
    }

};


#endif