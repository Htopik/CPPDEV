#pragma once
#include <mutex>
#include <iostream>
using namespace std;
struct Node
{
	Node(int data) : value(data), next(nullptr) { node_mutex = new mutex; }
	~Node() { delete node_mutex; }
	int value;
	Node* next;
	std::mutex* node_mutex;
};

class FineGrainedQueue
{
	
	Node* head;
	std::mutex* queue_mutex;
public:
	FineGrainedQueue() : head(nullptr) { queue_mutex = new mutex; }
	~FineGrainedQueue() { delete queue_mutex; }
	void remove(int);
	void insertIntoMiddle(int value, int pos);
	void push_back(int data);
	void show();
};

