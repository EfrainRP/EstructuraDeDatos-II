#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Graph.h"
#include "House.h"
#include "Integer.h"

class Menu {
private:
    ///Atributos
    Graph<House,Integer>* myGraph;

    ///Metodos Privados
    void displayMenu();//Metodo que imprimira como mensaje el menu de acciones que podra hacer el grafo
    void insertElement();//Metodo de la interfaz para insertar los datos al grafo
    void deleteElement();//Metodo de la interfaz para eliminar datos del grafo
    void findElement();//Metodo de la interfaz para buscar en el grafo
    void showInfo();//Metodo de la interfaz para imprimir todos los elementos del grafo

public:
    ///Constructor
    Menu(Graph<House,Integer>&);//Inicializando el apuntador de tipo grafo de la interfaz con el grafo recibido

    ///Metodo publico
    void mainMenu();//Metodo principal de la interfaz
};


#endif // MENU_H_INCLUDED
