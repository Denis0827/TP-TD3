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

	set<id_comm> ids_comentarios = this->_comentarios_de_cada_palabra.at(pos);

}

void EditorResaltado::insertar_palabra(const string& palabra, unsigned pos) {
	// TODO: implementar y justificar complejidad
}

void EditorResaltado::borrar_palabra(unsigned pos) {
	// TODO: implementar y justificar complejidad
}

id_comm EditorResaltado::comentar(const string& texto, unsigned pos_desde, unsigned pos_hasta) {
	// TODO: implementar y justificar complejidad
	return 0;
}

void EditorResaltado::resolver_comentario(id_comm id) {
	// TODO: implementar y justificar complejidad
}

unsigned EditorResaltado::cantidad_comentarios() const {
	// TODO: implementar y justificar complejidad
	return 0;
}

EditorResaltado EditorResaltado::con_texto(const string& texto) {
	// TODO: implementar y justificar complejidad
	return EditorResaltado();
}
