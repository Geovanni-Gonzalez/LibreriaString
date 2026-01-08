#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <cstddef> // for size_t

class String {
private:
    char* data;
    std::size_t length;
    std::size_t capacity;

    // Helper method to calculate string length
    std::size_t calculateLength(const char* str) const;

    // Helper method to copy string
    void copyString(char* dest, const char* src) const;

    // Internal reallocation logic
    void ensureCapacity(std::size_t newCap);

public:
    // Constructors
    String(const char* str = "");
    String(const String& other);
    String(String&& other) noexcept; // Move Constructor

    // Destructor
    ~String();

    // Assignment operators
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept; // Move Assignment

    // Functionalidades Requeridas
    char caracterEn(int index) const;
    int contarCaracter(char c) const;
    int ultimoIndice(char c) const;
    void cambiarCadena(const char* nueva);
    std::size_t len() const;
    bool equals(const String& other) const;
    
    // Operators
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;
    String& operator+=(const String& other);
    String operator+(const String& other) const;

    // New Utilities
    void toUpperCase();
    void toLowerCase();
    void trim();
    int find(const char* sub) const;
    bool contains(const char* sub) const;
    bool startsWith(const char* prefix) const;
    bool endsWith(const char* suffix) const;

    // Core functionality
    String** split(char delimiter, int& outCount) const;
    void concatenarEn(const char* sub, int pos);
    void concatenar(const char* other);
    void concatenar(const String& other);

    static String concatenarCadenas(char** cadenas, int count);

    void reemplazarEn(const char* sub, int pos);
    void reemplazarOcurrencias(const char* oldSub, const char* newSub);

    void guardarEnArchivo(const char* filepath) const;
    void leerArchivo(const char* filepath);

    const char* getData() const;

    // Friends for stream I/O
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);
};

#endif // STRING_HPP
