#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct lista {
 char mnemonico[10];
 int operandos;
 int codigo;
 int tamanho;

 struct lista* prox;
};

typedef struct lista Lista;

Lista* inicializa (void);
Lista* insere (Lista* , char[], int, int, int);
void imprime (Lista*);
Lista* criaListaInstrucao (Lista*);
Lista* criaListaDiretiva (Lista*);
void liberaLista (Lista*);

int main (int argc, char *argv[]){
    Lista *instrucao;
    Lista *diretiva;

    instrucao = criaListaInstrucao(instrucao);
    imprime(instrucao);

    diretiva = criaListaDiretiva(diretiva);
    imprime(diretiva);

    liberaLista(instrucao);
    liberaLista(diretiva);
    return 0;
}

/* função de inicialização: retorna uma lista vazia */
Lista* inicializa (void){
    return NULL;
}

/* inserção no início: retorna a lista atualizada */
Lista* insere (Lista* lista, char mnemonico[], int operandos, int codigo, int tamanho){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    strcpy(novo->mnemonico,mnemonico);
    novo->operandos = operandos;
    novo->codigo = codigo;
    novo->tamanho = tamanho;
    novo->prox = lista;
    return novo;
}

/* função imprime: imprime valores dos elementos */
void imprime (Lista* l){
    Lista* p; /* variável auxiliar para percorrer a lista */
    for (p = l; p != NULL; p = p->prox){
        printf("%s\t%d\t%d\t%d\n", p->mnemonico, p->operandos, p->codigo, p->tamanho );
    }
}

void liberaLista (Lista* l){
    Lista* p = l;
    while (p != NULL) {
        Lista* t = p->prox; /* guarda referência para o próximo elemento*/
        free(p); /* libera a memória apontada por p */
        p = t; /* faz p apontar para o próximo */
    }
}

Lista* criaListaInstrucao (Lista* instrucao){

    instrucao = inicializa();

    instrucao = insere(instrucao, "stop",   0, 14, 1);
    instrucao = insere(instrucao, "output", 1, 13, 2);
    instrucao = insere(instrucao, "input",  1, 12, 2);
    instrucao = insere(instrucao, "store",  1, 11, 2);
    instrucao = insere(instrucao, "load",   1, 10, 2);
    instrucao = insere(instrucao, "copy",   2, 9,  3);
    instrucao = insere(instrucao, "jmpz",   1, 8,  2);
    instrucao = insere(instrucao, "jmpp",   1, 7,  2);
    instrucao = insere(instrucao, "jmpn",   1, 6,  2);
    instrucao = insere(instrucao, "jmp",    1, 5,  2);
    instrucao = insere(instrucao, "div",    1, 4,  2);
    instrucao = insere(instrucao, "mult",   1, 3,  2);
    instrucao = insere(instrucao, "sub",    1, 2,  2);
    instrucao = insere(instrucao, "add",    1, 1,  2);

    return instrucao;

}


Lista* criaListaDiretiva (Lista* diretiva){

    diretiva = inicializa();

    diretiva = insere(diretiva, "if",      1, 0, 0);
    diretiva = insere(diretiva, "equ",     1, 0, 999999);
    diretiva = insere(diretiva, "const",   1, 0, 1);
    diretiva = insere(diretiva, "space",   1, 0, 0);
    diretiva = insere(diretiva, "section", 1, 0, 0);

    return diretiva;

}
