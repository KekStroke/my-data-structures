#include <iostream>

#include "ArrayList.h"
#include "QueueList.h"
#include "LinkedList.h"

int main() {
    LinkedList<int> mylist;

    mylist.add(1);
    mylist.add(2);
    mylist.add(3);
    mylist.add(2);
    mylist.add(0, 10);
    mylist.add_after(10, 20);

    for (int i = 0; i < mylist.size(); i++) {
        std::cout << mylist.get(i) << " ";
    } std::cout << std::endl;

    mylist.remove(1);

    for (int i = 0; i < mylist.size(); i++) {
        std::cout << mylist.get(i) << " ";
    } std::cout << std::endl;

    mylist.remove_after(10);

    for (int i = 0; i < mylist.size(); i++) {
        std::cout << mylist.get(i) << " ";
    } std::cout << std::endl;

    ArrayList<int> mylist1;

    mylist1.add(1);
    mylist1.add(2);
    mylist1.add(3);
    mylist1.add(2);
    mylist1.add(0, 10);
    mylist1.add_after(10, 20);

    for (int i = 0; i < mylist1.size(); i++) {
        std::cout << mylist1.get(i) << " ";
    } std::cout << std::endl;

    mylist1.remove(1);

    for (int i = 0; i < mylist1.size(); i++) {
        std::cout << mylist1.get(i) << " ";
    } std::cout << std::endl;

    mylist1.remove_after(10);

    for (int i = 0; i < mylist1.size(); i++) {
        std::cout << mylist1.get(i) << " ";
    } std::cout << std::endl;

    QueueList<int> myqueue;

    for (int i = 1; i < 20; i++) {
        myqueue.enqueue(i);
    }

    int currentsize = myqueue.size();
    for (int i = 0; i < currentsize; i++) {
        std::cout << myqueue.dequeue() << " ";
    } std::cout << '\n'<<'\n';

    int count = 0;
    while (count < 10) {
        for (int i = 0; i < 5; i++) {
            myqueue.enqueue(i);
        }

        currentsize = myqueue.size();
        for (int i = 0; i < currentsize; i++) {
            std::cout << myqueue.dequeue() << " ";
        } std::cout << '\n';

        count++;
    }

//    LinkedList<int> mylist2;
//
//    mylist2.add(1);
//
//    for (int i = 0; i < 10; i++) {
//        mylist2.add(i);
//        std::cout << mylist2.get(i) << ' ';
//    }

    return 0;
}
