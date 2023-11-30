#ifndef COMPACT_GEN
#define COMPACT_GEN

#include <psa/crypto.h>

// Función para generar y exportar llaves
void generar_y_exportar_llaves( psa_key_handle_t *llave_privada, uint8_t *llave_publica, size_t tamano_llave, size_t *olen);

// Función para realizar la operación de intercambio de claves
void com( psa_key_id_t private_key, const uint8_t *peer_key, uint8_t *output);

// Función para realizar la derivación de claves
void der( const uint8_t *data1, size_t data1_size, const uint8_t *compartida, size_t compartida_size, const uint8_t *data2, size_t data2_size, uint8_t *derivada, size_t derivada_size);



#endif  // COMPACT_GEN