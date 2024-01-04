#include "Menu.h"

//Direcciones de los archivos de vertices y aristas
string fileVertex = "file01.txt";
string fileEdge = "file02.txt";

using namespace std;

///Metodo privado
void Menu::displayMenu() {//Imprimira como mensaje el menu de acciones que podra hacer el grafo
    cout<< "\t\t MENU " <<endl;
    cout<< "\t[A]gregar " <<endl;
    cout<< "\t[E]liminar " <<endl;
    cout<< "\t[B]uscar " <<endl;
    cout<< "\t[M]ostrar" <<endl;
    cout<< "\t[S]alir " <<endl;
    cout<< "\tSelecciona una opcion (A,E,M,B,S):  ";
}

void Menu::insertElement() {//Metodo de la interfaz para insertar los datos al grafo
    system("cls"); //Limpia toda la pantalla

    //Inicializacion de variables a usar
    string myStr;
    int myInt;
    char myChar;

    House newHouse, destHouse;//Incicializacion de dato House
    Integer theInt; //Inicializacion del dato entero

    do {//Mini interfaz para la insercion de los datos del grafo
        system("cls");
        cout<< "Agregar [V]ertice (Agregue Casa) / [A]rista (Agregue distancia con..) / [R]egresar al Menu:      ";
        cin>>myChar;
        cin.sync();
        myChar = toupper(myChar);//Convierte las letras a mayusculas

        switch (myChar) {
        case 'V':///Insertar vertice
            cout << "\n\t\t Agregue Casa (Vertice)" << endl;

            ///Creacion de los datos de la Casa, insertando primero a la clase House y luego al grafo
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

            myGraph->insertVertex(newHouse);//Insertando vertice en el grafo
            system("pause");
            break;

        case 'A':///Insertar Arista

            cout << "\n\t\t Agregue su direccion (Arista)" << endl;
            cout<<endl<<"Ingrese el NUMERO de la Casa Inicial: ";
            cin>>myInt;
            newHouse.setNumber(myInt);//Obtencion de dato de casa origen

            cout<<endl<<"Ingrese el NUMERO de la Casa a conectar: ";
            cin>>myInt;
            destHouse.setNumber(myInt);//Obtencion de dato de casa destino

            cout<<endl<<"Ingrese la distacia en KM de la ruta: ";
            cin>>myInt;
            theInt.setInteger(myInt);//Obtencion de dato del peso de la arista

            myGraph->insertEdge(newHouse,destHouse,theInt);//Insertando arista en el grafo

            system("pause");
            break;

        case 'R':
            cout<<endl;
            break;

        default:
            cout<<endl<<"\tERROR, Ingrese opcion valida"<<endl;
            system("PAUSE");// Pausara el programa hasta que se presione un enter
        }
    } while(myChar != 'R');

    cout<<endl;
}

void Menu::deleteElement() {//Metodo de la interfaz para eliminar datos del grafo
    //Inicializacion de variables a usar
    int myInt;
    char myCharA, myCharB;
    House deleteHouseO, deleteHouseD;//Incicializacion de dato House

    do {// Mini interfaz para la eliminacion
        system("cls");
        showInfo();//Metodo de la interfaz para mostrar la tabla completa con recorrido PreOrder
        cout<< "\n\nEliminar [V]ertice / [A]rista de vertice a vertice / [R]egresar al Menu:      ";
        cin>>myCharA;
        cin.sync();
        myCharA = toupper(myCharA);//Convierte las letras a mayusculas

        switch (myCharA) {
        case 'V':///Elimina Vertice
            cout<< "\n\t[T]odo / [S]olo vertice :    ";
            cin>>myCharB;
            cin.sync();
            myCharB = toupper(myCharB);//Convierte las letras a mayusculas

            cout<<"\n\t";
            if(myCharB == 'T') {//Eliminar todos los vertices
                cout<<"\tConfirmacion [S]i / [N]o: ";

                cin>>myCharA;
                cin.sync();
                myCharA = toupper(myCharA);//Convierte las letras a mayusculas

                if(myCharA == 'S') {
                    myGraph->deleteAllVertex();//Metodo del grafo para eliminar todos sus elementos
                    cout<< "\tVertices Eliminados.....\n"<<endl;

                } else {
                    cout<< "\tVertices NO eliminados.....\n"<<endl;
                }
            } else if (myCharB== 'S') {//Eliminar solo un vertice
                cout<< "Ingrese el NUMERO de Casa Origen(Vertice) a eliminar: ";
                cin>>myInt;
                cin.ignore();

                deleteHouseO.setNumber(myInt);//Asignacion de la House para su busqueda

                cout<<endl;
                //Si existe algo en la posicion del grafo ejecutara el IF
                if(myGraph->findVertex(deleteHouseO)) { //Verificara que el elemento se encuentre en el grafo

                    myGraph->deleteVertex(deleteHouseO);//Metodo del grafo para eliminar el elemento deseado
                    cout<<"\tVertice eliminado.....\n"<<endl;

                } else {
                    cout<<"\tVertice NO encontrado.....\n"<<endl;
                }
            }
            system("PAUSE");// Pausara el programa hasta que se presione un enter
            break;

        case 'A':///Elimine Arista
            cout<< "\nIngrese el NUMERO de Casa Origen: ";
            cin>>myInt;
            cin.ignore();
            deleteHouseO.setNumber(myInt);//Asignacion de la House para su busqueda
            if(myGraph->findVertex(deleteHouseO)) { //Verificacion de la casa origen
                cout<< "\t[T]odo / [S]olo arista:    ";
                cin>>myCharB;
                cin.sync();
                myCharB = toupper(myCharB);//Convierte las letras a mayusculas

                cout<<"\n";
                if(myCharB == 'T') {//Eliminacion de todas las aristas del vertice origen
                    cout<<"Confirmacion [S]i / [N]o: ";
                    cin>>myCharA;
                    cin.sync();
                    myCharA = toupper(myCharA);//Convierte las letras a mayusculas

                    if(myCharA == 'S') {
                        if(myGraph->findVertex(deleteHouseO)) {//Verificacion de la casa origen
                            myGraph->deleteAllEdge(myGraph->findVertex(deleteHouseO));//Metodo del grafo para eliminar todos sus aristas
                            cout<< "\tAristas Eliminados.... \n"<<endl;

                        } else {
                            cout<< "\tAristas NO eliminados.... \n"<<endl;
                        }
                    }
                } else if (myCharB == 'S') {//Eliminacion de solo una arista
                    cout<< "Ingrese el NUMERO de Casa Destino: ";
                    cin>>myInt;
                    cin.ignore();
                    deleteHouseD.setNumber(myInt);//Asignacion de la House para su busqueda
                    cout<<endl;
                    if(myGraph->findVertex(deleteHouseD)) { //Verificacion de la casa destino
                        //Si existe algo en la posicion del grafo ejecutara el IF
                        if(myGraph->findEdge(deleteHouseO, deleteHouseD) != nullptr) { //Verificara que el elemento se encuentre en el grafo
                            myGraph->deleteEdge(deleteHouseO,deleteHouseD);//Metodo del grafo para eliminar el elemento deseado
                            cout<<"\n\tArista eliminado.....\n"<<endl;

                        } else {
                            cout<<"\tArista NO encontrado.....\n"<<endl;
                        }
                    } else {
                        cout<<"\tVertice destino NO encontrado.....\n"<<endl;
                    }
                }
            } else {
                cout<< "\tVertice origen NO encontrado.... \n"<<endl;
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
    } while(myCharA != 'R');//Hasta que sea R saldra de este mini menu de eliminacion
}


void Menu::findElement() { //Metodo de la interfaz para buscar un elemento del grafo
    char myCharA;//Inicializacion de variables a usar
    int myInt;

    House elementO, elementD;//Incicializacion de dato House
    Graph<House,Integer>::VertPos PosO = nullptr;
    Graph<House,Integer>::VertPos PosD = nullptr;
    Graph<House,Integer>::EdgePos PosEdge = nullptr;
    do {
        system("cls");//Limpia toda la pantalla
        cout<<"Buscar por numero de la [C]asa / [D]ireccion de ruta / [R]egresar al menu:  ";
        cin>> myCharA;
        myCharA = toupper(myCharA);//Convierte las letras a mayusculas

        switch (myCharA) {
        case 'C':///Busqueda por numero de casa (vertice)
            cout<<endl<<"Ingrese el NUMERO de la Casa Origen a buscar: ";
            cin>>myInt;
            elementO.setNumber(myInt);

            if((PosO = myGraph->findVertex(elementO)) != nullptr) {
                elementO = myGraph->retriveVertex(PosO);
                //Imprimira los datos de nuestro elemento, desglosado
                cout<<endl<<"\tLa Casa esta en la CALLE: "<<elementO.getStreet();
                cout<<" --->  En la COLONIA: "<<elementO.getColony()<<endl<<endl;

                cout << "Estan relacionado con: "<<endl<<endl;
                myGraph->getListEdge(PosO);
                cout<<endl;

            } else {
                cout<<endl<< "\tElemento NO encontrado"<<endl;
            }
            system("PAUSE");
            break;
        case 'D':///Busqueda por numero de casa para obtener su arista
            cout<<endl<<"Ingrese el NUMERO de la Casa Origen a buscar: ";
            cin>>myInt;
            elementO.setNumber(myInt);
            if((PosO = myGraph->findVertex(elementO))!=nullptr) { //Verificacion del vertice de origen de que exista

                cout<<endl<<"Ingrese el NUMERO de la Casa Destino a buscar: ";
                cin>>myInt;
                elementD.setNumber(myInt);
                if((PosD = myGraph->findVertex(elementD))!=nullptr) {//Verificacion del vertice de destino de que exista
                    if((PosEdge = myGraph->findEdge(elementO,elementD)) != nullptr) {//Verificacion de la arista entre vertice origen y destino de que exista
                        elementO = myGraph->retriveVertex(PosO);
                        //Imprimira los datos de nuestra casa origen, desglosado
                        cout<<endl<<"\tLa Casa Origen esta en la CALLE: "<<elementO.getStreet();
                        cout<<" --->  En la COLONIA: "<<elementO.getColony()<<endl;

                        //Imprimira los datos de nuestra casa destino con su peso, desglosado
                        elementD = myGraph->retriveVertex(PosD);
                        cout << "\n\tTiene una DISTANCIA de: "<< myGraph->retriveEdge(PosEdge).toString() << " KM " <<
                             " Con la Casa Destino en la CALLE: " << elementD.getStreet()
                             <<" --->  En la COLONIA: "<<elementD.getColony()<<endl<<endl;
                    } else {
                        cout<<endl<< "\tElementos NO relacionados"<<endl;
                    }
                } else {
                    cout<<endl<< "\tElemento destino NO encontrado"<<endl;
                }
            } else {
                cout<<endl<< "\tElemento origen NO encontrado"<<endl;
            }
            system("PAUSE");
            break;

        case 'R'://Rompera la iteracion del mini interfaz de la busqueda
            break;

        default:
            cout<<endl<<"\tERROR, Ingrese opcion valida"<<endl;
            system("PAUSE");
        }
        cin.sync();
    } while(myCharA != 'R');
}

void Menu::showInfo() {//Metodo de la interfaz para SOLO conocer los elementos dentro del grafo
    system("cls");//Limpia toda la pantalla

    string myStr;//Inicializacion para la impresion de la cabecera de la tabla
    myStr += " NUMERO_DE_CASA ";
    myStr.resize (15,' ');
    myStr += " | ";
    myStr += "CALLE";
    myStr.resize (33,' ');
    myStr += " | ";
    myStr += "COLONIA";
    myStr.resize (50,' ');
    myStr += " | ";

    cout<<"\t\tCASA ORIGEN\t\t\t\t\t\tCASAS DESTINO\n" << myStr
        << "   (DIST(KM) | NUMERO_DE_CASA | CALLE | COLONIA)" << endl;//Imprimira el mensaje con el formato anterior

    cout << myGraph->toString();//Metodo del grafo para poner en formato todo el grafo

    cout<<endl;
}

///Constructor
Menu::Menu(Graph<House,Integer>& _Graph): myGraph(&_Graph) {}//Inicializando el apuntador de tipo grafo de la interfaz con el grafo recibido

///Metodo publico
void Menu::mainMenu() {//Metodo principal de la interfaz
    char opc;//Inicializacion de variable para la intefaz principal

    myGraph->readFromDisk(fileVertex, fileEdge);//Metodo del grafo para leer desde el archivo

    do {
        showInfo();//Metodo de la interfaz para SOLO conocer los elementos dentro del grafo
        displayMenu();//Metodo de la interfaz que imprimira como mensaje el menu de acciones que podra hacer el grafo
        cin>> opc;
        cin.sync();
        opc = toupper(opc);//Convierte las letras a mayusculas

        switch (opc) {
        case 'A':
            displayMenu();//Metodo de la interfaz que imprimira como mensaje el menu de acciones
            insertElement();//Metodo de la interfaz para insertar los datos

            myGraph->writeToDisk(fileVertex, fileEdge);//Escribira en el archivo para que este siempre actualizado
            break;

        case 'E':
            if(!myGraph->isEmpty()) {//Si no esta vacio el grafo, podra borrar datos
                deleteElement();//Metodo de la interfaz para eliminar datos
                myGraph->writeToDisk(fileVertex, fileEdge);//Escribira en el archivo para que este siempre actualizado
            } else {
                cout << endl << "\tGRAFO VACIO, debe ingresar los datos" <<endl;
                system("PAUSE");// Pausara el programa hasta que se presione un enter
            }
            break;

        case 'B':
            findElement();//Metodo de la interfaz para buscar un elemento del grafo
            break;

        case 'M':
            showInfo();//Metodo de la interfaz para mostrar todo el grafo
            system("pause");
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
