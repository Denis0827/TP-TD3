#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include <tuple>

// Incluya aquí los headers que necesite

using std::string;
using std::set;
using std::map;
using std::vector;
using std::tuple;

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
		map<id_comm, tuple<string, pair<unsigned, unsigned>>> _comentarios; 
		vector<set<id_comm>> _comentarios_de_cada_palabra;
		unsigned _cantidad_comentarios;

		// Rep(e:estr) ≡

		// Los elementos de _texto no tienen espacios.
		// (forall i:int) 0 <= i < |e._texto| ⇒ ((forall j:int) 0 <= j < |e._texto[i]| ⇒ e._texto[i][j] != ' ') &&

		// El valor de _cantidad_comentarios equivale a la cantidad de claves en _comentarios.
		// e._cantidad_comentarios = #(claves(e._comentarios)) &&

		// El valor de _longitud_texto equivale a la cantidad de elementos en _texto y _comentarios_de_cada_palabra.
		// |e._texto| = |e._comentarios_de_cada_palabra| = e._longitud_texto &&

		// Los id_comm que están en los sets de _comentarios_de_cada_palabra están también en _comentarios (ida y vuelta).
		// (forall id:id_comm) id ∈ claves(e._comentarios) ⇒ ((exists i:int) 0 <= i < |e._comentarios_de_cada_palabra| && id ∈ e._comentarios_de_cada_palabra[i]) &&
		// (forall i:int) 0 <= i < |e._comentarios_de_cada_palabra| ⇒ ((forall id:id_comm) id ∈ e._comentarios_de_cada_palabra[i] ⇒ id ∈ claves(e._comentarios)) &&		
		
		// Los id_comm almacenados en los sets de _comentarios_de_cada_palabra solamente puede repetirse en los sets vecinos.
		// (forall i:int) 0 <= i <= |_comentarios_de_cada_palabra| ⇒  (forall j:int) 0 <= j <= |_comentarios_de_cada_palabra[j]| ⇒
		// ⇒ [(exists k:int) 0 <= k <= |_comentarios_de_cada_palabra[i-1]| || (exists n:int) 0 <= n <= |_comentarios_de_cada_palabra[i+1]|] &&
		// && _comentarios_de_cada_palabra[i][j] = comentarios_de_cada_palabra[i-1][k] || _comentarios_de_cada_palabra[i][j] = comentarios_de_cada_palabra[i+1][n]

		// Los segundos valores de las tuplas de cada id_comm de _comentarios equivale a la cantidad de elementos de _comentarios_de_cada_palabra que tienen incluido en su set dicha id_comm.
		// (foarll id:id_comm) id ∈ claves(e._comentarios) ⇒ e._comentarios[id].second = 

		// sum


};
