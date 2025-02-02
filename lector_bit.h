/*
 * lector_bit.h
 *
 *  Created on: 21/05/2013
 *      Author: jorge
 */

#ifndef LECTOR_BIT_H_
#define LECTOR_BIT_H_
#include <iostream>
#include <fstream>
/* clase que se encarga de la lectura de a 1 bit de un determinado archivo */
class LectorBit {
	std::ifstream arch;
	size_t contador;
	unsigned char buffer;
public:
	LectorBit(const char* nombre_archivo);
	/* Devuelve el siguiente bit leido del archivo, es decir un 0 o un 1
	 * En caso de algún error devuelve 2
	 * OJO: despues de leer un bit se tiene que comprobar que no se llegó
	 *  a fin de archivo con el metodo eof(),  ver ejemplo */
	~LectorBit();
	// Cierra el archivo y libera la memoria.
	unsigned int leer_bit();
	/* si se llegó al final del archivo devuelve true caso contrario devuelve false */
	bool eof();
	//Devuelve el offset de bytes en el que se encuentra.
	double devolver_offset_de_byte(void);
	//Devuelve el offset de bit en el que se encuentra.
	short devolver_offset_de_bit(void);
	//Avanza el cursor hasta la posición indicada, devuelve falso si no se puede.
	bool avanzar_cursor(int unByte, char unBit);

};



#endif /* LECTOR_BIT_H_ */
