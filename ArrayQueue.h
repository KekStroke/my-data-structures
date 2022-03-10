//
// Created by Anvar on 1/30/2022.
//

#ifndef PROJECT1_ARRAYQUEUE_H
#define PROJECT1_ARRAYQUEUE_H

template <class T>
class ArrayQueue {
public:
    // constructor
    ArrayQueue():arrlength{2}, queuesize{0}, front{0}, rear{0} {
        data = {new T[arrlength]};
    }

    T first() {
        return data[front];
    }

    T last() {
        return data[rear];
    }

    void enqueue(T item) {
        if (needtoresize()) {
            resize();
        }

        data[front] = item;
        front = (front+1) % arrlength;
        queuesize++;
    }

    T dequeue() {
        if (isEmpty())
            throw std::out_of_range("Attempt to dequeue from empty queue");
        T return_item = data[rear];
        rear = (rear+1) % arrlength;
        queuesize--;
        return return_item;
    }

    int size() {
        return queuesize;
    }

private:
    T *data;
    int queuesize;
    int arrlength;
    int front;
    int rear;

    void resize() {
        T *tmpqueue = new T[arrlength*2];

        if (front >= rear) {
            for (int i = 0; i < queuesize; i++) {
                tmpqueue[i] = data[i];
            }

            delete[] data;
            data = tmpqueue;
            arrlength *= 2;
        } else {
            for (int i = 0; i < front; i++) {
                tmpqueue[i] = data[i];
            }
            for (int i = rear+arrlength; i < arrlength; i++) {
                tmpqueue[i] = data[i-arrlength];
            }
            rear = rear+arrlength;

            delete[] data;
            data = tmpqueue;
            arrlength *= 2;
        }

    }

    bool needtoresize() {
        return queuesize >= arrlength-1;
    }

    bool isEmpty() {
        return !queuesize;
    }

};


#endif //PROJECT1_ARRAYQUEUE_H
