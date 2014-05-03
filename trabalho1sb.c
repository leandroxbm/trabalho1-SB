#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct lista
{
    char mnemonico[100];
    int operandos;
    int codigo;
    int tamanho;

    struct lista* prox;
};

struct listaEQU
{
    char chave[100];
    char valor[100];

    struct listaEQU *prox;
};

typedef struct lista Lista;
typedef struct listaEQU ListaEQU;

Lista* inicializa (void);
ListaEQU* inicializaEqu (void);
Lista* insere (Lista* , char[], int, int, int);
ListaEQU* insereListaEqu (ListaEQU* ,char [], char []);
ListaEQU  * pesquisarEqu(ListaEQU* , char []);
void imprime (Lista*);
void iprimeEqu (ListaEQU *);
Lista* criaListaInstrucao ();
Lista* criaListaDiretiva ();
void liberaLista (Lista*);
void liberaListaEqu (ListaEQU*);
FILE* abrirArquivoAsm();
FILE * abrirArquivoPre();
void  fecharArquivo(FILE *);
void preProcessamento(FILE *,FILE *);

int main (int argc, char *argv[])
{

    ///--------------------------------CRIAR LISTAS
    /*   Lista *instrucao;
       Lista *diretiva;

       instrucao = criaListaInstrucao();
       imprime(instrucao);

       diretiva = criaListaDiretiva();
       imprime(diretiva);

       liberaLista(instrucao);
       liberaLista(diretiva);
    */
    ///------------------------------ PRE PROCESSAMENTO
    FILE *fp,*fp2;

    //abrir o arquivo
    fp = abrirArquivoAsm();
    fp2 = abrirArquivoPre();
    preProcessamento(fp,fp2);








    fecharArquivo(fp);
    fecharArquivo(fp2);
    //---------------------------------------------------------
    return 0;
}

/* função de inicialização: retorna uma lista vazia */
Lista* inicializa (void)
{
    return NULL;
}

ListaEQU* inicializaEqu (void)
{
    return NULL;
}

/* inserção no início: retorna a lista atualizada */
Lista* insere (Lista* lista, char mnemonico[], int operandos, int codigo, int tamanho)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    strcpy(novo->mnemonico,mnemonico);
    novo->operandos = operandos;
    novo->codigo = codigo;
    novo->tamanho = tamanho;
    novo->prox = lista;
    return novo;
}

/* função imprime: imprime valores dos elementos */
void imprime (Lista* l)
{
    Lista* p; /* variável auxiliar para percorrer a lista */
    printf ("\n");
    for (p = l; p != NULL; p = p->prox)
    {
        printf("%s\t%d\t%d\t%d\n", p->mnemonico, p->operandos, p->codigo, p->tamanho );
    }
}

void liberaLista (Lista* l)
{
    Lista* p = l;
    while (p != NULL)
    {
        Lista* t = p->prox; /* guarda referência para o próximo elemento*/
        free(p); /* libera a memória apontada por p */
        p = t; /* faz p apontar para o próximo */
    }
}

Lista* criaListaInstrucao ()
{
    Lista * instrucao;
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


Lista* criaListaDiretiva ()
{
    Lista * diretiva;
    diretiva = inicializa();

    diretiva = insere(diretiva, "if",      1, 0, 0);
    diretiva = insere(diretiva, "equ",     1, 0, 999999);
    diretiva = insere(diretiva, "const",   1, 0, 1);
    diretiva = insere(diretiva, "space",   1, 0, 0);
    diretiva = insere(diretiva, "section", 1, 0, 0);

    return diretiva;

}
//ALTERAR NO FUTURO PARA ABRIR O ARQUIVO PELO NOME E RETORNAR O PONTEIRO FP
FILE * abrirArquivoAsm()
{
    FILE *fp;

    fp = fopen ("temp2.asm","r");
    if (fp!=NULL)
    {
       // printf("\nABRIU ARQUIVO\n");
    }
    else
    {
      //  printf ("\nArquivo nao abriu");
        exit(1);
    }

    return fp;
}

FILE * abrirArquivoPre()
{
    FILE *fp;

    fp = fopen ("teste.pre","w");
    if (fp!=NULL)
    {
       // printf("\nABRIU ARQUIVO\n");
    }
    else
    {
      //  printf ("\nArquivo nao abriu");
        exit(1);
    }

    return fp;
}

//FECHAR ARQUIVO
void  fecharArquivo(FILE *fp)
{
    fclose(fp);
}

ListaEQU* insereListaEqu (ListaEQU* lista,char chave[], char valor[])
{
    ListaEQU* novo = (ListaEQU*) malloc(sizeof(ListaEQU));
    strcpy(novo->chave,chave);
    strcpy(novo->valor,valor);
    novo->prox = lista;
    return novo;
}

void imprimeEqu (ListaEQU* l)
{
    ListaEQU* p; /* variável auxiliar para percorrer a lista */
    printf ("\n");
    for (p = l; p != NULL; p = p->prox)
    {
        printf("chave: %s\tvalor: %s\n", p->chave, p->valor );
    }
}

void liberaListaEqu (ListaEQU* l)
{
    ListaEQU* p = l;
    while (p != NULL)
    {
        ListaEQU* t = p->prox; /* guarda referência para o próximo elemento*/
        free(p); /* libera a memória apontada por p */
        p = t; /* faz p apontar para o próximo */
    }
}

ListaEQU* pesquisarEqu(ListaEQU* l, char chave[])
{
    ListaEQU* p; /* variável auxiliar para percorrer a lista */
    for (p = l; p != NULL; p = p->prox)
    {
       if( strcmp(chave, p->chave) ) //0 e false do if, 0 e igual do strcmp
       {}
       else{
        return p;
       }
    }
    return NULL;
}

//FAZER O PRE PROCESSAMENTO DO ARQUIVO ASM
void preProcessamento(FILE *fp, FILE *fp2)
{
    long lSize;
    char * buffer,*buffer2;
    char palavra[100],chave[100], valor[100];
    size_t result;
    int i, j=0,k,l;
    ListaEQU *equ;

//   short controle=0; //variavel para controlar se houve linha antes do comentario, se nao houve nao e necessario \n

    //pegar o tamanhgo do arquivo
    fseek (fp , 0 , SEEK_END);
    lSize = ftell (fp);

    // alocar memoria
    buffer = (char*) malloc (sizeof(char)*lSize);
    buffer2 =(char*) malloc (sizeof(char)*lSize);


    if (buffer == NULL||buffer2 == NULL)
    {
        exit (2);
    }

    // copiar arquivo para buffer
    rewind (fp);
    result = fread (buffer,1,lSize,fp);

    //passar todas as letras para maiusculo
    for(i=0; i<lSize; i++)
    {
        buffer[i]=toupper(buffer[i]);
    }


    //tirar comentarios ----------------------------------------------------------------------------------------------------------------------------------------
    for( i=0; i<result; i++)
    {
        //se for ; e comentario,
        if(buffer[i]==';')
        {
            //anda o ponteiro ate o fim da linha
            while (buffer[i]!='\n')
            {
                i++;
            }
            if(1/*SE A PASSADA NO PRE JA E \N NAO DEVE ENTRAR NESSE IF*/) //  <*************************************************************************************************>
            {
                buffer2[j] = '\n';
                j++;
                //fprintf(fp2,"\n");
            }
        }


        else
        {
            buffer2[j] = buffer[i];
            j++;
            //fprintf(fp2,"%c",buffer[i]);
        }
    }
    buffer2[j]='\0';

    puts(buffer2);



    //procurar EQU e criar lista ---------------------------------------------------------------------------------------------------------------------------------
    i=0;
    j=0;
    k=0;
    l=0;

    equ = inicializaEqu();

    int tamanhoString = strlen(buffer2);

    while (i<tamanhoString)
    {
        l = k;
        while ((buffer2[i]!='\n') && (buffer2[i]!=' ') &&(buffer2[i]!=':'))
        {
            palavra[j]=buffer2[i];
            buffer[k] = buffer2[i];
            i++;
            j++;
            k++;
        }
        palavra[j] = '\0';
        j=0;

        //ver se a palavra seguinte e EQU
        if ((buffer2[i+2]=='E') && (buffer2[i+3]=='Q') && (buffer2[i+4]=='U'))
        {
            strcpy(chave, palavra);
            printf ("\nchave:");
            puts(chave);
            i = i+6;
            while (buffer2[i]!='\n' )
            {
                palavra[j] = buffer2[i];
                i++;
                j++;
            }
            palavra[j] = '\0';
            j=0;
            strcpy(valor, palavra);
            printf ("\nvalor:");
            puts(valor);




            equ = insereListaEqu(equ,chave,valor);
            k = l;

        }
        else
        {
            buffer[k] = buffer2[i];
            k++;
            i++;
        }
    }




    buffer[k]='\0';


    printf ("\n\n\n******************** buffer com a tabela ja montada\n");
    puts(buffer);
    printf ("\n\n\n******************** tabela\n");
    imprimeEqu(equ);
    printf ("\n\n\n******************** ok\n");

    //substituir usando tabela EQU ------------------------------------------------------------------------------------------------------------------------------
    tamanhoString = strlen(buffer);
    strcpy(palavra, "");
    i=0;
    j=0;
    k=0;
    l=0;

    ListaEQU *resultado;

printf ("\nTESTE***********************\n");

     while (i<tamanhoString)
    {
         strcpy(palavra, "");
         j=0;
        while ((buffer2[i]!='\n') && (buffer2[i]!=' ') &&(buffer2[i]!=':'))
        {
            palavra[j]=buffer[i];
            i++;
            j++;
        }
        palavra[j] = '\0';


        //ver se a palavra esta na tabela
        resultado = pesquisarEqu(equ, palavra);
        if (resultado == NULL)
        {

            fprintf(fp2, "%s", palavra);
            puts(palavra);
        }
        else
        {

            fprintf(fp2, "%s", resultado->valor);
            puts(resultado->valor);
        }

        //continua
        if(i<=tamanhoString){
         fprintf(fp2, "%c", buffer[i]);
         printf ("%c", buffer[i]);
         i++;}
    }

// desalocar -----------------------------------------------------------------------------------------------------------------------------------------------------
    liberaListaEqu(equ);
    free (buffer);
    free (buffer2);

}
