//
// Created by Anvar on 2/2/2022.
//

#ifndef PROJECT1_LINKEDHASHMAP_H
#define PROJECT1_LINKEDHASHMAP_H

#include <vector>
#include <list>
#include <iostream>
#include <math.h>

using namespace std;

template <class K, class V>
class Entry {
public:

    Entry(K k, V v): key{k}, value{v} {};

    void setKey(K k) {
        key = k;
    }
    void setValue(V v) {
        value = v;
    }

    K getKey() {
        return key;
    }
    V getValue() {
        return value;
    }

    bool &operator==(Entry a) {
        return a.key == this->key && a.value == this->value;
    }

private:

    K key;
    V value;

};

template <class K, class V>
class LinkedHashMap {
public:

    LinkedHashMap(int capacity): capacity{capacity}, buckets{vector<list<Entry<K, V>>>(capacity)}  {};

    V get(K key) {
        if (contains(key))
            return findFirst(key)->getValue();

        return NULL;
    }

    void insert(K key, V value) {

         int index = getIndex(key);

        if (contains(key)) {
            auto oldEntry = findFirst(key);
            oldEntry->setValue(value);
        } else {
            buckets[index].push_front(Entry<K, V> (key, value));
        }
    }

    void remove(K k) {
        if (contains(k)) {
            int index = getIndex(k);

            auto bucketPtr = &buckets[index];

            for (auto it = bucketPtr->begin(); it != bucketPtr->end(); it++) {
                if (it->getKey() == k) {
                    buckets[index].erase(it);
                    return;
                }
            }
        }
        return;
    }

    int size() {

        int totalSize = 0;

        for (auto bucket : buckets) {
            totalSize += bucket.size();
        }

        return(totalSize);

    }

    Entry<K, V>* findFirst(K k) {
        int index = getIndex(k);

        auto bucketPtr = &buckets[index];

        for (auto it = bucketPtr->begin(); it != bucketPtr->end(); it++) {
            if (it->getKey() == k) {
                return &(*it);
            }
        }
        return nullptr;
    };


private:

    vector<list<Entry<K, V>>> buckets;
    int capacity;

    int getIndex (K key) {
        auto hashfunc = hash<K>();

        // hashing function
        int hashcode = hashfunc(key);

        // getting index

        int index = abs(hashcode) % capacity;

//        cout << "key " << key << " was mapped to index " << index << endl;
        return index;
    }

    bool contains(K k) {
        return findFirst(k) != nullptr;
    }
};


#endif //PROJECT1_LINKEDHASHMAP_H
