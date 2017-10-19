#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#define Reservar_Memoria_Pila (Nodo_Pila *)malloc(sizeof(Nodo_Pila))
#define Reservar_Memoria_Cola (Nodo_Cola *)malloc(sizeof(Nodo_Cola))
#define Liberar_Espacio_memoria free 

using namespace std;

//variables globales
bool EsPila=false; //variable que define a que lista le asignamos las acciones

struct Nodo_Pila {
	int dato;
	Nodo_Pila *siguiente;
}*Ppila=NULL; //puntero global para manejo de pila

struct Nodo_Cola{
	int dato;
	Nodo_Cola *siguiente;
}*PCinicio=NULL,*PCfin=NULL; //punteros globales para manejo de cola

unsigned Tinicio,Tfin; //Variables para el calculo del tiempo de ejecucion

//
//Prototipos de menus
void menu_principal();//prototipo funcion menu principal para pila- cola
void menu_general();//prototipo funcion menu para acciones generales (generar datos - ver - editar - eliminar ..)
void menu_generar_datos();//prototipo funcion menu para generar datos de millones
void menu_ordenar_datos(); // opciones para escojer el metodo de ordenamiento
//Fin prototipos de menu

//prototipo funciones generales
int Pedir_Dato(); //pide un dato numerico
void Generar_Datos(int); //genera un numero de datos determinado
void Tomar_Tiempo_De_Inicio(); //establece el tiempo de arranque de un proceso
void Mostrar_Tiempo_Ejecucion(); //muestra el tiempo tomado desde el tiempo de arranque hasta el actual
void Quicksort(int *&,int,int); //algoritmo general para ordenamiento
void Salvar_datos_De_lista(); //guardar datos de la lista en un archivo txt
void Cargar_datos_De_archivo(); //cargar datos de archivo de texto a la lista 
//fin prototipos funciones generales

//prototipos de funciones para pila
void Agregar_A_Pila(int);
void Mostrar_Pila();
void Quitar_De_Pila();
void Buscar_En_Pila(int);
void Editar_En_Pila(int, int);
void Eliminar_Toda_la_Pila();
void Ordenar_Por_Burbuja_Pila();
void Ordenar_Por_Quicksort_Pila();
//Fin prototipos de funciones para pila

//prototipos de funciones para cola
void Agregar_A_Cola(int);
void Mostrar_Cola();
void Quitar_De_Cola();
void Buscar_En_Cola(int);
void Editar_En_Cola(int, int);
void Eliminar_Toda_la_Cola();
void Ordenar_Por_Burbuja_Cola();
void Ordenar_Por_Quicksort_Cola();
//Fin prototipos de funciones para cola


int main(int argc, char *argv[]) {
	menu_principal();
	return 0;
}

void menu_principal(){
	int opcion=0;
	system("cls");//comando para limpiar pantalla
	printf("\tPROYECTO 2 - ESTRUCTURA DE DATOS II\n");//titulo de menu general
	printf("\tJHONEIDER HINCAPIE - JOHN ALEJANDRO GIRALDO\n\n");//titulo de integrantes
	//opciones del menu
	printf("1. Pila\n");
	printf("2. Cola\n");
	printf("3. Salir\n\n");
	//bucle para manejo de datos ingresados
	do{
		printf("Escoja la opcion de lista que desee manejar : ");
		scanf("%d",&opcion);
		
		switch(opcion){
			case 1:
				EsPila=true;
				menu_general();
				break;
			case 2:
				EsPila=false;
				menu_general();
				break;
			case 3:
				exit(0);
				break;
			default:
				printf("No es una opcion valida\n");
				break;
		}
	} while(opcion!=3);
}

void menu_general(){
	int opcion=0;
	system("cls");//comando para limpiar pantalla
	if(EsPila)printf("\t**** PILA ****\n\n");else printf("\t**** COLA ****\n\n"); //titulo segun lista elegida
	//titulo de menu general
	//opciones del menu
	printf("1. Generar datos\n");
	printf("2. Cargar datos\n");
	printf("3. Agregar dato \n");
	printf("4. Quitar dato \n");
	if(EsPila)printf("5. Mostrar pila (ver) \n");else printf("5. Mostrar cola (ver) \n"); //opcion segun lista elegida
	printf("6. Buscar dato\n");
	if(EsPila)printf("7. Editar dato en pila \n");else printf("7. Editar dato en cola \n"); //opcion segun lista elegida
	if(EsPila)printf("8. Eliminar pila \n");else printf("8. Eliminar cola \n"); //opcion segun lista elegida
	printf("9. Salvar datos\n");
	printf("10. Ordenar datos\n");
	printf("11. Regresar\n\n");
	//bucle para manejo de datos ingresados
	do{
		printf("Escoja la opcion que desee ejecutar : ");
		scanf("%d",&opcion);
		int Datoviejo,DatoNuevo,num; //variables para editar dato en lista
		switch(opcion){
		case 1:
			menu_generar_datos();
			break;
		case 2:
			printf("Se cargaran los datos  del archivo backup.txt de la carpeta donde esta el programa\n");
			Cargar_datos_De_archivo();
			system("pause");
			menu_general();
			break;
		case 3:
			num = Pedir_Dato();
			if(EsPila)Agregar_A_Pila(num);else Agregar_A_Cola(num);
			system("pause");
			menu_general();
			break;
		case 4:
			if(EsPila)Quitar_De_Pila();else Quitar_De_Cola();
			system("pause");
			menu_general();
			break;
		case 5:
			if(EsPila)Mostrar_Pila();else Mostrar_Cola();
			system("pause");
			menu_general();
			break;
		case 6:
			num = Pedir_Dato();
			if(EsPila)Buscar_En_Pila(num);else Buscar_En_Cola(num);
			system("pause");
			menu_general();
			break;
		case 7:
			printf("Ingrese el numero de la lista que desee editar, y luego el nuevo dato.\n");
			Datoviejo = Pedir_Dato();
			DatoNuevo = Pedir_Dato();
			if(EsPila)Editar_En_Pila(Datoviejo,DatoNuevo);else Editar_En_Cola(Datoviejo,DatoNuevo);
			system("pause");
			menu_general();
			break;
		case 8:
			if(EsPila)Eliminar_Toda_la_Pila();else Eliminar_Toda_la_Cola();
			printf("\n La lista se ha eliminado. \n");
			system("pause");
			menu_general();
			break;
		case 9:
			Salvar_datos_De_lista();
			system("pause");
			menu_general();
			break;
		case 10:
			menu_ordenar_datos();
			break;
		case 11:
			menu_principal();
			break;
		default:
			printf("No es una opcion valida\n");
			break;
		}
	} while(opcion!=11);
}

void menu_generar_datos(){
	int opcion=0;
	system("cls");//comando para limpiar pantalla
	if(EsPila)printf("\t**** GENERAR DATOS - PILA ****\n\n");else printf("\t**** GENERAR DATOS - COLA ****\n\n"); //titulo segun lista elegida
	//opciones del menu
	printf("1. 1 Millon de datos\n");
	printf("2. 2 Millones de datos\n");
	printf("3. 5 Millones de datos\n");
	printf("4. 10 Millones de datos\n");
	printf("5. 20 Millones de datos\n");
	printf("6. cantidad determinada datos\n");
	printf("7. Regresar\n\n");
	//bucle para manejo de datos ingresados
	do{
		printf("Escoja la opcion que desee ejecutar : ");
		scanf("%d",&opcion);
		
		switch(opcion){
		case 1:
			Generar_Datos(1000000);
			break;
		case 2:
			Generar_Datos(2000000);
			break;
		case 3:
			Generar_Datos(5000000);
			break;
		case 4:
			Generar_Datos(10000000);
			break;
		case 5:
			Generar_Datos(20000000);
			break;
		case 6:
			Generar_Datos(Pedir_Dato());
			break;
		case 7:
			menu_general();
			break;
		default:
			printf("No es una opcion valida\n");
			break;
		}
	} while(opcion!=6);
}

void menu_ordenar_datos(){
	int opcion=0;
	system("cls");//comando para limpiar pantalla
	if(EsPila)printf("\t**** ORDENAR DATOS - PILA ****\n\n");else printf("\t**** ORDENAR DATOS - COLA ****\n\n"); //titulo segun lista elegida
	//opciones del menu
	//opciones del menu
	printf("1. Directo (Burbuja)\n");
	printf("2. Rapido (quick sort)\n");
	printf("3. Regresar\n\n");
	//bucle para manejo de datos ingresados
	do{
		printf("Escoja la opcion de lista que desee manejar : ");
		scanf("%d",&opcion);
		
		switch(opcion){
		case 1:
			 if(EsPila)Ordenar_Por_Burbuja_Pila(); else Ordenar_Por_Burbuja_Cola();
			break;
		case 2:
			if(EsPila)Ordenar_Por_Quicksort_Pila(); else Ordenar_Por_Quicksort_Cola();
			break;
		case 3:
			menu_general();
			break;
		default:
			printf("No es una opcion valida\n");
			break;
		}
	} while(opcion!=3);
}

void Agregar_A_Pila(int NDato){
	Nodo_Pila *Nuevo_Nodo = Reservar_Memoria_Pila;
	Nuevo_Nodo->dato=NDato;
	Nuevo_Nodo->siguiente=Ppila;
	Ppila=Nuevo_Nodo; //asigna el valor a la variable global, como es global no se pasa por parametro
}

void Agregar_A_Cola(int NDato){
	Nodo_Cola *Nuevo_Nodo = Reservar_Memoria_Cola;
	Nuevo_Nodo->dato=NDato;//se le asigna el nuevo valor
	Nuevo_Nodo->siguiente=NULL;//el que dentra sera ultimo y apuntara a null
	
	if(PCinicio==NULL){
		PCinicio=Nuevo_Nodo;
	}else{
		PCfin->siguiente=Nuevo_Nodo;//se direcciona el anterior ultimo al ahora nuevo que sera ultimo
	}
	
	PCfin=Nuevo_Nodo; //el fin pasa a ser el nuevo
}

void Quitar_De_Pila(){
	if(Ppila==NULL){
		printf("\n la pila esta vacia.\n");
	} else {
	Nodo_Pila *aux = Ppila; //creo una copia del dato inicial de la pila
	Ppila = aux->siguiente; //puntero de inicio pasa  a apuntar al siguiente del auxiliar
	Liberar_Espacio_memoria(aux);//elimina  el espacio del dato auxiliar
	printf("\nSe ha eliminado un elemento de la lista\n");
	}
}

void Quitar_De_Cola(){
	if(PCinicio==NULL){
		printf("\n la cola esta vacia.\n");
	}else{
		Nodo_Cola *aux=PCinicio;//creo una copia del dato inicial de la cola
		PCinicio= aux ->siguiente;//puntero de inicio pasa  a apuntar al siguiente del auxiliar
		Liberar_Espacio_memoria(aux);//elimina  el espacio del dato auxiliar
		if(PCinicio==NULL){// puntero del inicio  es  igual a null el puntero fin es igual 
			PCfin=NULL;
		}
		printf("\nSe ha eliminado un elemento de la lista\n");
	}
}

void Tomar_Tiempo_De_Inicio(){
	Tinicio = clock();	
}
void Mostrar_Tiempo_Ejecucion(){
	Tfin=clock();
	double tiempo = (double(Tfin - Tinicio)/CLOCKS_PER_SEC);
	printf("\nTiempo transcurrido : %g Seg.\n",tiempo);
}

int Pedir_Dato(){
	int res;
	printf("\n Por favor ingrese un numero : ");
	scanf("%d",&res);
	fflush(stdin);
	return res;
}

void Generar_Datos(int cantidadDatos){
	Tomar_Tiempo_De_Inicio();
	srand(time(NULL));
	int aleatorio =0;
	for(int i = 0; i<cantidadDatos ; i++){
		aleatorio = (rand() % ((1999999 + 1) - 1000000)); //genera numero aleatorio desde -1000000 hasta 1000000
		
		if(EsPila){
			Agregar_A_Pila(aleatorio);
		} else {
			Agregar_A_Cola(aleatorio);
		}
	}
	
	printf("Se han creado %d datos, satisfactoriamente.\n",cantidadDatos);
	Mostrar_Tiempo_Ejecucion();
	system("pause");
	menu_general();
}

void Mostrar_Pila(){
	Tomar_Tiempo_De_Inicio();
	Nodo_Pila *Aux = Ppila;
	printf("\n");
	
	if(Aux==NULL){
		printf("No hay datos en la pila.\n");
	}
	
	while(Aux!=NULL){
		printf("%d \n",Aux->dato);
		Aux=Aux->siguiente;
	}
	
	Mostrar_Tiempo_Ejecucion();
}

void Mostrar_Cola(){
	Tomar_Tiempo_De_Inicio();
	Nodo_Cola *Aux=PCinicio;
	printf("\n");
	
	if(Aux==NULL){
		printf("No hay datos en la cola.\n");
	}
	
	while(Aux!=NULL){
		printf("%d \n",Aux->dato);
		Aux=Aux->siguiente;
	}
	
	Mostrar_Tiempo_Ejecucion();
}

void Buscar_En_Pila(int Nbuscado){
	Tomar_Tiempo_De_Inicio();
	printf("\n");
	Nodo_Pila *Aux = Ppila;
	if(Aux==NULL){
		printf("\nLa pila no contiene elementos.\n");
	} else {
		bool encontrado = false;
		int posc = 1;
		while(Aux!=NULL){
			
			int dat = Aux->dato;
			if(dat==Nbuscado){
				encontrado = true;
				printf(" \t%d\n",Aux->dato);
				break;
			}
			posc++;
			Aux = Aux->siguiente;
		}
		
		if(encontrado)printf("El valor ha sido encontrado en la pila, en la posicion %d\n",posc);else printf("El valor no ha sido encontrado en la pila\n");
	}
	
	Mostrar_Tiempo_Ejecucion();
}

void Buscar_En_Cola(int Nbuscado){
	Tomar_Tiempo_De_Inicio();
	printf("\n");
	Nodo_Cola *Aux = PCinicio;
	if(Aux==NULL){
		printf("\nLa cola no contiene elementos.\n");
	} else {
		bool encontrado = false;
		int posc = 1;
		while(Aux!=NULL){
			
			int dat = Aux->dato;
			if(dat==Nbuscado){
				encontrado = true;
				printf(" \t%d\n",Aux->dato);
				break;
			}
			posc++;
			Aux = Aux->siguiente;
		}
		
		if(encontrado)printf("El valor ha sido encontrado en la cola,en la posicion %d \n",posc);else printf("El valor no ha sido encontrado en la cola\n");
	}
	
	Mostrar_Tiempo_Ejecucion();
}

void Editar_En_Pila(int Nbuscado, int NDato){

	Tomar_Tiempo_De_Inicio();
	printf("\n");
	Nodo_Pila *Aux = Ppila;
	if(Aux==NULL){
		printf("\nLa pila no contiene elementos.\n");
	} else {
		bool encontrado = false;

		while(Aux!=NULL){
			
			int dat = Aux->dato;
			if(dat==Nbuscado){
				encontrado = true;
				Aux->dato = NDato;
				break;
			}

			Aux = Aux->siguiente;
		}
		
		if(encontrado)printf("El valor %d ha sido modificado por el nuevo valor : %d \n",Nbuscado,NDato);else printf("El valor no ha sido encontrado en la pila, por lo tanto no se ha realizado alguna modificacion\n");
	}
	
	Mostrar_Tiempo_Ejecucion();
}

void Editar_En_Cola(int Nbuscado, int NuevoDato){
	Tomar_Tiempo_De_Inicio();
	printf("\n");
	Nodo_Cola *Aux = PCinicio;
	if(Aux==NULL){
		printf("\nLa cola no contiene elementos.\n");
	} else {
		bool encontrado = false;
		while(Aux!=NULL){
			
			int dat = Aux->dato;
			if(dat==Nbuscado){
				encontrado = true;
				Aux->dato = NuevoDato;
				break;
			}
			
			Aux = Aux->siguiente;
		}
		
		if(encontrado)printf("El valor %d ha sido modificado por el nuevo valor : %d \n",Nbuscado,NuevoDato);else printf("El valor no ha sido encontrado en la cola, por lo tanto no se ha realizado alguna modificacion\n");
	}
	
	Mostrar_Tiempo_Ejecucion();
}

void Eliminar_Toda_la_Pila(){
	Tomar_Tiempo_De_Inicio();
	Nodo_Pila *Aux = Ppila;
	printf("\n");
	
	if(Aux==NULL){
		printf("No hay datos en la pila.\n");
	}
	
	while(Aux!=NULL){
		Ppila=Aux->siguiente;
		Liberar_Espacio_memoria(Aux);
		Aux=Ppila;
	}
	
	Mostrar_Tiempo_Ejecucion();
}

void Eliminar_Toda_la_Cola(){
	Tomar_Tiempo_De_Inicio();
	Nodo_Cola *Aux=PCinicio;
	printf("\n");
	
	if(Aux==NULL){
		printf("No hay datos en la cola.\n");
	}
	
	while(Aux!=NULL){
		PCinicio = Aux->siguiente;
		Liberar_Espacio_memoria(Aux);
		Aux=PCinicio;
	}
	
	PCfin=PCinicio;
	
	Mostrar_Tiempo_Ejecucion();
}

void Ordenar_Por_Burbuja_Pila(){
	Tomar_Tiempo_De_Inicio();
	Nodo_Pila *Aux1 = Ppila;
	
	if(Aux1!=NULL){
		Nodo_Pila *Aux2 = Aux1->siguiente;
		
		if(Aux2!=NULL){  //si aux2 es NULL QUIERE DECIR QUE HAY UN SOLO DATO EN LA LISTA, POR LO QUE ORDENAR SERIA ILOGICO
			int piv,pos;
			while(Aux1!=NULL){
				while(Aux2!=NULL){
					piv = Aux1->dato;
					pos = Aux2->dato;

					if(piv > pos){
						Aux2->dato=piv;
						Aux1->dato=pos;
					}
					Aux2=Aux2->siguiente;
				}
				Aux1=Aux1->siguiente;
				if(Aux1!=NULL)Aux2=Aux1->siguiente;
			}
			
			
			
			printf("Datos de pila ordenados correctamente (por burbuja).\n");
		
		} else {
				printf("Solo hay un dato en la pila.\n");
			}
		Mostrar_Tiempo_Ejecucion();
		
	} else {
		printf("No hay datos en la pila.\n");
	}
	
	system("pause");
	menu_general();
}

void Ordenar_Por_Burbuja_Cola(){
	Tomar_Tiempo_De_Inicio();
	Nodo_Cola *Aux1 = PCinicio;
	
	if(Aux1!=NULL){
		Nodo_Cola *Aux2 = Aux1->siguiente;
		
		if(Aux2!=NULL){  //si aux2 es NULL QUIERE DECIR QUE HAY UN SOLO DATO EN LA LISTA, POR LO QUE ORDENAR SERIA ILOGICO
			int piv,pos;
			while(Aux1!=NULL){
				while(Aux2!=NULL){
					piv = Aux1->dato;
					pos = Aux2->dato;
					
					if(piv > pos){
						Aux2->dato=piv;
						Aux1->dato=pos;
					}
					Aux2=Aux2->siguiente;
				}
				Aux1=Aux1->siguiente;
				if(Aux1!=NULL)Aux2=Aux1->siguiente;
			}
			
			
			
			printf("Datos de cola ordenados correctamente (por burbuja).\n");
			
		} else {
			printf("Solo hay un dato en la cola.\n");
		}
		Mostrar_Tiempo_Ejecucion();
		
	} else {
		printf("No hay datos en la cola.\n");
	}
	
	system("pause");
	menu_general();
}

void Ordenar_Por_Quicksort_Pila (){
	Tomar_Tiempo_De_Inicio();
	Nodo_Pila *Aux = Ppila;
	int Ndatos=0;
	while(Aux != NULL){ //cuenta los datos en pila
		Ndatos++;
		Aux=Aux->siguiente;
	}
	
	if(Ndatos==0){
		printf("No hay datos en la pila. \n");
	} else if(Ndatos==1){
		printf("La pila solo cuenta con un dato. \n");
	}else {
		int *Parreglo = (int*)malloc(sizeof(int) * Ndatos);
		Aux=Ppila;
		int pos=0;
		while(Aux != NULL){ //llena el arreglo
		   *(Parreglo + pos) = Aux->dato;
		   pos++;
			Aux=Aux->siguiente;
		}
		
		Quicksort(Parreglo,0,Ndatos); //ordenar
		
		Aux=Ppila; 
		pos=0; 
		while(Aux != NULL){ //llena el arreglo
			Aux->dato = *(Parreglo + pos);
			pos++;
			Aux=Aux->siguiente;
		}
		
		Liberar_Espacio_memoria(Parreglo);
		printf("Datos de pila ordenados correctamente (por quick sort).\n");
	}

	Mostrar_Tiempo_Ejecucion();
	
	system("pause");
	menu_general();
}

void Ordenar_Por_Quicksort_Cola (){
	Tomar_Tiempo_De_Inicio();
	Nodo_Cola *Aux = PCinicio;
	int Ndatos=0;
	while(Aux != NULL){ //cuenta los datos en pila
		Ndatos++;
		Aux=Aux->siguiente;
	}
	
	if(Ndatos==0){
		printf("No hay datos en la cola. \n");
	} else if(Ndatos==1){
		printf("La cola solo cuenta con un dato. \n");
	}else {
		int *Parreglo = (int*)malloc(sizeof(int) * Ndatos);
		Aux=PCinicio;
		int pos=0;
		while(Aux != NULL){ //llena el arreglo
			*(Parreglo + pos) = Aux->dato;
			pos++;
			Aux=Aux->siguiente;
		}
		
		Quicksort(Parreglo,0,Ndatos); //ordenar
		
		Aux=PCinicio; 
		pos=0; 
		while(Aux != NULL){ //pasa datos a la lista
			Aux->dato = *(Parreglo + pos);
			pos++;
			Aux=Aux->siguiente;
		}
		
		Liberar_Espacio_memoria(Parreglo);
		printf("Datos de cola ordenados correctamente (por quick sort).\n");
	}
	
	Mostrar_Tiempo_Ejecucion();
	
	system("pause");
	menu_general();
}

void Quicksort(int *&arreglo,int piz,int pde){
	int i = piz,j = pde, aux; //declara variables y establece el puntero izquierdo y el derecho
	int p = arreglo[(piz + pde) / 2]; //establece el pivote en la mitad del arreglo
	
	while(i <= j){
		while(arreglo[i] < p) i++; //avanza en la parte izquiera los menores
		while(arreglo[j] > p) j--; //avanza en la parte derecha los mayores
		
		if( i<= j){ //compara los 2 numeros posicionados anteriormente
			aux = arreglo[i]; 		//
			arreglo[i] = arreglo[j]; //se hace el cambio de posicion
			arreglo[j]=aux;			//
			i++; j--; //se realiza una comparacion simetrica siguiente
		}
	}
	
	if(piz < j) Quicksort(arreglo,piz,j); //se parte el arreglo en 2 y se ordena la parte izquierda
	if(i < pde) Quicksort(arreglo,i,pde); //se hace lo mismo que el anterior pero en la parte derecha
}

void Salvar_datos_De_lista(){
	Tomar_Tiempo_De_Inicio();
	ofstream archivo;
	
	archivo.open("backup.txt",ios::out);
	
	if(archivo.fail()){
		printf("No se pudo acceder al archivo. por favor intente de nuevo.\n");
	}
	else {
		if(EsPila){
			Nodo_Pila *Aux= Ppila;
			bool primero=true;
			while(Aux!=NULL){
				if(!primero){archivo<<endl<<Aux->dato;}else{
					archivo<<Aux->dato;
				}
				Aux=Aux->siguiente;
				primero=false;
			}
			
			archivo.close();
			printf("El archivo backup.txt, se ha creado correctamente.\n");
		}else{
			Nodo_Cola *Aux= PCinicio;
			bool primero=true;
			while(Aux!=NULL){
				if(!primero){archivo<<endl<<Aux->dato;}else{
					archivo<<Aux->dato;
				}
				Aux=Aux->siguiente;
				primero=false;
			}
			
			archivo.close();
			printf("El archivo backup.txt, se ha creado correctamente.\n");
		}
	}
	Mostrar_Tiempo_Ejecucion();
}

void Cargar_datos_De_archivo(){
	Tomar_Tiempo_De_Inicio();
	ifstream archivo;
	
	archivo.open("backup.txt",ios::in);
	
	if(archivo.fail()){
		printf("No se pudo acceder al archivo. por favor intente de nuevo.\n");
	}
	else {
		int dato;
		string cadena;
		if(EsPila){
			int cont=0;
			while(!archivo.eof()){
				getline(archivo,cadena);	//pasa a la siguiente linea del archivo
				dato = atoi(cadena.c_str());	//convierte el numero del archivo txt , de cadena a int
				Agregar_A_Pila(dato);	//agrega a cola el numero de la linea actual del archivo txt
				cont++;	//cuenta los datos pasados
			}
			
			archivo.close();	//cierra el archivo
			printf("Se han cargado %d dato(s) correctamente.\n",cont);//confirma la transferencia de datos a la lista
		}else{
			int cont=0;
			while(!archivo.eof()){
				getline(archivo,cadena);	//pasa a la siguiente linea del archivo
				dato = atoi(cadena.c_str()); 	//convierte el numero del archivo txt , de cadena a int
				Agregar_A_Cola(dato); //agrega a cola el numero de la linea actual del archivo txt
				cont++; //cuenta los datos pasados
			}
			
			archivo.close();	//cierra el archivo
			printf("Se han cargado %d dato(s) correctamente.\n",cont);//confirma la transferencia de datos a la lista
		}
	}
	Mostrar_Tiempo_Ejecucion();
}




