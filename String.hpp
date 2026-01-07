#ifndef STRING_HPP
#define STRING_HPP

class String {
private:
    char* data;
    int length;

    // Helper method to calculate string length (since we can't use strlen)
    int calculateLength(const char* str) const;

    // Helper method to copy string (since we can't use strcpy)
    void copyString(char* dest, const char* src) const;

public:
    // Constructor
    String(const char* str = "");
    
    // Copy Constructor
    String(const String& other);

    // Destructor
    ~String();

    // Assignment operator (Best practice in C++, needed for correct object copying)
    String& operator=(const String& other);

    // Funcionalidades Requeridas
    char caracterEn(int index) const;
    int contarCaracter(char c) const;
    int ultimoIndice(char c) const;
    void cambiarCadena(const char* nueva);
    int len() const;
    bool equals(const String& other) const; // Operator == can be overloaded too
    bool operator==(const String& other) const;

    // Split returns an array of String pointers (or char** as per prompt interpretation, 
    // but object array is safer for 'created by team'). 
    // Prompt says "retorna un string**". We will use String** for array of String objects.
    String** split(char delimiter, int& outCount) const;

    void concatenarEn(const char* sub, int pos);
    void concatenar(const char* other); // Overload for char*
    void concatenar(const String& other); // Overload for String object

    // Static method for multiple strings concatenation
    static String concatenarCadenas(char** cadenas, int count);

    void reemplazarEn(const char* sub, int pos);
    void reemplazarOcurrencias(const char* oldSub, const char* newSub);

    void guardarEnArchivo(const char* filepath) const;
    void leerArchivo(const char* filepath);

    // Accessor for raw data (useful for printing, though we could overload <<)
    const char* getData() const;
};

#endif // STRING_HPP
