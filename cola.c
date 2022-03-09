#include <stdbool.h>
#include <stdlib.h>
#include "cola.h"

typedef struct nodo {
    void* dato;
    struct nodo* siguiente;
} nodo_t;

struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
};

nodo_t* crear_nodo(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) {
        return NULL;
    }
    nodo->dato = valor;
    nodo->siguiente = NULL;
    return nodo;

}

cola_t* cola_crear(void) {
    cola_t* cola = malloc(sizeof(cola_t));
    if (cola == NULL) {
        return NULL;
    }
    cola->primero =  NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->primero == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t* nodo = crear_nodo(valor);
    if (nodo == NULL) {
        return false;
    }
    if (cola_esta_vacia(cola)) {
        cola->primero = nodo;
    } else {
        cola->ultimo->siguiente = nodo;
    }
    cola->ultimo = nodo;
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    return cola->primero->dato;
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    void* dato = cola->primero->dato;
    nodo_t* nodo_dato = cola->primero;
    if (cola->primero == cola->ultimo) {
        cola->primero = NULL;
        cola->ultimo = NULL;
    } else {
        cola->primero = cola->primero->siguiente;
    }
    free(nodo_dato);
    return dato;

}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
    void* dato;
    while (!cola_esta_vacia(cola)) {
        dato = cola_desencolar(cola);
        if (destruir_dato != NULL) {
            destruir_dato(dato);
        }
    }
    free(cola);
}
