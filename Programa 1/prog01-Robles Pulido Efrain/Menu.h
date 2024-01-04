#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "List.h"  //"libreria" de implementacion de lista simplemente ligada
#include "House.h" //"libreria" de mi objeto a manejar

#include <iostream>

class Menu {
    private:
        ///Atributos privados
        List<House>* myList;

        ///Metodos Privados
        void newElement();

        void deleteElement();

        void showListMenu();

        void findAnElement();

        void displayMenu();

    public:
        ///Constructor
        Menu(List<House>&);

        ///Metodo
        void mainMenu();
    };

#endif // MENU_H_INCLUDED
