#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/**
* Filter a file with a list of words by the number of letters
*
* @author Basel
* @version 28.01.2022
*/

bool checkLetters(std::string& word) {
	for (char& c : word) {
		c = std::tolower(c);
		if (!std::isalpha(c)) {
			return false;
		}
	}
	return true;
}

std::string readFileAsString(const std::string& filepath, const int& length, bool& outSuccess) throw(std::runtime_error) {
	std::ifstream stream;
	std::string line;
	std::string data;
	stream.open(filepath, std::ios::in);

	if (stream) {
		while (stream >> line) {
			if (checkLetters(line)) {
				if (line.size() == length) {
					data += line + "\n";
				}
			}
		}

		outSuccess = true;
		stream.close();
		return data;
	}

	stream.close();
	outSuccess = false;
	throw std::runtime_error("can't read from the file!");
	

}

void writeStringAsFile(const std::string& data, const std::string& path) {
	std::ofstream outFile;
	outFile.open(path, std::ios::out);
	outFile << data << std::endl;
	outFile.close();

}

void startProgramm() {
	std::string filePath;
	std::string newFilePath;
	std::string data;

	int letterLength = 1;
	bool outSuccess = false;

	try {
		std::cout << "Path of the file: ";
		std::getline(std::cin, filePath);

		std::cout << "\nPath of the new File:(Example: C:\\File.txt): ";
		std::getline(std::cin, newFilePath);

		std::cout << "\nNumber of letters: ";
		std::cin >> letterLength;

		data = readFileAsString(filePath, letterLength, outSuccess);
	}
	catch (std::runtime_error& msg) {
		std::cerr << "Runtime Error: " << msg.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown failure occurred." << std::endl;
	}


	if (outSuccess) {
		writeStringAsFile(data, newFilePath);
		std::cout << "The data has been successfully filtered\n";
		std::cin.clear();
		std::cin.ignore();
	}
	else {
		std::cout << "No data was found\n";
		std::cin.clear();
		std::cin.ignore();
	}

}

int main() {
	startProgramm();
	system("pause");

	return 0;
}

