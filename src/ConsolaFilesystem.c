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

void darMd5();
char* darPalabra(char*, int);
int contarPalabras(char*);
int contarLetras(char*);

int main(void) {
	char* comando; //string_new() -> esto no funciona o no se hacerlo, el problema del strcmp que puse mas abajo se fue cuando cambie esto por un malloc(128)
	char** p;
	int x, i;
	system("clear");
	printf(
			"Para ver los todos los comandos use el comando ayuda\n****************************************************\n");
	while (1) {
		printf("> ");
		comando = malloc(128);
		scanf("%128[^\n]s", comando);
		getchar();
		if (contarLetras(comando) > 128) { // los comandos tienen limite de 128 caracteres (lo podemos agrandar)
			printf("el comando es muy largo\n");
		} else {
			x = contarPalabras(comando);
			p = malloc(x * (sizeof(char*))); // creo un puntero a puntero para guardar los punteros a las palabras
			for (i = 0; i < x; i++) { // que me crea darPalabra para poder hacerles free despues
				p[i] = darPalabra(comando, i + 1); // p[0] es el puntero a la primera palabra, p[1] a la segunda, y asi
			}
//			for (i = 0; i < x; i++) {
//				printf("%s\n",p[i]);
//			}
			if (!strcmp("ayuda", p[0])) { //      cuando hace el strcmp me modifica el string
				printf("format/0\n"); //          original probar en debug comando: md5 /home/utnso/file1
				printf("remove/1\n"); //          (se fue cuando cambie string_new() por malloc(128)
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
			} else if (!strcmp("exit", p[0])) {
				for (i = 0; i < x; i++) { // libera la memoria que aloco en darPalabra(2)
					free(p[i]); // aca a veces tira el free(): invalid next size (fast)
				}          // lo pude reproducir una sola vez despues de tirarle
				free(p);                  // un monton de comandos
				free(comando);
				return 0;
			} else if (!strcmp(p[0], "format")) {
				if (x < 1) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te formateo\n");
			} else if (!strcmp(p[0], "remove")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te elimino %s\n", p[1]);
			} else if (!strcmp(p[0], "rename")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te renombro %s a %s\n", p[1], p[2]);
			} else if (!strcmp(p[0], "move")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te muevo %s a %s\n", p[1], p[2]);
			} else if (!strcmp(p[0], "copytomdfs")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te copio %s al MDFS\n", p[1]);
			} else if (!strcmp(p[0], "copytolocal")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te copio %s al FS local\n", p[1]);
			} else if (!strcmp(p[0], "md5")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				darMd5(p[1]);
			} else if (!strcmp(p[0], "verbloques")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te muestro los bloques de %s\n", p[1]);
			} else if (!strcmp(p[0], "rmbloque")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te borro el bloque %s del archivo %s\n", p[2], p[1]);
			} else if (!strcmp(p[0], "cpybloque")) {
				if (x < 3) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te copio el bloque %s del archivo %s en\n", p[2], p[1]);
			} else if (!strcmp(p[0], "addnodo")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te agrego el nodo %s\n", p[1]);
			} else if (!strcmp(p[0], "rmnodo")) {
				if (x < 2) {
					printf("falta uno o mas parametros\n");
					continue;
				}
				printf("te saco el nodo %s\n", p[1]);
			} else
				printf("no entiendo ese comando\n");
		}
		for (i = 0; i < x; i++) { // libera la memoria que aloco en darPalabra(2)
			free(p[i]);  // aca a veces tira el free(): invalid next size (fast)
		}                  // lo pude reproducir una sola vez despues de tirarle
		free(p);                  // un monton de comandos
		free(comando);
	}
	return 0;
}

// cuenta los espacios y le suma uno
// funciona bien si pones muchos espacios juntos por error
int contarPalabras(char* str) {
	int palabras = 1, i = 0;
	while (str[i] != '\0') {
		if (str[i] == '\ ' && str[i + 1] != '\ ' && str[i + 1] != '\0')
			palabras++;
		i++;
	}
	return palabras;
}

//cuenta las letras hasta el \0
int contarLetras(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}
//te devuelve la palabra n° pos del string str
//tambien funciona si pones espacios de mas
char* darPalabra(char* str, int pos) {
	int i = 0, j, k = 0;
	int primerLetra, largoPalabra;
	int ultimoEspacio = -1;
	for (j = 0; j < pos; j++) {
		while (str[i] == '\ ') {
			ultimoEspacio = i;
			i++;
		}
		while (str[i] != '\ ' && str[i] != '\0') {
			i++;
		}
	}
	primerLetra = ultimoEspacio + 1;
	largoPalabra = i - ultimoEspacio;
	char* palabra = malloc(largoPalabra * (sizeof(char)));
	while (k < largoPalabra) {
		palabra[k] = str[primerLetra + k];
		k++;
	}
	palabra[k - 1] = '\0';
	return palabra;
}
//printea el md5 del archivo por system call
void darMd5(char* s) {
	char *md5 = malloc(128);
	strcpy(md5, "openssl dgst -md5 -hex ");
	strcat(md5, s);
	system(md5);
	free(md5);
}
