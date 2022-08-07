#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct arv { // ESTRUTURA DE CADA NO DA ARVORE
int RA;
char nome[30];
float nota1;
float nota2;
float nota3;
float media;
struct arv* esq;
struct arv* dir;
}TArv;

typedef TArv *PArv;

PArv pedindo_dados(PArv arv);
PArv insere_ABB (PArv arv, int reg_aluno, char nome[], float a, float b, float c);
PArv libera (PArv a);
void imprimeIn (PArv a, int nivel);
void Mostrar_dados (PArv arv);
void buscando_nota(PArv r, int vetor[]);
void buscando_RA (PArv arv, int reg_aluno);
PArv retira (PArv r, int reg_aluno);
void verifica_RA (PArv arv, int reg_aluno);


//VARIAVEIS GLOBAL
int VarGlobal1 = 0; // A FUNCAO DESSA VARIAVEL GLOBAL É ARMAZENAR OS RAs NUM VETOR DE INTEIROS E A CADA VEZ QUE EU ENCONTREI UMA NOTA MENOR QUE 6, O NUMERO DO RA SERA ARMAZENADO NO VETOR

int VarGlobal2 = 0; // ESTA VARIAVEL ESTA IMPLEMENTADA PARA A CHECAGEM DA EXISTENCIA OU NAO DE UM DETERMINADO RA


int main(void) {

	int vetorAux[100], i; // ESTE VETOR EH USADO EM CONJUNTO DA VARIAVEL GLOBAL VarGlobal1 COM A INTENCAO DE ENCONTRAR OS RAs QUE POSSUEM A NOTA MEDIA MENOR QUE 6
  int menu;
  int buscar_RA;
  PArv no = NULL; // ESTE EH O NO DA RAIZ PRINCIPAL DA ARVORE

  do{ // LACO PARA REPETICAO DO MENU
  
  printf("O que deseja fazer? Digite\n1) Inserir um aluno na árvore;\n2) Imprimir a árvore atual;\n3) Mostrar os dados dos alunos que foram reprovados;\n4) Excluir da árvore todos os alunos que foram reprovados;\n5) Mostrar todos os alunos com chave menor ou igual a um dado RA;\n6) Iniciar uma nova árvore;\n7) Sair.\n\n");

  scanf("%d",&menu);

  printf("\n");

  switch(menu){ // ANALISANDO CADA CASO REQUERIDO PELO USUARIO
    case 1: // Inserir um aluno na árvore
    no = pedindo_dados(no); // ESTA FUNCAO pedindo_dados RECEBE OS DADOS E CRIA A ARVORE
    printf("Aluno cadastrado com sucesso.\n");

    break;

    case 2: // Imprimir a árvore atual
    printf("A Arvore impressa eh:\n\n");
    imprimeIn (no, 0); // ESTA FUNCAO IMPRIME A ARVORE
    printf("\n\n");

    break;

    case 3: // Mostrar os dados dos alunos que foram reprovados

    printf("Os dados do(s) aluno(s) sao:\n");
    Mostrar_dados (no); // ESTA FUNCAO PRINTA OS DADOS
    printf("\n\n");

    break;

    case 4: // Excluir da árvore todos os alunos que foram reprovados
		buscando_nota(no, vetorAux); // ESTA FUNCAO EH RESPONSAVEL POR ARMAZENAR O NO QUE TEM NOTA MEDIA MENOR QUE 6. A IMPLEMENTACAO DELA ESTA EM CONJUNTO COM A VARIAVEL GLOBAL VarGlobal1 E O VETOR PARA ARMAZENAR OS DADOS

		if(VarGlobal1 == 0){ // NAO POSSUEM VALORES A SEREM EXCLUIDOS
    printf("Nao existem alunos reprovados.\n");
    break;
		}

		else{ // POSSUE ALGUM VALOR A SER EXCLUIDO
			for(i = 0; i < VarGlobal1; i++){ // A VARIAVEL GLOBAL VarGlobal1 É ACRESCIDA NA FUNCAO buscando_nota CADA VEZ QUE ENCONTRAR UM RA COM NOTA MEDIA MENOR QUE 6
				no = retira(no, vetorAux[i]); // ESTA FUNCAO RETIRA OS NOS COM NOTA MENOR QUE 6
			}
			VarGlobal1 = 0; // AQUI A VARIAVEL VarGlobal1 EH RESETADA PARA CASO O USUARIO DIGITE OUTRA ARVORE. COM ISSO, ELA PODERA ENCONTRAR E ARMAZENAR OS NOVOS RAs COM MEDIA MENOR QUE 6
		}
    printf("Os alunos reprovados foram excluidos da arvore.\n");

    break;

    case 5: // Mostrar todos os alunos com chave menor ou igual a um dado RA
    printf("Digite o RA: ");
    scanf("%d",&buscar_RA);
    getc(stdin);

    printf("Os dados do(s) aluno(s) que tem o RA menor ou igual a %d sao:\n",buscar_RA);
    buscando_RA (no,buscar_RA); // ESTA FUNCAO SIMPLESMENTE MOSTRA OS RAs DE NUMERO MAIS BAIXO QUE UM DETERMINADO RA INSERIDO PELO USUARIO
    printf("\n\n");

    break;

    case 6: // Iniciar uma nova árvore
    no = libera(no); // FUNCAO QUE LIBERA A ARVORE. ELA RETORNARA NULL PARA QUE POSSA SER INCLUIDA UMA NOVA ARVORE.
    printf("A arvore foi reiniciada.\n");

    break;

    case 7: // Sair
    printf("Voce saiu do menu.\n");
    no = libera (no); // ESSA FUNCAO LIBERARA A ARVORE E SAIRA DA MAIN, ENCERRANDO O ALGORITMO

    break;

    default: // Caso em que o digito nao eh um numero
    printf("Digite apenas as opcoes dadas.\n");
    getc(stdin);
    break;
    
  }

  }while(menu != 7); // CONDICAO PARA QUE SE SAIA DO LACO

  return 0;
}



PArv pedindo_dados(PArv arv){

  int reg_aluno;
  char nome[30];
  float nota1, nota2, nota3;
  float media;


  do{ // VERIFICACAO DA PRE-EXISTENCIA DO RA

  VarGlobal2 = 0;

  printf("Digite o RA:\n");
  scanf("%d",&reg_aluno);
  getc(stdin);

  verifica_RA (arv,reg_aluno); // ESTA FUNCAO MUDARA O VALOR DA VARIAVEL VarGlobal2 PARA 1 E ISSO EH A CONDICAO PARA QUE O LACO AQUI SE REPITA. SEMPRE ZERO ELA INICIALMENTE PARA QUE N PERMANECA SEMPRE IGUAL A 1 E CONSEQUENTEMENTE O LACO FIQUE INFINITAMENTE SE REPETINDO

  if(VarGlobal2 == 1)
  printf("RA já existente.\n");

  }while(VarGlobal2 != 0);


  printf("Digite o nome:\n");
  scanf("%[^\n]s",nome);
  getc(stdin);

  do{ // ESSE LACO PERMANECERA EM LOOPING SE A ENTRADA DAS NOTAS NAO ESTIVER ENTRE 0 A 10

  printf("Digite de 0 a 10 a primeira nota:\n");
  scanf("%f",&nota1);
  getc(stdin);

  printf("Digite de 0 a 10 a segunda nota:\n");
  scanf("%f",&nota2);
  getc(stdin);

  printf("Digite de 0 a 10 a terceira nota:\n");
  scanf("%f",&nota3);
  getc(stdin);

  if((nota1 < 0 || nota1 > 10) || (nota2 < 0 || nota2 > 10) || (nota3 < 0 || nota3 > 10))
  printf("\nPor favor digite apenas numeros entre 0 e 10.\n\n");

  } while((nota1 < 0 || nota1 > 10) || (nota2 < 0 || nota2 > 10) || (nota3 < 0 || nota3 > 10));

  media = (nota1 + nota2 + nota3)/3.0;

  arv = insere_ABB (arv, reg_aluno, nome, nota1, nota2, nota3); // INSERCAO DO NO NA ARVORE COM OS DADOS PEDIDOS ACIMA

  return arv;
}


PArv insere_ABB (PArv arv, int reg_aluno, char nome[], float a, float b, float c) {

  PArv novo;

  if (arv == NULL) { // NO ESTA VAZIO E ALOCAREI ELE DINAMICAMENTE. MAS REPARE, A RECURSIVIDADE ABAIXO, CASO NAO ENTRE NESSE if, PERCORRERA A ARVORE ATE ENCONTRAR ESPACO CORRETO PARA O NO DA ARVORE BINARIA DE BUSCA

  novo = (PArv)malloc(sizeof(TArv));
  novo->RA = reg_aluno;
  strcpy(novo->nome,nome);
  novo->nota1 = a;
  novo->nota2 = b;
  novo->nota3 = c;
  novo->media = (a+b+c)/3.0;
  novo->esq = NULL;
  novo->dir = NULL;

  return (novo);
  }

  else if (reg_aluno < arv->RA){ // POR SE TRATAR DE UMA ABB, ESSAS RECURSOES GARANTIRAO QUE A ARVORE PERMANECA DE FORMA ORDENADA COM BASE NO RA DE CADA NO. ESTE RA QUE EH PASSADO COMO PARAMETRO DA FUNCAO insere_ABB
  arv->esq = insere_ABB(arv->esq,reg_aluno,nome,a,b,c);
  }
    else{ // ANALOGO AO COMENTARIO ACIMA
      arv->dir = insere_ABB(arv->dir,reg_aluno,nome,a,b,c);
    }

  return (arv); // O RETORNO SE TRATA DO NO RAIZ PRINCIPAL DA ABB
}


PArv libera (PArv a){ // ESSA FUNCAO PERCORRE DE FORMA RECURSIVA TODA A ARVORE E DARÁ FREE, LIBERARA, FOLHA POR FOLHA DA ABB
if (a!=NULL) {
libera(a->esq); /* LIBERA SAE */
libera(a->dir); /* LIBERA SAD */
free(a); /* LIBERA RAIZ */
}
return NULL;
}


void imprimeIn (PArv a, int nivel) { // ESTA FUNCAO PERCORRERA TODA MINHA ARVORE DA DIREITA PARA A ESQUERDA E SEMPRE IMPRIMIRA NESTA ORDEM. A VARIAVEL nivel SEMPRE SERA ACRESCIDA NA RECURSIVIDADE PORQUE ELA FARA COM QUE AS TABELACOES SEJAM DE ACORDO COM O NIVEL DA ARVORE. ISSO SOMENTE EH IMPLEMENTADO PARA QUE A IMPRESSAO DA ARVORE SEJA NA HORIZONTAL

  if (a!=NULL) {

    imprimeIn(a->dir, nivel+1); // IMPRIME SAE
    
    for(int i = 0; i < nivel; i++){
      printf("\t"); // SIMPLESMENTE USADA PARA IMPRIMIR DE ACORDO COM O PEDIDO
    }

    printf("%d\n", a->RA); // IMPRIME O NO DEPOIS DA DAR AS TABELACOES CORRETAS DE ACORDO COM O ACRESCIMO DA VARIAVEL NIVEL, NA RECURSIVIDADE

    imprimeIn(a->esq, nivel+1); // IMPRIME SAD
  }

}


void Mostrar_dados (PArv arv){ // ESTA FUNCAO SIMPLESMENTE PERCORRE, POR RECURSIVIDADE, A ARVORE DA ESQUERDA PARA A DIREITA E CASO ENCONTRE ALGUM NO COM MEDIA MENOR QUE 6, ELA IMPRIMIRA OS DADOS QUE ESTAO ARMAZENADOS NELE

  if (arv!=NULL){
    
    Mostrar_dados(arv->esq);

    if(arv->media < 6){

    printf("RA: %d\tNome: %s\nNota 1: %.2f\tNota 2: %.2f\tNota 3: %.2f\tMedia: %.2f\n",arv->RA,arv->nome,arv->nota1,arv->nota2,arv->nota3,arv->media);
    }

    Mostrar_dados(arv->dir);

  }


}


void buscando_nota (PArv arv, int vetor[]){ // ESTA FUNCAO PERCORRE IGUALMENTE A FUNÇÃO ACIMA. PORTANTO VIDE O COMENTARIO.

// MAS, TEM UMA DIFERENÇA. ESSA FUNCAO NAO IMPRIME NADA, ELA ALOCARA NUM VETOR, O RA DE CADA NO COM NOTA MENOR QUE 6. A IMPLEMENTACAO DELA ESTA EM CONJUNTO COM A FUNCAO QUE RETIRA OS NOS QUE POSSUEM MEDIAS MENORES QUE 6, OS ALUNOS REPROVADOS

  if(arv != NULL){

    buscando_nota(arv->esq, vetor);

		if(arv->media < 6){
			vetor[VarGlobal1++] = arv->RA;
		}
	
    buscando_nota(arv->dir, vetor);

  }

}



void buscando_RA (PArv arv, int reg_aluno){ // ESTA FUNCAO PERCORRERA A ARVORE DE FORMA RECURSIVA DA ESQUERDA PARA A DIREITA E EXIBIRA OS NOS QUE POSSUEM O RA MENOR OU IGUAL A UM ESPECIFICO PEDIDO DE ENTRADA.

// NAO FICOU MUITO CLARO QUAIS ERAM OS DADOS QUE DEVIAM SER MOSTRADOS, MAS PELA IDEIA DE BUSCAR OS RAs, ACHEI CONVENIENTE APENAS O RA E O NOME, JA QUE AS NOTAS SAO IRRELEVANTES NESSE TIPO DE BUSCA

  if(arv != NULL){

    buscando_RA(arv->esq,reg_aluno);
    if(arv->RA <= reg_aluno){
      printf("RA: %d\tNome: %s\n",arv->RA,arv->nome);
    }
    buscando_RA(arv->dir,reg_aluno);

  }

}


PArv retira (PArv r, int reg_aluno) { // ESTA FUNCAO RETIRARA O NO QUE POSSUA O MESMO RA PASSADO COMO PARAMETRO. NA IMPLEMENTACAO DELA, USEI OUTRA FUNCAO (buscando_nota) PARA ENCONTRAR OS NOS QUE POSSUEM NOTA MENOR QUE 6 E ARMAZENEI SEUS RAs NUM VETOR DE INTEIROS. PARA RETIRAGEM DE TODOS OS NOS COM NOTA MEDIA MENOR A 6, PERCORREREI O VETOR QUE ARMAZENA OS RAs E RETIRAREI NO POR NO.

  // ESSES NOS SAO USADOS PARA GUARDAR ENDEREÇOS
  PArv t;
  PArv pai;
  PArv f;

  if(r == NULL){ // ACABARAM OS NOS, PORTANTO, ENCERRARA A RECURVIDADE ABAIXO
    return NULL;
  }

  else if (reg_aluno < r->RA)
    r->esq = retira(r->esq, reg_aluno); // ESSA RECURSAO DA ABB ESTA EM FUNCAO DO PARAMETRO RA, E ISSO FAZ COM QUE A IMPLEMENTACAO DELA SEJA MUITO EFICIENTE, PERCORRENDO SEMPRE A ARVORE, NUM SENTIDO ACERTIVO

  else if (r->RA < reg_aluno)
    r->dir = retira(r->dir, reg_aluno); // MESMA INTENCAO DA RESURSAO ACIMA

  else{ // AQUI, QUER DIZER QUE FOI ENCONTRADO O NO COM RA IGUAL AO PASSADO COMO PARAMETRO NA FUNCAO

  if (r->esq==NULL && r->dir==NULL){ // NESSE CASO, O NO ENCONTRADO SE TRATA DE UMA FOLHA, E SIMPLEMENTE ACONTECE O FREE(LIBERACAO) DELA
    free(r);
    r = NULL;
  }

    else if (r->esq == NULL && r->dir != NULL) { // ESSA CONDICAO QUER DIZER QUE O NO ENCONTRADO, SO TEM FILHO A DIREITA. O PONTEIRO t ARMAZENARA O ENDEREÇO DE r E r ARMAZENARA O ENDERECO DO FILHO A DIREITA DELE. APOS ISSO, t, QUE ESTAVA ARMAZENANDO ENDEREÇO DE r(O NO QUE ERA PARA SER REMOVIDO) SERA LIBERADO E A ARVORE APONTARA PARA O FILHO A DIREITA DELA
      t = r;
      r = r->dir;
      free(t);
    }

      else if (r->dir == NULL && r->esq != NULL) { // FAÇO DO COMENTARIO ACIMA, ESTE. O QUE MUDA EH QUE AGORA O NO ENCONTRADO SO TEM FILHO A ESQUERDA.
      t = r;
      r = r->esq;
      free(t);
      }

        else { // NESTE CASO, O NO ENCONTRADO TEM DOIS FILHOS
        pai = r;
        f = r->esq;

        while (f->dir != NULL) { // A DECLARACAO ACIMA DE "f = r->esq" FAZ COM QUE f APONTE PARA O FILHO A ESQUERDA DE r, OU SEJA ESSE LACO DE f = f->dir FAZ COM QUE ENCONTREMOS O FILHO DE MAIOR VALOR, QUANDO A REFERENCIA SE TRATA DOS VALORES MENORES QUE r, POIS ESTAO A ESQUERDA DELE
          pai = f; // O PONTEIRO pai ARMAZENARA O VALOR DE f PARA  f SEMPRE APONTAR PARA SEU SUCESSOR MAIOR
          f = f->dir;
        }

        r->RA = f->RA; // AQUI, APOS ENCONTRAR O MAIOR FILHO, r RECEBE TODAS AS INFORMACOES DELE P/ DEPOIS SER RETORNADO NA FUNCAO
        strcpy(f->nome,r->nome);
        r->nota1 = f->nota1;
        r->nota2 = f->nota2;
        r->nota3 = f->nota3;
        r->media = f->media;


        if (pai==r) // QUANDO O PAI DO MAIOR VALOR EH O PROPRIO NO RAIZ QUE SERA REMOVIDO
        pai->esq = f->esq;

        else // CASO O PAI NAO SEJA MAIOR, OU SEJA, QUANDO ELE NAO EH A PROPRIA RAIZ REMOVIDA
        pai->dir = f->esq;

        free(f); // LIBERA f POIS f FOI USADO APENAS PARA PERCORRER A ARVORE E ARMAZENAR OS VALORES QUE r ARMAZENOU

        }
  }

  return r;
}


void verifica_RA (PArv arv, int reg_aluno){ // ESTA FUNCAO PERCORRERA DE FORMA RECURSIVA A ARVORE E CASO ENCONTRE UM RA JA EXISTENTE, ELA MUDARA O VALOR DA VARIAVEL VarGlobal2 PARA 1, E ISSO, NA MAIN, FARA COM QUE SEJA REPETIDO A ENTRADA DA VARIAVEL RA

  if(arv != NULL){

    verifica_RA(arv->esq,reg_aluno);
    if(arv->RA == reg_aluno){
      VarGlobal2 = 1;
    }
    verifica_RA(arv->dir,reg_aluno);

  }

}