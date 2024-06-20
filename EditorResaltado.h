#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>

// Incluya aquí los headers que necesite

using std::string;
using std::set;
using std::map;
using std::vector;

typedef unsigned id_comm;
	
class EditorResaltado {
	public:
		// Constructores
		EditorResaltado();
		// Método estático auxiliar para construir editores de forma conveniente
		static EditorResaltado con_texto(const string& texto);

		// Observadores
  	unsigned longitud() const;
  	const string& palabra_en(unsigned pos) const;
		const string& texto_comentario(id_comm id) const;
		const set<id_comm> & comentarios_palabra(unsigned pos) const;

		// Modificadores
	  	void cargar_texto(const string& archivo_texto, const string& archivo_comentarios);
		void insertar_palabra(const string& palabra, unsigned pos);
		void borrar_palabra(unsigned pos);
		id_comm comentar(const string& comentario, unsigned desde, unsigned hasta);
		void resolver_comentario(id_comm id);

		// Otras operaciones
		unsigned cantidad_comentarios() const;

	private:
		// TODO: Definir la estructura y describir claramente el invariante de
		// representación de la misma.
		unsigned _longitud_texto;
		vector<string> _texto;
		map<const id_comm, string> _comentario;
		vector<set<id_comm>> _comentarios_de_cada_palabra;

		/*
		"Hola soy Pepito como estas"
		0: 1
		1: 1
		2: 1
		3: 0
		4: 0
		map: {0: id1, 1: id1, 2: id1;id2, }

		"Hola soy Pepito como estas"
		0: 
		1:
		2:
		3:
		4:
		map: {(0,2): id1, (2,2): id2}
		*/

};
