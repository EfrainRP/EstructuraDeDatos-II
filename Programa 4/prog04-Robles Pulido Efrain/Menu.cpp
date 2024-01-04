#include "Menu.h" //"libreria" para la implementacion de la interfaz/menu

string fileTxt = "file01.bin"; //nombre de la del archivo a manipular

using namespace std;

///Metodos privados
void Menu::newElement() {
    system("cls"); //Limpia toda la pantalla

    //Inicializacion de variables a usar
    string myStr;
    int myInt;

    House newHouse;

    cout << "\n\t\t Agregue Casa" << endl;

    ///Datos de la Casa
    cout << "Ingrese el NUMERO de la Casa: ";
    cin>>myInt;
    newHouse.setNumber(myInt);

    cout << "\nIngrese la CALLE: ";
    cin.sync();
    getline(cin, myStr);
    newHouse.setStreet(myStr);

    cout << "\nIngrese la COLONIA que pertenece: ";
    getline(cin, myStr);
    newHouse.setColony(myStr);

    if (!myTable->isFull()) {///Cuando es el primer elemento a insertar a la lista
        myTable->insertData(newHouse);//Insertara despues del punto de referencia
    }else{
        cout << "\t\t\tTabla LLENA...\n" << endl;
    }
}

void Menu::deleteElement() {
    //Inicializacion de variables a usar
    int myInt;
    char myCharA, myCharB;
    House deleteHouse;

    do {
        system("cls"); //Limpia toda la pantalla
        showTableMenu();//Metodo de la interfaz para mostrar la tabla
        cout<< "Eliminar todos: [T]odos / [S]olo uno / [R]egresar al Menu:      ";
        cin>>myCharA;
        cin.sync();
        myCharA = toupper(myCharA);//Convierte las letras a mayusculas

        switch (myCharA) {
            case 'T'://Borrara todos los elementos de la lista
                cout<< "Confirmacion: [S]i / [N]o: ";
                cin>>myCharB;
                cin.sync();
                myCharB = toupper(myCharB);//Convierte las letras a mayusculas

                if(myCharB == 'S') {
                    myTable->deleteAllData();//Metodo de la lista para eliminar todos los elementos
                    cout<< "Elementos Eliminados.... ";

                    }
                else {
                    cout<< "Elementos NO eliminados.... ";
                    }

                break;

            case 'S':
                cout<< "Ingrese el NUMERO de Casa a eliminar: ";
                cin>>myInt;
                deleteHouse.setNumber(myInt);

                myTable->deleteData(deleteHouse);//Metodo de la para eliminar en una posicion de la lista
                break;

            case 'R'://Regresara al metodo principal de la interfaz, terminando la iteracion do-while
                break;

            default:
                cout<<endl<<"ERROR, Ingrese opcion valida    "<<endl;
            }
        system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
        }
    while(myCharA != 'R');

    }


void Menu::displayMenu() {//Metodo para imprimir las opciones de la interfaz
    cout<< "\t\t MENU " <<endl;
    cout<< "\t[A]gregar: " <<endl;
    cout<< "\t[E]liminar: " <<endl;
    cout<< "\t[M]ostrar toda la lista" <<endl;
    cout<< "\t[B]usqueda" <<endl;
    cout<< "\t[S]alir " <<endl;
    cout<< "\tSelecciona una opcion (A,E,M,B,S):  ";
    }

void Menu::showTableMenu() {//Metodo para imprimir el formato de la tabla y sus elementos
    system("cls"); //Limpia toda la pantalla

    string myStr;

    myStr += "POSICION | -> ";
    myStr += " [ Numero de la Casa | Calle | Colonia ]";
    cout<<myStr;//Imprimira el mensaje con el formato anterior

    cout<<endl<<myTable->toString()<<endl<<endl;//Imprimira lo que nos regresara el metodo de la lista
                                                //con todos los elementos de la lista

    }

void Menu::findAnElement() {
    //Inicializacion de variables
    List<House>::Position pointSearch;
    string myString;
    char myCharA;
    int myInt;
    House element;

    do {
        system("cls");//Limpia toda la pantalla
        cout<<"\tIngrese tipo de busqueda"<<endl;
        cout<<"Buscar por numero de la [C]asa / [R]egresar al menu:  ";
        cin>> myCharA;
        cin.sync();
        myCharA = toupper(myCharA);//Convertira las letras a mayusculas

        switch (myCharA) {
            case 'C':///Busqueda por numero de casa
                cout<<endl<<"Ingrese el NUMERO de la Casa a buscar: ";
                cin>>myInt;
                element.setNumber(myInt);

                if((pointSearch = myTable->findData(element)) != nullptr) {//Busqueda lineal de la lista
                    element = pointSearch->getData();//Recuperacion del elemento en aquella posicion
                    cout<<endl<<"La Casa esta en la CALLE: "<<element.getStreet();
                    cout<<"    ------->   En la COLONIA: "<<element.getColony()<<endl<<endl;
                    }
                else {
                    cout<<endl<< "\tNo existe la House"<<endl;
                    }
                break;

            case 'R'://Regresara al menu, interrumpiendo la iteracion do-while
                break;

            default:
                cout<<endl<<"ERROR, Ingrese opcion valida"<<endl;
            }
        system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
        }
    while(myCharA != 'R');
    }

///Constructor
Menu::Menu(Table<House,30>& _table): myTable(&_table) {}//Iniciara la lista de la interfaz con el constructor de la lista

///Metodo
void Menu::mainMenu() {
    char opc, opcContinue;//Inicializando variables

    myTable->readFromDisk(fileTxt);//Metodo de la lista para leer desde el archivo

    do {
        showTableMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
        displayMenu();//Metodo de la interfaz para mostrar las opciones de la interfaz
        cin>> opc;
        cin.sync();
        opc = toupper(opc);//Convertira las letras a mayusculas

        switch (opc) {
            case 'A'://Agregara elementos a la lista
                do {
                    showTableMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
                    displayMenu();//Metodo de la interfaz para mostrar las opciones de la interfaz

                    newElement();//Metodo de la interfaz donde hara el proceso para insertar elementos nuevos a la lista

                    cout<< "Ingresar otro dato [S]/[N]: ";
                    cin>> opcContinue;
                    opcContinue = toupper(opcContinue);//Convertira las letras a mayusculas
                    system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
                    }
                while(opcContinue != 'N');
                break;

            case 'E':
                showTableMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
                if(!myTable->isEmpty()) {//Si no esta vacia la lista podra hacer eliminaciones a la lista
                    deleteElement();//Metodo de la interfaz donde hara el proceso de eliminacion de elementos a la lista

                    }
                else {
                    cout<< "\nLISTA VACIA, debe ingresar los datos" <<endl;
                    system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
                    }
                break;

            case 'M':
                cout<<endl<<endl;
                showTableMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
                system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
                break;

            case 'B':
                findAnElement();//Metodo de la interfaz deonde hara el proceso de buscar y mostrar aquel elemento
                break;

            case 'S'://Terminara el programa, terminando la iteracion do-while
                cout << "\n\tFIN del programa" << endl;
                myTable->writeToDisk(fileTxt);//Metodo del indice para escribir en el archivo, para actualizarlo
                break;

            default:
                cout<< "ERROR, ingrese opcion valida" <<endl;
                system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
            }
        }
    while (opc!='S');

    }


