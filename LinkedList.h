//
// Created by Anvar on 1/30/2022.
//

#ifndef PROJECT1_LINKEDLIST_H
#define PROJECT1_LINKEDLIST_H

#include "node.cpp"

template <class T>
class LinkedList {
public:
    LinkedList():head{nullptr}, tail{nullptr}, listsize{0}{}

    // accessors
    bool contains(T item) {
        node<T> *trav = head;
        while(trav->value != item || trav->next != nullptr) {
            trav = trav->next;
        }
        return (trav->next != nullptr);
    }

    T get(int index) {
        if (index < 0 || index >= listsize) {
            std::cout << "Invalid index";
            return -1;
        }
        node<T> *trav = head;
        for (int i = 0; i < index; i++) {
            trav = trav->next;
        }
        return (trav->data);
    }

    int size() {
        return listsize;
    }

    void add(int index, T item) {
        if (index < 0 || index >= listsize) {
            std::cout << "Invalid index";
            return;
        }
        if (index == 0) {
            auto n = new node<T>;
            n->next = head;
            n->data = item;
            head = n;
            listsize++;
            return;
        }

        node<T> *trav = head;
        for (int i = 0; i < index-1; i++) {
            trav = trav->next;
        }
        auto n = new node<T>;
        n->data = item;
        n->next = trav->next;
        trav->next = n;
        listsize++;
    }

    void add(T item) {
        if (head == nullptr) {
            head = new node<T>;
            head->data = item;
            head->next = nullptr;
        } else if (tail == nullptr) {
            tail = new node<T>;
            head->next = tail;
            tail->data = item;
            tail->next = nullptr;
        } else {
            auto n = new node<T>;
            n->data = item;
            n->next = nullptr;
            tail->next = n;
            tail = n;
        }

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

        node<T> *trav = head;
        for (int i = 0; i < index-1; i++) {
            trav = trav->next;
        }
        auto n = trav->next;
        trav->next = trav->next->next;
        delete[] n;
        listsize--;
    }

    void remove_after(T item) {
        int index = indexof(item);
        remove(index+1);
    }

private:

    node<T> *head;
    node<T> *tail;
    int listsize;

    int indexof(T item) {
        node<T> *trav = head;
        int counter = 0;
        while(trav->data != item && trav-> next != nullptr) {
            counter++;
            trav = trav->next;
        }
        if (trav->next == nullptr) {
            std::cout << "Such element does not exist\n";
            return -1;
        }
        return (counter);
    }
};


#endif //PROJECT1_LINKEDLIST_H
