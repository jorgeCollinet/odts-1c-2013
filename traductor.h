#ifndef TRADUCTOR_H_
#define TRADUCTOR_H_
#include "lector_bit.h"
#include "escritor_bit.h"
#include <iostream>
#include <cmath>
#include "lector_bit.h"
#include "escritor_bit.h"

#define READ 1
#define WRITE 2

class Traductor{

private:
	LectorBit* reader;
	Escritor_bit* writer;
	int modo;

public:

	// indicar el modo y el archivo
	Traductor(const int modo,const char* arch_destino);

	// lee el siguiente gamma. -1 para error.
	int read_gamma();

	// escribe 1 int en gamma en el destino.
	bool write_gamma(int num);

	// lee el siguiente delta. -1 para error.
	int read_delta();

	// escribe 1 int en gamma en el destino.
	bool write_delta(int num);

	char read_char();

	bool write_char(char letra);

	//Escribe una palabra en modo bit
	bool write_string(std::string palabra);

	size_t read_uint();

	bool write_uint(size_t num);

	// indica el modo
	const int mode();

	double devolver_offset_de_byte(void);

	short devolver_offset_de_bit(void);

	bool avanzar_cursor(int unByte, char unBit);

	void mostrar_archivo_delta(void);

	~Traductor();

};
#endif
