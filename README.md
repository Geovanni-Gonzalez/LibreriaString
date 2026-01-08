# LibreriaString

Una librería de C++ moderna, eficiente y fácil de usar para el manejo de cadenas de caracteres, diseñada como una alternativa ligera a `std::string`.

## Características Principales

- **Gestión de Capacidad Eficiente**: Reduce las reasignaciones de memoria duplicando el buffer dinámicamente.
- **Semántica de Movimiento (C++11)**: Soporte completo para constructores y asignaciones por movimiento para un rendimiento óptimo.
- **Sobrecarga de Operadores**: Integración natural con operadores como `+`, `+=`, `==`, `!=`, `[]`, `<<` y `>>`.
- **Utilidades Avanzadas**:
  - Transformación de mayúsculas/minúsculas (`toUpperCase`, `toLowerCase`).
  - Búsqueda de subcadenas (`find`, `contains`).
  - Validación de prefijos y sufijos (`startsWith`, `endsWith`).
  - Limpieza de espacios en blanco (`trim`).
  - División de cadenas (`split`).
- **Interfaz de Usuario (UI/UX)**:
  - Suite de pruebas colorida para una fácil lectura de resultados.
  - Modo interactivo CLI para probar funciones en tiempo real.

## Instalación

Simplemente incluye `String.hpp` y `String.cpp` en tu proyecto.

```bash
g++ main.cpp String.cpp -o main.exe
./main.exe
```

## Uso Básico

```cpp
#include "String.hpp"
#include <iostream>

int main() {
    String s = "Hola";
    s += " Mundo";
    s.toUpperCase();
    std::cout << s << std::endl; // "HOLA MUNDO"
    return 0;
}
```

## Requisitos

- Compilador compatible con C++11 o superior.
- Solo se utilizan librerías estándar básicas (`iostream`, `fstream`, `cstddef`).
