#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Table_Index.h" //"libreria" de implementacion de lista simplemente ligada
#include "House.h" //"libreria" de mi objeto a manejar

#include <iostream>

class Menu {
    private:
        ///Atributos privados
        Table<House,30>* myTable;

        ///Metodos Privados
        void newElement();

        void deleteElement();

        void showTableMenu();

        void findAnElement();

        void displayMenu();

    public:
        ///Constructor
        Menu(Table<House,30>&);

        ///Metodo
        void mainMenu();
    };

#endif // MENU_H_INCLUDED
