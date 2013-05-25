#include "Traductor.h"

int traductor::read_gamma(LectorBit* reader){

	int unary = 0;
	int binary = 0;

	// leo la parte unaria-1, corto en el primer 0
	while (reader.leer_bit()==1){
		unary++;
		if(reader.eof()) return -1;
	}

	//leo el resto
	for(int i=unary;i>0;i--){
		// decodifico la parte binaria
		if(reader.leer_bit() == 1){
			binary=binary+(int)pow((float)2, (float)i);
		}
		if(reader.eof()) return -1;
	}
	return((int)pow((float)2,(float)unary)+binary);
};


void traductor::write_gamma(int num,Escritor_bit* writer){

	int unary;
	int binary;
	int aux,aux2;

	// calculo los componentes
	aux = floor(log2(num));
	unary = 1 + aux;
	binary = num - (int)pow((float)2,(float)aux);

	// escribo la parte unaria
	for(int i=1;i<unary;i++){
		writer.put(1);
	};
	writer.put(0);

	// escribo la parte binaria
	for(int i=aux;i>0;i--){
		aux2 = (int)pow ((float)2, (float)i);
		if(aux2 <= num){
			writer.escribir_bit_desde_abajo(1);
			num = num - aux2;
		}else{
			writer.escribir_bit_desde_abajo(0);
		}
	}
};


int traductor::read_delta(LectorBit* reader){

	int gamma = 0;
	int binary = 0;
	int aux;

	// decodifico la parte gamma
	gamma = (this.read_gamma(LectorBit* reader) - 1);

	for(int i=gamma;i>0;i--){
		// decodifico la parte binaria
		if(reader.leer_bit()){
			binary=binary+(int)pow((float)2, (float)i);
		}
		if(reader.eof()) return -1;
	}
	return((int)pow((float)2,(float)gamma)+binary);
}


void traductor::write_delta(int num,Escritor_bit* writer){

	int gamma;
	int binary;
	int aux,aux2;

	// calculo los componentes
	aux = floor(log2(num));
	gamma = 1 + aux;
	binary = num - (int)pow((float)2,(float)aux);

	// escribo la parte gamma
	this.Write_gamma(gamma,writer);

	// escribo la parte binaria
	for(int i=aux;i>0;i--){
		aux2 = (int)pow ((float)2, (float)i);
		if(aux2 <= num){
			writer.escribir_bit_desde_abajo(1);
			num = num - aux2;
		}else{
			writer.escribir_bit_desde_abajo(0);
		}
	}
};
