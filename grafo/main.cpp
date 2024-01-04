#include <iostream>

class Vertice;
class Arista;

class Vertice {
public:
    std::string name;
    Vertice *next;
    Arista *h_arista;
public:
    Vertice() : name{""}, next{nullptr}, h_arista{nullptr} {}
    Vertice(std::string name, Vertice *next, Arista *h_arista) : name{name}, next{next}, h_arista{h_arista} {}
};

class Arista {
public:
    int weight;
    Vertice *dest;
    Arista *next;
public:
    Arista() : weight{0}, dest{nullptr}, next{nullptr} {}
    Arista(int weight, Vertice *dest, Arista *next) : weight{weight}, dest{dest}, next{next} {}
};

class Grafo {
public:
    Vertice *h_grafo;
public:
    Grafo() : h_grafo{nullptr} {}
    Grafo(Vertice *h) : h_grafo{h} {}
public:
    void insertarVertice(std::string nomVertice) {
        //Se comportara como una lista simple
        Vertice* aux=new Vertice(nomVertice, nullptr, nullptr);
        Vertice* temp=h_grafo;

        if(temp!=nullptr) {
            h_grafo=aux;
        } else {
            while(temp->next!=nullptr) { //se ira hasta el ultimo elemento
                temp=temp->next;
            }
            temp->next=aux;
        }
    }
    void insertarVertice(std::string, Vertice*);///opcional
    void insertarArista(std::string origen, std::string destino, int peso) { //Buscar con los nombre de los vertices en los parametros de string
        Vertice* tempVer = h_grafo;
        Arista* tempArista = nullptr;
        bool flag=true;

        while(tempVer!=nullptr and flag) { //tempVer por si solo equivale lo mismo
            if(tempVer->name==origen) {
                flag=false;
            } else
                tempVer=tempVer->next;
        }
        if(tempVer) {
            tempArista=tempVer->h_arista;//en arista
            if(!tempArista) {//(si no existe), si no es nulo
                Vertice* dest=buscarVertive(destino);
                if(dest) {
                    Arista* aux=new Arista(peso,dest,nullptr);
                    tempVer->h_arista = aux;
                } else {
                    std::cout<<"Destino no encontrado"<<std::endl;
                }
            } else {//si la arista tiene elementos, insertar al principio
               Vertice* dest=buscarVertive(destino);
               if(dest) {
                    Arista* aux=new Arista(peso,dest,nullptr);
                    aux->next= tempVer->h_arista;
                    tempVer->h_arista=aux;
                } else {
                    std::cout<<"Destino no encontrado"<<std::endl;
                }
            }
        } else {
            std::cout<<"origen no encontrado"<<std::endl;
        }

    };
    Vertice* buscarVertive(std::string nomVertice) {
        Vertice* temp=h_grafo;
        while(temp!=nullptr and temp->name== nomVertice) {
            temp=temp->next;
        }
        return temp;
    };

    void mostrarG(void){
        Vertice* tempVer=h_grafo;
        Arista* tempAr=nullptr;

        while(tempVer){
            tempAr=tempVer->h_arista;
            std::cout<<"Origen-------"<<tempVer->name<<"-------";
            while(tempAr){
                std::cout<<"  "<<tempAr->dest->name<<"  ";
                tempAr= tempAr->next;
            }
            cout<<std::endl;
            tempVer= tempVer->next;
        }
    };
};

int main() {
    Grafo g;
    g.insertarVertice("uno");//es la etiqueta del vertice
    g.insertarVertice("dos");
    g.insertarVertice("tres");
    g.insertarVertice("cuatro");

    g.insertarArista("uno","cuatro",7);
    g.insertarArista("uno","cuatro",6);

    g.mostrarG();
    return 0;
}
