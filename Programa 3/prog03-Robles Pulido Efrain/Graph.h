#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <fstream> //contiene tipos de procesamiento de flujos de archivos

#include <string>

template<class V, class E>
class Graph {
private:
    class VertexNode;
    class EdgeNode;

///Definicion del Nodo Vertice
    class VertexNode {
    private:
        friend class Graph;//Haciendo amiga la clase Grafo
        V data;
        VertexNode* next;
        EdgeNode* h_Edge;

    public:
        VertexNode() ;
        VertexNode(const V&, VertexNode*, EdgeNode*);
    };

    ///Definicion del Nodo Arista
    class EdgeNode {
    private:
        friend class Graph;//Haciendo amiga la clase Grafo
        E weight;
        VertexNode* dest;
        EdgeNode* next;

    public:
        EdgeNode();
        EdgeNode(const E&, VertexNode*, EdgeNode*);
    };

public://Se cambiara de nombre los nodos del grafo
    typedef VertexNode* VertPos;
    typedef EdgeNode* EdgePos;

private:
    VertexNode* h_graph;///Atributo privado del Grafo

public:
    ///Constructores
    Graph();
    Graph(VertexNode*);

    ///Metodos publicos del grafo
    bool isEmpty();//Verifica si esta vacio el grafo
    void insertVertex(const V&);//Insertara un vertice
    void deleteVertex(const V&);//Eliminara un vertice
    void deleteAllVertex(void);//Eliminara todos los vertices del grafo

    void insertEdge(const V&, const V&, E&); //Insertara una arista desde el vertice de origen hacia el destino con su peso
    void deleteEdge(const V&, const V&);//Eliminara una arista desde su vertice de origen haci su arista destino
    void deleteAllEdge(VertexNode*);//Eliminara todas las aristas del vertice recibido

    void getListEdge(VertexNode*);//Imprimira todas las aristas que tenga el vertice recibido
    VertexNode* findVertex(const V&);//Buscara el vertice en la lista de vertices del grafo
    V retriveVertex(VertexNode*);//Recuperara el dato del vertice del grafo

    EdgeNode* findEdge(const V&, const V&);//Buscara la arista en su lista de arista del vertice recibido
    E retriveEdge(EdgeNode*);//Recuperara el peso de la arista recibido

    std::string toString(void);//Pone en fomato todo el grafo en una cadena

    void readFromDisk(const std::string&, const std::string&);//Metodo para leer desde un archivo vertice y otro de arista
    void writeToDisk(const std::string&, const std::string&);//Metodo para escribir a un archivo vertice y otro de arista
};

///Implementacion de......
using namespace std;

///Nodo Vertice
//Constructores
template <class V, class E>
Graph<V, E>::VertexNode::VertexNode(): next(nullptr), h_Edge(nullptr) {}

template <class V, class E>
Graph<V, E>::VertexNode::VertexNode(const V& d, VertexNode* n, EdgeNode* h_edge): data(d), next(n), h_Edge(h_edge) {}

///Nodo Arista
//Constructores
template <class V, class E>
Graph<V, E>::EdgeNode::EdgeNode():dest(nullptr), next(nullptr) {}

template <class V, class E>
Graph<V, E>::EdgeNode::EdgeNode(const E& e, VertexNode* d, EdgeNode* n): weight(e), dest(d), next(n) {}

///Grafo
//Constructores
template<class V, class E>
Graph<V, E>::Graph(): h_graph(nullptr) {}//Inicializacion del grafo

template<class V, class E>
Graph<V, E>::Graph(VertexNode* h): h_graph(h) {}//Inicializara el grafo desde un vertice recibido

//Metodos publicos del Grafo
template<class V, class E>
bool Graph<V, E>::isEmpty() {//Verifica si esta vacio el grafo
    return h_graph == nullptr;
}
template<class V, class E>
void Graph<V, E>::insertVertex(const V& v) {//Insertara un vertice hasta el final
    //Se comportara como una lista simple
    VertexNode* aux=new VertexNode(v, nullptr, nullptr);
    VertexNode* tempVer=h_graph;

    if(isEmpty()) {//Si esta vacia el grafo
        h_graph=aux;//Inserta en el ancla
    } else {
        while(tempVer->next) { //Se insertara hasta el ultimo elemento
            tempVer=tempVer->next;
        }
        tempVer->next = aux;//Insercion al final
    }

}

template<class V, class E>
void Graph<V, E>::deleteVertex(const V& dataV) {//Eliminara un vertice
    VertexNode* v = findVertex(dataV);//Obtencin de la posicion del vertice en el grafo

    if(v) {//Verificacion de que exista datos
        VertexNode* auxV = h_graph;
        EdgeNode* auxEdge = nullptr;
        EdgeNode* ePrev = nullptr;

        while(auxV != nullptr) {//Recorre todos los vertices para eliminar el vertice destino de las aristas posibles
            auxEdge = auxV->h_Edge;

            while (auxEdge!=nullptr) { //Recorre la lista de arista en el vertice actual
                if(auxEdge->dest == v) {//Si encontro el mismo dato en laista de arista
                    if (auxEdge == auxV->h_Edge) { //Si esta en el ancla
                        auxV->h_Edge = auxEdge->next;//Reasigna en el ancla
                    } else {
                        ePrev->next = auxEdge->next;//el siguiente del dato encontrado sera el siguiente del anterior de la lista
                    }
                    delete auxEdge;//Eliminacion del dato

                }
                ePrev = auxEdge;//Almacenamos el anterior en cada recorrido de las aristas
                auxEdge = auxEdge->next;
            }
            auxV= auxV->next;
        }

        deleteAllEdge(v);//Eliminamos la lista de arista del vertice deseado

        VertexNode* vPrev=nullptr;
        auxV = h_graph;
        while(auxV != nullptr and auxV != v) {//Recorrido de los vertices para tener el anterior del vertice deseado
            vPrev = auxV;
            auxV=auxV->next;
        }

        if (v == h_graph) {//Si se encuentra en el ancla el vertice deseado
            h_graph = v->next;//Se reasigna el ancla
        } else {
            vPrev->next = v->next;//el siguiente del vertice sera el siguiente del anterior de la lista de vertice
        }
        delete v;//Eliminacion del vertice deseado
        v = nullptr;
    } else {
        cout<<"Vertice NO encontrado"<<endl;

    }
}

template<class V, class E>
void Graph<V,E>::deleteAllVertex(void) {//Eliminara todos los vertices del grafo
    VertexNode* auxV;
    while (h_graph != nullptr) {//Recorrido de los vertices
        auxV = h_graph;//Reasignacion de la cabecera
        deleteAllEdge(auxV);//Eliminacion de todas las aristas del vertice actual
        delete auxV;//Liberacion de espacio
        auxV=nullptr;
        h_graph = h_graph->next;
    }
}

template<class V, class E>
void Graph<V, E>::insertEdge(const V& origen, const V& destino, E& peso) {//Insercion de arista desde vertice origen hacia el destino y su peso
    VertexNode* orig = findVertex(origen);//Almacenamiento de direccion de los vertices
    VertexNode* dest=findVertex(destino);

    if(orig and dest) {//Verificacion de que existan datos dentro ellos
        EdgeNode* auxEdge=orig->h_Edge;
        EdgeNode* aux=new EdgeNode(peso,dest,nullptr);
        if(auxEdge == nullptr) {//Si esta vacia la lista de arista
            orig->h_Edge = aux;//Reasigna en el ancla
        } else {//si la lista de arista tiene elementos, insertar al principio
            aux->next= orig->h_Edge;//Asigna el siguiente de nuesta arista al ancla
            orig->h_Edge=aux;//Reasigna en el ancla
        }
    } else {
        if (!orig) {
            cout<<"Vertice destino NO encontrado"<<endl;
        }
        if(!dest) {
            cout<<"Vertice origen NO encontrado"<<endl;
        }
    }
}

template<class V, class E>
void Graph<V, E>::deleteEdge(const V& origen, const V& destino) {
    VertexNode* auxVerO = findVertex(origen);//Almacenamiento de direccion de los vertices
    VertexNode* auxVerD = findVertex(destino);

    if(auxVerO and auxVerD) {//Verificacion de los vertices
        EdgeNode* auxEdgeO=auxVerO->h_Edge;//Inicio de las aristas
        EdgeNode* prevEdgeO = nullptr;

        if (auxVerO->h_Edge->dest == auxVerD) {//Si esta en el ancla de las aristas
            auxVerO->h_Edge = auxEdgeO->next;//Reasigna el ancla

        } else {
            while(auxEdgeO != nullptr and auxEdgeO->dest != auxVerD) {//Recorrido de las aristas para encontra la posicion del vertice destino
                prevEdgeO = auxEdgeO;//Almacenamos el vertice anterior del deseado
                auxEdgeO = auxEdgeO->next;
            }
            prevEdgeO->next = auxEdgeO->next;//El siguiente del anterior sera el siguiente del vertice deseado
        }
        delete auxEdgeO;//Liberacion de espacio
    } else {
        if (!auxVerO) {
            cout<<"Vertice destino NO encontrado"<<endl;
        }
        if(!auxVerD) {
            cout<<"Vertice origen NO encontrado"<<endl;
        }
    }
}

template<class V, class E>
void Graph<V,E>::deleteAllEdge(VertexNode* beginEdge) {//Eliminara todas las aristas del vertice recibido
    if(beginEdge){//Verificacion de que exista dicho vertice
    EdgeNode* auxE;

    while(beginEdge->h_Edge != nullptr) {//Recorrido para eliminar toda la lista de arista del vertice a eliminar
        auxE = beginEdge->h_Edge;//Reasigna el ancla al siguiente
        beginEdge->h_Edge = beginEdge->h_Edge->next;
        delete auxE;//Libera espacio
        auxE = nullptr;
    }
    }else{
        cout<<"Vertice VACIO"<<endl;
    }
}

template<class V, class E>
void Graph<V, E>::getListEdge(VertexNode* Ver) {//Impresion de toda la lista de arista del certice recibido
    if(Ver->h_Edge) {//Verificacion de que exista el vertice
        EdgeNode* auxEdge = Ver->h_Edge;
        V vertex;
        E edge;
        while(auxEdge != nullptr) {//Recorrido de la lista de arista del vertice
            vertex=auxEdge->dest->data;
            edge=auxEdge->weight;
            cout<< "\tCASA: " << to_string(vertex.getNumber())<<//Imprimimos los datos del vertice destino y su peso
                " | CALLE: " << vertex.getStreet() << " | COLONIA: " << vertex.getColony() <<
                " | Distancia (KM): " << edge.toString()<< endl;
            auxEdge =auxEdge->next;
    }
    }else{
        cout<<"NO hay relaciones"<<endl;
    }
}

template<class V, class E>
class Graph<V,E>::VertexNode* Graph<V, E>::findVertex(const V& nomVertex) {//Busqueda del vertice en el grafo
    VertexNode* aux = h_graph;
    while(aux != nullptr and aux->data != nomVertex) {//Recorrido de vertices para encontrar la posicion deseada de vertices
        aux = aux->next;
    }
    return aux;//Regresa su direccion de memoria encontrado
}

template<class V, class E>
V Graph<V, E>::retriveVertex(VertexNode* v) {//Recupera el dato de la direccion del vertice
    return v->data;
}

template<class V, class E>
class Graph<V,E>::EdgeNode* Graph<V, E>::findEdge(const V& origen, const V& destiny) {//Busqueda de la arista desde el vertice origen hacia su destino
    VertexNode* auxVO = findVertex(origen);//Almacenamiento de las direcciones de cada vertice
    VertexNode* auxVD = findVertex(destiny);

    EdgeNode* auxEO = auxVO->h_Edge;

    while (auxEO != nullptr and  auxEO->dest != auxVD) {//Recorrido de las aristas del vertice origen hasta encontrar el vetice destino
        auxEO = auxEO->next;
    }
    return auxEO;//Regresa su direccion de memoria encontrado
}

template<class V, class E>
E Graph<V, E>::retriveEdge(EdgeNode* e) {//Recupera el peso de la arista
    return e->weight;
}

template<class V, class E>
string Graph<V, E>::toString(void) {//Regresara como cadena todo el grafo, sus vertices y sus aristas
    string str;
    if (isEmpty()) {//Verificacin si esta vacio el grafo
        return str;
    }

    VertexNode* auxVer = h_graph;
    EdgeNode* auxEdge=nullptr;

    while(auxVer!=nullptr) {//Recorrido de los vertices
        auxEdge=auxVer->h_Edge;
        str += auxVer->data.toString();
        while(auxEdge!=nullptr) {//Recorrido de las aristas
            V vertD = auxEdge->dest->data;
            str += "-> " + auxEdge->weight.toString() + " | " + to_string(vertD.getNumber())
            + " | " + vertD.getColony() + " | " + vertD.getStreet() + " ";
            auxEdge= auxEdge->next;
        }
        str += "\n";
        auxVer= auxVer->next;
    }
}

template <class V, class E>
void Graph<V, E>::readFromDisk(const string& fileNameVertex, const string& fileNameEdge) {//Metodo para leer desde un archivo vertice y otro de arista
    ifstream fileVertex;//Constructor de ifstream abre el archivo de vertices
    ifstream fileEdge;//Constructor de ifstream abre el archivo de aristas

    fileVertex.open(fileNameVertex, ios_base::in);//Se abre el archivo de vertices y se configura de modo entrada
    fileEdge.open(fileNameEdge, ios_base::in);//Se abre el archivo de aristas y se configura de modo entrada

    if(!fileVertex.is_open() and !fileEdge.is_open()) {//Verifica que se hayan abierto bien los archivos
        cout<<"No se pudo abrir los archivo (Lectura, readFromDisk)";
        return;
    }

    V myVertexO, myVertexD;//Inicializacion de las variables con plantilla
    //Se uso un sobrecarga de operados de flujo de la clase plantilla
    while(fileVertex >> myVertexO) {//Recorrera el archivo "handle" hasta que no encuentre nada o al final del archivo "handle"
        insertVertex(myVertexO);
    }

    E myEdge;//Inicializacion de la variable con plantilla
    //Leera el archivo de aristas con este orden de los datos >>myEdge >> myVertexO >> myVertexD
    while(fileEdge >> myEdge >> myVertexO >> myVertexD) {//Recorrera el archivo "handle" hasta que no encuentre nada o al final del archivo "handle"
        insertEdge(myVertexO, myVertexD, myEdge);
    }
    //Cierre de archivos "handle" para evitar futuras fallas
    fileVertex.close();//Cierra el archivo "handle" para evitar futuras fallas
    fileEdge.close();

    cout<<"\t\t\t\tLeyendo del disco..."<<endl;
    system("Pause");//Pausara el programa hasta que se le de un enter
}

template <class V, class E>
void Graph<V, E>::writeToDisk(const string& fileNameVertex, const string& fileNameEdge) {//Metodo para escribir a un archivo vertice y otro de arista
    ofstream fileVertex;//Constructor de ofstream abre el archivo de vertices
    ofstream fileEdge;//Constructor de ofstream abre el archivo de aristas

    //Se abren los archivo y se configura de modo trunc
    fileVertex.open(fileNameVertex, ios_base::trunc);//ios_base::trunc  -> Cualquier contenido actual se descarta, asumiendo una longitud de cero al abrir.
    fileEdge.open(fileNameEdge, ios_base::trunc);//ios_base::trunc  -> Cualquier contenido actual se descarta, asumiendo una longitud de cero al abrir.

    if(!fileVertex.is_open() and !fileEdge.is_open()) {//Verifica que se hayan abierto bien los archivos
        cout<<"No se pudo abrir los archivo (Lectura, readFromDisk)";
        return;
    }
    //Inicializacion para los recorridos del grafo
    VertexNode* auxV = h_graph;
    EdgeNode* auxE =nullptr;
    //Inicializacion de la variable con plantilla
    V vertexO, vertexD;
    E edge;
    while(auxV!=nullptr) {//Recorrido de vertices
        vertexO = auxV->data;
        fileVertex << vertexO;//Se uso una sobrecarga de operados de flujo de la clase plantilla, para su escritura al archivo vertice
        auxE = auxV->h_Edge;//Asignacion del ancla de las aristas

        while(auxE != nullptr) {//Recorrido de las aristas
            vertexD = auxE->dest->data;
            edge = auxE->weight;
            fileEdge << edge ;//Se uso una sobrecarga de operados de flujo de la clase plantilla, para su escritura al archivo arista
            fileEdge<< vertexO << vertexD;//Se uso una sobrecarga de operados de flujo de la clase plantilla, para su escritura al archivo arista
            auxE = auxE->next;
        }
        auxV=auxV->next;
    }
    //Cierre de archivos "handle" para evitar futuras fallas
    fileVertex.close();
    fileEdge.close();

    cout<<"\t\t\t\tEscribiendo al disco..."<<endl;
    system("PAUSE");//Pausara el programa hasta que se le de un enter
}
#endif // GRAPH_H_INCLUDED
