#include <iostream>

#include "House.h"
#include "Integer.h"

#include "Graph.h"
#include "Menu.h"

using namespace std;

int main() {
    Graph<House,Integer> graph;
    Menu interfaz(graph);
    interfaz.mainMenu();
    return 0;
}
