#include "EditorResaltado.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

EditorResaltado::EditorResaltado() {
	this->_longitud_texto = 0;  // O(1)
	this->_texto;  // O(1)
	this->_comentarios;  // O(1) 
	this->_comentarios_de_cada_palabra;  // O(1)
	this->_cantidad_comentarios = 0;  // O(1)
}

unsigned EditorResaltado::longitud() const {
	return this->_longitud_texto;  // O(1)
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
	return this->_texto[pos];  // O(1)
}

const string& EditorResaltado::texto_comentario(id_comm id) const {
	return get<0>(this->_comentarios.at(id));  // O(1)
}

const set<id_comm>& EditorResaltado::comentarios_palabra(unsigned pos) const {
	set<id_comm> ids_comentarios = this->_comentarios_de_cada_palabra[pos];  // O(1)
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
			++it;
		}
        this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, aux);  // 
    } else {
    	this->_comentarios_de_cada_palabra.insert(this->_comentarios_de_cada_palabra.begin() + pos, set<id_comm>());  // 
    }
    
    this->_longitud_texto++;  // 
}

void EditorResaltado::borrar_palabra(unsigned pos) {
	set<id_comm> comentarios = this->_comentarios_de_cada_palabra[pos];  // O(1)
	this->_texto.erase(this->_texto.begin() + pos);  // O(P) porque elimina un valor de un vector

	auto it_cada_comen = comentarios.begin();  // O(1)
	while(it_cada_comen != comentarios.end()) {  // O(M) porque la cantidad de veces que se recorre el ciclo depende de la cantidad de comentarios de la palabra
		string texto = get<0>(this->_comentarios[*it_cada_comen]);  // O(log(C)) porque accede al valor de una clave de un map
		int palabras = get<1>(this->_comentarios[*it_cada_comen]);  // O(log(C))
		this->_comentarios[*it_cada_comen] = tuple(texto, palabras - 1);  // O(log(C)) porque reasigna el valor de una clave de un map
		++it_cada_comen;  // O(1)
	}

	auto it_todos_comens = this->_comentarios.begin();  // O(1)
	while(it_todos_comens != this->_comentarios.end()) {  // O(C) porque la cantidad de veces que se recorre el ciclo depende de la cantidad de comentarios totales
		if(get<1>(it_todos_comens->second) == 0) {  // O(1) porque accede al valor de una clave de un map con un iterador
			it_todos_comens = this->_comentarios.erase(it_todos_comens);  // O(1) amortizado porque elimina un valor de un map con un iterador
			this->_cantidad_comentarios--;  // O(1)
		} else {
			++it_todos_comens;  // O(1)
		}
	}
	
	this->_comentarios_de_cada_palabra.erase(this->_comentarios_de_cada_palabra.begin() + pos);  // O(M) porque elimina un valor de un vector
	this->_longitud_texto--;  // O(1)
}

// Cuenta de complejidad total:
// O(1) + O(P) + O(1) + O(M) * [O(log(C)) + O(log(C)) + O(log(C)) + O(1)] + O(1) + O(C) * [O(1) + O(1) + O(1) + O(1)] + O(M) + O(1) =
// O(1) + O(P) + O(1) + O(M) * O(log(C)) + O(1) + O(C) * O(1) + O(M) + O(1) =
// O(P) + O(M) * O(log(C)) + O(C)

id_comm EditorResaltado::comentar(const string& texto, unsigned pos_desde, unsigned pos_hasta) {
	unsigned ultimo_id;
	if(this->_comentarios.empty()) {
		ultimo_id = 1;
	} else {
		ultimo_id = (this->_comentarios.end())->first + 1;  // 
	}
	this->_comentarios[ultimo_id] = tuple(texto, pos_hasta - pos_desde);  // 
	
  	for (int k = pos_desde; k < pos_hasta; k++) {  // 
		this->_comentarios_de_cada_palabra[k].insert(ultimo_id);  // 
	}

	this->_cantidad_comentarios++;  // 
}

void EditorResaltado::resolver_comentario(id_comm id) {
	this->_comentarios.erase(id);  // 
	this->_cantidad_comentarios--;  // 

	/*
	int i = 0;  // 
	while(i < this->_comentarios_de_cada_palabra.size()) {  // 
		auto it = this->_comentarios_de_cada_palabra[i].find(id);  // 
		if(it != this->_comentarios_de_cada_palabra[i].end()) {  // 
			this->_comentarios_de_cada_palabra[i].erase(it);  // 
		} 
		i++;
	}
	*/
}

unsigned EditorResaltado::cantidad_comentarios() const {
	return this->_cantidad_comentarios;  // O(1)
}

EditorResaltado EditorResaltado::con_texto(const string& texto) {
	EditorResaltado editor = EditorResaltado();
	int i = 0; int j = 0;
	editor._texto = vector<string>();
	editor._comentarios_de_cada_palabra = vector<set<id_comm>>();

	if (!texto.empty()) {
        editor._texto.push_back("");
        editor._comentarios_de_cada_palabra.push_back(set<id_comm>());
    }

	while(i < texto.size()) {
		if(texto[i] != ' ') {
			editor._texto[j].push_back(texto[i]); // agrego una letra a la palabra
		} else {
			editor._texto.push_back(""); // agrego la palabra
			editor._longitud_texto++;
			editor._comentarios_de_cada_palabra.push_back(set<id_comm>());
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
