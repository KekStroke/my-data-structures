////
//// Created by Anvar on 1/29/2022.
////
//
//#include "ArrayList.h"
//#include <iostream>
//
//template <class T>
//ArrayList<T>::ArrayList():data{new T[1]}, arrlength{0}, listsize{1}{}
//
//template <class T>
//void ArrayList<T>::resize() {
//    if (needtoresize()) {
//        T *temparr = new T[listsize*2];
//        for (int i = 0; i < listsize; i++) {
//            temparr[i] = data[i];
//        }
//        data = temparr;
//        arrlength *= 2;
//    }
//}
//
//template <class T>
//bool ArrayList<T>::needtoresize() {
//    return listsize == arrlength;
//}
//
//template <class T>
//void ArrayList<T>::add(T item) {
//    if (needtoresize())
//        resize();
//    data[listsize] = item;
//    listsize++;
//}
//
//template <class T>
//void ArrayList<T>::add(int pos, T item) {
//    if (needtoresize())
//        resize();
//    for (int i = listsize; i > pos; i--) {
//        data[i] = data[i-1];
//    }
//    data[pos] = item;
//    listsize++;
//}
//
//template <class T>
//void ArrayList<T>::add_after(T from, T item) {
//    int pos = indexof(from);
//    if (pos == -1) {
////        std::cout << "Such element does not exist";
//        return;
//    }
//    add(pos+1, item);
//}
//
//template <class T>
//int ArrayList<T>::indexof(T item) {
//    if (!contains(item)) {
//        std::cout << "Such element does not exist";
//        return -1;
//    }
//    for (int i = 0; i < listsize; i++) {
//        if (data[i] == item) return i;
//    }
//    return -1;
//}
//
//template <class T>
//int ArrayList<T>::size() {
//    return listsize;
//}
//
//template <class T>
//bool ArrayList<T>::contains(T item) {
//    for (int i = 0; i < listsize; i++) {
//        if (data[i] == item) return true;
//    }
//    return false;
//}
//
//template <class T>
//T* ArrayList<T>::get(int index) {
//    if (index < 0 || index >= listsize) {
//        std::cout << "Invalid index, Null pointer exception";
//        return nullptr;
//    }
//    return &data[index];
//}
//
//template <class T>
//void ArrayList<T>::remove(int index) {
//    for (int i = index; i < listsize; i++) {
//        data[i] = data[i+1];
//    }
//    listsize--;
//}
