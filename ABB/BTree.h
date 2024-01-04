#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>
#include <exception>

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

    Position& getLowest (Position&);//Metodo para encontrar
    Position& getHighest (Position&);

    void parsePostOrderDeleteAll(Position&);

    void parsePreOrderCopy(Position&, Position&);

    void parsePreOrder (Position&);
    void parseInOrder (Position&);
    void parsePostOrder (Position&);

    void writeParsePreOrder (Position&,std::ofstream&);

public:
    ///Constructores
    BTree();
    BTree(BTree<T>&);
    ~BTree(); ///Destructor

    ///Sobrecarga de operador
    BTree<T>& operator = (const BTree<T>&);

    ///Metodos para un Arbol
    bool isEmpty()const;

    void insertData(const T&);
    void deleteData(const T&);
    void deleteAll();

    T retrieve(Position&)const;

    Position& findData(const T&);
    Position& getLowest();
    Position& getHighest();

    bool isLeaf(Position&);

    int getHeight(Position&);
    int getHeight();

    void parsePreOrder ();
    void parseInOrder ();
    void parsePostOrder ();

    void readFromDisk(const std::string&);
    void writeToDisk(const std::string&);
};

///Implementacion
using namespace std;

///del Nodo
template <class T>
BTree<T>::Node::Node():dataPtr(nullptr),left(nullptr), right(nullptr) {}

template <class T>
BTree<T>::Node::Node(const T& e): dataPtr(new T(e)), left(nullptr), right(nullptr) {
    if(dataPtr == nullptr) {
        throw Exception ("Memoria insuficiente, creando nodo");
    }
}

template <class T>
BTree<T>::Node::~Node() {
    delete dataPtr;
}

template <class T>
T* BTree<T>::Node::getDataPtr()const {
    return dataPtr;
}

template <class T>
T BTree<T>::Node::getData()const {
    if(dataPtr == nullptr) {
        throw Exception("Dato inexistente, getData");
    }

    return *dataPtr;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getLeft() {
    return left;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getRight() {
    return right;
}

template <class T>
void BTree<T>::Node::setDataPtr(T* e) {
    dataPtr = e;
}

template <class T>
void BTree<T>::Node::setData(const T& e) {
    if(dataPtr == nullptr) {
        if((dataPtr = new T(e)) == nullptr) {
            throw Exception("Memoria no disponible, setData");
        }
    } else {
        *dataPtr = e;
    }
}

template <class T>
void BTree<T>::Node::setLeft(Node*& p) {
    left = p;
}

template <class T>
void BTree<T>::Node::setRight(Node*& p) {
    right = p;
}

///del Arbol
///Metodos privados
template <class T>
void BTree<T>::copyAll( BTree<T>& t) {
    parsePreOrderCopy(root, t.root);
}

template <class T>
void BTree<T>::insertData(Position& r, const T& e) {
    if(r == nullptr) {
        try {
            if((r = new Node(e)) == nullptr) {
                throw Exception("Memoria no disponible, insertData");
            }
        } catch (typename Node::Exception ex) {
            throw Exception(ex.what());
        }
    } else {
        if(e < r->getData()) {
            insertData(r->getLeft(),e);
        } else {
            insertData(r->getRight(),e);
        }
    }
}

template <class T>
void BTree<T>::deleteData(Position& r, const T& e) {
    if(r == nullptr) {
        return;
    }
    if(e == r->getData()) {
        if(isLeaf(r)) {//Si es hoja
            delete r;
            r = nullptr;
            return;
        } else if(r->getRight() == nullptr or r->getLeft() == nullptr) {
            //Si tiene un hijo
            Position aux(r);
            r = r->getLeft() == nullptr? r->getRight():r->getLeft();
            delete aux;
            return;
        }
//Si tiene dos hijos
        T sustitution(getHighest(r->getLeft())->getData());
        r->setData(sustitution);
        deleteData(r->getLeft(),sustitution);
    } else {
        if(e < r->getData()) {
            deleteData(r->getLeft(), e);
        } else {
            deleteData(r->getRight(), e);
        }
    }
}


template <class T>
typename BTree<T>::Position& BTree<T>::findData (Position& r, const T& e) {
    if(r == nullptr or r->getData() == e) {
        return r;
    }
    if(e < r->getData()) {
        return findData(r->getLeft(), e);
    } else {
        return findData(r->getRight(), e);
    }
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest (Position& r) {
    if(r == nullptr or r->getLeft() == nullptr) {
        return r;
    }
    return getLowest(r->getLeft());
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest (Position& r) {
    if(r == nullptr or r->getRight() == nullptr) {
        return r;
    }
    return getHighest(r->getRight());
}

template <class T>
void BTree<T>::parsePostOrderDeleteAll(Position& r) {
    if(r == nullptr) {
        return;
    }
    parsePostOrderDeleteAll(r->getLeft());
    parsePostOrderDeleteAll(r->getRight());
    delete r;
}

template <class T>
void BTree<T>::parsePreOrderCopy(Position& r, Position& rCopy) {
    if(rCopy == nullptr) {
        r = nullptr;
    } else {
        try {
            if((r = new Node(rCopy->getData())) == nullptr) {
                throw Exception("Memoria no disponible, copyAll");
            }
        } catch (typename Node::Exception ex) {
            throw Exception(ex.what());
        }

        parsePreOrderCopy(r->getLeft(), rCopy->getLeft());
        parsePreOrderCopy(r->getRight(), rCopy->getRight());
    }
}


template <class T>
void BTree<T>::parsePreOrder (Position& r) {
    if(r == nullptr) {
        return;
    }
    cout << r->getData().toString() << endl;
    parsePreOrder(r->getLeft());
    parsePreOrder(r->getRight());
}

template <class T>
void BTree<T>::parseInOrder (Position& r) {
    if(r == nullptr) {
        return;
    }
    parseInOrder(r->getLeft());
    cout << r->getData().toString() << endl;
    parseInOrder(r->getRight());
}

template <class T>
void BTree<T>::parsePostOrder (Position& r) {
    if(r == nullptr) {
        return;
    }
    parsePostOrder(r->getLeft());
    parsePostOrder(r->getRight());
    cout << r->getData().toString() << endl;
}

///Constructores
template <class T>
BTree<T>::BTree(): root(nullptr) {}

template <class T>
BTree<T>::BTree(BTree<T>& t): BTree() {//Llama otra vez al contructor
    copyAll(t);
}

template <class T>
BTree<T>::~BTree() {///Destructor
    deleteAll();
}

///Sobre carga de operador
template <class T>
BTree<T>& BTree<T>::operator =(const BTree<T>&t) {
    deleteAll();
    copyAll(t);
    return *this;
}

///Metodos publicos de la BTreea
template <class T>
bool BTree<T>::isEmpty() const {
    return root == nullptr;
}

template <class T>
void BTree<T>::insertData(const T& e) {
    insertData(root, e);
}

template <class T>
void BTree<T>::deleteData(const T& e) {
    deleteData(root, e);
}

template <class T>
void BTree<T>::deleteAll() {
    parsePostOrderDeleteAll(root);
    root = nullptr;
}

template <class T>
T BTree<T>::retrieve(Position& r) const {
    return r->getData();
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(const T& e) {
    return findData(root, e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest() {
    return getLowest(root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest() {
    return getHighest(root);
}

template <class T>
bool BTree<T>::isLeaf(Position& r) {
    return r != nullptr and r->getLeft() == r->getRight();
}

template <class T>
int BTree<T>::getHeight() {
    return getHeight(root);
}

template <class T>
int BTree<T>::getHeight(Position& r) {
    if(r == nullptr) {
        return 0;
    }
    int lH(getHeight(r->getLeft()));
    int rH(getHeight(r->getRight()));

    return (lH > rH ? lH : rH) + 1;
}

template <class T>
void BTree<T>::parsePreOrder () {
    parsePreOrder(root);
}

template <class T>
void BTree<T>::parseInOrder () {
    parseInOrder(root);
}

template <class T>
void BTree<T>::parsePostOrder () {
    parsePostOrder(root);
}

template <class T>
void BTree<T>::readFromDisk(const string& fileName) {
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
void BTree<T>::writeToDisk(const string& fileName) {
    ofstream myFile;//Constructor de ofstream abre el archivo

    //Se abre el archivo y se configura de modo trunc
    myFile.open(fileName, ios_base::trunc);//ios_base::trunc  -> Cualquier contenido actual se descarta, asumiendo una longitud de cero al abrir.

    if(!myFile.is_open()) {//Verifica que se haya abierto bien el archivo
        throw Exception ("No se pudo abrir el archivo (Escritura, writeToDisk)");
    } else {
        ///while(aux!=nullptr) {//Recorrimiento de toda la lista para la obtencion de los datos, uno por uno
        writeParsePreOrder(root, myFile);

        myFile.close();//Cierra el archivo "handle" para evitar futuras fallas
    }
    cout<<"\t\t\t\tEscribiendo al disco..."<<endl;
    system("PAUSE");//Pausara el programa hasta que se le de un enter
}

template <class T>
void BTree<T>::writeParsePreOrder(Position& r,std::ofstream& myFile) {
    if(r == nullptr) {
        return;
    }
    T myData(r->getData());
    myFile << myData;//Se uso una sobrecarga de operados de flujo de la clase plantilla, para su escritura al archivo "handle"

    writeParsePreOrder(r->getLeft(),myFile);
    writeParsePreOrder(r->getRight(),myFile);
}
#endif // BTREE_H_INCLUDED
