/*
 ============================================================================
 Name        : ConsolaFilesystem.c
 Author      : Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Consola del File System
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <commons/string.h>
#define STRLEN 128
/*void formatearMdfs();
 void eliminarArchivo();
 void renombrarArchivo();
 void moverArchivo();
 void crearDirectorio();
 void eliminarDirectorio();
 void renombrarDirectorio();
 void moverDirectorio();
 void copiarArchivoLocalAMdfs();
 void copiarArchivoMdfsALocal();
 void verBloques();
 void borrarBloque();
 void copiarBloque();
 void agregarNodo();
 void eliminarNodo();*/

int contarSpliteado(char**);
void darMd5();
char* darPalabra(char*, int);
int contarPalabras(char*);
int contarLetras(char*);

int main(void) {
	char* comando; //string_new() -> esto no funciona o no se hacerlo, el problema del strcmp que puse mas abajo se fue cuando cambie esto por un malloc(128)
	char* p;
	int x, i;
	system("clear");
	printf(
			"Para ver los todos los comandos use el comando ayuda\n***************************************************\n");
	while (1) {
		printf(">");
		comando = malloc(128);
		scanf("%128[^\n]s", comando);
		getchar();
		if (contarLetras(comando) > 128) {    // los comandos tienen limite de 128 caracteres (lo podemos agrandar)
			printf("el comando es muy largo\n");
		} else {
			x = contarPalabras(comando);
			if (!strcmp("ayuda", darPalabra(comando, 1))) { //cuando hace el strcmp me modifica el string
				printf("format/0\n");                       //original probar en debug comando: md5 /home/utnso/file1
				printf("remove/1\n");
				printf("rename/2\n");
				printf("move/2\n");
				printf("copytomdfs/1\n");
				printf("copytolocal/1\n");
				printf("md5/1\n");
				printf("verbloques/1\n");
				printf("rmbloque/2\n");
				printf("cpybloque/2\n");
				printf("addnodo/1\n");
				printf("rmnodo/1\n");
				printf("exit\n");
			} else if (!strcmp("exit", darPalabra(comando, 1))) {
				return 0;
			} else if (!strcmp(darPalabra(comando, 1), "format")) {
				if (x < 1) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te formateo\n");
			} else if (!strcmp(darPalabra(comando, 1), "remove")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te elimino %s\n", darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "rename")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te renombro %s a %s\n", darPalabra(comando, 2),
						darPalabra(comando, 3));
			} else if (!strcmp(darPalabra(comando, 1), "move")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te muevo %s a %s\n", darPalabra(comando, 2),
						darPalabra(comando, 3));
			} else if (!strcmp(darPalabra(comando, 1), "copytomdfs")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te copio %s al MDFS\n", darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "copytolocal")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te copio %s al FS local\n", darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "md5")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				darMd5(darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "verbloques")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te muestro los bloques de %s\n",
						darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "rmbloque")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te borro el bloque %s del archivo %s\n",
						darPalabra(comando, 3), darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "cpybloque")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te copio el bloque %s del archivo %s en\n",
						darPalabra(comando, 3), darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "addnodo")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te agrego el nodo %s\n", darPalabra(comando, 2));
			} else if (!strcmp(darPalabra(comando, 1), "rmnodo")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te saco el nodo %s\n", darPalabra(comando, 2));
			} else
				printf("no entiendo ese comando\n");
		}
		free(comando);
	}
	return 0;
}

int contarPalabras(char* str) {
	int palabras = 1, i = 0;
	while (str[i] != '\0') {
		if (str[i] == '\ ' && str[i + 1] != '\ ' && str[i + 1] != '\0')
			palabras++;
		i++;
	}
	return palabras;
}

int contarLetras(char* str){
	int i=0;
	while(str[i]!= '\0'){
		i++;
	}
	return i;
}

char* darPalabra(char* str, int pos) {
	int i = -1, j, k = 0;
	int primerLetra, largoPalabra;
	int ultimoEspacio;
	for (j = 0; j < pos; j++) {
		ultimoEspacio = i;
		i++;
		while (str[i] != '\ ' && str[i] != '\0') {
			i++;
		}
	}
	primerLetra = ultimoEspacio + 1;
	largoPalabra = i - ultimoEspacio;
	char* palabra = malloc(largoPalabra * (sizeof(char))); //no se como liberar esto, si es que hace falta
	while (k < largoPalabra) {
		palabra[k] = str[primerLetra + k];
		k++;
	}
	palabra[k - 1] = '\0';
	return palabra;
}

void darMd5(char* s) {
	char *md5 = strdup("openssl dgst -md5 -hex ");
	strcat(md5, s);
	system(md5);
}

int contarSpliteado(char** s) {
	int i = 0;
	while (s[i] != NULL) {
		i++;
	}
	return i;
}
