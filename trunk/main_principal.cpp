//#define papa
#ifndef papa
#include <iostream>
#include "lector_directorios.h"
#include "parser.h"
#include "merge2.h"
#include "CargadorMemoria.h"
#include "indexer.h"
#include <vector>
#include <stdio.h>

#define INDEXAR 1
#define CONSULTAR 2
#define ERROR_MODO 3

#define CERRAR "xCerrar"
using namespace std;
/* la llamada al programa se hace pasandole el directorio donde están los archivos */
vector<string> capturar_consultas(const char* consultas) {
	//Debe capturar las consultas y devolverlas al main.
	vector<string> aux ;
	return aux;
}


void crear_repositorio(string& dir_archivos, string& nombre_repositorio) {
	// ruta donde están los archivos a trabajar
	// se buscan los archivos con los cuales trabajaremos
	Lector_directorios lector;
	vector<string>& archivos = lector.leer_dir(dir_archivos.c_str());
	vector<string> archivos_a_mergear;
	cout << "Parser funcionando." << endl;
	// se parsean los archivos
	for (size_t i = 0; i < archivos.size(); i++) {
		string aux = dir_archivos;
		aux += "/";
		aux += archivos[i];
		Parseador pars;
		archivos_a_mergear.push_back(pars.parser(aux, i));
	}
	cout << "Archivos parseados a mergear:" << endl;
	for (size_t i = 0; i < archivos_a_mergear.size(); ++i) {
		cout << archivos_a_mergear[i] << endl;
	}
	// se mergean los archivos
	Merge merger;
	string aux_path_merge = nombre_repositorio + ".merge";
	merger.merge_n_archivos(archivos_a_mergear, aux_path_merge, PRIMERA_PASADA);
	cout << "Termino el merge." << endl;

	// se eliminan los archivos temporales del parser
	for (size_t i = 0; i < archivos_a_mergear.size(); ++i) {
		remove(archivos_a_mergear[i].c_str());
	}

	// se construyen los indices
	cout << "Se comienzan a construir los indices." << endl;
	indexer _idx;
	_idx.indexar(aux_path_merge.c_str());
	cout << "Se indexaron los archivos." << endl;

	delete &archivos;

}
vector<size_t> cargar_terminos_y_resolver_consulta(string& nombre_repositorio, const char* consulta) {
	CargadorMemoria unCargador(nombre_repositorio.c_str());
	try {
		unCargador.cargar_lexico();
		unCargador.cargar_ocurrencias();
	} catch (exception &e) {
		cout << "Hubo un problema al cargar el índice, el programa se cerrará."
				<< endl;
		exit(1);
	}
	//Tomar las consultas

	vector<string> consulta_parc = capturar_consultas(consulta);
	if (consulta_parc.size() == 0) {
		cout<<"consulta vacia";
		vector<size_t> vacio;
		return vacio;
	}
	//Aquí hacer algo con la consulta, por ejempo:
	vector<Termino> terminos;
	for (size_t i = 0; i < consulta_parc.size(); i++) {
		if(unCargador.buscar_termino(consulta_parc[i])==-1){
			cout<<"el termino "<<consulta_parc[i]<<" no aparece en ningun documento"<<endl;
			vector<size_t> vacio;
			return vacio;
		}
		terminos.push_back( unCargador.devolver_ocurrencias_termino(consulta_parc[i]) );
	}
	//Aca el resolvedor tendria que hacer la magia y escupir el resultado.

	ResolvedorDeConsultas resolvedor;
	// FALTA HACER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	size_t cant_total_docs = 800;
	return resolvedor.resolver_consulta(terminos, cant_total_docs);
}

int main(int args, char* argv[]) {
	if (args < 3) {
		cout << "Faltan parametros de llamada al programa." << endl
				<< "./programa -m 'directorio'" << endl
				<< "El directorio es el lugar donde se encuentran los archivos."
				<< endl << "-m es el modo: -q consultas, -r indexar" << endl;
		return 0;
	}
	if (args == 3) {
		cout<<"indexando repositorio"<<endl;
		cout<<"directorio a indexar: "<<argv[1]<<endl;
		cout<<"nombre repositorio: "<<argv[2]<<endl;
		string nombre_repositorio = argv[2];
		string dir_archivos = argv[1];
		crear_repositorio(dir_archivos, nombre_repositorio);
		cout<<"indexado terminado"<<endl;
		return 0;
	}
	if (args!=5 || string(argv[1]) != "-r" || string(argv[3]) != "-q") {
		throw ios_base::failure("formato de parametros incorrecto");
	}
	string nombre_repo = argv[2];
	const char* consulta = argv[4];
	cargar_terminos_y_resolver_consulta(nombre_repo, consulta);
}


#endif
