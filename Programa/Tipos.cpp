#include <iostream>
#include <cstdlib>
#include "Tipos.h"
#include <iomanip>

using namespace std;

Lista::~Lista()
{
    pNodoLista aux;
    esCabeza();
    while(cabeza)
    {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    cabeza=NULL;
    actual = NULL;
    final=NULL;
}

void Lista::insertarNodo(Paquete p, char c)
{
    pNodoLista aux;
    char tipoInsercion;
    tipoInsercion=c;
    if (listaVacia()) // Si la lista está vacía
    {
        aux = new NodoLista(p,NULL,NULL);
        final = cabeza = aux;
    }
    else if (tipoInsercion=='f')  //Inserción por el final
    {
        aux= new NodoLista(p,NULL,NULL);
        aux->anterior=final;
        final->siguiente=aux;
        final = aux;
    }
    else if (tipoInsercion=='p')  //Inserción por el principio
    {
        aux= new NodoLista(p,NULL,NULL);
        aux->siguiente=cabeza;
        cabeza->anterior=aux;
        cabeza=aux;
    }
}

void Lista::borrarNodo(char c)
{
    char tipoBorrado;
    tipoBorrado=c;
    if(tipoBorrado=='f')  //Eliminación por el final
    {
        pNodoLista aux=NULL;
        if((cabeza==final))   //Sólo hay elemento
        {
            aux=final;
            cabeza = final = NULL;
            aux=NULL;
            delete aux;
        }
        else
        {
            aux=final;
            final=final->anterior;
            aux->anterior=NULL;
            final->siguiente=NULL;
            delete aux;
        }
    }

    else if(tipoBorrado=='p')  //Eliminación por el Principio
    {
        pNodoLista aux=NULL;
        if((cabeza==final))  //Sólo hay elemento
        {
            aux=cabeza;
            cabeza = final = NULL;
            aux=NULL;
            delete aux;
        }
        else
        {
            aux=cabeza;
            cabeza=cabeza->siguiente;
            aux->siguiente=NULL;
            cabeza->anterior=NULL;
            delete aux;
        }
    }
}



pNodoLista Lista::borrarNodo()
{
    // Si la lista está vacía tiene que devolver un NULL y no hacer nada
    if (listaVacia())
    {
        return NULL;
    }

    pNodoLista nodoBorrado = NULL;
    pNodoLista aux = cabeza;
    if (cabeza==actual)
    {
        if (actual==cabeza) actual=actual->siguiente;
        cabeza = actual->siguiente;
    }
    else
    {
        while (aux!=NULL && aux->siguiente!=actual)
        {
            aux = aux->siguiente;
        }
        aux->siguiente=actual->siguiente;
        if (aux->siguiente==NULL)
        {
            final=aux;
        }
    }
    nodoBorrado = actual;
    actual=actual->siguiente;
    nodoBorrado->siguiente=NULL;

    return nodoBorrado;
}

void Lista::borrarNodoIntermedio(pNodoLista nodo)
{

    // Si la lista está vacía tiene que devolver un NULL y no hacer nada
    if (listaVacia() || nodo==NULL)
    {
        return;
    }

    pNodoLista nodoBorrado = NULL;
    pNodoLista aux = cabeza;
    if (cabeza==nodo)
    {
        if (actual==cabeza) actual=nodo->siguiente;
        cabeza = nodo->siguiente;
    }
    else
    {
        while (aux!=NULL && aux->siguiente!=nodo)
        {
            aux = aux->siguiente;
        }
        aux->siguiente=nodo->siguiente;
        if (actual==nodo) actual = aux;
        if (aux->siguiente==NULL)
        {
            final=aux;
        }
    }
//    nodo->siguiente=NULL;
}


bool Lista::listaVacia()
{
    return cabeza == NULL;
}

void Lista::mostrarLista()
{
    pNodoLista aux;
    aux = cabeza;
    int j=0;
    while(aux!=NULL)
    {
        cout << setw(4)<< ++j << " " << setw(7) <<
             aux->getPaquete().idPaquete << " " << setw(9)
             << aux->getPaquete().NIF << " " << setw(2) <<
             aux->getPaquete().coordenadas.latitud[0] << "*"
             << setw(2) << aux->getPaquete().coordenadas.latitud[1]
             << "'" << setw(2) << aux->getPaquete().coordenadas.latitud[2]
             << "''" << " " << setw(2) << aux->getPaquete().coordenadas.longitud[0]
             << "*"<< setw(2) << aux->getPaquete().coordenadas.longitud[1] << "'" <<
             setw(2) << aux->getPaquete().coordenadas.longitud[2] << "''" << endl;
        aux = aux->siguiente;
    }
}

void Lista::esCabeza()
{
    actual = cabeza;
}

void Lista::esFinal()
{
    actual=final;
}

void Lista::esSiguiente()
{
    if(actual) actual = actual->siguiente;
}

void Lista::esAnterior()
{
    if(actual) actual = actual->anterior;
}

bool Lista::esActual()
{
    return actual != NULL;
}

Paquete Lista::paqueteActual()
{
    return actual->paquete;
}

pNodoLista Lista::borrarAntiguo()
{
    actual= final;
    return borrarNodo();
}

int Lista::numNodos()
{
    pNodoLista aux;
    aux = cabeza;
    int j=0;
    while(aux!=NULL)
    {
        j++;
        aux = aux->siguiente;
    }
    return j;
}


pNodoLista Lista::existe(string idPaquete)
{
    Paquete p;
    pNodoLista aux = cabeza;
    while (aux!=NULL)
    {
        p = aux->getPaquete();
        if (p.idPaquete==idPaquete)
        {
            return aux;
        }
        else
        {
            aux = aux->siguiente;
        }
    }
    return NULL;
}


void Arbol::podar(pNodoArbol &NodoArbol)
{
    if(NodoArbol)
    {
        podar(NodoArbol->izquierdo); // Podar izquierdo
        podar(NodoArbol->derecho);   // Podar derecho
        delete NodoArbol;            // Eliminar nodo
        NodoArbol = NULL;
    }
}

void Arbol::insertar(CP cp)
{
    pNodoArbol padre = NULL;

    actual = raiz;
    while(!vacio(actual) && cp.numCP  != actual->centralP.numCP)
    {
        padre = actual;
        if(cp.numCP > actual->centralP.numCP) actual = actual->derecho;
        else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
    }

    if(!vacio(actual)) return;

    if(vacio(padre)) raiz = new NodoArbol(cp);

    else if(cp.numCP < padre->centralP.numCP) padre->izquierdo = new NodoArbol(cp);

    else if(cp.numCP > padre->centralP.numCP) padre->derecho = new NodoArbol(cp);
}

void Arbol::borrar(CP cp)
{
    pNodoArbol padre = NULL;
    pNodoArbol nodo;
    CP aux;

    actual = raiz;

    while(!vacio(actual))
    {
        if(cp.numCP == actual->centralP.numCP)
        {
            if(esHoja(actual))
            {
                if(padre)

                    if(padre->derecho == actual) padre->derecho = NULL;
                    else if(padre->izquierdo == actual) padre->izquierdo = NULL;

                delete actual;
                actual = NULL;
                return;
            }
            else
            {
                padre = actual;
                if(actual->derecho)
                {
                    nodo = actual->derecho;
                    while(nodo->izquierdo)
                    {
                        padre = nodo;
                        nodo = nodo->izquierdo;
                    }
                }
                else
                {
                    nodo = actual->izquierdo;
                    while(nodo->derecho)
                    {
                        padre = nodo;
                        nodo = nodo->derecho;
                    }
                }

                aux = actual->centralP;
                actual->centralP = nodo->centralP;
                nodo->centralP = aux;
                actual = nodo;
            }
        }
        else
        {
            padre = actual;
            if(cp.numCP > actual->centralP.numCP) actual = actual->derecho;
            else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
        }
    }
}


void Arbol::inOrden(void (*func)(int&), pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    if(nodo->izquierdo) inOrden(func, nodo->izquierdo, false);
    func(nodo->centralP.numCP);
    if(nodo->derecho) inOrden(func, nodo->derecho, false);
}


void Arbol::preOrden(void (*func)(int&), pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    func(nodo->centralP.numCP);
    if(nodo->izquierdo) preOrden(func, nodo->izquierdo, false);
    if(nodo->derecho) preOrden(func, nodo->derecho, false);
}


void Arbol::postOrden(void (*func)(int&), pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    if(nodo->izquierdo) postOrden(func, nodo->izquierdo, false);
    if(nodo->derecho) postOrden(func, nodo->derecho, false);
    func(nodo->centralP.numCP);
}


void Arbol::inOrdenCP(void (*func)(CP&), pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    if(nodo->izquierdo) inOrdenCP(func, nodo->izquierdo, false);
    func(nodo->centralP);
    if(nodo->derecho) inOrdenCP(func, nodo->derecho, false);
}


void Arbol::preOrdenCP(void (*func)(CP&), pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    func(nodo->centralP);
    if(nodo->izquierdo) preOrdenCP(func, nodo->izquierdo, false);
    if(nodo->derecho) preOrdenCP(func, nodo->derecho, false);
}


void Arbol::postOrdenCP(void (*func)(CP&), pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    if(nodo->izquierdo) postOrdenCP(func, nodo->izquierdo, false);
    if(nodo->derecho) postOrdenCP(func, nodo->derecho, false);
    func(nodo->centralP);
}

Paquete *Arbol::buscarInOrdenCP(Paquete *(*func)(CP&, string),string idPaquete, pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    Paquete *p;
    if(nodo->izquierdo)
    {
        p=buscarInOrdenCP(func, idPaquete, nodo->izquierdo, false);
        if (p!=NULL) return p;
    }
    p=func(nodo->centralP,idPaquete);
    if (p!=NULL) return p;
    if(nodo->derecho) p=buscarInOrdenCP(func, idPaquete, nodo->derecho, false);
    return p;
}

pNodoArbol Arbol::buscarNodoInOrdenCP(bool (*func)(CP&, string),string idPaquete, pNodoArbol nodo, bool r)
{
    if(r) nodo = raiz;
    pNodoArbol p;
    if(nodo->izquierdo)
    {
        p=buscarNodoInOrdenCP(func, idPaquete, nodo->izquierdo, false);
        if (p!=NULL) return p;
    }
    if(func(nodo->centralP,idPaquete))
    {
        cout << "encontrado" << endl;
        return nodo;
    }
    if(nodo->derecho) return buscarNodoInOrdenCP(func, idPaquete, nodo->derecho, false);
}


pNodoArbol Arbol::buscar(CP cp)
{
    actual = raiz;

    while(!vacio(actual))
    {
        if(cp.numCP == actual->centralP.numCP) return actual;
        else if(cp.numCP > actual->centralP.numCP) actual = actual->derecho;
        else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
    }
    return NULL;
}

int Arbol::calculaAltura(CP cp)
{
    int altura = 0;
    actual = raiz;

    while(!vacio(actual))
    {
        if(cp.numCP == actual->centralP.numCP) return altura;
        else
        {
            altura++;
            if(cp.numCP > actual->centralP.numCP) actual = actual->derecho;
            else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
        }
    }
    return -1;
}

const int Arbol::numeroNodos()
{
    contador = 0;

    auxContador(raiz);
    return contador;
}


void Arbol::auxContador(pNodoArbol nodo)
{
    contador++;
    if(nodo->izquierdo) auxContador(nodo->izquierdo);
    if(nodo->derecho)   auxContador(nodo->derecho);
}

const int Arbol::alturaArbol()
{
    altura = 0;

    auxAltura(raiz, 0); // Función auxiliar
    return altura;
}


void Arbol::auxAltura(pNodoArbol nodo, int a)
{
    if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
    if(nodo->derecho)   auxAltura(nodo->derecho, a+1);

    if(esHoja(nodo) && a > altura) altura = a;
}

void Mostrar(int &d)
{
    cout << d << ",";
}

void generarArbol(Arbol& arbolNew)
{
    int i = 0;
    int num=0;
    int MAX=20;

    for (i=0; i<MAX; i++)
    {
        num=rand()%MAX;
        cout << num << endl;
    }
}

