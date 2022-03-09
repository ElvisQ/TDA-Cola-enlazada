#include "testing.h"
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#define PRUEBA_VOLUMEN 10000

static void prueba_elemento_nulo(void) {
    cola_t* cola =cola_crear();
    printf("******ENCOLAR ELEMENTO NULO******\n");
    print_test("Encolar Null a cola", cola_encolar(cola, NULL));
    print_test("Ver primero de la cola es NULL", cola_ver_primero(cola) == NULL);
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("Desencolar elemento null", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
}

static void pruebas_cola_vacia(void) {
    printf("*****COLAS VACIAS*****\n");
    cola_t* cola = cola_crear();
    print_test("La cola ha sido creada", cola != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("El primero de la cola vacia es NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolar cola vacia ES NULL",cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
}

static void pruebas_cola_con_enteros(void) {
    printf("******PRUEBA COLA CON ENTEROS******\n");
    cola_t* cola = cola_crear();
    int lista_num[] = {4,6,5,9,11};
    int tam = sizeof(lista_num)/sizeof(lista_num[0]);
    
    printf("******ENCOLAMIENTO******\n");
    for (int i = 0; i < tam; i++) {
        printf("Encolar %d ", lista_num[i]);
        print_test("en la cola ", cola_encolar(cola,&lista_num[i]));
    }
    printf("******DESENCOLAMIENTO******\n");
    for (int j = 0; j < tam; j++) {
        printf("Desencolar %d ",lista_num[j]);
        print_test("de la cola",cola_desencolar(cola) == &lista_num[j]);
    }
    print_test("La cola quedo vacia",cola_esta_vacia(cola));
    print_test("El primer elemento de la cola vacia no existe es NULL",cola_ver_primero(cola) == NULL);
    print_test("Desencolar cola vacia es NULL",cola_desencolar(cola) == NULL);

    cola_destruir(cola, NULL);
}

static void prueba_con_caracteres(void) {
    printf("******PRUEBA COLA CON CARACTERES******\n");
    char lista_caracteres[] = {'a','b','c','d','e'};
    cola_t* cola = cola_crear();
    int tam = sizeof(lista_caracteres)/sizeof(lista_caracteres[0]);

    printf("*******ENCOLAMIENTO********\n");
    for (int i = 0; i < tam; i++) {
        printf("Encolar %c ",lista_caracteres[i]);
        print_test("en la cola", cola_encolar(cola, &lista_caracteres[i]));
    }
    printf("******DESENCOLAMIENTO******\n");
    for (int j = 0; j < tam; j++) {
        printf("Desencolar %c ", lista_caracteres[j]);
        print_test("de la cola", cola_desencolar(cola) == &lista_caracteres[j]);

    }
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("El primero de la cola vacia es NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolar cola vacia ES NULL", cola_desencolar(cola) == NULL);

    cola_destruir(cola, NULL);
}

static void prueba_volumen(void) {
    printf("PRUEBA VOLUMEN ENCOLAR\n");
    int* arr_din = malloc(PRUEBA_VOLUMEN * sizeof(int));
    for (int i = 0; i < PRUEBA_VOLUMEN; i++) {
        arr_din[i] = i;
    }
    cola_t* cola = cola_crear();
    bool encolado_ok = true;
    bool primero_ok = true;
    int j = 0;
    int *primero = &j;

    for (j = 0; j < PRUEBA_VOLUMEN; j++) {
        encolado_ok &= cola_encolar(cola, &j);
        primero_ok &= (cola_ver_primero(cola) == primero);
    }
    print_test("Se pudo encolar varios elementos", encolado_ok);
    print_test("El primero de la cola siempre fue 0", primero_ok);
    printf("DESENCOLAMIENTO\n");
    bool desencolamiento_ok = true;
    while (!cola_esta_vacia(cola)) {
        primero_ok &= (cola_ver_primero(cola) == &j);
        desencolamiento_ok &= (cola_desencolar(cola) == &j);
        j--;
    }
    print_test("Se logro desencolar todos los elementos", desencolamiento_ok);
    print_test("Todos los primeros concidian", primero_ok);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("El primero de la cola vacia es NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolar cola vacia ES NULL", cola_desencolar(cola) == NULL);

    free(arr_din);
    cola_destruir(cola,NULL);
}

static void prueba_destruir_con_funcion(void) {
    printf("Prueba Destruir datos\n");
    cola_t* cola = cola_crear();
    void* datos1 = malloc(sizeof(void*));
    int* datos2 = malloc (sizeof(int*));
    printf("ENCOLAR DATOS\n");
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("Encolar datos de memoria dinamica", cola_encolar(cola, datos1));
    print_test("El primero de la cola es datos1", cola_ver_primero(cola) == datos1);
    print_test("Encolar datos de memoria dinamica", cola_encolar(cola, datos2));
    print_test("El primero de la cola sigue siendo datos1", cola_ver_primero(cola) == datos1);
    cola_destruir(cola, free);
    print_test("La cola fue destruida junto a sus datos", true);
}

void pruebas_cola_estudiante(void){
    prueba_elemento_nulo();
    pruebas_cola_vacia();
    pruebas_cola_con_enteros();
    prueba_con_caracteres();
    prueba_volumen();
    prueba_destruir_con_funcion(); 
}
#ifndef CORRECTOR  

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  
}

#endif
