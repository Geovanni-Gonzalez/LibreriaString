#include <iostream>
#include <vector>
#include <string>
#include "String.hpp"

// ANSI Color Codes for UI/UX
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLDBLUE "\033[1m\033[34m"

void printHeader(const char* title) {
    std::cout << "\n" << BOLDBLUE << "=== " << title << " ===" << RESET << std::endl;
}

void assertTest(bool condition, const char* testName) {
    if (condition) {
        std::cout << GREEN << "[PASS] " << RESET << testName << std::endl;
    } else {
        std::cout << RED << "[FAIL] " << RESET << testName << std::endl;
    }
}

void runAutomatedTests() {
    printHeader("Running Automated Test Suite");

    // 1. Constructor & len()
    String s1("Hola");
    assertTest(s1.len() == 4, "Constructor & len()");

    // 2. Move Semantics
    String sTemp("Temporal");
    String sMoved(std::move(sTemp));
    assertTest(sMoved.len() == 8 && sTemp.len() == 0, "Move Constructor");

    // 3. Operators
    String op1("ABC");
    String op2("DEF");
    String op3 = op1 + op2;
    assertTest(op3 == String("ABCDEF"), "Operator + and ==");
    
    op1 += "123";
    assertTest(op1 == String("ABC123"), "Operator +=");
    assertTest(op1[0] == 'A', "Operator []");

    // 4. Case Transformation
    String caseStr("Hello World");
    caseStr.toUpperCase();
    assertTest(caseStr == String("HELLO WORLD"), "toUpperCase()");
    caseStr.toLowerCase();
    assertTest(caseStr == String("hello world"), "toLowerCase()");

    // 5. Trim
    String trimStr("   espacios   ");
    trimStr.trim();
    assertTest(trimStr == String("espacios"), "trim()");

    // 6. Search
    String searchStr("Buscando una aguja en un pajar");
    assertTest(searchStr.contains("aguja"), "contains() true");
    assertTest(!searchStr.contains("perro"), "contains() false");
    assertTest(searchStr.startsWith("Buscando"), "startsWith()");
    assertTest(searchStr.endsWith("pajar"), "endsWith()");

    // 7. split
    String splitStr("uno-dos-tres");
    int count = 0;
    String** parts = splitStr.split('-', count);
    assertTest(count == 3, "split() count");
    if (count == 3) {
        assertTest(parts[1]->equals(String("dos")), "split() element verify");
        for(int i=0; i<count; i++) delete parts[i];
        delete[] parts;
    }

    std::cout << CYAN << "\nAll automated tests completed." << RESET << std::endl;
}

void interactiveMenu() {
    String userStr("");
    int choice = 0;

    while (true) {
        printHeader("LibreriaString Interactive CLI");
        std::cout << "Current String: [" << GREEN << userStr << RESET << "]" << std::endl;
        std::cout << "1. Set String" << std::endl;
        std::cout << "2. Concatenate" << std::endl;
        std::cout << "3. Upper/Lower Case" << std::endl;
        std::cout << "4. Trim spaces" << std::endl;
        std::cout << "5. Find Substring" << std::endl;
        std::cout << "6. Replace occurrences" << std::endl;
        std::cout << "7. Save to file (interactive.txt)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << YELLOW << "Choice: " << RESET;
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string dummy;
            std::cin >> dummy;
            continue;
        }
        std::cin.ignore(); // flush newline

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                std::cout << "Enter new string: ";
                char buffer[256];
                std::cin.getline(buffer, 256);
                userStr.cambiarCadena(buffer);
                break;
            }
            case 2: {
                std::cout << "Enter string to append: ";
                char buffer[256];
                std::cin.getline(buffer, 256);
                userStr += buffer;
                break;
            }
            case 3:
                std::cout << "1. Upper, 2. Lower: ";
                int sub; std::cin >> sub;
                if (sub == 1) userStr.toUpperCase();
                else userStr.toLowerCase();
                break;
            case 4:
                userStr.trim();
                std::cout << "Trimmed!" << std::endl;
                break;
            case 5: {
                std::cout << "Look for: ";
                char buffer[256];
                std::cin.getline(buffer, 256);
                int idx = userStr.find(buffer);
                if (idx != -1) std::cout << GREEN << "Found at index: " << idx << RESET << std::endl;
                else std::cout << RED << "Not found" << RESET << std::endl;
                break;
            }
            case 6: {
                char oldS[256], newS[256];
                std::cout << "Replace: "; std::cin.getline(oldS, 256);
                std::cout << "With: "; std::cin.getline(newS, 256);
                userStr.reemplazarOcurrencias(oldS, newS);
                break;
            }
            case 7:
                userStr.guardarEnArchivo("interactive.txt");
                std::cout << CYAN << "Saved to interactive.txt" << RESET << std::endl;
                break;
            default:
                std::cout << RED << "Invalid option" << RESET << std::endl;
        }
    }
}

int main() {
    runAutomatedTests();
    
    std::cout << "\nDo you want to enter Interactive Mode? (y/n): ";
    char c;
    std::cin >> c;
    if (c == 'y' || c == 'Y') {
        interactiveMenu();
    }

    std::cout << "\n" << MAGENTA << "Thank you for using LibreriaString!" << RESET << std::endl;
    return 0;
}
