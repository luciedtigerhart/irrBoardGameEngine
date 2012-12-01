#include "Logger.h"

Logger::Logger(string filename)
{
	//Store file to be written
    file = filename;

	//Store comma and newline
	c = ",";
	newline = "\n";
}

Logger::~Logger(void)
{
}

void Logger::addText(std::string newText)
{
	//Add some new text
    text += newText;
}

void Logger::addCase(std::string N1, std::string N2, std::string S1, std::string S2, std::string W1, std::string W2,
					 std::string E1, std::string E2, std::string NW, std::string NE, std::string SW, std::string SE,
					 std::string move)
{
	//Clear previous text
	text.clear();

	//Concatenate conditions and resulting move
	text = N1+c+N2+c+S1+c+S2+c+W1+c+W2+c+E1+c+E2+c+NW+c+NE+c+SW+c+SE+c+move+newline;
}

void Logger::write(void)
{
	//Open file, write text, close file

    outputFile.open (file.c_str(), fstream::in | fstream::out | fstream::app);
    outputFile << text;
    outputFile.close();
}