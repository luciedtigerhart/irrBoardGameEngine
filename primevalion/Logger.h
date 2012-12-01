#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger {
    private:
		//File that's going to be written
        ofstream outputFile;

		//Some text storages
        std::string file, text, c, newline;

    public:
        Logger(std::string filename);
        ~Logger(void);

		//Add single entry to file
        void addText(std::string newText);

		//Add an entire case to file
		void addCase(std::string N1, std::string N2, std::string S1, std::string S2, std::string W1, std::string W2,
					 std::string E1, std::string E2, std::string NW, std::string NE, std::string SW, std::string SE,
					 std::string move);

		//Write into file
        void write(void);
};

#endif