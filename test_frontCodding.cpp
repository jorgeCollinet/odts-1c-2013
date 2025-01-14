#define prueba_para_la_estructura_de_front_codding
#ifndef prueba_para_la_estructura_de_front_codding
/*Esto es una prueba para la estructura de front codding, se espera que no pinche(por ahora)*/
#include "front_codding.h"

int main(void){
	std::string palabras[] = {"perra", "perros", "perritos", "puchache","pantomima", "panqueque","pantalon", "talvez?","tambien","yestamaldita?"};
	Front_codding* fc = new Front_codding("archivo.dat");
	fc->modo_escritura();
	for (unsigned int i=0; i < 10; i++) {
		fc->agregar_palabra(palabras[i].c_str());
	}
	delete (fc);
	Front_codding* fc2 = new Front_codding("archivo.dat");
	int res = 0;
	fc2->modo_lectura();
	for (int i=0; i < 10; i++) {
		string aux = fc2->leer_proxima_palabra();
		if (palabras[i] != aux) {
			res = 1;
			cout << aux << endl;
		}
	}
	cout << "Guardar y leer palabras en front codding: ";
	if (res == 1)
		cout << "incorrecto.";
	else
		cout << "correcto.";
	cout << std::endl << "Inicio prueba de lectura fuera de los limites: ";
	for (unsigned int i=0; i < 10000; i++ ) {
		string aux = fc2->leer_proxima_palabra();
	}
	cout << "correcto." << std::endl << fc2->leer_proxima_palabra();
	delete (fc2);
}
#endif
