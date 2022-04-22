#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include "iostream"
using namespace std;

template <typename C> class Grafo
{
public:
    class Arco
    {
    public:
        Arco();
        Arco(int adyacente, const C & costo);
        int devolver_adyacente() const;
        const C & devolver_costo() const;
    private:
        int vertice;
        C costo;
    }; // class Arco

public:
    // NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
    Grafo();
    Grafo(const Grafo & otroGrafo);

    ~Grafo();

    Grafo & operator = (const Grafo & otroGrafo);

    // Devuelve true si la cantidad de vértices es cero
    bool esta_vacio() const;

    // Indica la cantidad de vértices del grafo
    int devolver_longitud() const;

    bool existe_vertice(int vertice) const;

    bool existe_arco(int origen, int destino) const;

    // PRE CONDICION: existe_arco(origen, destino)
    const C & costo_arco(int origen, int destino) const;

    void devolver_vertices(list<int> & vertices) const;

    void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

    void agregar_vertice(int vertice);

    // POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
    void eliminar_vertice(int vertice);

    // PRE CONDICION: existeArco(origen, destino)
    void modificar_costo_arco(int origen, int destino, const C & costo);

    // PRE CONDICION: existeVertice(origen) && existeVertice(destino)
    // POST CONDICION: existeArco(origen, destino)
    void agregar_arco(int origen, int destino, const C & costo);

    // POST CONDICION: !existeArco(origen, destino)
    void eliminar_arco(int origen, int destino);

    void vaciar();

private:
    struct Vertice
    {
        int vertice;
        list<Arco> adyacentes;
    };
    list<Vertice> vertices;

}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco() //constructor vacio de arco
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo) //constructor con datos de arco
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


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    this = &otroGrafo;
}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{

    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{
    return this->vertices.empty();
}

template <typename C> int Grafo<C>::devolver_longitud() const
{
    return this->vertices.size();
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{
    bool existe = false;
    typename list<Vertice>::const_iterator it = this->vertices.begin();
    while(!existe && (it != this->vertices.end()))
    {
        if(it->vertice == vertice)
        {
            existe = true;
        }
        it++;
    }
    return existe;
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    bool existe = false;
    typename list<Vertice>::const_iterator it = this->vertices.begin();
    while(!existe && (it != this->vertices.end()))
    {
        bool bandera = false;
        if(it->vertice == origen)
        {
            typename list<Arco>::const_iterator it2 = it->adyacentes.begin();
            while(!bandera && (it2 != it->adyacentes.end()))
            {
                if(it2->devolver_adyacente() == destino)
                {
                    bandera = true;
                }
                it2++;
            }
        }
        if(bandera)
        {
            existe = true;
        }
        it++;
    }
    return existe;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{

}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    typename list<Vertice>::const_iterator it = this->vertices.begin();
    while(it != this->vertices.end())
    {
        vertices.push_back(it->vertice);
        it++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    bool bandera = false;
    typename list<Vertice>::const_iterator it = this->vertices.begin();

    while(!bandera && (it != vertices.end()))
    {
        if(origen == it->vertice)
        {
            bandera = true;
            typename list<Arco>::const_iterator it2 = it->adyacentes.begin();
            while(it2 != it->adyacentes.end())
            {
                adyacentes.push_back(*it2);
                it2++;
            }
        }
        it++;
    }
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    Vertice v;
    v.vertice = vertice;
    this->vertices.push_back(v);
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    bool bandera = false;
    typename list<Vertice>::iterator it = this->vertices.begin();
    typename list<Vertice>::iterator auxit;
    if(this->existe_vertice(vertice))
    {
        while((it != this->vertices.end()))
        {
            if(it->vertice == vertice)
            {
                bandera = true;
                auxit = it;
            }
            else
            {
                if(this->existe_arco(it->vertice, vertice))
                {
                    this->eliminar_arco(it->vertice, vertice);
                }
            }
            it++;
        }
        if(bandera)
        {
            auxit->adyacentes.clear();
            this->vertices.erase(auxit);
        }
    }

}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{

}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    bool bandera = false;
    typename list<Vertice>::iterator it = this->vertices.begin();
    while((it != this->vertices.end())&& !bandera)
    {
        if(it->vertice == origen)
        {
            bandera = true;
            Arco a1(destino, costo);
            it->adyacentes.push_back(a1);
        }
        it++;
    }
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    bool bandera = false;
    typename list<Vertice>::iterator it = this->vertices.begin();
    while((it != this->vertices.end()) && !bandera)
    {
        if(it->vertice == origen)
        {
            bandera = true;
            typename list<Arco>::iterator it2 = it->adyacentes.begin();
            bool bandera2 = false;
            while((it2 != it->adyacentes.end()) && !bandera2)
            {
                if(it2->devolver_adyacente() == destino)
                {
                    bandera2 == true;
                    it->adyacentes.erase(it2);
                }
                it2++;
            }
        }
        it++;
    }
}

template <typename C> void Grafo<C>::vaciar()
{
    typename list<Vertice>::iterator it = this->vertices.begin();
    while(it != this->vertices.end())
    {
        it->adyacentes.clear();
        it++;
    }
    this->vertices.clear();
}

#endif /* GRAFO_H_ */
