#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

struct Libro {
  string titulo;
  string autor;
  int veces_prestado;
  int copias_disponibles;
  float indice_popularidad;
};

void solicitar_informacion_libro(Libro& libro) {
  cout << "Titulo: ";
  std::getline(cin, libro.titulo);

  cout << "Autor: ";
  std::getline(cin, libro.autor);

  cout << "Veces prestado: ";
  cin >> libro.veces_prestado;

  cout << "Copias disponibles: ";
  cin >> libro.copias_disponibles;

  cin.ignore();
}

void calcular_indice_de_popularidad(Libro& libro) {
  libro.indice_popularidad =
      static_cast<float>(libro.veces_prestado) /
      static_cast<float>(libro.copias_disponibles + 1);
}

void buscar_libro_por_palabra_clave(
    const map<string, map<string, Libro>>& bibliotecas,
    const string& palabra) {
  bool encontrado = false;

  for (const auto& biblioteca : bibliotecas) {
    for (const auto& par : biblioteca.second) {
      const Libro& libro = par.second;

      if (libro.titulo.find(palabra) != string::npos ||
          libro.autor.find(palabra) != string::npos) {
        cout << "Biblioteca: " << biblioteca.first << endl;
        cout << "Titulo: " << libro.titulo << endl;
        cout << "Autor: " << libro.autor << endl;
        cout << "Popularidad: " << libro.indice_popularidad << endl;
        cout << "--------------------------" << endl;
        encontrado = true;
      }
    }
  }

  if (!encontrado) {
    cout << "No se encontraron coincidencias." << endl;
  }
}

void obtener_top_5_libros_mas_populares(
    const map<string, map<string, Libro>>& bibliotecas) {
  vector<Libro> todos_los_libros;

  for (const auto& biblioteca : bibliotecas) {
    for (const auto& par : biblioteca.second) {
      todos_los_libros.push_back(par.second);
    }
  }

  std::sort(todos_los_libros.begin(), todos_los_libros.end(),
            [](const Libro& a, const Libro& b) {
              return a.indice_popularidad > b.indice_popularidad;
            });

  cout << "Top 5 libros mas populares:" << endl;

  int limite =
      todos_los_libros.size() < 5 ? todos_los_libros.size() : 5;

  for (int i = 0; i < limite; ++i) {
    cout << i + 1 << ". " << todos_los_libros[i].titulo
         << " - Popularidad: "
         << todos_los_libros[i].indice_popularidad << endl;
  }
}

void copiar_libro_de_biblioteca(
    map<string, map<string, Libro>>& bibliotecas,
    const string& biblioteca_origen, const string& biblioteca_destino,
    const string& titulo) {
  if (bibliotecas.find(biblioteca_origen) ==
      bibliotecas.end()) {
    cout << "Biblioteca origen no existe." << endl;
    return;
  }

  if (bibliotecas.find(biblioteca_destino) ==
      bibliotecas.end()) {
    cout << "Biblioteca destino no existe." << endl;
    return;
  }

  auto& libros_origen = bibliotecas[biblioteca_origen];

  if (libros_origen.find(titulo) == libros_origen.end()) {
    cout << "El libro no existe en la biblioteca origen." << endl;
    return;
  }

  bibliotecas[biblioteca_destino][titulo] =
      libros_origen[titulo];

  cout << "Libro copiado correctamente." << endl;
}

void imprimir_bibliotecas(
    const map<string, map<string, Libro>>& bibliotecas) {
  for (const auto& biblioteca : bibliotecas) {
    cout << "Biblioteca: " << biblioteca.first << endl;

    for (const auto& par : biblioteca.second) {
      const Libro& libro = par.second;
      cout << "Titulo: " << libro.titulo << endl;
      cout << "Autor: " << libro.autor << endl;
      cout << "Prestado: " << libro.veces_prestado << endl;
      cout << "Copias: " << libro.copias_disponibles << endl;
      cout << "Popularidad: " << libro.indice_popularidad << endl;
      cout << "--------------------------" << endl;
    }
  }
}

int main() {
  map<string, map<string, Libro>> bibliotecas;

  int opcion = 0;

  do {
    cout << "\nMENU\n";
    cout << "1. Solicitar datos\n";
    cout << "2. Ordenar (Top 5)\n";
    cout << "3. Imprimir\n";
    cout << "4. Buscar\n";
    cout << "5. Copiar libro\n";
    cout << "6. Salir\n";
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore();

    if (opcion == 1) {
      string nombre_biblioteca;
      cout << "Nombre de la biblioteca: ";
      std::getline(cin, nombre_biblioteca);

      Libro libro;
      solicitar_informacion_libro(libro);
      calcular_indice_de_popularidad(libro);

      bibliotecas[nombre_biblioteca][libro.titulo] = libro;
    } else if (opcion == 2) {
      obtener_top_5_libros_mas_populares(bibliotecas);
    } else if (opcion == 3) {
      imprimir_bibliotecas(bibliotecas);
    } else if (opcion == 4) {
      string palabra;
      cout << "Palabra clave: ";
      std::getline(cin, palabra);
      buscar_libro_por_palabra_clave(bibliotecas, palabra);
    } else if (opcion == 5) {
      string origen, destino, titulo;

      cout << "Biblioteca origen: ";
      std::getline(cin, origen);

      cout << "Biblioteca destino: ";
      std::getline(cin, destino);

      cout << "Titulo del libro: ";
      std::getline(cin, titulo);

      copiar_libro_de_biblioteca(bibliotecas, origen, destino,
                                 titulo);
    }

  } while (opcion != 6);

  return 0;
}