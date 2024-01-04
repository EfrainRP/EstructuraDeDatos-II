#include "Menu.h" //"libreria" para la implementacion de la interfaz/menu

string fileTxt = "file01.txt"; //nombre de la del archivo a manipular

using namespace std;

///Metodos privados
void Menu::newElement() {
    system("cls"); //Limpia toda la pantalla

    //Inicializacion de variables a usar
    string myStr;
    int myInt;
    char myChar;

    House newHouse, temp;
    List<House>::Position insertPoint;//Direccion de memoria de tipo Nodo

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

    try {//Atrapara un error o excepcion
        if (myList->isEmpty()) {///Cuando es el primer elemento a insertar a la lista
            myList->insertData(nullptr,newHouse);//Insertara despues del punto de referencia
            cout << "\t\t\tCasa Agregado...\n" << endl;
            }
        else {///Cuando ya hay elementos en la lista
            cout<<"Insertar al [P]rincipio  /  [E]legir posicion  /  [F]inal (siguiente del ultimo) :  ";
            cin>>myChar;
            cin.ignore();
            myChar = toupper(myChar);//Convertira a mayusculas las letras

            switch(myChar) {
                case 'P'://Insercion al principio
                    insertPoint = nullptr;
                    myList->insertData(insertPoint,newHouse);//Inserta despues del punto de referencia
                    cout << "\t\t\tCasa Agregada...\n" << endl;
                    break;

                case 'E'://Insercion a elegir a partir de una posicion
                    cout<< "Ingrese el NUMERO de Casa a partir del que se insertara: ";
                    cin>>myInt;
                    temp.setNumber(myInt);

                    if((insertPoint = myList->findDataLinear(temp)) != nullptr) {//Busqueda lineal para encontrar la posicion del elemento deseado
                        myList->insertData(insertPoint,newHouse);//Inserta despues del punto de referencia
                        cout << "\t\t\tCasa Agregada...\n" << endl;
                        }
                    else {
                        cout << "\t\t\t\nCasa No Encontrada" <<endl<<"\t\t\nCasa No Agregada...\n"<<endl;
                        }

                    break;

                case 'F'://Insercion al final de la lista
                    insertPoint=myList->getLastPos();
                    myList->insertData(insertPoint,newHouse);//Inserta despues del punto de referencia
                    cout << "\t\t\tCasa Agregada...\n" << endl;
                    break;

                default:
                    cout << "\t\t\tCasa No Agregada...\n" << endl;
                }
            }
        }
    catch(List<House>::ListException ex) {
        cout << "Ocurrio un error" << endl;
        cout << "Error de sistema:" << ex.what() << endl;
        system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
        return;
        }
    }

void Menu::deleteElement() {
    //Inicializacion de variables a usar
    int pos, myInt;
    char myCharA, myCharB;
    House deleteHouse;
    List<House>::Position deletePoint;

    do {
        system("cls"); //Limpia toda la pantalla
        showListMenu();//Metodo de la interfaz para mostrar la tabla
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
                    myList->deleteAll();//Metodo de la lista para eliminar todos los elementos
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

                try {//Atrapara un error
                    if((deletePoint = myList->findDataLinear(deleteHouse)) != nullptr) {//Busqueda lineal para encontrar la posicion a eliminar
                        myList->deleteData(deletePoint);//Metodo de la para eliminar en una posicion de la lista
                        cout<<"\n\t\t\tDato eliminado... "<<endl;
                        }
                    else {
                        cout << "\nNo existe la Casa..." << endl;

                        }
                    break;

                    }
                catch(List<House>::ListException ex) {
                    cout << "Ocurrio un error" << endl;
                    cout << "Error de sistema:" << ex.what() << endl;
                    return;
                    }
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

void Menu::showListMenu() {//Metodo para imprimir el formato de la tabla y sus elementos
    system("cls"); //Limpia toda la pantalla

    string myStr;

    myStr += "POSICION | ";
    myStr += "Numero de la Casa";
    myStr.resize (36,' ');
    myStr += " | ";
    myStr += "Calle";
    myStr.resize (67,' ');
    myStr += " | ";
    myStr += "Colonia";
    myStr.resize (99,' ');
    myStr += " | ";
    cout<<myStr;//Imprimira el mensaje con el formato anterior

    cout<<endl<<myList->toString()<<endl<<endl;//Imprimira lo que nos regresara el metodo de la lista
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

                if((pointSearch = myList->findDataLinear(element)) != nullptr) {//Busqueda lineal de la lista
                    element = myList->retrieve(pointSearch);//Recuperacion del elemento en aquella posicion
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
Menu::Menu(List<House>& _list): myList(&_list) {}//Iniciara la lista de la interfaz con el constructor de la lista

///Metodo
void Menu::mainMenu() {
    char opc, opcContinue;//Inicializando variables

    myList->readFromDisk(fileTxt);//Metodo de la lista para leer desde el archivo

    do {
        showListMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
        displayMenu();//Metodo de la interfaz para mostrar las opciones de la interfaz
        cin>> opc;
        cin.sync();
        opc = toupper(opc);//Convertira las letras a mayusculas

        switch (opc) {
            case 'A'://Agregara elementos a la lista
                do {
                    showListMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
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
                showListMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
                if(!myList->isEmpty()) {//Si no esta vacia la lista podra hacer eliminaciones a la lista
                    deleteElement();//Metodo de la interfaz donde hara el proceso de eliminacion de elementos a la lista
                    }
                else {
                    cout<< "\nLISTA VACIA, debe ingresar los datos" <<endl;
                    system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
                    }
                break;

            case 'M':
                cout<<endl<<endl;
                showListMenu();//Metodo de la interfaz para mostrar la tabla de los elementos de la lista
                system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
                break;

            case 'B':
                findAnElement();//Metodo de la interfaz deonde hara el proceso de buscar y mostrar aquel elemento
                break;

            case 'S'://Terminara el programa, terminando la iteracion do-while
                cout << "\n\tFIN del programa" << endl;
                break;

            default:
                cout<< "ERROR, ingrese opcion valida" <<endl;
                system("\n\nPAUSE");// Pausara el programa hasta que se presione un enter
            }
        myList->writeToDisk(fileTxt);//Metodo de la lista para escribir en el archivo, para actualizarlo
        }
    while (opc!='S');
    }


