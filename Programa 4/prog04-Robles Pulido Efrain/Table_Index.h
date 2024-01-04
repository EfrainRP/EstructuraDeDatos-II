#ifndef TABLE_INDEX_H_INCLUDED
#define TABLE_INDEX_H_INCLUDED

#include "List.h"

template <class T, int ARRAYSIZE>//Implementacion de plantilla
class Table {///Definicion de la tabla
private:
    ///Atributos Privado de la tabla
    List<T> ind[ARRAYSIZE];
    int cant;

    bool isValidPos(const int&);//Validacion de posicion del arreglo
    int doHash(const int&);//Obtencion del valor hash

public:
    //Constructores
    Table();
    Table(const Table<T,ARRAYSIZE>&);

    //Metodos publicos de Indice
    bool isEmpty(void);//Verificacion de arreglo vacio
    bool isFull(void);//Verificacion de que este lleno el arreglo
    void insertData(const T&);//Metodo para la insercion

    void deleteAllData(void);//Metodo para vaciar la tabla de indice
    void deleteData(const T&);//Metodo para eliminar un dato
    typename List<T>::Position findData(const T&);//Metodo para obtener la posicion de la lista del arreglo

    std::string toString(void);//Metodo para obtener los datos de la tabla en una cadena
    void readFromDisk(const std::string&);//Metodo para leer desde un archivo
    //void writeToDisk(const std::string&, T&);//Metodo para escribir a un archivo
    void writeToDisk(const std::string&);//Metodo para escribir el archivo
};

///Implementacion de......
using namespace std;

///Tabla de Indice
//Constructor
template <class T, int ARRAYSIZE>
Table<T, ARRAYSIZE>::Table(): cant(-1) {}//Inicia la tabla como "vacia"

template <class T, int ARRAYSIZE>
Table<T, ARRAYSIZE>::Table(const Table<T,ARRAYSIZE>& t) {//Pasa el arreglo de indice a otro
    this->ind = t.ind;
}

//Metodos privados
template <class T, int ARRAYSIZE>
bool Table<T, ARRAYSIZE>::isValidPos(const int& p) {//Validacion del indice del arreglo
    return p >= 0 && p <= ARRAYSIZE;
}

template <class T, int ARRAYSIZE>
int Table<T, ARRAYSIZE>::doHash(const int& key) {//Metodo para obtener el valor hash para el indice
    return key % ARRAYSIZE;
}

//Metodos publicos
template <class T, int ARRAYSIZE>
bool Table<T, ARRAYSIZE>::isEmpty(void) {//Vefificion del arreglo este vacio
    return cant == -1;
}

template <class T, int ARRAYSIZE>
bool Table<T, ARRAYSIZE>::isFull(void) {//Verificacion del arreglo este lleno
    return cant >= ARRAYSIZE;
}

template <class T, int ARRAYSIZE>
void Table<T, ARRAYSIZE>::insertData(const T& data) {//Insercion del dato a la tabla de indices
    if(isFull()) {//Verificaciones del arreglo
        cout<<"Tabla llena, insertData"<<endl;
        return;
    }
    int key = doHash(data.getNumber());//Obtencion del valor hash para insertar

    if(!isValidPos(key)) {//Validacion de la posicion del valor hash
        cout << "\t\t\tCasa NO Agregado...\n" << endl;
        return;
    }
    if (findData(data)==nullptr){//Verificacion de dato repetido
        ind[key].insertData(ind[key].getLastPos(),data);//Insertara al final de la lista
        cant++;
        cout << "\t\t\tCasa Agregado...\n" << endl;
    }else{
        cout << "\t\t\tCasa Repetida...\n" << endl;
    }
}

template <class T, int ARRAYSIZE>
void Table<T, ARRAYSIZE>::deleteAllData(void) {//Eliminacion del dato de la tabla de indices
    int i(0);
    while (i < ARRAYSIZE) {
        ind[i].deleteAll();//Eliminara el dato de la lista
        i++;
    }
    cant=-1;
}

template <class T, int ARRAYSIZE>
void Table<T, ARRAYSIZE>::deleteData(const T& data) {//Eliminacion del dato de la tabla de indices
    int key = doHash(data.getNumber());
    if(!isValidPos(key)) {
        cout<<"Posicion Invalida, deleteData"<<endl;
        return;
    }
    typename List<T>::Position pos(nullptr);
    if(pos = ind[key].findDataLinear(data)){
        ind[key].deleteData(pos);//Eliminara el dato de la lista
        cant--;
        cout<<"\n\t\tDato eliminado"<<endl;
    }else{
        cout<<"\n\t\tDato NO existe"<<endl;
    }
}

template <class T, int ARRAYSIZE>
typename List<T>::Position Table<T, ARRAYSIZE>::findData(const T& data) { //Buscara el dato en las listas enlazadas
    int key = doHash(data.getNumber());
    if(!isValidPos(key)) {
        cout<<"Posicion Invalida, findData"<<endl;
        return nullptr;
    }
    return ind[key].findDataLinear(data);//Regresara la posicion en el arreglo de la tabla de indice
}

template <class T, int ARRAYSIZE>
string Table<T, ARRAYSIZE>::toString(void) {//Metodo que nos regresara como cadena todo el valor de la tabla
    string myStr;
    int i(0);
    char pos[9];

    if(isEmpty()) {
        myStr = "----------------EMPTY LIST----------------";
    } else {
        while(i < ARRAYSIZE) {
            if(!ind[i].isEmpty()){
                    sprintf(pos,"   %2d   ",i);
                myStr += pos + ind[i].toString() + "\n";
            }
            i++;
        }
    }
    return myStr;
}

template <class T, int ARRAYSIZE>
void Table<T, ARRAYSIZE>::readFromDisk(const string& fileName) {//Metodo para leer desde un archivo
    ifstream myFile;//Constructor de ifstream abre el archivo

    myFile.open(fileName, ios_base::in | ios_base::binary);//Se abre el archivo y se configura de modo entrada

    if(!myFile.is_open()) {//Verifica que se haya abierto bien el archivo
        cout<<"No se pudo abrir el archivo (Lectura, readFromDisk)";
        return;
    }

    T myData;//Inicializacion de la variable con plantilla

    //Se uso un sobrecarga de operados de flujo de la clase plantilla
    while(myFile >> myData) {//Recorrera el archivo "handle" hasta que no encuentre nada o al final del archivo "handle"
        insertData(myData);//Insertara los elementos del archivo "handle" hasta la ultima posicion de la lista
        }
    myFile.close();//Cierra el archivo "handle" para evitar futuras fallas

    cout<<"\t\t\t\tLeyendo del disco..."<<endl;
    system("Pause");//Pausara el programa hasta que se le de un enter
}

template <class T, int ARRAYSIZE>
void Table<T, ARRAYSIZE>::writeToDisk(const string& fileName) {//Metodo para escribir desde un archivo
    ofstream myFile;//Constructor de ofstream abre el archivo

    //Se abre el archivo y se configura de modo trunc
    myFile.open(fileName, ios_base::out | ios_base::binary | ios_base::trunc);//ios_base::trunc  -> Cualquier contenido actual se descarta, asumiendo una longitud de cero al abrir.

    if(!myFile.is_open()) {//Verifica que se haya abierto bien el archivo
        cout<<"No se pudo abrir el archivo (updateToDisk)";
        return;
        }

    string str;//Inicializacion de las variables
    int i(0);

    while(i<ARRAYSIZE) {//Recorrimiento de toda la lista para la obtencion de los datos, uno por uno
        str += ind[i].getAllList(ind[i].getFirstPos());//Obtendremos como cadena todo los valores de cada lista del arreglo
        i++;
        }
        myFile << str;//Se uso una sobrecarga de operados de flujo de la clase plantilla, para su escritura al archivo "handle"
    myFile.close();//Cierra el archivo "handle" para evitar futuras fallas

    cout<<"\t\t\t\tEscribiendo al disco..."<<endl;
    system("PAUSE");//Pausara el programa hasta que se le de un enter
}

#endif // TABLE_INDEX_H_INCLUDED
