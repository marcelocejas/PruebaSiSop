/*
 ============================================================================
 Name        : Serializer.c
 Author      : marcelocejas
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

/**
 * @NAME: Info_NodoFSCarga_Bloques_t
 * @DESC: Estructura para el envio de info para el bloque.
 */
typedef struct {
	int bloqueNro;
	char *data;
}__attribute__((__packed__)) data_t;

char *InfoData_serializer(data_t *self, int16_t *length);
data_t *InfoData_deserializer(char *serialized);
void InfoData_destroy(data_t *bloqueData);

int main(void) {

	data_t* dataSent;
	int16_t* dataLength;
	data_t* dataRecived;
	char* payload;

	dataSent = malloc(sizeof(data_t));
	dataSent->bloqueNro = 12;
	dataSent->data = "Hola serializer";

	puts("!!!Hello serializer!!"); /* prints !!!Hello serializer!! */

	printf("Bloque Nro: %d mensaje: %s.\n", dataSent->bloqueNro,
			dataSent->data);

	dataLength = malloc(sizeof(dataLength));
	payload = InfoData_serializer(dataSent, dataLength);

	puts(payload);

	dataRecived = malloc(sizeof(data_t));

	dataRecived = InfoData_deserializer(payload);

	printf("Bloque Nro: %d mensaje: %s.\n", dataRecived->bloqueNro,
			dataRecived->data);

	InfoData_destroy(dataSent);

	return EXIT_SUCCESS;
}

char *InfoData_serializer(data_t *self, int16_t *length) {
	int size = strlen(self->data) + sizeof(self->bloqueNro) + 1;
	char *serialized = malloc(size);
	int offset = 0, tmp_size = 0;

	memcpy(serialized, &self->bloqueNro, tmp_size = sizeof(self->bloqueNro));
	offset = tmp_size;

	memcpy(serialized + offset, self->data, tmp_size = strlen(self->data) + 1);
	offset += tmp_size;

	*length = offset;
	return serialized;
}
data_t *InfoData_deserializer(char *serialized) {
	data_t *self = malloc(sizeof(data_t));
	int offset = 0, tmp_len = 0;

	memcpy(&self->bloqueNro, serialized, tmp_len = sizeof(self->bloqueNro));
	offset = tmp_len;

	for (tmp_len = 1; (serialized + offset)[tmp_len - 1] != '\0'; tmp_len++)
		;
	self->data = malloc(tmp_len);
	memcpy(self->data, serialized + offset, tmp_len);
	offset += tmp_len;

	return self;
}
void InfoData_destroy(data_t *bloqueData) {
	free(&bloqueData->bloqueNro);
	free(bloqueData->data);
	free(bloqueData);
}
