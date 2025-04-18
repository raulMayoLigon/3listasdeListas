#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct infoPersona{
    char dni[9];
    char nombre[20];
};

struct nodoPersona {
    struct infoPersona informacion;
    struct nodoPersona *siguiente;
    struct nodoPersona *anterior;
};

struct listaPersonas {
    struct nodoPersona *primero;
    struct nodoPersona *ultimo;
};

struct infoVentanilla{
    int numeroVentanilla;
    char operacion[20];
};

struct nodoVentanilla {
    struct infoVentanilla informacion;
    struct listaPersonas personas; //lista doble de personas en la ventanilla
    struct nodoVentanilla *siguiente;
    struct nodoVentanilla *anterior;
};

struct listaVentanillas {
    struct nodoVentanilla *primero;
    struct nodoVentanilla *ultimo;
};

int menu (void);
void crearListaDelistas (struct listaVentanillas *listaVentanillas);
void addNodoVentanilla (struct listaVentanillas *listaVentanillas);
void addNodoPersona (struct listaPersonas *listaPersonas);
void visualizar (struct nodoVentanilla *primero);
void ponerseACola (struct listaVentanillas *listaVentanillas);
void atenderPersona (struct listaVentanillas *listaVentanillas);
void cerrarVentanilla (struct listaVentanillas *listaVentanillas);

int main(void) {
    struct listaVentanillas listaVentanillas;
    int opc;
    
    crearListaDelistas(&listaVentanillas);
    do {
        opc = menu();
        switch (opc)
        {
            case 1:
                visualizar(listaVentanillas.primero);
                break;
            case 2:
                atenderPersona(&listaVentanillas);
                break;
            case 3:
                cerrarVentanilla(&listaVentanillas);
                break;
            case 4:
                ponerseACola(&listaVentanillas);
                break;

                
            default:
                printf("Opción no válida vuelve a intentarlo.\n");
                break;
        }
    } while (opc != 0);
    return 0;
}

int menu(void)
{
    int opc;
    
    do
    {
        printf("\n1. Visualizar los numeros de ventanillas y el numero de personas a la cola");
        printf("\n2. Realizar un cambio de ventanilla.");
        printf("\n3. Visualizar todo.");
        printf("\n4. Ponerse a la cola.");
        printf("\n5. Atender a una persona.");
        printf("\n0. Salir");
        printf("\nIntroduce la opcion deseada... ");
        scanf("%d", &opc);
    } while ((opc<0) || (opc>5));
    return opc;
}

void visualizarPersonas (struct nodoPersona *primero){
    struct nodoPersona *recorre = primero;
    int contador = 1;
    if (primero == NULL){
        printf("\n\t No hay personas a la cola");
        return;
    }
    while (recorre != NULL){
        printf("\n\t %d: dni:%s nombre:%s",   contador,recorre->informacion.dni,recorre->informacion.nombre);
        contador += 1;
        recorre = recorre->siguiente;
    }
    printf("\n\n");
}

void visualizar (struct nodoVentanilla *primero){
    struct nodoVentanilla *recorre = primero;
    if (primero == NULL){
        printf("\n Lista de ventanillas vacía");
        return;
    }
    while (recorre != NULL){
        printf("\n Ventanilla n. %d: %s",recorre->informacion.numeroVentanilla,recorre->informacion.operacion);
        /*
        LLAMAR A LA FUNCIÓN QUE VISUALIZA LAS PERSONAS
        */
        visualizarPersonas(recorre->personas.primero);
        recorre = recorre->siguiente;
    }
    
}

void crearListaDelistas (struct listaVentanillas *listaVentanillas) {
    int n, i;
    
    //inicializo la lista
    listaVentanillas->primero = listaVentanillas->ultimo = NULL; //lista vacÌa
    printf("\n Introduce el numero de ventanillas que hay: ");scanf("%d", &n);
    
    for (i = 0;i < n; i++) {
        printf("\n Para la ventanilla %d",i+1);
        /*
        //LLAMAR A addNodoVentanilla
        */
        addNodoVentanilla(listaVentanillas);
    }
}

void addNodoVentanilla (struct listaVentanillas *listaVentanillas) {
    //añado por el final
    struct nodoVentanilla *nuevo;
    int numPersonas, i;
    
    //1. reservo
    nuevo = (struct nodoVentanilla *)malloc(sizeof(struct nodoVentanilla));
    if (nuevo == NULL) {
        printf("\n ERROR de memoria");
        return;
    }
    
    //2. relleno
    printf("\n Introduce la informaciÛn del numero de la ventanilla: ");
    scanf("%d", &nuevo->informacion.numeroVentanilla);
    printf("\n Introduce la operacion de la ventanilla: ");fflush(stdin);
    fpurge(stdin);
    scanf("%s", nuevo->informacion.operacion);
    
    nuevo->personas.primero = nuevo->personas.ultimo = NULL;
    
    //tb relleno las personas
    printf("\n Introduce el numero de personas: ");
    scanf("%d", &numPersonas);
    /*
     AÑADIR LAS PERSONAS A LA COLA QUE HAY AHORA
     LLAMANDO A addNodoPersona
     */
    for (i = 0; i < numPersonas; i++) {
            addNodoPersona(&nuevo->personas);
    }
    
    //3. Conecto con  la lista
    if (listaVentanillas->primero == NULL) {
        //lista vacia añado el primero
        listaVentanillas->primero = nuevo;
    }
    else {//no esta vacía, va despues del ultimo
        listaVentanillas->ultimo->siguiente = nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = listaVentanillas->ultimo;
    listaVentanillas->ultimo = nuevo;
}

void addNodoPersona (struct listaPersonas *listaPersonas) {
    struct nodoPersona *nuevo;
    //1. Reservo
    nuevo = (struct nodoPersona *)malloc(sizeof(struct nodoPersona));
    if (nuevo == NULL) {
        printf("\n ERROR de memoria");
        return;
    }
    
    //2.Relleno
    printf("\n DNI de la persona: ");fflush(stdin);
    fpurge(stdin);
    scanf("%s", nuevo->informacion.dni);
    printf("\n Nombre de la persona: ");fflush(stdin);
    fpurge(stdin);
    scanf("%s", nuevo->informacion.nombre);
    
    //3. Conecto
    if (listaPersonas->primero == NULL) {
        //lista vacia aÒado el primero
        listaPersonas->primero = nuevo;
    }
    else {//no esta vacÌa, va despues del ultimo
        listaPersonas->ultimo->siguiente = nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = listaPersonas->ultimo;
    listaPersonas->ultimo = nuevo;
}

void ponerseACola (struct listaVentanillas *listaVentanillas) {
    int numVentanilla;
    struct nodoVentanilla *recorre = listaVentanillas->primero;
    struct nodoPersona *nuevo;
    
    printf("\n Introduce el numero de ventanilla: ");
    scanf("%d", &numVentanilla);
    
    while (recorre != NULL && recorre->informacion.numeroVentanilla != numVentanilla) {
        recorre = recorre->siguiente;
    }
    
    if (recorre == NULL) {
        printf("\n La ventanilla no existe.\n");
        return;
    }
    
    addNodoPersona(&recorre->personas);
}

void atenderPersona (struct listaVentanillas *listaVentanillas) {
    int numVentanilla;
    struct nodoVentanilla *recorre = listaVentanillas->primero;
    
    printf("\n Introduce el numero de ventanilla: ");
    scanf("%d", &numVentanilla);
    
    while (recorre != NULL && recorre->informacion.numeroVentanilla != numVentanilla) {
        recorre = recorre->siguiente;
    }
    
    if (recorre == NULL) {
        printf("\n La ventanilla no existe.\n");
        return;
    }
    
    if (recorre->personas.primero == NULL) {
        printf("\n No hay personas en la cola de la ventanilla %d.\n", numVentanilla);
        return;
    }
    
    struct nodoPersona *atendido = recorre->personas.primero;
    printf("\n DNI:%s Nombre:%s atendido en la ventanilla numero %d.\n", atendido->informacion.dni, atendido->informacion.nombre, numVentanilla);
    
    recorre->personas.primero = atendido->siguiente;
    if (recorre->personas.primero != NULL) {
        recorre->personas.primero->anterior = NULL;
    } else {
        recorre->personas.ultimo = NULL;
    }
    
    free(atendido);
}

void cerrarVentanilla (struct listaVentanillas *listaVentanillas) {
    int numVentanilla;
    struct nodoVentanilla *recorre = listaVentanillas->primero;
    
    printf("\n Introduce el numero de ventanilla a cerrar: ");
    scanf("%d", &numVentanilla);
    
    while (recorre != NULL && recorre->informacion.numeroVentanilla != numVentanilla) {
        recorre = recorre->siguiente;
    }
    
    if (recorre == NULL) {
        printf("\n La ventanilla no existe.\n");
        return;
    }
    
    struct nodoPersona *aux;
    while (recorre->personas.primero != NULL) {
        aux = recorre->personas.primero;
        recorre->personas.primero = recorre->personas.primero->siguiente;
        free(aux);
    }
    recorre->personas.ultimo = NULL;
    
    printf("\n Ventanilla %d cerrada y cola eliminada.\n", numVentanilla);
}
