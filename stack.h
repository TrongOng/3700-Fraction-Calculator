#include <stdexcept>
#include "fraction.h"

#ifndef _STACK_H
#define _STACK_H

const int STACK_SIZE = 100;

template <typename T>

class Stack {
    private:
        T arr[STACK_SIZE];
        int count;

    public:
        Stack(void) {count = 0;}
        ~Stack() = default;

        void clear() {count = 0;}
        int size() {return count;}
        bool isEmpty() {return count == 0;}

        void push(const T &n) {
            if (count == STACK_SIZE)
                throw std::overflow_error("Stack is full");

            arr[count] = n;
            count++;
        }

        T pop() {
            if (!count)
                throw std::underflow_error("Stack is empty");

            count--;
            return arr[count];
        }

        T peek() {
            if (!count)
                throw std::underflow_error("Stack is empty");

            return arr[count-1];
        }

};

#endif