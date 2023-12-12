#include <iostream>
#include <fstream>
#include <iomanip>  
#include <cstring>  
#include <string>
#include <cctype>
#include <new>  

bool contains(const char* str, char ch) {
	while (*str != '\0') {
		if (*str == ch) {
			return true;
		}
		++str;
	}
	return false;
}

char* commonCharsC(char* destination, const char* source1, const char* source2) {
	char* dest = destination;
	while (*source1 != '\0') {
		if (contains(source2, *source1) && !contains(destination, *source1)) {
			*dest++ = *source1;
		}
		++source1;
	}
	*dest = '\0';
	return destination;
}

std::string commonCharsCpp(const std::string& source1, const std::string& source2) {
	std::string result;

	for (char ch : source1) {
		if (source2.find(ch) != std::string::npos && result.find(ch) == std::string::npos) {
			result += ch;
		}
	}

	return result;
}

int main() {
	std::ifstream file("infile.txt");
	if (!file) {
		std::cerr << "cant open file" << std::endl;
		return 1;
	}

	char* cStyleStr = nullptr;
	char* cStyleStr2 = nullptr;
	char* resultC = nullptr;

	try {
		std::string line;
		while (std::getline(file, line)) {
			int length = std::stoi(line);
			cStyleStr = new char[length + 1];
			file.getline(cStyleStr, length + 1);

			std::getline(file, line);
			int length2 = std::stoi(line);

			try {
				cStyleStr2 = new char[length2 + 1];
			}
			catch (const std::bad_alloc&) {
				delete[] cStyleStr;
				throw;
			}

			file.getline(cStyleStr2, length2 + 1);

			try {
				resultC = new char[length + 1];
			}
			catch (const std::bad_alloc&) {
				delete[] cStyleStr;
				delete[] cStyleStr2;
				throw;
			}

			commonCharsC(resultC, cStyleStr, cStyleStr2);
			std::cout << "C-style: " << resultC << std::endl;

			std::string resultCpp = commonCharsCpp(cStyleStr, cStyleStr2);
			std::cout << "C++-style: " << resultCpp << std::endl;

			delete[] cStyleStr;
			delete[] cStyleStr2;
			delete[] resultC;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed: " << e.what() << std::endl;
		delete[] cStyleStr;
		delete[] cStyleStr2;
		delete[] resultC;
		return 1;
	} 

	return 0;
}