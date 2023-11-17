#pragma once
#include "common.h"
//Самопальный вектор
template <class T>
class StaticArray {
public:
    StaticArray(int size = 0) {
        count = size;
        if (size > 0) {
            for(int i =0;i <size; i++)
                array[i] = T();
        }
    }
    void add(T newval) {
        if (count < SIZE) {
            array[count++] = newval;
        }
    }
    void del(int index) {
        if (index < 0 || index >= count)
            return;
        count--;
        for (int i = index; i < count; i++) {
            array[i] = array[i + 1];
        }
    }
    T& operator [](int index) {
        if (index < 0 || index >= count)
            throw 0;
        return array[index];
    }

    int find(const T& val) {
        for (int i = 0; i < count; i++)
            if (array[i] == val)
                return i;
        return -1;
    }

    int size() {
        return count;
    }

private:
    T array[SIZE];
    int count;
};