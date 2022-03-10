//
// Created by Anvar on 1/29/2022.
//

#ifndef PROJECT1_ARRAYLIST_H
#define PROJECT1_ARRAYLIST_H

#include <iostream>

template <class T>
class ArrayList {
public:
    // constructor
    ArrayList():data{new T[1]}, listsize{0}, arrlength{1}{}

    // accessors
    bool contains(T item) {
        for (int i = 0; i < listsize; i++) {
            if (data[i] == item) return true;
        }
        return false;
    }

    T get(int index) {
        if (index < 0 || index >= listsize) {
            std::cout << "Invalid index";
            return -1;
        }
        return data[index];
    }

    int size() {
        return listsize;
    }

    void add(int index, T item) {
        if (index < 0 || index >= listsize) {
            std::cout << "Invalid index";
            return;
        }
        if (needtoresize())
            resize();

        for (int i = listsize; i > index; i--) {
            data[i] = data[i-1];
        }
        data[index] = item;
        listsize++;
    }

    void add(T item) {
        if (needtoresize())
            resize();
        data[listsize] = item;
        listsize++;
    }

    void add_after(T from, T item) {
        int pos = indexof(from);
        if (pos == -1) {
            //        std::cout << "Such element does not exist";
            return;
        }
        add(pos+1, item);
    }

    void remove(int index) {
        if (index < 0 || index >= listsize) {
            std::cout << "Invalid index";
            return;
        }

        for (int i = index; i < listsize; i++) {
            data[i] = data[i+1];
        }
        listsize--;
    }

    void remove_after(T item) {
        int index = indexof(item);
        remove(index+1);
    }

private:

    T *data;
    int arrlength;
    int listsize;

    void resize() {
        if (needtoresize()) {
            T *temparr = new T[listsize*2];
            for (int i = 0; i < listsize; i++) {
                temparr[i] = data[i];
            }
            delete []data;
            data = temparr;
            arrlength *= 2;
        }
    }

    bool needtoresize() {
        return listsize == arrlength;
    }

    int indexof(T item) {
        if (!contains(item)) {
            std::cout << "Such element does not exist";
            return -1;
        }
        for (int i = 0; i < listsize; i++) {
            if (data[i] == item) return i;
        }
        return -1;
    }

    // int lastindexof (T item);

};

#endif
