#include <iostream>
#include "String.hpp"

// Helper to print test results
void assertTest(bool condition, const char* testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << std::endl;
    } else {
        std::cout << "[FAIL] " << testName << std::endl;
    }
}

int main() {
    std::cout << "=== Test Suite: LibreriaString ===" << std::endl;

    // 1. Constructor & len()
    String s1("Hola");
    assertTest(s1.len() == 4, "Constructor & len()");

    // 2. copy constructor & equals
    String s2(s1);
    assertTest(s2.equals(s1), "Copy Constructor & equals()");
    
    // 3. cambiarCadena
    s2.cambiarCadena("Mundo");
    assertTest(s2.len() == 5 && !s2.equals(s1), "cambiarCadena()");

    // 4. caracterEn
    assertTest(s1.caracterEn(1) == 'o', "caracterEn() valid");
    assertTest(s1.caracterEn(10) == '\0', "caracterEn() invalid");

    // 5. contarCaracter
    String s3("bananas");
    assertTest(s3.contarCaracter('a') == 3, "contarCaracter()");

    // 6. ultimoIndice
    assertTest(s3.ultimoIndice('n') == 4, "ultimoIndice()");

    // 7. concatenar
    s1.concatenar(" Mundo");
    String expected("Hola Mundo");
    assertTest(s1.equals(expected), "concatenar()");

    // 8. concatenarEn
    String s4("HoMundo");
    s4.concatenarEn("la ", 2);
    assertTest(s4.equals(expected), "concatenarEn()");

    // 9. reemplazarEn
    String s5("Hola Mundo");
    s5.reemplazarEn("Tierra", 5);
    String expected2("Hola Tierra");
    assertTest(s5.equals(expected2), "reemplazarEn() normal");
    
    // 10. reemplazarEn (extension)
    String s6("ABC");
    s6.reemplazarEn("XYZ", 2); // Should become ABXYZ
    String expectedExtension("ABXYZ");
    assertTest(s6.equals(expectedExtension), "reemplazarEn() extension");

    // 11. reemplazarOcurrencias
    String s7("La casa es roja y la flor es roja");
    s7.reemplazarOcurrencias("roja", "azul");
    String expectedReplace("La casa es azul y la flor es azul");
    assertTest(s7.equals(expectedReplace), "reemplazarOcurrencias()");

    // 12. split
    String s8("uno,dos,tres");
    int count = 0;
    String** parts = s8.split(',', count);
    assertTest(count == 3, "split() count");
    if (count == 3) {
        assertTest(parts[0]->equals(String("uno")), "split() part 1");
        assertTest(parts[1]->equals(String("dos")), "split() part 2");
        assertTest(parts[2]->equals(String("tres")), "split() part 3");
    }
    // Cleanup split result
    if (parts) {
        for(int i=0; i<count; i++) delete parts[i];
        delete[] parts;
    }

    // 13. concatenarCadenas (Static)
    char* strs[] = { (char*)"Uno", (char*)"Dos", (char*)"Tres" };
    String combined = String::concatenarCadenas(strs, 3);
    assertTest(combined.equals(String("UnoDosTres")), "concatenarCadenas()");

    // 14. File I/O
    String sFile("Contenido de prueba");
    sFile.guardarEnArchivo("test.txt");
    
    String sRead;
    sRead.leerArchivo("test.txt");
    assertTest(sRead.equals(sFile), "File I/O");

    std::cout << "=== Tests Completed ===" << std::endl;
    return 0;
}
