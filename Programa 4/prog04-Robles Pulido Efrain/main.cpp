#include <iostream>

#include "Menu.h"
#include "Table_Index.h"


using namespace std;

int main(){
    Table<House, 30> myTable;
    Menu interfaz(myTable);
    interfaz.mainMenu();
    return 0;
}
