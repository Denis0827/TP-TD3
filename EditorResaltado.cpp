#include "EditorResaltado.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

EditorResaltado::EditorResaltado() {
	this->_longitud_texto = 0;  // 
	this->_texto;  // 
	this->_comentarios;  // 
	this->_comentarios_de_cada_palabra;  // 
	this->_cantidad_comentarios = 0;  // 
}

unsigned EditorResaltado::longitud() const {
	return this->_longitud_texto;  // 
}

void EditorResaltado::cargar_texto(const string& txt, const string& comments) {
    this->_texto.clear();
    this->_comentarios.clear();
	this->_cantidad_comentarios = 0;
	this->_longitud_texto = 0;
	this->_comentarios_de_cada_palabra;
    
    ifstream archivo_txt(txt);
    ifstream archivo_comments(comments);

    string linea;
    while (getline(archivo_txt, linea)) {
        this->_texto.push_back(linea);
		this->_longitud_texto++;
		this->_comentarios_de_cada_palabra.push_back(set<id_comm>());
    }

	int i = 1;
    while (getline(archivo_comments, linea)) {
		this->_comentarios[i] = tuple(linea, 0);
		this->_cantidad_comentarios++;
		i++;

		int j; string desde; string hasta;

		while(linea[j] != ' ') {
			desde += linea[j];
			j++;
		}

		while(linea[j] != ' ') {
			hasta += linea[j];
			j++;
		}

		comentar(linea, stoi(desde), stoi(hasta));
    }

    archivo_txt.close();
    archivo_comments.close();
}

const string& EditorResaltado::palabra_en(unsigned pos) const {
	return this->_texto[pos];  // 
}

const string& EditorResaltado::texto_comentario(id_comm id) const {
	return get<0>(this->_comentarios.at(id));  // 
}

const set<id_comm>& EditorResaltado::comentarios_palabra(unsigned pos) const {
	set<id_comm> ids_comentarios = this->_comentarios_de_cada_palabra[pos];  // 
}

void EditorResaltado::insertar_palabra(const string& palabra, unsigned pos) {  // 
    this->_texto.insert(this->_texto.begin() + pos, palabra);  // 
	
    if (pos != 0 && !this->_comentarios_de_cada_palabra[pos - 1].empty()){  // 
        set<id_comm> aux = this->_comentarios_de_cada_palabra[pos - 1];  // 
		auto it = aux.begin();  // 
		while(it != aux.end()) {  // 
			string texto = get<0>(this->_comentarios[*it]);  // 
			unsigned palabras = get<1>(this->_comentarios[*it]);  // 
			this->_comentarios[*it] = tuple(texto, palabras + 1);  // 
		}
        this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, aux);  // 
    } else {
    	this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, set<id_comm>());  // 
    }
    
    this->_longitud_texto++;  // 
}

void EditorResaltado::borrar_palabra(unsigned pos) {
	set<id_comm> comentarios = this->_comentarios_de_cada_palabra[pos];  //
	this->_texto.erase(this->_texto.begin() + pos);  // 

	auto it_cada_comen = comentarios.begin();  // 
	while(it_cada_comen != comentarios.end()) {  // 
		string texto = get<0>(this->_comentarios[*it_cada_comen]);  // 
		int palabras = get<1>(this->_comentarios[*it_cada_comen]);  // 
		this->_comentarios[*it_cada_comen] = tuple(texto, palabras - 1);  // 
		++it_cada_comen;  // 
	}

	auto it_todos_comens = this->_comentarios.begin();  // 
	while(it_todos_comens != this->_comentarios.end()) {  //
		if(get<1>(it_todos_comens->second) == 0) {  //
			this->_comentarios.erase(it_todos_comens);  //
			this->_cantidad_comentarios--;  // 
		} else {
			++it_todos_comens;  //
		}
	}

	this->_comentarios_de_cada_palabra.erase(this->_comentarios_de_cada_palabra.begin() + pos);  // 
	this->_longitud_texto--;  //
}

id_comm EditorResaltado::comentar(const string& texto, unsigned pos_desde, unsigned pos_hasta) {
	unsigned ultimo_id = (this->_comentarios.end())->first + 1;  // 
	this->_comentarios[ultimo_id] = tuple(texto, pos_hasta - pos_desde);  // 
	
  	for (int k = pos_desde; k <= pos_hasta; k++) {  // 
		this->_comentarios_de_cada_palabra[k].insert(ultimo_id);  // 
	}

	this->_cantidad_comentarios++;  // 
}

void EditorResaltado::resolver_comentario(id_comm id) {
	this->_comentarios.erase(id);  // 
	this->_cantidad_comentarios--;  // 

	int i = 0;  // 
	while(i < this->_comentarios_de_cada_palabra.size()) {  // 
		auto it = this->_comentarios_de_cada_palabra[i].find(id);  // 
		if(it != this->_comentarios_de_cada_palabra[i].end()) {  // 
			this->_comentarios_de_cada_palabra[i].erase(it);  // 
		}
		i++;  // 
	}
}

unsigned EditorResaltado::cantidad_comentarios() const {
	return this->_cantidad_comentarios;  // 
}

EditorResaltado EditorResaltado::con_texto(const string& texto) {
	EditorResaltado editor = EditorResaltado();
	int i = 0; int j = 0;

	while(i < texto.size()) {
		if(texto[i] != ' ') {
			if(j == 0 && i == 0) {
				editor._texto.push_back("");
				editor._comentarios_de_cada_palabra.push_back(set<id_comm>());
			}
			editor._texto[j].push_back(texto[i]); // agrego una letra a la palabra
		} else {
			editor._texto.push_back(""); // agrego la palabra
			editor._longitud_texto++;
			j++;
		}
		i++;
	}

	if(!editor._texto.empty()) {
		editor._longitud_texto++;
	}

	editor._cantidad_comentarios = 0;

	return editor;
}

