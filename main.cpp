#include <iostream>
#include <string>

#include "ArrayList.h"
#include "ArrayQueue.h"
#include "LinkedList.h"
#include "LinkedHashMap.h"

int main() {
    LinkedList<int> mylist;
    ArrayQueue<int> myqueue;
    ArrayList<int> mylist2;

    LinkedHashMap<string, int> myHashMap(17);

    cout << myHashMap.size() << endl;

    myHashMap.insert("hello", 10);
    myHashMap.insert("Billy", 40);
    myHashMap.insert("whoohoo",30);

//    Entry<int, int> * entryPtr = myHashMap.findFirst(1);

int val = myHashMap.get("hello");

cout << "value of hello: " << val << endl;
cout << "value of 2: " << myHashMap.get("2") << endl;
cout << "value of Billy: " << myHashMap.get("Billy") << endl;
cout << "value of whoohoo: " << myHashMap.get("whoohoo") << endl;

cout << "Erased hello" << endl;

myHashMap.remove("hello");

cout << "value of hello: " << myHashMap.get("hello")  << endl;
cout << "value of 2: " << myHashMap.get("2") << endl;
cout << "value of Billy: " << myHashMap.get("Billy") << endl;
cout << "value of whoohoo: " << myHashMap.get("whoohoo") << endl;

    return 0;
}
