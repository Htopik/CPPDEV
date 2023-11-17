#include "IntegerArray.h"
int main() {
    try {
        IntegerArray array(10);
        for (int i = 0; i < 10; ++i)
            array[i] = i + 1;
        array.resize(8);
        array.insertBefore(20, 5);
        array.remove(3);
        array.insertAtEnd(30);
        array.insertAtBeginning(40);
        cout << array.find(30) << endl;
        for (int i{ 0 }; i < array.getLength(); ++i)
            std::cout << array[i] << ' ';
        return 0;
    }
    catch (bad_length& ba) {
        cout << ba.what() << endl;
    }
    catch (bad_range& br) {
        cout << br.what() << endl;
    }
	return 0;
}