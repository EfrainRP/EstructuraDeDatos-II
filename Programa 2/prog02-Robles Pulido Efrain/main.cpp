/*Efrain Robles Pulido*/
#include "Menu.h"
#include "House.h"
#include <iostream>

using namespace std;

int main() {
    BTree<House> myTree;
    Menu interfaz(myTree);
    interfaz.mainMenu();
    return 0;
}
