#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "BTree.h"
#include "House.h"

#include <iostream>

class Menu {
private:
    ///Atributos
    BTree<House>* myBTree;

    ///Metodos Privados
    void displayMenu();//Metodo que imprimira como mensaje el menu de acciones que podra hacer el arbol
    void insertElement();//Metodo de la interfaz para insertar los datos al arbol
    void deleteElement();//Metodo de la interfaz para eliminar datos del arbol
    void findElement();//Metodo de la interfaz para buscar un elemento del arbol
    void showParseOrder();//Metodo para mostrar todos los datos del arbol segun el recorrido deseado
    void showInfo();//Metodo de la interfaz para SOLO conocer los elementos dentro del arbol

public:
    ///Constructor
    Menu(BTree<House>&);//Inicializando el apuntador de tipo arbol de la interfaz con el arbol recibido

    ///Metodo publico
    void mainMenu();//Metodo principal de la interfaz
};


#endif // MENU_H_INCLUDED
