#include "Logger.h"
#include <thread>

Logger::Logger() {
	file.open("log.txt", std::fstream::in | std::fstream::out);

	if (!file)
	{
		file.open("log.txt", std::fstream::trunc | std::fstream::out);
		// re-open with original flags
		file.open("log.txt",std::fstream::in | std::fstream::out);
	}
}

Logger::~Logger() {
	file.close();
}

void Logger::getString(string& str) {
	
	std::thread thr([&]() {
		mut.lock();
		file >> str;
		mut.unlock();
		});
	thr.join();
}

void Logger::outString(const string& str) {
	std::thread thr([&]() {
		mut.lock();
		file.seekp(0, std::ios_base::end);
		file << '\n';
		file << str;
		mut.unlock();
		});
	thr.join();
}
