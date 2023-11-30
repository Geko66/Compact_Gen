#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cJSON.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "esp_tls.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>
#include <psa/crypto.h>
#include <psa/crypto_values.h>
#include <psa/crypto_builtin_primitives.h>
#include <mbedtls/ecdh.h>
#if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif
#include compact_gen.h

#include "esp_http_client.h"

void generar_y_exportar_llaves( psa_key_id_t * key, uint8_t * data){
	size_t olen;
	psa_key_attributes_t attributes;
    attributes = psa_key_attributes_init();
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DERIVE);
    psa_set_key_lifetime(&attributes, PSA_KEY_LIFETIME_VOLATILE);
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDH);
    psa_set_key_type(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_bits(&attributes, 256);
	 // 1. Generar la llave privada
    if (psa_generate_key(*attributes, *key) != PSA_SUCCESS) {
        fprintf(stderr, "Error al generar la llave privada\n");
        
    }

    // 2. Exportar la llave pública
    if (psa_export_public_key(*key, data, sizeof(data), olen) != PSA_SUCCESS) {
        fprintf(stderr, "Error al exportar la llave pública\n");
	}
}
void com( psa_key_id_t private_key, const uint8_t * peer_key, uint8_t * output){
	size_t output_lenB;
	// 1 Compartida
	if(psa_raw_key_agreement(PSA_ALG_ECDH, private_key, peer_key, sizeof(peer_key), output, sizeof(output), &output_lenB) != PSA_SUCCESS ){
		fprintf(stderr, "Error en psa_raw_key_agreement\n");
}
	
void der( uint8_t * data1, uint8_t * data2 ,uint8_t * compartida,uint8_t * derivada){
	psa_key_derivation_operation_t operacion;
	operacion = psa_key_derivation_operation_init();
// 2 Derivada
	if (psa_key_derivation_setup(&operacion,  PSA_ALG_HKDF(PSA_ALG_SHA_256)) != PSA_SUCCESS){
	fprintf(stderr, "Error de configuracion 1\n");
	}
	if (psa_key_derivation_input_bytes(*operacion, PSA_KEY_DERIVATION_INPUT_SALT, data1, sizeof(data1)) != PSA_SUCCESS){
	fprintf(stderr, "Error de configuracion 2\n");}
	if (psa_key_derivation_input_bytes(*operacion,PSA_KEY_DERIVATION_INPUT_SECRET,compartida,sizeof(compartida)) != PSA_SUCCESS){
	fprintf(stderr, "Error de configuracion 3\n");}
	if (psa_key_derivation_input_bytes(*operacion, PSA_KEY_DERIVATION_INPUT_INFO, data2, sizeof(*data2)) != PSA_SUCCESS){
	fprintf(stderr, "Error de configuracion 4\n");}
	if (psa_key_derivation_output_bytes(*operacion, derivada, sizeof(derivada)) != PSA_SUCCESS){
		fprintf(stderr, "Error de obtencion de derivada revisar configuracion 4\n");
	}

}