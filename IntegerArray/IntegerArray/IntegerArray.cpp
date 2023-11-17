#include "IntegerArray.h"

IntegerArray::IntegerArray(int length) :
    m_length{ length }
{
    if (length < 0) throw bad_length();
    if (length > 0)
        m_data = new int[length] {};
}

IntegerArray::IntegerArray(const IntegerArray& a)
{
    reallocate(a.getLength());
    for (int index{ 0 }; index < m_length; ++index)
        m_data[index] = a.m_data[index];
}

IntegerArray::~IntegerArray()
{
    delete[] m_data;
}

void IntegerArray::erase()
{
    delete[] m_data;
    m_data = nullptr;
    m_length = 0;
}

int& IntegerArray::operator[](int index)
{
    if (!(index >= 0 && index < m_length)) throw bad_range();
    return m_data[index];
}

void IntegerArray::reallocate(int newLength) //resising of array
{
    erase();
    if (newLength <= 0) //if resising to the 0, then task done
        return;
    m_data = new int[newLength];
    m_length = newLength;
}

// resize resizes the array.  Any existing elements will be kept.  This function operates slowly.
void IntegerArray::resize(int newLength)
{
    if (newLength == m_length)
        return;
    if (newLength <= 0)
    {
        erase();
        return;
    }

    int* data{ new int[newLength] }; //Allocating new array, copying old with new lenght and then delete old array and make ptr to the new
    if (m_length > 0)
    {
        int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

        for (int index{ 0 }; index < elementsToCopy; ++index)
            data[index] = m_data[index];
    }
    delete[] m_data;
    m_data = data;
    m_length = newLength;
}

IntegerArray& IntegerArray::operator=(const IntegerArray& a)
{
    if (&a == this)
        return *this;

    reallocate(a.getLength());

    for (int index{ 0 }; index < m_length; ++index)
        m_data[index] = a.m_data[index];

    return *this;
}

void IntegerArray::insertBefore(int value, int index)
{
        if (!(index >= 0 && index <= m_length)) throw bad_range();
        int* data{ new int[m_length + 1] };
        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        data[index] = value;
        for (int after{ index }; after < m_length; ++after)
            data[after + 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        ++m_length;
}

void IntegerArray::remove(int index)
{
        if (!(index >= 0 && index < m_length)) throw bad_range();
        if (m_length == 1)
        {
            erase();
            return;
        }

        int* data{ new int[m_length - 1] };

        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        for (int after{ index + 1 }; after < m_length; ++after)
            data[after - 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        --m_length;
}

void IntegerArray::insertAtBeginning(int value) { insertBefore(value, 0); }
void IntegerArray::insertAtEnd(int value) { insertBefore(value, m_length); }

int IntegerArray::getLength() const { return m_length; }
int IntegerArray::find(int key) {
    for (int i = 0; i < (*this).getLength(); ++i) {
        if (m_data[i] == key) {
            return i;
        }
    }
    return -1;
}
