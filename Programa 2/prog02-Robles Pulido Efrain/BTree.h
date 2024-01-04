#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <windows.h>

///Definicion del Arbol
template <class T>
class BTree {
private:
    ///Definicion del Nodo
    class Node {
    private:///Atributos privados del Nodo
        T* dataPtr;//Se usa el dato plantilla como apuntador para que sea mas eficaz el administrar los datos
        Node* left;
        Node* right;

    public:
        ///Definicion de la clase Excepcion para el Nodo
        class Exception : public std::exception {
        private:
            std::string msg;
        public:
            explicit Exception(const char* message): msg(message) {}
            explicit Exception(const std::string& message): msg(message) {}
            virtual ~Exception() throw() {}
            virtual const char* what() const throw () {
                return msg.c_str();
            }
        };

        ///Constructores del Nodo
        Node();
        Node(const T&);

        ~Node();    ///Destructor del Nodo

        ///Metodos publicos del Nodo (Getters y Setters)
        T* getDataPtr()const;
        T getData()const;
        Node*& getLeft();
        Node*& getRight();

        void setDataPtr(T*);
        void setData(const T&);
        void setLeft(Node*&);
        void setRight(Node*&);
    };

public:
    /*"Habilitamos esta seccion" para que sea publico y podamos definir la
    clase Exception y el nombre a continuacion*/
    ///Definimos el nombre al nodo apuntador como Position
    typedef Node* Position;

    ///Definicion de la clase Excepcion para el arbol
    class Exception : public std::exception {
    private:
        std::string msg;
    public:
        explicit Exception(const char* message): msg(message) {}
        explicit Exception(const std::string& message): msg(message) {}
        virtual ~Exception() throw() {}
        virtual const char* what() const throw () {
            return msg.c_str();
        }
    };

private:
    Position root;//Sera la raiz de nuestro arbol, como el ancla en una lista

    ///Metodos privados del Arbol
    //Donde se hara principalmente la recursividad de los metodos
    void copyAll(BTree<T>&);//Metodo para copiar los elementos de un arbol a otro arbol

    void insertData(Position&, const T&);//Metodo para insertar un elemento al sub-arbol

    void deleteData(Position&, const T&);//Metodo para eliminar un elemento del sub-arbol

    Position& findData (Position&, const T&);//Metodo para encontrar un elemento dentro del arbol regresando
                                            //la posicion del elemento del sub-arbol

    Position& getHighest (Position&);//Metodo para encontrar el mayor del sub-arbol, siendo utilizado para la eliminacion en el arbol

    bool isLeaf(Position&);//Metodo para determinar si es una hoja(o no es padre) la posicion del arbol, utilizada para la eliminacion del arbol

    void parsePostOrderDeleteAll(Position&);//Metodo de eliminacion por recorrdio post-Order

    void parsePreOrderCopy(Position&, Position&);//Metodo para realizar la copia del sub-arbol por recorrido
                                                    //pre-Order, del sub-arbol copia al sub-arbol

    void parsePreOrder (Position&);//Metodo para mostrar los elementos con un recorrido pre-order del sub-arbol

    void parseInOrder (Position&);//Metodo para mostrar los elementos con un recorrido in-order del sub-arbol

    void parsePostOrder (Position&);//Metodo para mostrar los elementos con un recorrido post-order del sub-arbol

    void gotoxy(int, int);//Metodo extra, para escribir en un determinado lugar de la pantalla de ejecucion

    void showLikeTree(Position&, int);//Metodo para mostrar los elementos con forma de arbol al sub-arbol, con la ayuda del entero para los espacios

    void writeParsePreOrder (Position&,std::ofstream&);//Metodo para escribir los elementos del sub-arbol con un recorrido pre-order al archivo

public:
    ///Constructores
    BTree();
    BTree(BTree<T>&);
    ~BTree(); ///Destructor

    int posX= 0;//Variable bublica para la impresion del arbol

    ///Sobrecarga de operador (=)
    BTree<T>& operator = (const BTree<T>&);

    ///Metodos publicos para un Arbol ABB
    /*La mayoria de los metodos siguientes se volveran a llamar, sobrecarga de metodos,
    para empezar la recursividad a partir de la rais del arbol*/

    bool isEmpty()const;//Metodo para checar que este vacia el arbol, revisando su raiz es nulo

    void insertData(const T&);//Metodo para insertar el elemento a la raiz del arbol

    void deleteData(const T&);//Metodo para insertar el elemento a la raiz del arbol

    void deleteAll();//Metodo para eliminar todo el arbol, comenzando su recorrido post-order desde la raiz

    T retrieve(Position&)const;//Metodo para recuperar el elemento del arbol a partir de su posicion

    Position& findData(const T&);//Metodo de busqueda para el arbol, donde empezara desde su raiz

    void parsePreOrder ();//Metodo para iniciar el recorrido pre-order desde la raiz del arbol

    void parseInOrder ();//Metodo para iniciar el recorrido in-order desde la raiz del arbol

    void parsePostOrder ();//Metodo para iniciar el recorrido post-order desde la raiz del arbol

    void showLikeTree();//Metodo para mostrar los elementos con forma de arbol desde la raiz del arbol

    void readFromDisk(const std::string&);//Metodo en donde leera desde el archivo para insertarlo al arbol

    void writeToDisk(const std::string&);//Metodo para escribir a un archivo, iniciando desde la raiz con un recorrido pre-order
};

///Implementacion
using namespace std;

///del Nodo
template <class T>
BTree<T>::Node::Node():dataPtr(nullptr),left(nullptr), right(nullptr) {}//Inicializacion de punteros en nulos

template <class T>
BTree<T>::Node::Node(const T& e): dataPtr(new T(e)), left(nullptr), right(nullptr) {//Inicializacion de punteros en nulo, pero se insertara nuestro dato tipo plantilla
    if(dataPtr == nullptr) {//Verificacion del puntero de dato, si se inserto correctamente
        throw Exception ("Memoria insuficiente, creando nodo");//Lanzar una excepcion si no hay memoria
    }
}

template <class T>
BTree<T>::Node::~Node() {//Destructor del nodo, eliminara el contenido del puntero del dato de tipo plantilla
    delete dataPtr;
}

template <class T>
T* BTree<T>::Node::getDataPtr()const {//Regresara el puntero de tipo plantilla de nuestro dato
    return dataPtr;
}

template <class T>
T BTree<T>::Node::getData()const {//Regresara el dato de tipo plantilla
    if(dataPtr == nullptr) {//Verificacion del puntero del dato, si existe
        throw Exception("Dato inexistente, getData");
    }
    return *dataPtr;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getLeft() {//Se obtiene la posicion(nodo) izquierdo de ese posicion(nodo)
    return left;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getRight() {//Se obtiene la posicion(nodo) derecho de ese posicion(nodo)
    return right;
}

template <class T>
void BTree<T>::Node::setDataPtr(T* e) { //Modificacion del puntero del dato tipo plantilla de ese nodo o posicion
    dataPtr = e;
}

template <class T>
void BTree<T>::Node::setData(const T& e) {//Modificacion del dato tipo plantilla de ese nodo o posicion
    if(dataPtr == nullptr) {//Verificacion de que ese puntero exista
        if((dataPtr = new T(e)) == nullptr) {//Verificacion de que exista memoria
            throw Exception("Memoria no disponible, setData");//Arrojara una excepcion si no hay memoria, al crear el dato tipo plantilla
        }
    } else {//Sino modificara el existente por el nuevo dato
        *dataPtr = e;
    }
}

template <class T>
void BTree<T>::Node::setLeft(Node*& p) {//Modificacion de la posicion(nodo) izquierdo por una nueva posicion
    left = p;
}

template <class T>
void BTree<T>::Node::setRight(Node*& p) {//Modificacion de la posicion(nodo) derecho por una nueva posicion
    right = p;
}

///del Arbol
///Metodos privados
template <class T>
void BTree<T>::copyAll( BTree<T>& t) {//Copiara todo el arbol recibido al nuestro arbol
    parsePreOrderCopy(root, t.root);//Mediante un recorrido pre-order
}

template <class T>
void BTree<T>::insertData(Position& r, const T& e) {//Metodo para insertar un elemento al sub-arbol
    if(r == nullptr) {//Si hay nulo en el nodo de la posicion recibido, en ese se insertara nuestro dato
        try {
            if((r = new Node(e)) == nullptr) {//Verificacion de que exista memoria cuando se crea el nodo
                throw Exception("Memoria no disponible, insertData");//Arrojando una excepcion si no hay memoria
            }
        } catch (typename Node::Exception ex) {
            throw Exception(ex.what());
        }
    } else {//Si existe algun valor en la posicion recibida, se insertara a la izquierda si es menor al dato en esa posicion
        if(e < r->getData()) {//Se llamara otra vez la funcion ya que es recursiva
            insertData(r->getLeft(),e);
        } else {
            insertData(r->getRight(),e);
        }
    }
}

template <class T>
void BTree<T>::deleteData(Position& r, const T& e) {//Metodo para eliminar un elemento del sub-arbol
    /*Implicitamente se utiliza la busqueda binaria natural del arbol ABB para eliminar los datos*/

    if(r == nullptr) {//Si hay nulo en el nodo de la posicion recibido, regresara en ese momento
        return;
    }
    if(e == r->getData()) {//Si es el valor recibido es igual al de esa posicion
        if(isLeaf(r)) {///Si la posicion es hoja
            delete r;//Elimina el nodo, aplicando automaticamente el destructor del nodo
            r = nullptr;//Limpiandolo completamente para poder usar ese espacio despues
            return;//Regresando una vez eliminado el nodo

        } else if(r->getRight() == nullptr or r->getLeft() == nullptr) {///Pero si la posicion tiene un solo hijo
            Position aux(r);//Creamos un nodo para tener una referencia hacia los datos
            r = r->getLeft() == nullptr? r->getRight():r->getLeft();///Se le asignara a la posicion recibida,
                                            ///su posicion contraria si la posicion izquierda tiene nulo, si izq. tiene nulo se le asigna la posicion derecha
                                            ///segun el caso, se asignara la posicion contraria a analizar
            delete aux;//Elimina el nodo referenciador, aplicando automaticamente el destructor del nodo
            return;//Regresando una vez eliminado el nodo
        }

        ///Si la posicion tiene dos hijos
        T sustitution(getHighest(r->getLeft())->getData());//Inicializacon del dato, que sera mayor del lado izq. del sub-arbol donde estamos
        r->setData(sustitution);//Sustitucion del dato de la posicion actual por el dato sustituto
        deleteData(r->getLeft(),sustitution);//Eliminacion del nodo que tenga el mayor del lado izq. del subarbol donde estamos

    } else {//Si es diferente el valor en la posicion recibida con la deseada
        if(e < r->getData()) {//Si es menor el dato deseado con la de la posicion actual, se va por la izq. sino por la derecha
            deleteData(r->getLeft(), e);
        } else {
            deleteData(r->getRight(), e);
        }
    }
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData (Position& r, const T& e) {//Metodo para encontrar un elemento dentro del
                                                                //arbol regresando la posicion del elemento del sub-arbol

    /*Sera como la busqueda binaria para encontrar nuestro dato, aprovechando la naturaleza ordenada del arbol ABB*/
    if(r == nullptr or r->getData() == e) {//Si la posicion tiene un nulo o encontro el dato deseado en ese nodo
        return r;//Regresara la posicion directamente
    }
    if(e < r->getData()) {//Si es menor el dato de la posicion con el dato deseado
        return findData(r->getLeft(), e);//Se movera por la izq. del nodo actual
    } else {
        return findData(r->getRight(), e);//Sino se movera por la derecha del nodo actual
    }
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest (Position& r) {//Metodo para encontrar el mayor del sub-arbol
/*Este metodo aprovecha que todos los mayores del sub-arbol se encontrara hasta el final DERECHA del sub-arbol*/
    if(r == nullptr or r->getRight() == nullptr) {//Si la posicion tiene nulo O su posicion deracha tiene nulo
        return r;//Regresara su posicion
    }
    return getHighest(r->getRight());//Llama otra vez la funcion como un recorrido, pero todo hacia la derecha
}

template <class T>
bool BTree<T>::isLeaf(Position& r) {//Metodo para determinar si no tiene hijos la posicion recibida
    return r != nullptr and r->getLeft() == r->getRight();//Regresando un booleano segun el caso de la posicion
}//Sera hoja si tiene algun dato Y su posicion izquierda sea igual a su posicion derecha, es decir, que sean NULOS ambas posiciones

template <class T>
void BTree<T>::parsePostOrderDeleteAll(Position& r) {//Metodo de eliminacion por recorrdio post-Order
    if(r == nullptr) {//Si tiene nulo la posicion se detendra la recursividad
        return;
    }
    parsePostOrderDeleteAll(r->getLeft());//Se llama otra vez la misma funcion pero se movera hacia la izquierda
    parsePostOrderDeleteAll(r->getRight());//Se llama otra vez la misma funcion pero se movera hacia la derecha
    delete r;//Eliminara el dato de la posicion actual
}

template <class T>
void BTree<T>::parsePreOrderCopy(Position& r, Position& rCopy) {//Metodo para realizar la copia del sub-arbol por recorrido
    if(rCopy == nullptr) {//Si tiene nulo la posicion se detendra la recursividad
        r = nullptr;
    } else {//Sino se creara un nuevo nodo del nuevo arbol
        try {
            if((r = new Node(rCopy->getData())) == nullptr) {//Verificando que exista memoria para la insercion del nodo hacia el arbol
                throw Exception("Memoria no disponible, copyAll");//Arrojando una excepcion si no hay memoria
            }
        } catch (typename Node::Exception ex) {
            throw Exception(ex.what());
        }

        parsePreOrderCopy(r->getLeft(), rCopy->getLeft());//Se llama otra vez la misma funcion pero se movera hacia la izquierda de ambos sub-arboles
        parsePreOrderCopy(r->getRight(), rCopy->getRight());//Se llama otra vez la misma funcion pero se movera hacia la deracha de ambos sub-arboles
    }
}

template <class T>
void BTree<T>::parsePreOrder (Position& r) {//Metodo para mostrar los elementos con un recorrido pre-order del sub-arbol
    if(r == nullptr) {//Si tiene nulo la posicion se detendra la recursividad
        return;
    }
    cout << r->getData().toString() << endl;//Imprimira nuestro dato con nuestro formato para una tabla, de la posicion actual en el sub-arbol
    parsePreOrder(r->getLeft());//Se llama otra vez la misma funcion pero se movera hacia la izquierda
    parsePreOrder(r->getRight());//Se llama otra vez la misma funcion pero se movera hacia la derecha
}

template <class T>
void BTree<T>::parseInOrder (Position& r) {//Metodo para mostrar los elementos con un recorrido in-order del sub-arbol
    if(r == nullptr) {//Si tiene nulo la posicion se detendra la recursividad
        return;
    }
    parseInOrder(r->getLeft());//Se llama otra vez la misma funcion pero se movera hacia la izquierda
    cout << r->getData().toString() << endl;//Imprimira nuestro dato con nuestro formato para una tabla, de la posicion actual en el sub-arbol
    parseInOrder(r->getRight());//Se llama otra vez la misma funcion pero se movera hacia la derecha
}

template <class T>
void BTree<T>::parsePostOrder (Position& r) {//Metodo para mostrar los elementos con un recorrido post-order del sub-arbol
    if(r == nullptr) {//Si tiene nulo la posicion se detendra la recursividad
        return;
    }
    parsePostOrder(r->getLeft());//Se llama otra vez la misma funcion pero se movera hacia la izquierda
    parsePostOrder(r->getRight());//Se llama otra vez la misma funcion pero se movera hacia la derecha
    cout << r->getData().toString() << endl;//Imprimira nuestro dato con nuestro formato para una tabla, de la posicion actual en el sub-arbol
}

template <class T>
void BTree<T>::showLikeTree(Position& r, int cont){//Metodo para mostrar los elementos con forma de arbol al sub-arbol
    if(r == nullptr){//Realizando un recorrido in-order pero iniciando de la rama derecha
        return;//Si tiene nulo la posicion se detendra la recursividad
    }
    showLikeTree(r->getRight(),cont+1);//Se llama otra vez la misma funcion pero se movera hacia la derecha, aumentando el contador recibido para los espacios

    for(int i(0);i<cont;i++){//Imprimir los espacios necesarios para darle forma a un arbol HORIZONTAL
        cout<<"         ";
    }
    cout<<"CASA #"<<r->getData().getNumber()<<" -> "<<"CALLE: "<<r->getData().getStreet()<<" -> "
        <<"COLONIA: "<<r->getData().getColony()<<endl<<endl;//Impresion los datos de nuestros elementos a mostrar como un arbol graficamente

    showLikeTree(r->getLeft(),cont+1);//Se llama otra vez la misma funcion pero se movera hacia la izquierda, aumentando el contador recibido para los espacios
}

template <class T>
void BTree<T>::writeParsePreOrder(Position& r,std::ofstream& myFile) {//Metodo para escribir los elementos del sub-arbol con un recorrido pre-order al archivo
    ///Recibira la posicion para hacer el recorrido y el archivo handle para ir escribiendo con el recorrido hecho
    if(r == nullptr) {//Si tiene nulo la posicion se detendra la recursividad
        return;
    }
    T myData(r->getData());//Inicializacion de nuestro dato para utilizar la sobrecarga de los operadores de flujo de la clase Hoouse
    myFile << myData;//Se uso una sobrecarga de operados de flujo de la clase plantilla, para su escritura al archivo "handle"
                    //y vaya escribiendo con nuestro formato con delimitadores

    writeParsePreOrder(r->getLeft(),myFile);//Se llama otra vez la misma funcion pero se movera hacia la izquierda
    writeParsePreOrder(r->getRight(),myFile);//Se llama otra vez la misma funcion pero se movera hacia la derecha
}

///Constructores
template <class T>
BTree<T>::BTree(): root(nullptr) {}//Iniciara nuestra raiz en nulo

template <class T>//Constructor copia
BTree<T>::BTree(BTree<T>& t): BTree() {//Iniciara con el constructor "original" (llamando otra vez al constructor),
    copyAll(t);                         //y pasara el arbol recibido al nuevo arbol mediante el metodo de copiar el arbol
}

template <class T>
BTree<T>::~BTree() {///Destructor
    deleteAll();//Eliminara todo el arbol con un recorrio post-order
}

///Sobre carga de operador
template <class T>
BTree<T>& BTree<T>::operator =(const BTree<T>&t) {
    deleteAll();//Eliminara todo el arbol que tengamos actualmente
    copyAll(t);//Para despues copiar el arbol recibido hacia el arbol "vaciado" recientemente
    return *this;//Regresando todo el arbol actualizado
}

///Metodos publicos de la BTreea
template <class T>
bool BTree<T>::isEmpty() const {//Verificara si el arbol esta vacio, pricipalmente desde su raiz
    return root == nullptr;//Regresando verdadero o falso, segun la raiz del arbol principal
}

template <class T>
void BTree<T>::insertData(const T& e) {//Metodo de insercion del arbol donde iniciara la recursividad
    insertData(root, e);//Iniciando desde la raiz principal
}

template <class T>
void BTree<T>::deleteData(const T& e) {//Metodo de eliminacion del arbol donde iniciara la recursividad
    deleteData(root, e);//Iniciando desde la raiz principal
}

template <class T>
void BTree<T>::deleteAll() {//Metodo de elimanacion completa del arbol donde iniciara la recursividad
    parsePostOrderDeleteAll(root);//iniciando desde la raiz principal
    root = nullptr;//Finalizando con la liberacion de memoria de la raiz del arbol
    ///Eliminara por completo el arbol
}

template <class T>
T BTree<T>::retrieve(Position& r) const {//Metodo para recuperar el dato de la posicion recibida
    return r->getData();//Este sera utilizada para recuperar los datos en nuestra interfaz, siendo mas comoda para programar
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(const T& e) {////Metodo de busqueda binaria del arbol donde iniciara la recursividad
    return findData(root, e);//Iniciando desde la raiz principal, nos regresara la posicion del dato deseado
}

template <class T>
void BTree<T>::parsePreOrder () {//Metodo para iniciar el recorrido pre-order desde la raiz del arbol
    parsePreOrder(root);//Iniciando su recursividad desde la raiz y asi sucesivamente con sus nodos
}

template <class T>
void BTree<T>::parseInOrder () {//Metodo para iniciar el recorrido in-order desde la raiz del arbol
    parseInOrder(root);//Iniciando su recursividad desde la raiz y asi sucesivamente con sus nodos
}

template <class T>
void BTree<T>::parsePostOrder () {//Metodo para iniciar el recorrido in-order desde la raiz del arbol
    parsePostOrder(root);//Iniciando su recursividad desde la raiz y asi sucesivamente con sus nodos
}

template <class T>
void BTree<T>::showLikeTree(){//Metodo para mostrar los elementos con forma de arbol desde la raiz del arbol
    int cont(0);//Iniciara el contador para los espacios del formato del arbol
    showLikeTree(root,cont);//Iniciara la recursividad desde la raiz, con un recorrido in-order

    /*Se modifico el recorrido para que la orientación del arbol sea HORIZONTAL hacia la izq.
    Empezando el recorrdio in-order con el sub-arbol derecho, imprime el elemento y luego se movera hacia el sub-arbol izq.*/
}

template <class T>
void BTree<T>::readFromDisk(const string& fileName) {//Metodo en donde leera desde el archivo para insertarlo al arbol
    ifstream myFile;//Constructor de ifstream abre el archivo

    myFile.open(fileName, ios_base::in);//Se abre el archivo y se configura de modo entrada

    if(!myFile.is_open()) {//Verifica que se haya abierto bien el archivo
        throw Exception ("No se pudo abrir el archivo (Lectura, readFromDisk)");
    }

    T myData;//Inicializacion de la variable con plantilla
    //Se uso un sobrecarga de operados de flujo de la clase plantilla
    while(myFile >> myData) {//Recorrera el archivo "handle" hasta que no encuentre nada o al final del archivo "handle"
        insertData(root,myData);//Insertara los elementos del archivo "handle" hasta la ultima posicion de la lista
    }
    myFile.close();//Cierra el archivo "handle" para evitar futuras fallas

    cout<<"\t\t\t\tLeyendo del disco..."<<endl;
    system("Pause");//Pausara el programa hasta que se le de un enter
}

template <class T>
void BTree<T>::writeToDisk(const string& fileName) {//Metodo para escribir a un archivo, iniciando desde la raiz con un recorrido pre-order
    ofstream myFile;//Constructor de ofstream abre el archivo

    //Se abre el archivo y se configura de modo trunc
    myFile.open(fileName, ios_base::trunc);//ios_base::trunc  -> Cualquier contenido actual se descarta, asumiendo una longitud de cero al abrir.

    if(!myFile.is_open()) {//Verifica que se haya abierto bien el archivo
        throw Exception ("No se pudo abrir el archivo (Escritura, writeToDisk)");
    } else {

        writeParsePreOrder(root, myFile);//Iniciara la recursividad para escribir al archivo handle conforme se vaya recorriedo en pre-order

        myFile.close();//Cierra el archivo "handle" para evitar futuras fallas
    }
    cout<<"\t\t\t\tEscribiendo al disco..."<<endl;
    system("PAUSE");//Pausara el programa hasta que se le de un enter
}
#endif // BTREE_H_INCLUDED
