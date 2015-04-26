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

int contarSpliteado(char**);
void darMd5();

int main(void) {
	char* comando = string_new();
	char** spliteado = malloc(50);
	int x;
	system("clear");
	printf(
			"Para ver los todos los comandos use el comando ayuda\n***************************************************\n");
	while (1) {
		printf(">");
		scanf("%[^\n]s", comando);
		getchar();
		spliteado = string_split(comando, "\ ");
		x = contarSpliteado(spliteado);
		if (string_equals_ignore_case(spliteado[0], "ayuda")) {
			printf("format/0\n");
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
		} else if (string_equals_ignore_case(spliteado[0], "exit")) {
			return 0;
		} else if (string_equals_ignore_case(spliteado[0], "format")) {
			if (x < 1) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te formateo\n");
		} else if (string_equals_ignore_case(spliteado[0], "remove")) {
			if (x < 2) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te elimino %s\n", spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "rename")) {
			if (x < 3) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te renombro %s a %s\n", spliteado[1], spliteado[2]);
		} else if (string_equals_ignore_case(spliteado[0], "move")) {
			if (x < 3) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te muevo %s a %s\n", spliteado[1], spliteado[2]);
		} else if (string_equals_ignore_case(spliteado[0], "copytomdfs")) {
			if (x < 2) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te copio %s al MDFS\n", spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "copytolocal")) {
			if (x < 2) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te copio %s al FS local\n", spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "md5")) {
			if (x < 2) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			darMd5(spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "verbloques")) {
			if (x < 2) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te muestro los bloques de %s\n", spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "rmbloque")) {
			if (x < 3) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te borro el bloque %s del archivo %s\n", spliteado[2],
					spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "cpybloque")) {
			if (x < 3) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te copio el bloque %s del archivo %s en\n", spliteado[2],
					spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "addnodo")) {
			if (x < 2) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te agrego el nodo %s\n", spliteado[1]);
		} else if (string_equals_ignore_case(spliteado[0], "rmnodo")) {
			if (x < 2) {
				printf("falta uno o mas parametros\n");
				continue;
			}
			printf("te saco el nodo %s\n", spliteado[1]);
		} else
			printf("no entiendo ese comando");
	}
	return 0;
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
