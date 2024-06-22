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
	this->_comentario;
	this->_comentarios_de_cada_palabra;
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
	return this->_comentario.at(id);
}

const set<id_comm>& EditorResaltado::comentarios_palabra(unsigned pos) const {
	// TODO: implementar y justificar complejidad

	set<id_comm> ids_comentarios = this->_comentarios_de_cada_palabra[pos];
}

void EditorResaltado::insertar_palabra(const string& palabra, unsigned pos) { 
    this->_texto.insert(_texto.begin() + pos, palabra);

    if (!this->_comentarios_de_cada_palabra[pos].empty()){
        set<id_comm> aux = this->_comentarios_de_cada_palabra[pos];
        this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, aux);
		_cantidad_de_palabras_por_comentario[pos] = _cantidad_de_palabras_por_comentario[pos] + aux.size();
    } else {
    	this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, set<id_comm>());
    }
    
    this->_longitud_texto++;
}


void EditorResaltado::borrar_palabra(unsigned pos) {
	// TODO: implementar y justificar complejidad
	auto it_texto = this->_texto.begin();
	auto it_comentario = this->_comentarios_de_cada_palabra.begin();
	int i = 0;

	while(it_texto != this->_texto.end() && it_comentario != this->_comentarios_de_cada_palabra.end()) {
		if(i == pos) {
			this->_texto.erase(it_texto);
			break;
		}
		++it_texto; ++it_comentario;
		i++;
	}

	auto it_set_comentario = it_comentario->begin();

	while(it_set_comentario != it_comentario->end()) {
		this->_cantidad_de_palabras_por_comentario[*it_set_comentario]--;
		++it_set_comentario;
	}

	auto it_todos_los_comentarios = this->_comentario.begin();
	auto it_cant_palabras = this->_cantidad_de_palabras_por_comentario.begin();
	
	while(it_todos_los_comentarios != this->_comentario.end() && it_cant_palabras != this->_cantidad_de_palabras_por_comentario.end()) {
		if(*it_cant_palabras == 0) {
			this->_comentario.erase(it_todos_los_comentarios);
			this->_cantidad_de_palabras_por_comentario.erase(it_cant_palabras);
		} else {
			++it_todos_los_comentarios; 
			++it_cant_palabras;
		}
	}

	this->_longitud_texto--;
}

id_comm EditorResaltado::comentar(const string& texto, unsigned pos_desde, unsigned pos_hasta) {
	// TODO: implementar y justificar complejidad
	id_comm nuevo;
	if (this->_comentario.empty()){
		id_comm first = 1;
		this->_comentario[first] = texto;
	} else{
		id_comm ultimo_id_comm = 0;
    	// Iterar a través del map para encontrar el último id_comm
		for (auto it = this->_comentario.begin(); it != this->_comentario.end(); ++it) {
			if (it->first > ultimo_id_comm) {
				ultimo_id_comm = it->first;
			}
		}
		nuevo = ultimo_id_comm + 1;
		this->_comentario[nuevo] = texto;
	}
  
	_cantidad_de_palabras_por_comentario[nuevo] = pos_hasta - pos_desde;
	
  for (int k = pos_desde; k <= pos_hasta; k++){
		this->_comentarios_de_cada_palabra[k].insert(nuevo);
	}
}

void EditorResaltado::resolver_comentario(id_comm id) {
	// TODO: implementar y justificar complejidad
}

unsigned EditorResaltado::cantidad_comentarios() const {
	// TODO: implementar y justificar complejidad
	return this->_cantidad_comentario;
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
