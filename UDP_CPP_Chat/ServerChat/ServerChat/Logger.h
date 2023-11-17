#pragma once
#include "Message.h"
#include <mutex>
#include <fstream>
using namespace std;
class Logger
{
private:
	fstream file;
	mutex mut;
public:
	Logger();
	~Logger();
	void getString(string&);
	void outString(const string&);
};

