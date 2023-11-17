#pragma once
#include <iostream>
using namespace std;
class IntegerArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntegerArray() = default;
    IntegerArray(int);
    IntegerArray(const IntegerArray&);
    ~IntegerArray();
    void erase();
    int& operator[](int);
    void reallocate(int);
    void resize(int);
    IntegerArray& operator=(const IntegerArray&);
    void insertBefore(int, int);
    void remove(int);
    void insertAtBeginning(int); 
    void insertAtEnd(int);
    int getLength() const;
    int find(int);
};
class bad_range : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "Array index out of bounds";
    }
};
class bad_length : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "Incorrect array length provided";
    }
};

