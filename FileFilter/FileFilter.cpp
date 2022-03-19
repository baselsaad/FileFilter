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

std::string readFileAsString(const std::string& filepath, const int& length, bool& outSuccess)throw (std::exception) {
    std::ifstream stream;
    std::string line;
    std::string data;

    try {
        stream.open(filepath, std::ios::in);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        outSuccess = false;
    }

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
    return data;
}

void writeStringAsFile(const std::string& data, const std::string& path) {
    std::ofstream outFile;
    try {
        outFile.open(path, std::ios::out);
        outFile << data << std::endl;
        outFile.close();
    }
    catch (std::exception& msg) {
        std::cerr << "Error: " << msg.what() << std::endl;
    }
   
    
}

void startProgramm(bool& outEnd) {
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
        std::cout << "The data has been successfully filtered";
        outEnd = true;
    }
    else {
        std::cout << "No data was found in the file";
        outEnd = false;
    }

}

int main() {
    bool outEnd = false;
    while (!outEnd) {
        try {
            startProgramm(outEnd);
        }
        catch (std::runtime_error& msg) {
            std::cerr << msg.what()<<std::endl;
        }
        catch (std::exception& msg) {
            std::cerr << msg.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown failure occurred." << std::endl;
        }
    }
    


    system("pause");

    return 0;
}

