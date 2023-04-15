#include "Grafo.h"


//Clase Arco()

template <typename C>Grafo<C>::Arco::Arco()
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    this->costo = costo;
    this->vertice = adyacente;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const
{
    return this->vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const
{
    return this->costo;
}

template <typename C> void Grafo<C>::Arco::modificar_costo(const C & costo)
{
    this->costo = costo;
}

//Clase Grafo()


template <typename C> Grafo<C>:: Grafo()

{
    //ctor
}

template <typename C> Grafo<C>::Grafo(bool dirigido)
{
    this->dirigido = dirigido;
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    *this = otroGrafo;
}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    this->vaciar(); //Lo vacio ya que si tiene contenido no sera igual al otro grafo
    list<int> vertices;
    otroGrafo.devolver_vertices(vertices);
    list<int>::iterator itV = vertices.begin();
    while(itV != vertices.end()) {
        this->agregar_vertice(*itV);
        list<Arco> adyacentes;
        otroGrafo.devolver_adyacentes(*itV, adyacentes);
        typename list<Arco>::iterator itA = adyacentes.begin();
        while(itA != adyacentes.end()) {
            this->agregar_arco(*itV, itA->devolver_adyacente(), itA->devolver_costo());
            itA++;
        }
        itV++;
    }
    return *this;
}

template <typename C> Grafo<C>:: ~Grafo()
{
    //dtor
}

template <typename C> bool Grafo<C>::esta_vacio() const
{
    return this->grafo.empty();
}

template <typename C> int Grafo<C>::devolver_longitud() const
{
    return this->grafo.size();
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{
    typename map<int, list<Arco>>::const_iterator it = this->grafo.find(vertice);
    if(it != this->grafo.end()) return true;
    return false;
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    typename map<int, list<Arco>>::const_iterator itV = this->grafo.find(origen);
    if(itV != this->grafo.end()) {
        typename list<Arco>::const_iterator itA= itV->second.begin();
        while(itA != itV->second.end()) {
            if(itA->devolver_adyacente() == destino) return true;
            itA++;
        }
    }
    return false;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{
   typename map<int, list<Arco>>::const_iterator itV = this->grafo.find(origen);
   typename list<Arco>::const_iterator itA = itV->second.begin();
   while(itA != itV->second.end()) {
    if(itA->devolver_adyacente() == destino) return itA->devolver_costo();
    itA++;
   }
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    typename map<int, list<Arco>>::const_iterator itV = this->grafo.begin();
    while(itV != this->grafo.end()) {
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int, list<Arco>>::const_iterator itV = this->grafo.find(origen);
    adyacentes = itV->second;
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    this->grafo.insert({vertice, list<Arco>{}});
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    this->grafo.erase(vertice);
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
    typename map<int, list<Arco>>::iterator itV = this->grafo.find(origen);
    typename list<Arco>::iterator itA= itV->second.begin();
    while(itA->devolver_adyacente() != destino)
    {
        itA++;
    }
    itA->modificar_costo(costo);
}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    typename map<int, list<Arco>>::iterator itV= this->grafo.find(origen);
    if(itV != this->grafo.end()) {
        Arco a1(destino, costo);
        itV->second.push_back(a1);
    }
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    typename map<int, list<Arco>>::iterator itV = this->grafo.find(origen);
    typename list<Arco>::iterator itA = itV->second.begin();
    while(itA->devolver_adyacente() != destino) {
        itA++;
    }
    itV->second.erase(itA);
}

template <typename C> void Grafo<C>::vaciar()
{
    this->grafo.clear();
}

template class Grafo<int>;
