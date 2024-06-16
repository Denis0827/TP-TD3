#pragma once

#include "EditorResaltado.h"

#include <iostream>
#include <sstream>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;
using namespace ftxui;

class UI {
  public:
    UI(EditorResaltado & editor) : _editor(editor), _pos(0), _reset_position(""), _screen(Screen::Create(Dimension::Full(), Dimension::Full())) {};

    void ejecutar() {
      while(true) {
        render();
        ejecutar_comando();
      }
    }

  private:
    EditorResaltado _editor;
    int _pos;

    string _reset_position;
    Screen _screen;

    void ejecutar_comando() {
      string tmp, tmp2;
      int desde, hasta;

      char ch;
      cin >> ch;
      switch(ch) {
        case 'q':
          exit(0); break;
        case 'i': {
          getline(cin,tmp);
          stringstream ss(tmp);
          while (ss >> tmp2)
            _editor.insertar_palabra(tmp2,_pos++);
        } break;
        case 'e':
          if (_pos < _editor.longitud())
            _editor.borrar_palabra(_pos);
          break;
        case 'c':
          cin >> desde >> hasta;
          getline(cin,tmp);
          _editor.comentar(tmp,desde % _editor.longitud(), hasta%_editor.longitud());
          break;
        case 'f':
          cin >> tmp >> tmp2;
          _editor.cargar_texto(tmp,tmp2);
          _pos = 0;
          break;
        case 'r':
          if (_pos < _editor.longitud() and _editor.comentarios_palabra(_pos).size() > 0)
          {
            if (_editor.comentarios_palabra(_pos).size() == 1) {
              _editor.resolver_comentario(*_editor.comentarios_palabra(_pos).cbegin());
            } else {
              cout << endl << "id?:";
              cin >> desde;
              _editor.resolver_comentario(desde);
            }
          }
          break;
        case 'h':
          _pos = (_pos-1) % (_editor.longitud()+1);
          break;
        case 'l':
          _pos = (_pos+1) % (_editor.longitud()+1);
        default:
          break;
      }
    }

    void render() {
      stringstream status_posicion, status_comentarios, instrucciones, ft;
      std::vector<Element> palabras;
      status_posicion    << "Posición: " << _pos << " de " << _editor.longitud();
      status_comentarios << "Comentarios: " << _editor.cantidad_comentarios() << endl;
      instrucciones      << "Comandos: [i]nsertar y [e]liminar palabra, [c]omentar, [r]esolver comentario, [h/l] mover a derecha/izquierda, [f] cargar texto y comentarios" << endl;

      for (int i=0; i < _editor.longitud(); ++i) {
        stringstream txt;
        if (_pos == i) txt << "[";
        txt << _editor.palabra_en(i);
        if (_pos == i) txt << "]";
        txt << " ";

        if (_editor.comentarios_palabra(i).size() > 0){
          auto last_id = *_editor.comentarios_palabra(i).rbegin();
          palabras.push_back(bgcolor(Color(Color::Palette256(last_id%256)),text(txt.str())));
        }
        else
          palabras.push_back(text(txt.str()));
      }

      std::vector<Element> comentarios;

      if (_pos == _editor.longitud()) {
        palabras.push_back(text(">"));
      } else {
        for (auto c: _editor.comentarios_palabra(_pos)) {
          ft << "[" << c << "]:" << _editor.texto_comentario(c);
          comentarios.push_back(text(ft.str()));
          ft = stringstream();
        }
      }

      auto document = vbox({
        vbox({
          text(status_posicion.str()),
          text(status_comentarios.str()),
        }),
        hflow(palabras) | border | flex,
        vbox(comentarios) | flex,
        text(instrucciones.str()),
      });

      _screen.Clear();
      Render(_screen, document);

      cout << _reset_position;
      _screen.Print();
      _reset_position = _screen.ResetPosition();
    }
};
