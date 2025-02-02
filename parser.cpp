/*
 * ParserTex.h
 *
 *  Created on: 06/06/2013
 *      Author: pablo
 */

#include "parser.h"
#include "ManejadorArchivos.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <list>
#include <algorithm>

//#ifndef CANTIDAD_DE_SEPARADORES
#define CANTIDAD_DE_SEPARADORES 42



Parseador::Parseador(){

}


Parseador::~Parseador(){

}


//Parsea el documento de texto extrayendo los terminos(filtrados) y su ubicacion en el mismo
std::string Parseador::parser(std::string& archivoaparsear,int doc){
				if(doc==0) cout << "Eaquí el problema.";

				this->nombrearchivo=archivoaparsear;//guardo el nombre

				std::string nombrearchivofinal;//archivo a devolver
				nombrearchivofinal=this->getnombrearchivofinal();//nombre del archivo a crear
				ofstream archivofinal;
				archivofinal.open(nombrearchivofinal.c_str(),std::ofstream::out); //creacion del archivo


				int pos=1; // Posicion de la palabra en el documento actual
				//int doc; // QUE DOC USO? PONGO EL NOMBRE DEL ARCHIVO?? MMM
				std::string palabra;

				const char* invalidos[CANTIDAD_DE_SEPARADORES] = {"¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`"};
				ManejadorArchivos archivo;

				archivo.abrirLectura(archivoaparsear);
				std::string auxLinea;

				while ( archivo.leerunalinea(auxLinea)){
	                char *linea = new char[256];
	                strcpy(linea,auxLinea.c_str());
	                char* auxPalabra = strtok(linea,*invalidos);

	                while ( auxPalabra != NULL ){
	                        palabra = auxPalabra;
	                        this->pasarAminusculas(palabra);

	                        termino term;

	                        term.doc=doc;
	                        term.term=palabra;
	                        term.posi=pos;

	                        //Meto en mi lista el conjunto palabra-posicion
	                        this->milista.push_back(term);


	                        pos++;
	                        auxPalabra = strtok (NULL, *invalidos);
	                }
	                delete []linea;
	                delete auxPalabra;
	               // pos--;
	        }

		//Comienza etapa de ordenar, calcular distancias y escribir en archivo

		    this->ordenarlistaposta();
		    this->acomodador(archivofinal);
		    archivofinal.close();
		//delete archivo; // cierra el archivo, no lo borra
		//delete direccion;
		//i++;

	      return nombrearchivofinal;
	 }


//Devuelve el nombre de mi archivo parseado
std::string Parseador::getnombre(){

	return this->nombrearchivo;


}

//Devuelve el nombre del archivo final dps de parsear y ordenar(va a hacer el nombre del archivo
//donde se va a grabar al final)
std::string Parseador::getnombrearchivofinal(){


	ostringstream os;

	os << this->nombrearchivo << "final.txt";

	return os.str();


}
void Parseador::pasarAminusculas(std::string& str){
     std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}


int Parseador::cantidadpalabras(){

	return this->milista.size();

}

//Defino un ordenamiento de estructuras para mi lista
bool Parseador::ordenamiento(termino const& izq,termino const& der){

	if (izq.term != der.term)

	     return (izq.term < der.term);

	if (izq.posi != der.posi)

	     return (izq.posi < der.posi);

	else return true;
}

void Parseador::mostrarlista(){

	std::list<termino>::iterator it;
	//itero mi lista
	for(it=this->milista.begin();it != this->milista.end(); ++it){

		cout<<(*it).term<<(*it).posi<<endl;


	}


}

//Ordeno mi lista con mi metodo de ordenamiento prefijado
void Parseador::ordenarlistaposta(){

	this->milista.sort(&ordenamiento);

}

// Manda al archivo la estructura final para el merge)
// Lo escribe como termino - ndoc - frec - offs en dist
void Parseador::acomodador(std::ofstream& of){

	std::list<int> lista_aux;// lista para guardar las posiciones de un mismo termino
	std::list<termino>::iterator it; // para iterar toda mi lista
	string palabraanterior; // para comparar con la palabra actual
	int frec = 1;
	int contador=0;
	int doc=0;
	//Itero toda la lista
	for(it=this->milista.begin();it != this->milista.end(); ++it){

		//Si es el primer termino, lo guardo y uso ese para empezar comparar
		if(contador==0){

			lista_aux.push_back((*it).posi);
			palabraanterior=(*it).term;
			doc=(*it).doc;
			contador++;
		} else

		if(palabraanterior==(*it).term && contador!=0){

			frec++;
			lista_aux.push_back((*it).posi);



		}

		else if(palabraanterior!=(*it).term && contador!=0) {
			of<<palabraanterior<<" "<<(*it).doc<<" "<<frec<<" ";
			posicionadistancia(lista_aux,of);
			of<<endl;


			frec=1;
			palabraanterior=(*it).term;
			lista_aux.clear();
			lista_aux.push_back((*it).posi);


		}





	}
	of<<palabraanterior<<" "<<doc<<" "<<frec<<" ";
					posicionadistancia(lista_aux,of);
					of<<endl;

}

	//Agarra una lista de offset y la pasa a distancia
void Parseador::posicionadistancia(std::list<int>& lista,std::ofstream& of){

		std::list<int>::iterator it;
		int primer=0;
		int offanterior;
		for(it=lista.begin();it != lista.end(); ++it){

			if(primer==0) {
				of<<(*it)<<" ";
				offanterior=(*it);
				primer++;
			}

			else{

				of<<((*it)-offanterior)<<" ";
				offanterior=(*it);

			}


			primer++;

		}

}

vector<std::string> Parseador::parsearlinea(std::string unString) {
	const char* invalidos[CANTIDAD_DE_SEPARADORES] = {"¡!#$%&'( )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`"};
	char *linea = new char[unString.size()+1];
	linea[unString.size()] = '\0'; // seguro preventivo por si strcpy funciona mal
	strcpy(linea,unString.c_str());
	char* auxPalabra = strtok(linea,*invalidos);
	string palabra;
	short pos=1;
	vector<string> resultado;
	while ( auxPalabra != NULL ){
			palabra = auxPalabra;
			this->pasarAminusculas(palabra);
			resultado.push_back(palabra);
			pos++;
			//delete auxPalabra;
			auxPalabra = strtok (NULL, *invalidos);
	}
	delete []linea;
	return resultado;
   // pos--;
}





