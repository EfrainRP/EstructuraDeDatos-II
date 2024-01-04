/*Efrain Robles Pulido*/

#include "Menu.h" //"libreria" del interfaz/menu
#include <iostream>

using namespace std;

int main() {
    List<House> newList;//se inicializa una lista
    Menu interfaz(newList);//inicia un menu con una lista para trabajar
    interfaz.mainMenu();//ejecuta el metodo principal de la interfaz
    return 0;
    }
