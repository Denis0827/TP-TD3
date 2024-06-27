#include "EditorResaltado.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

	// TODO: implementar y justificar complejidad
EditorResaltado::EditorResaltado() {
	this->_longitud_texto = 0;
	this->_texto;
	this->_comentarios;
	this->_comentarios_de_cada_palabra;
	this->_cantidad_comentarios = 0;
	this->_ultimo_id = 0;
}

unsigned EditorResaltado::longitud() const {
	// TODO: implementar y justificar complejidad
	return this->_longitud_texto;
}

void EditorResaltado::cargar_texto(const string& txt, const string& comments) {
	// TODO: implementar y justificar complejidad
}


const string& EditorResaltado::palabra_en(unsigned pos) const {
	// TODO: implementar y justificar complejidad
	return this->_texto[pos];
}

const string& EditorResaltado::texto_comentario(id_comm id) const {
	// TODO: implementar y justificar complejidad
	return get<0>(this->_comentarios.at(id));
}

const set<id_comm>& EditorResaltado::comentarios_palabra(unsigned pos) const {
	// TODO: implementar y justificar complejidad

	set<id_comm> ids_comentarios = this->_comentarios_de_cada_palabra[pos];
}

void EditorResaltado::insertar_palabra(const string& palabra, unsigned pos) { 
    this->_texto.insert(_texto.begin() + pos, palabra);

    if (!this->_comentarios_de_cada_palabra[pos].empty()){
        set<id_comm> aux = this->_comentarios_de_cada_palabra[pos];
		auto it = aux.begin();
		while(it != aux.end()) {
			string texto = get<0>(this->_comentarios[*it]);
			unsigned palabras = get<1>(this->_comentarios[*it]);
			this->_comentarios[*it] = tuple(texto, palabras++); 
		}
        this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, aux);
    } else {
    	this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, set<id_comm>());
    }
    
    this->_longitud_texto++;
}


void EditorResaltado::borrar_palabra(unsigned pos) {
	// TODO: implementar y justificar complejidad
	this->_texto.erase(this->_texto.begin() + pos);
	set<id_comm> comentarios = this->_comentarios_de_cada_palabra[pos];

	auto it_cada_comen = comentarios.begin();
	while(it_cada_comen != comentarios.end()) {
		string texto = get<0>(this->_comentarios[*it_cada_comen]);
		int palabras = get<1>(this->_comentarios[*it_cada_comen]);
		this->_comentarios[*it_cada_comen] = tuple(texto, palabras--);
		++it_cada_comen;
	}

	auto it_todos_comens = this->_comentarios.begin();
	unsigned ultimo_id = 0;
	while(it_todos_comens != this->_comentarios.end()) {
		if(get<1>(it_todos_comens->second) == 0) {
			this->_comentarios.erase(it_todos_comens);
			this->_cantidad_comentarios--;
		} else {
			if(ultimo_id < it_todos_comens->first) {
				ultimo_id = it_todos_comens->first;
			}
			++it_todos_comens;
		}
	}

	this->_comentarios_de_cada_palabra.erase(this->_comentarios_de_cada_palabra.begin() + pos);
	this->_longitud_texto--;
}

id_comm EditorResaltado::comentar(const string& texto, unsigned pos_desde, unsigned pos_hasta) {
	// TODO: implementar y justificar complejidad
	this->_ultimo_id += 1;
	this->_comentarios[this->_ultimo_id] = tuple(texto, pos_hasta - pos_desde);
	
  	for (int k = pos_desde; k <= pos_hasta; k++) {
		this->_comentarios_de_cada_palabra[k].insert(this->_ultimo_id);
	}

	this->_cantidad_comentarios++;
}

void EditorResaltado::resolver_comentario(id_comm id) {
	// TODO: implementar y justificar complejidad
	this->_comentarios.erase(id);
	this->_cantidad_comentarios--;

	unsigned ultimo_id = 0;
	
	

}

unsigned EditorResaltado::cantidad_comentarios() const {
	// TODO: implementar y justificar complejidad
	return this->_cantidad_comentarios;
}

EditorResaltado EditorResaltado::con_texto(const string& texto) {
	// TODO: implementar y justificar complejidad
	EditorResaltado editor = EditorResaltado();
	int i = 0;
	int j = 0;

	while(i < texto.size()) {
		if(texto[i] != ' ') {
			editor._texto[j].push_back(texto[i]); // agrego una letra a la palabra
		} else {
			editor._texto.push_back(""); // agrego la palabra
			editor._longitud_texto++;
			j++;
		}
		i++;
	}

	return editor;
}
