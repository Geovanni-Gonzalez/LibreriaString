#include "String.hpp"
#include <fstream>
#include <iostream>
#include <algorithm> // for std::max

// Helper: Calculate length
std::size_t String::calculateLength(const char* str) const {
    if (!str) return 0;
    std::size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Helper: Copy string
void String::copyString(char* dest, const char* src) const {
    if (!dest || !src) return;
    std::size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Internal reallocation logic
void String::ensureCapacity(std::size_t newCap) {
    if (newCap <= capacity && data != nullptr) return;
    
    // Growth strategy: double or exact if very large
    std::size_t nextCap = (capacity == 0) ? newCap : capacity * 2;
    if (nextCap < newCap) nextCap = newCap;

    char* newData = new char[nextCap + 1];
    if (data) {
        // Use manual copy for safety
        std::size_t i = 0;
        while (i < length && data[i] != '\0') {
            newData[i] = data[i];
            i++;
        }
        newData[i] = '\0';
        delete[] data;
    } else {
        newData[0] = '\0';
    }
    data = newData;
    capacity = nextCap;
}

// Constructor
String::String(const char* str) {
    if (str) {
        length = calculateLength(str);
        capacity = length;
        data = new char[capacity + 1];
        copyString(data, str);
    } else {
        length = 0;
        capacity = 0;
        data = new char[1];
        data[0] = '\0';
    }
}

// Copy Constructor
String::String(const String& other) {
    length = other.length;
    capacity = other.length;
    data = new char[capacity + 1];
    copyString(data, other.data);
}

// Move Constructor
String::String(String&& other) noexcept {
    data = other.data;
    length = other.length;
    capacity = other.capacity;
    
    other.data = nullptr;
    other.length = 0;
    other.capacity = 0;
}

// Destructor
String::~String() {
    delete[] data;
}

// Assignment Operator
String& String::operator=(const String& other) {
    if (this != &other) {
        ensureCapacity(other.length);
        length = other.length;
        copyString(data, other.data);
    }
    return *this;
}

// Move Assignment
String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        length = other.length;
        capacity = other.capacity;
        
        other.data = nullptr;
        other.length = 0;
        other.capacity = 0;
    }
    return *this;
}

// caracterEn
char String::caracterEn(int index) const {
    if (index >= 0 && (std::size_t)index < length) {
        return data[index];
    }
    return '\0';
}

// contarCaracter
int String::contarCaracter(char c) const {
    int count = 0;
    for (std::size_t i = 0; i < length; i++) {
        if (data[i] == c) {
            count++;
        }
    }
    return count;
}

// ultimoIndice
int String::ultimoIndice(char c) const {
    if (length == 0) return -1;
    for (int i = (int)length - 1; i >= 0; i--) {
        if (data[i] == c) {
            return i;
        }
    }
    return -1;
}

// cambiarCadena
void String::cambiarCadena(const char* nueva) {
    std::size_t newLen = calculateLength(nueva);
    ensureCapacity(newLen);
    if (nueva) {
        copyString(data, nueva);
        length = newLen;
    } else {
        length = 0;
        if (data) data[0] = '\0';
    }
}

// len
std::size_t String::len() const {
    return length;
}

// equals
bool String::equals(const String& other) const {
    if (length != other.length) return false;
    for (std::size_t i = 0; i < length; i++) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

// Operators
bool String::operator==(const String& other) const {
    return equals(other);
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

char& String::operator[](std::size_t index) {
    return data[index];
}

const char& String::operator[](std::size_t index) const {
    return data[index];
}

String& String::operator+=(const String& other) {
    concatenar(other);
    return *this;
}

String String::operator+(const String& other) const {
    String res(*this);
    res.concatenar(other);
    return res;
}

// New Utilities
void String::toUpperCase() {
    for (std::size_t i = 0; i < length; i++) {
        if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] -= 32;
        }
    }
}

void String::toLowerCase() {
    for (std::size_t i = 0; i < length; i++) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] += 32;
        }
    }
}

void String::trim() {
    if (length == 0) return;
    std::size_t start = 0;
    while (start < length && (data[start] == ' ' || data[start] == '\t' || data[start] == '\n' || data[start] == '\r')) {
        start++;
    }
    if (start == length) {
        length = 0;
        data[0] = '\0';
        return;
    }
    std::size_t end = length - 1;
    while (end > start && (data[end] == ' ' || data[end] == '\t' || data[end] == '\n' || data[end] == '\r')) {
        end--;
    }
    
    std::size_t newLen = end - start + 1;
    for (std::size_t i = 0; i < newLen; i++) {
        data[i] = data[start + i];
    }
    data[newLen] = '\0';
    length = newLen;
}

int String::find(const char* sub) const {
    if (!sub) return -1;
    std::size_t subLen = calculateLength(sub);
    if (subLen == 0) return 0;
    if (subLen > length) return -1;

    for (std::size_t i = 0; i <= length - subLen; i++) {
        bool match = true;
        for (std::size_t j = 0; j < subLen; j++) {
            if (data[i + j] != sub[j]) {
                match = false;
                break;
            }
        }
        if (match) return (int)i;
    }
    return -1;
}

bool String::contains(const char* sub) const {
    return find(sub) != -1;
}

bool String::startsWith(const char* prefix) const {
    if (!prefix) return false;
    std::size_t preLen = calculateLength(prefix);
    if (preLen > length) return false;
    for (std::size_t i = 0; i < preLen; i++) {
        if (data[i] != prefix[i]) return false;
    }
    return true;
}

bool String::endsWith(const char* suffix) const {
    if (!suffix) return false;
    std::size_t sufLen = calculateLength(suffix);
    if (sufLen > length) return false;
    std::size_t offset = length - sufLen;
    for (std::size_t i = 0; i < sufLen; i++) {
        if (data[offset + i] != suffix[i]) return false;
    }
    return true;
}

// split
String** String::split(char delimiter, int& outCount) const {
    outCount = 0;
    if (length == 0) return nullptr;

    int parts = 1;
    for (std::size_t i = 0; i < length; i++) {
        if (data[i] == delimiter) parts++;
    }

    String** result = new String*[parts];
    std::size_t start = 0;
    int currentPart = 0;
    for (std::size_t i = 0; i <= length; i++) {
        if (i == length || data[i] == delimiter) {
            std::size_t partLen = i - start;
            char* buffer = new char[partLen + 1];
            for (std::size_t j = 0; j < partLen; j++) {
                buffer[j] = data[start + j];
            }
            buffer[partLen] = '\0';
            result[currentPart++] = new String(buffer);
            delete[] buffer;
            start = i + 1;
        }
    }
    outCount = parts;
    return result;
}

// concatenarEn
void String::concatenarEn(const char* sub, int pos) {
    if (!sub) return;
    std::size_t subLen = calculateLength(sub);
    if (pos < 0) pos = 0;
    if ((std::size_t)pos > length) pos = (int)length;

    ensureCapacity(length + subLen);
    
    // Shift right
    for (int i = (int)length; i >= pos; i--) {
        data[i + subLen] = data[i];
    }
    // Insert
    for (std::size_t i = 0; i < subLen; i++) {
        data[pos + i] = sub[i];
    }
    length += subLen;
    data[length] = '\0';
}

// concatenar
void String::concatenar(const char* other) {
    if (!other) return;
    std::size_t oLen = calculateLength(other);
    ensureCapacity(length + oLen);
    for (std::size_t i = 0; i < oLen; i++) {
        data[length + i] = other[i];
    }
    length += oLen;
    data[length] = '\0';
}

void String::concatenar(const String& other) {
    concatenar(other.data);
}

// static
String String::concatenarCadenas(char** cadenas, int count) {
    String res("");
    for (int i = 0; i < count; i++) {
        res.concatenar(cadenas[i]);
    }
    return res;
}

// reemplazarEn
void String::reemplazarEn(const char* sub, int pos) {
    if (!sub) return;
    std::size_t subLen = calculateLength(sub);
    if (pos < 0) pos = 0;
    
    std::size_t endPos = pos + subLen;
    ensureCapacity(std::max(length, endPos));
    
    for (std::size_t i = 0; i < subLen; i++) {
        data[pos + i] = sub[i];
    }
    if (endPos > length) {
        length = endPos;
        data[length] = '\0';
    }
}

// reemplazarOcurrencias
void String::reemplazarOcurrencias(const char* oldSub, const char* newSub) {
    if (!oldSub || !newSub) return;
    std::size_t oLen = calculateLength(oldSub);
    std::size_t nLen = calculateLength(newSub);
    if (oLen == 0) return;

    String result("");
    int lastIdx = 0;
    int idx = find(oldSub);
    
    while (idx != -1) {
        // Add part before match
        for (int i = lastIdx; i < idx; i++) {
            char temp[2] = {data[i], '\0'};
            result.concatenar(temp);
        }
        result.concatenar(newSub);
        lastIdx = idx + (int)oLen;
        
        // Find next manually
        idx = -1;
        for (std::size_t i = (std::size_t)lastIdx; i <= length - oLen; i++) {
            bool match = true;
            for (std::size_t j = 0; j < oLen; j++) {
                if (data[i + j] != oldSub[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                idx = (int)i;
                break;
            }
        }
    }
    // Add rest
    for (std::size_t i = (std::size_t)lastIdx; i < length; i++) {
        char temp[2] = {data[i], '\0'};
        result.concatenar(temp);
    }
    
    *this = std::move(result);
}

// File I/O
void String::guardarEnArchivo(const char* filepath) const {
    std::ofstream outFile(filepath);
    if (outFile.is_open()) {
        outFile << data;
        outFile.close();
    }
}

void String::leerArchivo(const char* filepath) {
    std::ifstream inFile(filepath, std::ios::binary | std::ios::ate);
    if (inFile.is_open()) {
        std::streamsize size = inFile.tellg();
        inFile.seekg(0, std::ios::beg);
        
        ensureCapacity((std::size_t)size);
        if (inFile.read(data, size)) {
            length = (std::size_t)size;
            data[length] = '\0';
        }
        inFile.close();
    }
}

const char* String::getData() const {
    return data ? data : "";
}

// Stream friends
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.getData();
    return os;
}

std::istream& operator>>(std::istream& is, String& str) {
    char buffer[1024];
    if (is >> buffer) {
        str.cambiarCadena(buffer);
    }
    return is;
}
