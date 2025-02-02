/*
 * ManejadorNombreArchivo.cpp
 *
 *  Created on: 05/06/2013
 *      Author: juan
 */

#include "ManejadorNombreArchivo.h"
//#define CLASEENPRUEBA
#ifndef CLASEENPRUEBA
ManejadorNombreArchivo::ManejadorNombreArchivo() {
	nombres = new std::vector<std::string>();
}

ManejadorNombreArchivo::ManejadorNombreArchivo(const char* unNombreArchivo) {
	nombres = new std::vector<std::string>();
	nombreArchivo = std::string (unNombreArchivo);
}

ManejadorNombreArchivo::~ManejadorNombreArchivo() {
	// TODO Auto-generated destructor stub
	delete (nombres);
}

int ManejadorNombreArchivo::agregar_nombre(std::string unNombre) {
	// Agrega un nombre y devuelve el entero que lo representa.
	nombres->push_back(unNombre);
	return nombres->size() - 1;
}

std::string ManejadorNombreArchivo::obtener_nombre(int unEntero) {
	//Devuelve el nombre que corresponde a la posiciòn 'unEntero'
	return (*nombres)[unEntero];
}

bool ManejadorNombreArchivo::guardar_nombres(void) {
	std::ofstream salida;
	salida.open(nombreArchivo.c_str(),std::ios::out);
	if (! salida.is_open()) return false;
	for (unsigned int i= 0 ; i< nombres->size(); i++) {
		salida << (*nombres)[i] << std::endl;
	}
	salida.close();
	return true;
}

bool ManejadorNombreArchivo::cargar_nombres(void){
	std::ifstream entrada;
	entrada.open(nombreArchivo.c_str(), std::ios::in);
	if (! entrada.is_open()) return false;
	while (!entrada.eof()) {
		//Cargo todas las lineas.
		std::string auxiliar;
		entrada >> auxiliar;
		this->agregar_nombre(auxiliar);
	}
	entrada.close();
	return true;
}
#endif
