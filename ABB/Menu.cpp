#include "Menu.h"
string fileTxt = "file01.txt";

using namespace std;

///Metodo privado
void Menu::displayMenu() {//Imprimira como mensaje el menu de acciones que podra hacer el arbol
    cout<< "\t\t MENU " <<endl;
    cout<< "\t[A]gregar elemento: " <<endl;
    cout<< "\t[E]liminar elemento: " <<endl;
    cout<< "\t[B]uscar elemento: " <<endl;
    cout<< "\t[M]ostrar Arbol" <<endl;
    cout<< "\t[S]alir " <<endl;
    cout<< "\tSelecciona una opcion (A,E,M,B,S):  ";
}

void Menu::insertElement() {//Metodo de la interfaz para insertar los datos al arbol
    system("cls"); //Limpia toda la pantalla

    //Inicializacion de variables a usar
    string myStr;
    int myInt;
    char myChar;

    House newHouse;//Incicializacion de dato House
    BTree<House>::Position insertPoint = nullptr;//Direccion de memoria de tipo Nodo para insercion

    cout << "\n\t\t Agregue Casa" << endl;

    ///Creacion de los datos de la Casa, insertando primero a la clase House y luego al Arbol
    cout << "Ingrese el NUMERO de la Casa: ";
    cin>>myInt;
    cin.ignore();
    newHouse.setNumber(myInt);

    cout << "\nIngrese la CALLE: ";
    cin.sync();
    getline(cin, myStr);
    newHouse.setStreet(myStr);

    cout << "\nIngrese la COLONIA que pertenece: ";
    getline(cin, myStr);
    newHouse.setColony(myStr);

    try {//Atrapara alguna excepcion en la insercion
        myBTree->insertData(newHouse);//Insertando en el arbol

    } catch(BTree<House>::Exception ex) {
        cout << "Ocurrio un error" << endl;
        cout << "Error de sistema:" << ex.what() << endl;
        system("PAUSE");// Pausara el programa hasta que se presione un enter
    }
    cout<<endl;
}

void Menu::deleteElement() {//Metodo de la interfaz para eliminar datos del arbol
    //Inicializacion de variables a usar
    int myInt;
    char myCharA, myCharB;
    House deleteHouse;//Incicializacion de dato House
    BTree<House>::Position deletePoint = nullptr;//Direccion de memoria de tipo Nodo para insercion

    do {
        showInfo();//Metodo de la interfaz para mostrar la tabla completa con recorrido PreOrder
        cout<< "Eliminar todos: [T]odos / [S]olo uno / [R]egresar al Menu:      ";
        cin>>myCharA;
        cin.sync();
        myCharA = toupper(myCharA);//Convierte las letras a mayusculas

        try {//Atrapara alguna excepcion del arbol

            switch (myCharA) {
            case 'T'://Borrara todos los elementos de la lista
                cout<< "Confirmacion: [S]i / [N]o: ";
                cin>>myCharB;
                cin.sync();
                myCharB = toupper(myCharB);//Convierte las letras a mayusculas

                cout<<"\n\t";
                if(myCharB == 'S') {//Confirmacion de eliminacion total
                    myBTree->deleteAll();//Metodo del arbol para eliminar todos sus elementos
                    cout<< "\tElementos Eliminados.... "<<endl;

                } else {
                    cout<< "\tElementos NO eliminados.... "<<endl;
                }
                system("PAUSE");// Pausara el programa hasta que se presione un enter
                break;

            case 'S':
                cout<< "Ingrese el NUMERO de Casa a eliminar: ";
                cin>>myInt;
                cin.ignore();

                deleteHouse.setNumber(myInt);//Asignacion de la House para su busqueda

                cout<<endl;
                //Si existe algo en la posicion del arbol ejecutara el IF
                if(myBTree->findData(deleteHouse)) { //Verificara que el elemento se encuentre en el arbol

                    myBTree->deleteData(deleteHouse);//Metodo del arbol para eliminar el elemento deseado
                    cout<<"\tElemento eliminado"<<endl;

                } else {
                    cout<<"\tElemento NO encontrado"<<endl;
                }
                system("PAUSE");// Pausara el programa hasta que se presione un enter
                break;

            case 'R'://Regresara al metodo principal de la interfaz, terminando la iteracion do-while
                cout<<endl;
                break;

            default:
                cout<<endl<<"\tERROR, Ingrese opcion valida"<<endl;
                system("PAUSE");// Pausara el programa hasta que se presione un enter
            }

        } catch(BTree<House>::Exception ex) {
            cout << "Ocurrio un error" << endl;
            cout << "Error de sistema:" << ex.what() << endl;
            system("PAUSE");// Pausara el programa hasta que se presione un enter
            return;
        }
    } while(myCharA != 'R');//Hasta que sea R saldra de este mini menu de eliminacion
}

void Menu::findElement(){//Metodo de la interfaz para buscar un elemento del arbol
    char myCharA;//Inicializacion de variables a usar
    int myInt;

    House element;//Incicializacion de dato House
    BTree<House>::Position pointSearch = nullptr;//Direccion de memoria de tipo Nodo para insercion
    do {
        system("cls");
        cout<<"Buscar por numero de la [C]asa / [R]egresar al menu:  ";
        cin>> myCharA;
        cin.sync();
        myCharA = toupper(myCharA);

        switch (myCharA) {
            case 'C':///Busqueda por numero de casa
                cout<<endl<<"Ingrese el NUMERO de la Casa a buscar: ";
                cin>>myInt;
                element.setNumber(myInt);

                if((pointSearch = myBTree->findData(element)) != nullptr) {
                    element = pointSearch->getData();
                    cout<<endl<<"\tLa Casa esta en la CALLE: "<<element.getStreet();
                    cout<<"    ------->   En la COLONIA: "<<element.getColony()<<endl<<endl;
                    }
                else {
                    cout<<endl<< "\tElemento NO encontrado"<<endl;
                    }
                    system("PAUSE");
                break;

            case 'R':
                break;

            default:
                cout<<endl<<"\tERROR, Ingrese opcion valida"<<endl;
                system("PAUSE");
            }
        }
    while(myCharA != 'R');
}
void Menu::showParseOrder() {//Metodo para mostrar todos los datos del arbol segun el recorrido deseado
    //Inicialicacion de variables a usar
    char opc;
    string myStr;

    do {
        system("cls");//Limpia toda la pantalla
        cout<< "Seleccione forma de recorrido del Arbol:"<<endl
            <<"\t[1] PreOrder\n\t[2] InOrder\n\t[3] PostOrder\n\t[4] Regresar al Menu: ";
        cin>>opc;
        cin.ignore();

        /*Aceptara valores de tipo caracter, incluso numeros, pero usaremos la tabla ascii para determinar
        el rango de los numeros deseados y excluir letras u otros no deseada*/

        if(opc>48 and opc<52) {//48 es '0' y 52 es '4' en la tabla ascii
            cout << endl;
            myStr += " Numero de la Casa";
            myStr.resize (18,' ');
            myStr += " | ";
            myStr += "Calle";
            myStr.resize (48,' ');
            myStr += " | ";
            myStr += "Colonia";
            myStr.resize (80,' ');
            myStr += " | \n";
            cout<<myStr;//Imprimira la cabecera de la tabla con el formato anterior

            switch (opc) {
            case '1':
                myBTree->parsePreOrder();//Metodo para imprimir el arbol con recorrido pre-order
                cout<<endl<<endl<<"\t";
                system("PAUSE");// Pausara el programa hasta que se presione un enter
                cout<<endl;
                break;

            case '2':
                myBTree->parseInOrder();//Metodo para imprimir el arbol con recorrido in-order
                cout<<endl<<endl<<"\t";
                system("PAUSE");// Pausara el programa hasta que se presione un enter
                cout<<endl;
                break;

            case '3':
                myBTree->parsePostOrder();//Metodo para imprimir el arbol con recorrido post-order
                cout<<endl<<endl<<"\t";
                system("PAUSE");// Pausara el programa hasta que se presione un enter
                cout<<endl;
                break;

            default:
                cout<<endl<<"ERROR, Ingrese opcion valida    "<<endl<<endl;
            }
        }
        if(opc>52) { //Valores de la tabla ascii mayores del '4'
            cout<<endl<<"\tERROR, Ingrese opcion valida"<<endl<<endl;
        }
    } while(opc != '4');
}

void Menu::showInfo() {//Metodo de la interfaz para SOLO conocer los elementos dentro del arbol
    system("cls");//Limpia toda la pantalla

    string myStr;//Inicializacion para la impresion de la cabecera de la tabla
    myStr += " Numero de la Casa";
    myStr.resize (18,' ');
    myStr += " | ";
    myStr += "Calle";
    myStr.resize (48,' ');
    myStr += " | ";
    myStr += "Colonia";
    myStr.resize (80,' ');
    myStr += " | \n";
    cout<<myStr;//Imprimira el mensaje con el formato anterior

    myBTree->parsePreOrder();//Metodo para imprimir el arbol con recorrido pre-order

    cout<<endl;
}

///Constructor
Menu::Menu(BTree<House>& _BTree): myBTree(&_BTree) {}//Inicializando el apuntador de tipo arbol de la interfaz con el arbol recibido

///Metodo publico
void Menu::mainMenu() {//Metodo principal de la interfaz
    char opc, opcContinue;//Inicializacion de variables para la intefaz principal

    myBTree->readFromDisk(fileTxt);//Metodo del arbol para leer desde el archivo

    do {
        showInfo();//Metodo de la interfaz para SOLO conocer los elementos dentro del arbol
        displayMenu();//Metodo de la interfaz que imprimira como mensaje el menu de acciones que podra hacer el arbol
        cin>> opc;
        cin.sync();
        opc = toupper(opc);//Convierte las letras a mayusculas

        switch (opc) {
        case 'A':
            do {//Estara insertando las veces que quiera el usuario hasta que el lo cancele
                displayMenu();//Metodo de la interfaz que imprimira como mensaje el menu de acciones que podra hacer el arbol
                insertElement();//Metodo de la interfaz para insertar los datos al arbol

                cout<< "Ingresar otro dato [S]/[N]: ";
                cin>> opcContinue;
                opcContinue = toupper(opcContinue);//Convierte las letras a mayusculas

            } while(opcContinue != 'N');
            myBTree->writeToDisk(fileTxt);//Escribira en el archivo para que este siempre actualizado
            break;

        case 'E':
            if(!myBTree->isEmpty()) {//Si no esta vacio el arbol, podra borrar datos del arbol
                deleteElement();//Metodo de la interfaz para eliminar datos del arbol
            } else {
                cout << endl << "\tLISTA VACIA, debe ingresar los datos" <<endl;
                system("PAUSE");// Pausara el programa hasta que se presione un enter
            }
            myBTree->writeToDisk(fileTxt);//Escribira en el archivo para que este siempre actualizado
            break;

        case 'B':
            findElement();//Metodo de la interfaz para buscar un elemento del arbol
            break;

        case 'M':
            showParseOrder();//Metodo para mostrar todos los datos del arbol segun el recorrido deseado
            break;

        case 'S'://Opcion para terminar la iteracion del menu y terminar la interfaz
            cout << endl << "\n\tFIN del programa" << endl;
            break;

        default:
            cout << endl << "\tERROR, ingrese opcion valida" <<endl;
            system("PAUSE");// Pausara el programa hasta que se presione un enter
        }
    } while (opc!='S');
}
