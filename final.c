#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct  nodo{
    struct nodo* der;
    struct nodo* izq;
    struct nodo* padre;

    int dato;
};

typedef struct nodo Nodo;


struct arbol{
    struct nodo* raiz;

};

typedef struct arbol spl;


Nodo* crearNodo(int dato){

    Nodo* nuevo = (Nodo*) malloc((sizeof(Nodo)));

    nuevo->dato = dato;
    nuevo->der = NULL;
    nuevo->izq = NULL;

    return nuevo;
}


void insertar(Nodo** raiz, Nodo* nuevo){
    if(*raiz == NULL){
        *raiz = nuevo;
    }
    else if((*raiz)->dato == nuevo->dato){
        return;
    }
    else if((*raiz)->dato < nuevo->dato){
        nuevo->padre = *raiz;
        insertar(&((*raiz)->der), nuevo);
    }
    else if((*raiz)->dato > nuevo->dato){
        nuevo->padre = *raiz;
        insertar(&((*raiz)->izq), nuevo);
    }

}

void subirARaiz(Nodo** raiz,spl** arbol){
    Nodo* padre = (*raiz)->padre;
    if(padre==NULL){
        return;
    }
    if(padre->padre == NULL){
        if(padre->izq == (*raiz)){
            Nodo* pad = (*raiz)->padre;
            Nodo* der = (*raiz)->der;
            Nodo* rai = (*raiz);

            if(der!=NULL)
            der->padre = pad;
            pad->izq = der;

            rai->padre = NULL;


            rai->der = pad;
            pad->padre = rai;
            raiz = &rai;

        }
        else if(padre->der == (*raiz)){
            Nodo* pad = (*raiz)->padre;
            Nodo* izq = (*raiz)->izq;
            Nodo* rai = (*raiz);

            if(izq!=NULL)
            izq->padre = pad;
            pad->der = izq;

            rai->padre = NULL;


            rai->izq = pad;
            pad->padre = rai;
            raiz = &rai;


        }
        (*arbol)->raiz = *raiz;
        return;
    }

    while(padre != (*arbol)->raiz){
        padre = (*raiz)->padre;

        if(padre->padre == NULL){
            if(padre->izq == (*raiz)){
                Nodo* pad = (*raiz)->padre;
                Nodo* der = (*raiz)->der;
                Nodo* rai = (*raiz);

                if(der!=NULL)
                der->padre = pad;
                pad->izq = der;

                rai->padre = NULL;


                rai->der = pad;
                pad->padre = rai;
                raiz = &rai;

            }
            else if(padre->der == (*raiz)){
                Nodo* pad = (*raiz)->padre;
                Nodo* izq = (*raiz)->izq;
                Nodo* rai = (*raiz);

                if(izq!=NULL)
                izq->padre = pad;
                pad->der = izq;

                rai->padre = NULL;


                rai->izq = pad;
                pad->padre = rai;
                raiz = &rai;


            }
            (*arbol)->raiz = *raiz;
            return;
        }

        if(padre->izq == (*raiz)){
            Nodo* pad = (*raiz)->padre;
            Nodo* der = (*raiz)->der;
            Nodo* rai = (*raiz);

            if(der!=NULL)
            der->padre = pad;
            pad->izq = der;

            rai->padre = pad->padre;
            if(pad->padre->der == pad){
                pad->padre->der = rai;
            }else{
                pad->padre->izq = rai;
            }

            rai->der = pad;
            pad->padre = rai;
            raiz = &rai;

        }
        else if(padre->der == (*raiz)){
            Nodo* pad = (*raiz)->padre;
            Nodo* izq = (*raiz)->izq;
            Nodo* rai = (*raiz);

            if(izq!=NULL)
            izq->padre = pad;
            pad->der = izq;

            rai->padre = pad->padre;
            if(pad->padre->der == pad){
                pad->padre->der = rai;
            }else{
                pad->padre->izq = rai;
            }

            rai->izq = pad;
            pad->padre = rai;
            raiz = &rai;


        }
        else if(padre == NULL){
            (*arbol)->raiz = (*raiz);
        }
    }
}



Nodo* buscar(Nodo** raiz, int dato, spl** arbol){
    if(*raiz == NULL){
        return NULL;
    }
    else if((*raiz)->dato == dato){
        Nodo* aux = *raiz;
        subirARaiz(raiz,arbol);

        return aux;
    }
    else if((*raiz)->dato < dato){
        return buscar(&((*raiz)->der), dato, arbol);
    }
    else if((*raiz)->dato > dato){
        return buscar(&((*raiz)->izq), dato, arbol);
    }
}



Nodo* eliminar(Nodo** raiz){
    if(*raiz==NULL){return NULL;}
    if((*raiz)->izq==NULL){
       if((*raiz)->der!=NULL){
           Nodo* temp = (*raiz);
           if((*raiz)->padre->der == (*raiz)){
              (*raiz)->padre->der = (*raiz)->der;
           }else{
               (*raiz)->padre->izq = (*raiz)->der;
           }

           temp->der= NULL;
           temp->padre= NULL;
            return temp;
       }else{
           Nodo* temp = (*raiz);
           temp->der= NULL;
           temp->padre= NULL;
           (*raiz) = NULL;
            return temp;
       }
    }

    return eliminar(&((*raiz)->izq));

}

void buscarParaEliminar(Nodo** raiz, int dato,spl** arbol){
    if(*raiz == NULL){
        return;
    }
    else if((*raiz)->dato == dato){
          Nodo* temp = eliminar(&((*raiz)->der));
        if(temp==NULL){
            if((*raiz)->izq==NULL){
                (*raiz)=NULL;

            }else{
                (*raiz) = (*raiz)->izq;
                (*raiz)->padre= NULL;
            }
            return;
        }
          (*raiz)->dato = temp->dato;
        

    }
    else if((*raiz)->dato < dato){
        buscarParaEliminar(&((*raiz)->der), dato,arbol);
    }
    else if((*raiz)->dato > dato){
        buscarParaEliminar(&((*raiz)->izq), dato,arbol);
    }
}

void modificar(Nodo** raiz, int dato, int nuevo,spl** arbol){
    if(*raiz == NULL){
        return;
    }
    else if((*raiz)->dato == dato){
        (*raiz)->dato = nuevo;
        subirARaiz(raiz,arbol);
    }
    else if((*raiz)->dato < dato){
        modificar(&((*raiz)->der), dato, nuevo,arbol);
    }
    else if((*raiz)->dato > dato){
        modificar(&((*raiz)->izq), dato, nuevo,arbol);
    }
}

char* graficar(Nodo** arbol){
    char* retorno = (char*)calloc(255, sizeof(char));
    char* grafo = "\n digraph grafo {\n node [style=filled]; label = \"Arbol SPL\"; color=green \n";


    GraficarArbol(arbol,&grafo);

    FILE *file;
    file = fopen("grafo.txt", "w+");
    fputs(grafo, file);
    fputs("}", file);



    fclose(file);

    system("dot -Tpng grafo.txt -o grafo.png  ");
    system("xdg-open grafo.png");
    return grafo;
}

void GraficarArbol(Nodo** raiz, char** retorno){
    if((*raiz) != NULL){
        GraficarArbol(&((*raiz)->izq),retorno);

        if((*raiz)->izq!=NULL){
            char* cad1;
            cad1 = (char*)calloc(255, sizeof(char));
            sprintf(cad1,"%d",(*raiz)->dato);
            char* cad2 =  (char*)calloc(255, sizeof(char));
            sprintf(cad2,"%d",(*raiz)->izq->dato);

            char* gr = (char*)calloc(255, sizeof(char));
            strcat(gr, *retorno);
            strcat(gr, cad1);
            strcat(gr, "->");
            strcat(gr, cad2);
            strcat(gr, "\n ");
            *retorno = gr;
        }
        if((*raiz)->der!=NULL){
            char* cad1 =  (char*)calloc(255, sizeof(char));
            sprintf(cad1,"%d",(*raiz)->dato);
            char* cad2 =  (char*)calloc(255, sizeof(char));
            sprintf(cad2,"%d",(*raiz)->der->dato);

            char* gr = (char*)calloc(255, sizeof(char));

            strcat(gr, *retorno);
            strcat(gr, cad1);
            strcat(gr, "->");
            strcat(gr, cad2);
            strcat(gr, "\n ");
            *retorno = gr;
        }
        GraficarArbol(&((*raiz)->der),retorno);
    }
}



int main()
{

    printf("201602797\n");
    spl* arbol = (spl*) malloc(sizeof(spl));
    arbol->raiz = NULL;

    int i=0;
    while (i != 6) {
        printf("-----Menu-----\n");
        printf("Agregar    -> 1\n");
        printf("Buscar     -> 2\n");
        printf("Modificar  -> 3\n");
        printf("Eliminar   -> 4\n");
        printf("Graficar   -> 5\n");
        printf("Salir      -> 6\n");
        printf("Agregar nodos-> 7\n");
        printf("***Ingrese un numero: ");

        scanf("%d",&i);
        if(i==1){
            int x =0;
            printf("Numero a ingresar: ");
            scanf("%d",&x);
            insertar(&(arbol->raiz), crearNodo(x));

        }else if(i==2){
            int x =0;
            printf("Numero a buscar: ");
            scanf("%d",&x);
            int dato = buscar(&(arbol->raiz), x,&arbol)->dato;

            printf("Dato buscado: %d",dato);

        }else if(i==3){
            int x =0;
            int y =0;
            printf("Numero a modificar: ");
            scanf("%d",&x);
            printf("Nuevo dato: ");
            scanf("%d",&y);
            modificar(&(arbol->raiz), x, y,&arbol);

        }else if(i==4){
            int x =0;
            printf("Numero a eliminar: ");
            scanf("%d",&x);
            buscar(&(arbol->raiz), x,&arbol);
            buscarParaEliminar(&(arbol->raiz), x,&arbol);

        }else if(i==5){
            graficar(&(arbol->raiz));
        }
        else if(i==7){
			
			
            insertar(&(arbol->raiz), crearNodo(1));
			insertar(&(arbol->raiz), crearNodo(2));
			insertar(&(arbol->raiz), crearNodo(5));
			insertar(&(arbol->raiz), crearNodo(20));
			insertar(&(arbol->raiz), crearNodo(10));
			insertar(&(arbol->raiz), crearNodo(15));
			insertar(&(arbol->raiz), crearNodo(8));
			insertar(&(arbol->raiz), crearNodo(67));
			insertar(&(arbol->raiz), crearNodo(35));
			insertar(&(arbol->raiz), crearNodo(40));
			insertar(&(arbol->raiz), crearNodo(37));
			insertar(&(arbol->raiz), crearNodo(3));
			insertar(&(arbol->raiz), crearNodo(9));

        }


        printf("\n\n");

    }

    return 0;
}

