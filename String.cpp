#include "String.hpp"
#include <fstream> // Allowed for file I/O? "Solo se permiten estructuras dinámicas lineales creadas por el equipo... Queda prohibido el uso de la librería string.h". 
// Prompt says: "Solo se permiten librerías vistas en clase". Usually iostream/fstream are standard. I will assume they are allowed.
#include <iostream> 

// Helper: Calculate length
int String::calculateLength(const char* str) const {
    if (!str) return 0;
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Helper: Copy string
void String::copyString(char* dest, const char* src) const {
    if (!dest || !src) return;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Constructor
String::String(const char* str) {
    if (str) {
        length = calculateLength(str);
        data = new char[length + 1];
        copyString(data, str);
    } else {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
}

// Copy Constructor
String::String(const String& other) {
    length = other.length;
    data = new char[length + 1];
    copyString(data, other.data);
}

// Destructor
String::~String() {
    delete[] data;
}

// Assignment Operator
String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] data; // Free existing
        length = other.length;
        data = new char[length + 1];
        copyString(data, other.data);
    }
    return *this;
}

// caracterEn
char String::caracterEn(int index) const {
    if (index >= 0 && index < length) {
        return data[index];
    }
    return '\0'; // Return null char if invalid
}

// contarCaracter
int String::contarCaracter(char c) const {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] == c) {
            count++;
        }
    }
    return count;
}

// ultimoIndice
int String::ultimoIndice(char c) const {
    for (int i = length - 1; i >= 0; i--) {
        if (data[i] == c) {
            return i;
        }
    }
    return -1; // Not found
}

// cambiarCadena
void String::cambiarCadena(const char* nueva) {
    delete[] data;
    if (nueva) {
        length = calculateLength(nueva);
        data = new char[length + 1];
        copyString(data, nueva);
    } else {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
}

// len
int String::len() const {
    return length;
}

// equals (method)
bool String::equals(const String& other) const {
    if (length != other.length) return false;
    for (int i = 0; i < length; i++) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

// operator ==
bool String::operator==(const String& other) const {
    return equals(other);
}

// split
String** String::split(char delimiter, int& outCount) const {
    outCount = 0;
    // First pass: count parts
    int parts = 1; // At least one part unless empty
    if (length == 0) parts = 0;
    else {
        for (int i = 0; i < length; i++) {
            if (data[i] == delimiter) parts++;
        }
    }

    if (parts == 0) {
        outCount = 0;
        return nullptr;
    }

    String** result = new String*[parts];
    
    int start = 0;
    int currentPart = 0;
    for (int i = 0; i <= length; i++) {
        if (data[i] == delimiter || data[i] == '\0') {
            int partLen = i - start;
            char* buffer = new char[partLen + 1];
            for (int j = 0; j < partLen; j++) {
                buffer[j] = data[start + j];
            }
            buffer[partLen] = '\0';
            
            result[currentPart] = new String(buffer);
            delete[] buffer;
            currentPart++;
            start = i + 1;
        }
    }
    
    outCount = parts;
    return result;
}

// concatenarEn
void String::concatenarEn(const char* sub, int pos) {
    if (!sub) return;
    
    int subLen = calculateLength(sub);
    
    // Normalize index
    if (pos < 0) pos = 0;
    if (pos > length) pos = length;

    char* newData = new char[length + subLen + 1];
    
    // Copy first part
    for (int i = 0; i < pos; i++) {
        newData[i] = data[i];
    }
    // Copy sub
    for (int i = 0; i < subLen; i++) {
        newData[pos + i] = sub[i];
    }
    // Copy rest
    for (int i = pos; i < length; i++) {
        newData[pos + subLen + (i - pos)] = data[i];
    }
    newData[length + subLen] = '\0';

    delete[] data;
    data = newData;
    length += subLen;
}

// concatenar (char*)
void String::concatenar(const char* other) {
    concatenarEn(other, length);
}

// concatenar (String)
void String::concatenar(const String& other) {
    concatenar(other.data);
}

// concatenarCadenas (static)
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
    int subLen = calculateLength(sub);

    // Prompt says: "Si sobrepasa el tamaño, se agregan los caracteres extra."
    // Meaning we overwrite, and extend if necessary.

    if (pos < 0) pos = 0; 
    // If pos is beyond length, we treat it as append or fill with spaces?
    // "Insertar una cadena es concatenarEn", this is "ReemplazarEn" aka Overwrite.
    // Assuming pos is within [0, length]. If pos > length, maybe append? 
    // Let's assume typical overwrite behavior starting at pos.
    
    // Calculate new length required
    int endPos = pos + subLen;
    int newLength = (endPos > length) ? endPos : length;
    
    // If we need to extend, reallocate
    if (newLength > length) {
        char* newData = new char[newLength + 1];
        copyString(newData, data);
        delete[] data;
        data = newData;
        length = newLength;
    }
    
    // Overwrite
    for (int i = 0; i < subLen; i++) {
        data[pos + i] = sub[i];
    }
    // Ensure null terminator if we extended
    data[length] = '\0';
}

// reemplazarOcurrencias
void String::reemplazarOcurrencias(const char* oldSub, const char* newSub) {
    if (!oldSub || !newSub) return;
    int oldLen = calculateLength(oldSub);
    int newLen = calculateLength(newSub);
    if (oldLen == 0) return; // infinite loop prevention

    // Quick implementation: repeatedly find and replace (not efficient but simple)
    // Or build a new string. Building new string is safer.
    
    // count occurrences
    int count = 0;
    int i = 0;
    while (i <= length - oldLen) {
        bool match = true;
        for (int j = 0; j < oldLen; j++) {
            if (data[i + j] != oldSub[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            count++;
            i += oldLen;
        } else {
            i++;
        }
    }

    if (count == 0) return;

    int newTotalLen = length - (count * oldLen) + (count * newLen);
    char* newData = new char[newTotalLen + 1];

    int srcIdx = 0;
    int dstIdx = 0;
    while (srcIdx < length) {
        // check match
        bool match = false;
        if (srcIdx <= length - oldLen) {
            match = true;
            for (int j = 0; j < oldLen; j++) {
                if (data[srcIdx + j] != oldSub[j]) {
                    match = false;
                    break;
                }
            }
        }

        if (match) {
            for (int k = 0; k < newLen; k++) {
                newData[dstIdx++] = newSub[k];
            }
            srcIdx += oldLen;
        } else {
            newData[dstIdx++] = data[srcIdx++];
        }
    }
    newData[newTotalLen] = '\0';

    delete[] data;
    data = newData;
    length = newTotalLen;
}

// guardarEnArchivo
void String::guardarEnArchivo(const char* filepath) const {
    std::ofstream outFile(filepath);
    if (outFile.is_open()) {
        outFile << data;
        outFile.close();
    }
}

// leerArchivo
void String::leerArchivo(const char* filepath) {
    std::ifstream inFile(filepath);
    if (inFile.is_open()) {
        // Determine file size to allocate buffer?
        // Or read line by line. "Lee una cadena desde un archivo".
        // Let's read the whole file content into the string.
        
        inFile.seekg(0, std::ios::end);
        int size = inFile.tellg();
        inFile.seekg(0, std::ios::beg);
        
        delete[] data;
        length = size;
        data = new char[length + 1];
        
        inFile.read(data, length);
        data[length] = '\0';
        
        inFile.close();
    }
}

const char* String::getData() const {
    return data;
}
