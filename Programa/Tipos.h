#ifndef Tipos
#define Tipos

#include <iostream>

using namespace std;

//Definición de tipos de datos:
struct CoordenadasGPS
{
    int latitud[3];
    int longitud[3];
};

struct Paquete
{
    string idPaquete;
    CoordenadasGPS coordenadas;
    string NIF;
    int numCP;
};


//Lista
class NodoLista
{
private:
    Paquete paquete;
    NodoLista *siguiente;
    NodoLista *anterior;
    friend class Lista;

public:
    NodoLista(Paquete p, NodoLista *sig = NULL, NodoLista *ant = NULL)
    {
        paquete= p;
        siguiente = sig;
        anterior = ant;
    }
    //
    Paquete getPaquete(){
        return paquete;
    }
};
typedef NodoLista *pNodoLista;

class Lista
{
private:
    pNodoLista cabeza, actual, final;
public:
    Lista()
    {
        cabeza = actual = final = NULL;
    }
    ~Lista();
    void insertarNodo(Paquete p, char c);
    void borrarNodo(char c);
    pNodoLista borrarNodo();
    void borrarNodoIntermedio(pNodoLista nodo);
    bool listaVacia();
    void esCabeza();
    void esFinal();
    void esSiguiente();
    void esAnterior();
    bool esActual();
    Paquete paqueteActual();
    void mostrarLista();
    pNodoLista borrarAntiguo();
    int numNodos();
    pNodoLista existe(string idPaquete);
};

struct CP
{
    int numCP;
    string localidad;
    Lista *listaPaq;
};

class NodoArbol {
    private:
        // Miembros:
        CP centralP;
        NodoArbol *izquierdo;
        NodoArbol *derecho;
        friend class Arbol;

    public:
        // Constructor:
        NodoArbol(CP cp, NodoArbol *izq=NULL, NodoArbol *der=NULL) :
        centralP(cp), izquierdo(izq), derecho(der) {};
        CP getCentrarlP(){
            return centralP;
        };

};
typedef NodoArbol *pNodoArbol;

class Arbol {
    private:
        // Punteros de la lista, para cabeza y nodo actual:
        pNodoArbol raiz;
        pNodoArbol actual;
        int contador;
        int altura;

    public:
        // Constructor y destructor básicos:
        Arbol() : raiz(NULL), actual(NULL) {}
        ~Arbol() { podar(raiz); }
        // Insertar en árbol ordenado:
        void insertar(CP cp);
        // Borrar un elemento del árbol:
        void borrar(CP cp);
        // Función de búsqueda:
        pNodoArbol buscar(CP cp);
        // Comprobar si el árbol está vacío:
        bool vacio(pNodoArbol r) { return r==NULL; }
        // Comprobar si es un nodo hoja:
        bool esHoja(pNodoArbol r) { return r->derecho!=NULL && r->izquierdo!=NULL; }
        // Contar número de nodos:
        const int numeroNodos();
        const int alturaArbol();
        // Calcular altura de un int:
        int calculaAltura(CP cp);
        // Devolver referencia al int del nodo actual:
        CP cpActual() { return actual->centralP; } //&ValorActual()
        // Moverse al nodo raiz:
        void volverARaiz() { actual = raiz; }
        // Aplicar una función a cada elemento del árbol:
        void inOrden(void (*func)(int&) , pNodoArbol nodo=NULL, bool r=true);
        void preOrden(void (*func)(int&) , pNodoArbol nodo=NULL, bool r=true);
        void postOrden(void (*func)(int&) , pNodoArbol nodo=NULL, bool r=true);
        void inOrdenCP(void (*func)(CP&) , pNodoArbol nodo=NULL, bool r=true);
        void preOrdenCP(void (*func)(CP&) , pNodoArbol nodo=NULL, bool r=true);
        void postOrdenCP(void (*func)(CP&) , pNodoArbol nodo=NULL, bool r=true);
        Paquete *buscarInOrdenCP(Paquete *(*func)(CP&, string),string idPaquete, pNodoArbol nodo=NULL, bool r=true);
        pNodoArbol buscarNodoInOrdenCP(bool (*func)(CP&, string),string idPaquete, pNodoArbol nodo=NULL, bool r=true);
        private:
        // Funciones auxiliares
        void podar(pNodoArbol &nodo);
        void auxContador(pNodoArbol nodo);
        void auxAltura(pNodoArbol nodo, int alt);
};


#endif
