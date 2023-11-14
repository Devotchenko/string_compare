#include <iostream>
#include <fstream>
#include <iomanip>	
#include <cstring>	
#include <string>
#include <cctype>

// Функция для проверки наличия символа в строке
bool contains(const char* str, char ch) {
    while (*str != '\0') {
        if (*str == ch) {
            return true;
        }
        ++str;
    }
    return false;
}

// Основная функция для формирования новой строки из общих символов двух строк
char* commonCharsC(char* destination, const char* source1, const char* source2) {
    char* dest = destination; 
    while (*source1 != '\0') {
        if (contains(source2, *source1)) {
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
        // Проверяем, содержится ли символ из первой строки во второй строке
        if (source2.find(ch) != std::string::npos && result.find(ch) == std::string::npos) {
            result += ch; // Добавляем символ в результат, если он есть в обеих строках и ещё не добавлен
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

    // Считывание данных из файла
    std::string line;
    while (std::getline(file, line)) {
        int length = std::stoi(line);
        char* cStyleStr = new char[length + 1];
        file.getline(cStyleStr, length + 1);

        // Дополнительное считывание для второй строки
        std::getline(file, line);
        int length2 = std::stoi(line);
        char* cStyleStr2 = new char[length2 + 1];
        file.getline(cStyleStr2, length2 + 1);

        // Использование функции в стиле C
        char* resultC = new char[length + 1];
        commonCharsC(resultC, cStyleStr, cStyleStr2);
        std::cout << "C-style: " << resultC << std::endl;

        // Использование функции в стиле C++
        std::string resultCpp = commonCharsCpp(cStyleStr, cStyleStr2);
        std::cout << "C++-style: " << resultCpp << std::endl;

        // Освобождение памяти
        delete[] cStyleStr;
        delete[] cStyleStr2;
        delete[] resultC;
    }

    return 0;
}


