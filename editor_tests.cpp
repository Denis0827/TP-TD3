#include <gtest/gtest.h>
#include <string>

#include "EditorResaltado.h"

using namespace std;

void chequear_comentario(const EditorResaltado & e, unsigned pos, string texto_esperado) {
  set<id_comm> comentarios_en_posicion = e.comentarios_palabra(pos);

  for (auto id: comentarios_en_posicion) {
    if (e.texto_comentario(id) == texto_esperado) {
      return;
    }
  }

  FAIL();
}

TEST(editor_tests, test_al_iniciar_no_tiene_palabras_ni_comentarios) {
  EditorResaltado e;
  ASSERT_EQ(e.longitud(), 0);
  ASSERT_EQ(e.cantidad_comentarios(), 0);
}

TEST(editor_tests, test_permite_construir_un_editor_con_un_texto_inicial) {
  EditorResaltado e = EditorResaltado::con_texto("gato sol árbol libro");

  ASSERT_EQ(e.longitud(), 4);

  ASSERT_EQ(e.palabra_en(0), "gato");
  ASSERT_EQ(e.palabra_en(1), "sol");
  ASSERT_EQ(e.palabra_en(2), "árbol");
  ASSERT_EQ(e.palabra_en(3), "libro");

  ASSERT_EQ(e.cantidad_comentarios(), 0);
}

TEST(editor_tests, test_insertar_una_palabra_modifica_el_texto_y_la_longitud) {
  EditorResaltado e = EditorResaltado::con_texto("Hola");
  e.insertar_palabra("mundo", 1);

  ASSERT_EQ(e.longitud(), 2);
  ASSERT_EQ(e.palabra_en(0), "Hola");
  ASSERT_EQ(e.palabra_en(1), "mundo");

  ASSERT_EQ(e.cantidad_comentarios(), 0);
}

TEST(editor_tests, test_borrar_una_palabra_modifica_el_texto_y_la_longitud) {
  EditorResaltado e = EditorResaltado::con_texto("Hola mundo");
  e.borrar_palabra(1);

  ASSERT_EQ(e.longitud(), 1);
  ASSERT_EQ(e.palabra_en(0), "Hola");

  ASSERT_EQ(e.cantidad_comentarios(), 0);
}

TEST(editor_tests, test_borrar_palabra_elimina_comentarios_vacios) {
  EditorResaltado e = EditorResaltado::con_texto("Hola mundo");
  e.comentar("este se va", 0, 1);
  e.borrar_palabra(0);

  ASSERT_EQ(e.longitud(), 1);
  ASSERT_EQ(e.palabra_en(0), "mundo");

  ASSERT_EQ(e.cantidad_comentarios(), 0);
}

TEST(editor_tests, test_comentar_agrega_un_comentario_en_el_rango) {
  EditorResaltado e = EditorResaltado::con_texto("gato sol árbol libro");

  e.comentar("comentario sobre 'sol' y 'árbol'", 1, 3);

  ASSERT_EQ(e.cantidad_comentarios(), 1);

  chequear_comentario(e, 1, "comentario sobre 'sol' y 'árbol'");
  chequear_comentario(e, 2, "comentario sobre 'sol' y 'árbol'");
}

TEST(editor_tests, test_agregar_texto_en_medio_de_un_comentario_agranda_el_comentario) {
  EditorResaltado e = EditorResaltado::con_texto("gato sol árbol libro");

  e.comentar("este comentario se va a agrandar", 1, 3);

  e.insertar_palabra("loro", 2);

  chequear_comentario(e, 1, "este comentario se va a agrandar");
  chequear_comentario(e, 2, "este comentario se va a agrandar");
  chequear_comentario(e, 3, "este comentario se va a agrandar");
}

TEST(editor_tests, test_resolver_comentario_elimina_el_comentario) {
  EditorResaltado e = EditorResaltado::con_texto("gato sol árbol libro");

  id_comm id = e.comentar("un comentario", 1, 3);

  e.resolver_comentario(id);

  ASSERT_EQ(e.cantidad_comentarios(), 0);
  ASSERT_EQ(e.comentarios_palabra(1).size(), 0);
  ASSERT_EQ(e.comentarios_palabra(3).size(), 0);
}

TEST(editor_tests, test_resolver_comentario_deja_otros_comentarios_intactos) {
  EditorResaltado e = EditorResaltado::con_texto("gato sol árbol");

  id_comm id1 = e.comentar("este se va", 0, 2);    // comentario sobre "gato" y "sol"
  id_comm id2 = e.comentar("este se queda", 1, 3); // comentario sobre "sol" y "árbol"

  e.resolver_comentario(id1);

  ASSERT_EQ(e.cantidad_comentarios(), 1);
  chequear_comentario(e, 1, "este se queda");
}

TEST(editor_tests, test_cargar_texto) {
  EditorResaltado e;

  // NOTE: la ruta a ambos archivos incluye ".." porque se asume que el test se
  // va a correr dentro del directorio "build" generador por CMake.
  e.cargar_texto("../texto.txt","../comentarios.txt");

  ASSERT_EQ(e.longitud(), 69);

  ASSERT_EQ(e.cantidad_comentarios(), 5);

  chequear_comentario(e, 0, "El Lorem Ipsum es un texto de relleno usado por la industria tipográfica desde aproximadamente el año 1500.");
  chequear_comentario(e, 1, "\"Lorem ipsum\" proviene de las palabras \"dolorem ipsum\" truncadas.");
  chequear_comentario(e, 60, "Los fragmentos de texto provienen del texto \"De finibus bonurum et malorum\".");
}
