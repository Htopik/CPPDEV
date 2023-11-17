#include <mutex>
#include "FineGrainedQueue.h"

int main() {
	FineGrainedQueue l;
    l.push_back(11);
    l.push_back(22);
    l.push_back(44);
    l.push_back(5);
    l.push_back(19);
    l.show();
    l.insertIntoMiddle(10, 2);
    l.show();
    l.insertIntoMiddle(10, 4);
    l.show();
    l.insertIntoMiddle(10, 100);
    l.show();
}