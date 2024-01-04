#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>
#include <fstream> //contiene tipos de procesamiento de flujos de archivos

#include <string> //libreria de las cadenas
#include <exception> //libreria para las excepciones

///Definicion de Lista
template <class T>//Implementacion de plantilla
class List {
    private:
        ///Definicion del Nodo
        class Node {//Es una clase anidad de la lista aprovechando la plantilla
            private:
                ///Atributos privados
                T data;
                Node* next;
            public:
                ///Constructores
                Node();
                Node(const T&);

                ///Setters y getters
                T getData()const;
                Node* getNext()const;

                void setData(const T&);
                void setNext(Node*);
            };

    public:
        typedef Node* Position;//Aunque el nodo sea pivado, el nodo sera publico a traves de Position y se inicializa
                                                //solo se le cambia el nombre
        ///Definicion de Excepcion
        class ListException : public std::exception {
            private:
                std::string msg;
            public:
                explicit ListException(const char* message): msg(message) {}
                explicit ListException(const std::string& message): msg(message) {}
                virtual ~ListException() throw() {}
                virtual const char* what() const throw () {
                    return msg.c_str();
                    }
            };

    private:
        Node* anchor;//Se abre esta area para aprovechar e incializar lo que tengo anteriormente

        ///Metodos privados de la lista
        bool isValidPos(Node*)const;
        void copyAll(const List<T>&);//Guardara el objeto creado a una copia

    public:
        ///Constructores
        List();
        List(const List<T>&);
        ~List(); ///Destructor

        ///Sobrecarga de operador
        List<T>& operator = (const List<T>&);//No es necesario el <T> porque para el compilador ya esta todo esta plantillado asi que ya no es necesario

        ///Metodos para una Lista
        bool isEmpty()const; //Revisa si esta vacia la lista
        std::string toString()const;//Pondra la lista en formato para nuestro uso

        void insertData(Position, const T&);//Insercion de elemento en alguna posicion
        void deleteData(Position);//Eliminacion de algun elemento en alguna posicion
        void deleteAll();//Elininara todos los elementos de la lista

        T retrieve(Position)const;//Recupera el elemento en alguna posicion

        Position getFirstPos()const;//Recupera la posicion del primero en la lista
        Position getLastPos()const;//Recupera la posicion del ultimo en la lista
        Position getPrevPos(Position)const;//Recupera el anterior de alguna posicion dada en la lista
        Position getNextPos(Position)const;//Recupera el siguiente de alguna posicion dada en la lista

        Position findDataLinear(const T&)const;////Recupera la posicion de la busqueda lineal de la lista

        void readFromDisk(const std::string&);//Metodo para leer desde un archivo
        void writeToDisk(const std::string&);//Metodo para escribir a un archivo
    };

///Implementacion.....
using namespace std;

///del Nodo
template <class T>
List<T>::Node::Node():next(nullptr) {}

template <class T>
List<T>::Node::Node(const T& e): next(nullptr), data(e) {}

template <class T>
T List<T>::Node::getData()const {
    return data;
    }

template <class T>
typename List<T>::Position List<T>::Node::getNext()const {
    return next;
    }

template <class T>
void List<T>::Node::setData(const T& e) {
    data = e;
    }

template <class T>
void List<T>::Node::setNext(Node* p) {
    next = p;
    }

///de la Lista
///Metodos privados
template <class T>
bool List<T>::isValidPos(Position p) const {//Validara si la direccion es valida para la lista
    Position aux(anchor);

    while (aux != nullptr) {//Recorrido de toda la lista
        if(aux == p) {//Si lo encuentra regresara un TRUE
            return true;
            }
        aux=aux->getNext();
        }
    return false;//Si no lo encuentra regresara un FALSE
    }

template <class T>
void List<T>::copyAll(const List<T>& l) {//Creara una lista copia a partir de la que tenemos
    Position aux(l.anchor);
    Position last(nullptr);
    Position newNode;

    while(aux != nullptr) {//Recorrido de la lista "Llena"
        newNode = new Node(aux->getData());

        if(newNode == nullptr) {//Verificacion de creacion del nodo
            throw ListException("Memoria no disponible, inserData");
            }
        //Religado de los apuntadores del nodo
        if(last == nullptr) {
            anchor = newNode;
            }
        else {
            last->setNext(newNode);
            }
        last = newNode;
        aux = aux->getNext();
        }
    }

///Constructores
template <class T>
List<T>::List(): anchor(nullptr) {}//Inicializara el ancla en nulo

template <class T>
List<T>::List(const List<T>& l):anchor(nullptr) { //Inicializara la lista copia en nulo para despues hacer la copia de la otra lista
    copyAll(l);
    }

template <class T>
List<T>::~List() {///Destructor
    deleteAll();//Eliminara todos los elementos de la lista
    }

///Sobre carga de operador
template <class T>
List<T>& List<T>::operator =(const List<T>&l) {//Limpirara toda la lista a asignar y luego copiara toda la lista actual a la nueva
    deleteAll();
    copyAll(l);
    return *this;
    }

///Metodos publicos de la Lista
template <class T>
bool List<T>::isEmpty() const {//Verifica si la ancla esta vacia
    return anchor == nullptr;
    }

template <class T>
std::string List<T>::toString() const {
    string myStr;
    char pos[10];
    Position aux(anchor);

    for(int i(0); aux != nullptr; i++) {//Iteracion donde imprimira toda la lista con su respectivo formato
        sprintf(pos, "%5i    | ", i);
        myStr +=  pos + aux->getData().toString() + "\n";
        aux = aux->getNext();
        }
    return myStr;//Regresando una cadena con todo el formato de una tabla
    }

template <class T>
void List<T>::insertData(Position p, const T& e) {

    if(p != nullptr and !isValidPos(p)) {//Verificara si la posicion recibida es diferente a nulo Y no es valida su posicion
        throw ListException("Posicion Invalida, insetData");
        }

    Position aux(new Node(e));
    if(aux == nullptr) {//Arrojara una excepcion si el nodo creado es nulo, porque ya no hay memoria
        throw ListException ("Memoria no disponible, inserData");
        }

    //Religado de nodos
    if(p == nullptr) { //Insertara al principio
        aux->setNext(anchor);
        anchor = aux;
        }
    else { //Insertar en cualquier posicion (despues del punto de interes)
        aux->setNext(p->getNext());
        p->setNext(aux);
        }
    }

template <class T>
void List<T>::deleteData(Position p) {
    if(!isValidPos(p)) {//Verificara si no es valida la posicion para lanzar una excepcion
        throw ListException ("Posicion invalida, deleteData");
        }
    //Se reasignara la posicion para "eliminar" los datos
    if(p == anchor) { //Eliminar el primero de la lista
        anchor = anchor->getNext();
        }
    else {//Eliminar cualquier otro elemento
        getPrevPos(p)->setNext(p->getNext());//Utilizando un metodo de la lista(getPrevPos) para encontrar su anterior posicion
        }

    delete p;//Eliminara el nodo recibido, para tener espacio en la memoria
    }

template <class T>
void List<T>::deleteAll() {
    Position aux;
    while(anchor != nullptr) {//Hara un recorrido a toda la lista para eliminar uno por uno
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
        }
    }

template <class T>
T List<T>::retrieve(Position p) const {
    if(!isValidPos(p)) {//Verificara la posicon recibida
        throw ListException ("Posicion invalida, retrieve");
        }
    return p->getData();//Regresara el dato del nodo
    }

template <class T>
typename List<T>::Position List<T>::getFirstPos() const {
    return anchor;//Regresara la posicion a partir del ancla
    }

template <class T>
typename List<T>::Position List<T>::getLastPos() const {
    if(isEmpty()) {//Verificara si esta vacia la lista
        return nullptr;
        }

    Position aux(anchor);
    while(aux->getNext() != nullptr) {//Hara un recorrido de la lista hasta el ultimo elemento
        aux=aux->getNext();
        }
    return aux;//Regresara la posicion del ultimo, mediante su recorrido
    }

template <class T>
typename List<T>::Position List<T>::getPrevPos(Position p) const {
    if(p == anchor) {//Verificara si la posicion recibida es igual al ancla
        return nullptr;//Regresara nulo
        }

    Position aux(anchor);
    while(aux != nullptr and aux->getNext() != p ) {//Recorrido de la lista hasta encontrar la posicion recibida,
        aux=aux->getNext();                         //antes de que acabe la lista Y sea diferente a la posicion siguiente a buscar
        }
    return aux;//Regresara la ultima posicion guardara
    }

template <class T>
typename List<T>::Position List<T>::getNextPos(Position p) const {
    if(!isValidPos(p)) {//Verificara si no es valida la posicion recibida
        return nullptr;
        }
    return p->getNext();//Regresara la posicion siguiente de la posicion recibida
    }

template <class T>
typename List<T>::Position List<T>::findDataLinear(const T& e) const {
    Position aux(anchor);

    while(aux!=nullptr and aux->getData()!= e) {//Recorrido de la lista hasta encontrar la posicion recibida
        aux=aux->getNext();
        }
    return aux;//Regresara la ultima posicion guardara
    }

template <class T>
void List<T>::readFromDisk(const string& fileName) {
    ifstream myFile;//Constructor de ifstream abre el archivo

    myFile.open(fileName, ios_base::in);//Se abre el archivo y se configura de modo entrada

    if(!myFile.is_open()) {//Verifica que se haya abierto bien el archivo
        throw ListException ("No se pudo abrir el archivo (Lectura, readFromDisk)");
        }

    T myData;//Inicializacion de la variable con plantilla
    //Se uso un sobrecarga de operados de flujo de la clase plantilla
    while(myFile >> myData) {//Recorrera el archivo "handle" hasta que no encuentre nada o al final del archivo "handle"
        insertData(getLastPos(),myData);//Insertara los elementos del archivo "handle" hasta la ultima posicion de la lista
        }
    myFile.close();//Cierra el archivo "handle" para evitar futuras fallas

    cout<<"\t\t\t\tLeyendo del disco..."<<endl;
    system("Pause");//Pausara el programa hasta que se le de un enter
    }

template <class T>
void List<T>::writeToDisk(const string& fileName) {
    ofstream myFile;//Constructor de ofstream abre el archivo

    //Se abre el archivo y se configura de modo trunc
    myFile.open(fileName, ios_base::trunc);//ios_base::trunc  -> Cualquier contenido actual se descarta, asumiendo una longitud de cero al abrir.

    if(!myFile.is_open()) {//Verifica que se haya abierto bien el archivo
        throw ListException ("No se pudo abrir el archivo (Escritura, writeToDisk)");
        }

    T myData;//Inicializacion de las variables
    Position aux(anchor);

    while(aux!=nullptr) {//Recorrimiento de toda la lista para la obtencion de los datos, uno por uno
        myData = aux->getData();
        aux = aux->getNext();

        myFile << myData;//Se uso una sobrecarga de operados de flujo de la clase plantilla, para su escritura al archivo "handle"
        }
    myFile.close();//Cierra el archivo "handle" para evitar futuras fallas

    cout<<"\t\t\t\tEscribiendo al disco..."<<endl;
    system("PAUSE");//Pausara el programa hasta que se le de un enter
    }

#endif // LIST_H_INCLUDED
