# Compact_Gen

##Descripción

Biblioteca para criptografía de ESP32 diseñada para facilitar y simplificar la generacion de claves usando curvas elipticas

##Instalación 

Clona este repositorio en tu proyecto ESP32.

# 1. **Uso**
  ## Generar y Exportar claves
  ```c
  #include "MiBibliotecaESP32.h"
psa_key_handle_t llave_privada;
uint8_t llave_publica[32];
size_t tamano_llave = sizeof(llave_publica);
size_t olen;

// Generar y exportar llaves
generar_y_exportar_llaves( &llave_privada, llave_publica, tamano_llave, &olen);
```
De esta manera solo habria que pasar donde queremos que se guarde tanto la llave privada como la llave pública.
## Derivación de Claves
```c
#include "MiBibliotecaESP32.h"

// Inicializar operación de derivación
psa_key_derivation_operation_t operacion;
uint8_t salt[/* ... */], info[/* ... */], compartida[/* ... */], derivada[/* ... */];

// Derivar claves
der(& salt, info, compartida, derivada);
```
En esta funcion que se encarga la derivacion de la clave compartida usando hkdf solo habria que pasarle la clave a derivar y los valores de salt e info para que se haga la correcta derivacion de la clave y nos devuelva ese valor.
## Obtencion de la clave compartida
```c
#include "MiBibliotecaESP32.h"

// Configurar algoritmo y claves
psa_algorithm_t alg = /* ... */;
psa_key_id_t private_key = /* ... */;
const uint8_t peer_key[/* ... */];
uint8_t output[/* ... */];

// Realizar operación de intercambio de claves
com( private_key, peer_key, output);
```
De esta manera si se le pasa una clave privada y la publica del otro extremo generara la clave dcompartida en la variable output.
# 2.Contribuciones
Siéntete libre de contribuir a este proyecto. Abre un problema o envía una solicitud de extracción para sugerencias y correcciones
# 3.Licencia
Este archivo markdown proporciona información detallada sobre el uso, la instalación, las contribuciones y la licencia de tu biblioteca. Asegúrate de personalizarlo según las necesidades específicas de tu proyecto.
