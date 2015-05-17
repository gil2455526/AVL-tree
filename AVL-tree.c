#include <stdio.h> 
#include <conio.h> 
#include <string.h>
#include <stdlib.h>
#define clrscr(); system("cls"); 

// define o tipo no
typedef struct elemento { int info; 
 struct elemento *dir, *esq; 
 } no; 
no *apraiz, *apno, *apaux, *pai; 
int valor;

int menu (void);
void localiza (int valor); 
no* insere (int valor, no *apno); 
int inordem_exc (no *apno, int trf);
void inordem (no *apno);
int altura (no *apno);
void imprime_arvore(no *apno, int h);
int fatoreq (no *apno);
no* equilibra (no *apno);
no* rodar_dir(no *apno);
no* rodar_esq(no *apno);
no* excluir (no *apno, int valor);
void antecessor(no *apno);

int main ( ) 
{int opcao = 1, j;
 clrscr(); 
 printf("\n Este programa cria e manipula uma estrutura de \n arvore binaria de busca AVL com alocacao dinamica\n\n\n"); 
 printf(" <ENTER> para comecar ... "); 
 getch();
 apraiz = malloc(sizeof(no)); 
 apraiz = NULL;
 valor = 0;
 for (j=1; j<10; j++)//auto povoamento da árvore = DEBUG
  insere(j, apraiz);
 while (opcao)
   opcao = menu();
 printf("\n Fim do programa. Pressione uma tecla ..."); 
 getch(); 
 return 0; 
}

int menu(void)
{  int opcao;
   clrscr();
   printf("\n");
   imprime_arvore(apraiz, 1);
   printf("\n Menu Principal:\n\t1. Insercao\n\t2. Exclusao\n\t3. Pesquisar\n\t4. Imprimir inordem\n\t0. Sair\n\n >: ");
   scanf("%i", &opcao);
   if (opcao > 1 && apraiz == NULL)
     { printf("\n Crie a arvore antes de manipula-la!");
       opcao = 1;}
   switch (opcao)
   { case 1: 
     { printf("\n\n Digite o NUMERO a entrar na arvore binaria: ");
       scanf("%i",&valor);
       insere(valor, apraiz);
       break;}
     case 2:
     { printf("\n\n Digite o NUMERO a ser excluido na arvore binaria: ");
       scanf("%i", &valor);
       excluir(apraiz, valor);
       break;}
     case 3:
     { printf("\n Localiza nos na arvore binaria\n"); 
       if (apraiz == NULL) 
         printf("\nA arvore binaria esta vazia...."); 
       else
       { valor = 0;
         printf("\n Numero a ser localizado na arvore: "); 
         scanf("%i",&valor);
         apno = apraiz; 
         localiza(valor); 
         if (apno == NULL) 
           printf("\n Nao existe um no com esta informacao na arvore.");
         else 
           printf("\n O no se encontra na arvore", apno->info); 
         getch();
       }
       break;}
     case 4:
     { printf("\n\n Nos da arvore binaria em inordem "); 
       inordem(apraiz);
       getch(); 
       break;}
     case 0: break;
     default: 
     { printf("\n Opcao invalida");
       getch();}
   }
   return opcao;
}

void localiza (int valor) 
{ while (apno != NULL && apno->info != valor) 
   if (apno->info < valor) 
     apno = apno->dir; 
   else 
     apno = apno->esq; 
} 

no* insere (int valor, no *apno) 
 /* ...... Procura o lugar na arvore binaria onde o novo no com a informacao info deve entrar e o insere ordenadamente, caso ele ja nao se encontre na arvore .....*/ 
{if (apno != NULL) 
 { if (apno->info < valor)
    { apaux = apno;
      apno->dir = insere(valor, apno->dir);}
   else if (apno->info > valor) 
     { apaux = apno;
       apno->esq = insere(valor, apno->esq);}
   else 
   { printf("\n O no com o valor %i ja se encontra na arvore. ",valor);
     getch();}
 }
 else
 {apno = malloc(sizeof(no)); 
  apno->info = valor; 
  apno->dir = NULL; 
  apno->esq = NULL;
  if (apraiz == NULL)
   apraiz = apno;
 }
 apno = equilibra (apno);
 return apno;
}

void inordem (no *apno)
{if (apno != NULL) 
 { inordem(apno->esq); 
   printf("\n Info = %i ",apno->info);
   inordem(apno->dir); 
 } 
}

int altura (no *apno) 
{int hesq =0, hdir=0; 
 if (apno == NULL) 
  return 0; //arvore vazia 
 else { 
  hesq = altura(apno->esq); 
  hdir = altura(apno->dir); 
  if (hesq < hdir) 
   return hdir + 1; 
  else 
   return hesq + 1; 
 }
} 

void imprime_arvore(no *apno, int tabulacoes) 
//imprime a arvore t com identacao de tabulacoes \t 
{ int j; 
 if ( apno != NULL) 
 {
  imprime_arvore(apno->dir, tabulacoes+1); 
  for (j=1; j<=tabulacoes; j++) 
   printf ("\t"); 
  printf("%i \n",apno->info); 
  imprime_arvore(apno->esq,tabulacoes+1); 
 } 
}

int fatoreq (no *apno)
{ if (apno)
  { int fator = 0;
    fator = (altura(apno->esq) - altura(apno->dir));
    return fator;
  }
  return 0;
}

no* equilibra (no *apno)
{ if (apno)
  { if (fatoreq(apno) > 1)
    { printf("\n Desequilibrio! Antes: \n");
      imprime_arvore(apraiz, 1);
      getch();
      if(fatoreq(apno->esq) <= -1)
      { apno->esq = rodar_esq(apno->esq);
        printf("\n\n");
        imprime_arvore(apraiz, 1);
        getch();}
    if (apno != apraiz)
      apno = rodar_dir(apno);
    else apraiz = rodar_dir(apraiz);
    }
    else if (fatoreq(apno) < -1)
    { printf("\n Desequilibrio! Antes: \n");
      imprime_arvore(apraiz, 1);
      getch();
      if (fatoreq(apno->dir) >= 1)
      { apno->dir = rodar_dir(apno->dir);
        printf("\n\n");
        imprime_arvore(apraiz, 1);
        getch();
      }
      if (apno != apraiz)
        apno = rodar_esq(apno);
      else apraiz = rodar_esq(apno);
    }
  }
  return apno;
}

no* rodar_dir(no *apno)
{ apaux = apno->esq;
  apno->esq = apaux->dir;
  apaux->dir = apno;
  apno = apaux;
  return apno;
}

no* rodar_esq(no *apno)
{ apaux = apno->dir;
  apno->dir = apaux->esq;
  apaux->esq = apno;
  apno = apaux;
  return apno;
}

no* excluir (no *apno, int valor)
{  if (apno == NULL)
   { printf("\n Nao existe um no com esta informacao na arvore.");
     getch();
     return apno;
   }
   else if(valor < apno->info)
   { pai = apno;
     apno->esq = excluir(apno->esq, valor);
     equilibra(apno);
     return apno;
   }
   else if (valor > apno->info)
   { pai = apno;
     apno->dir = excluir(apno->dir, valor);
     equilibra(apno);
     return apno;
   }
   else if (valor == apno->info)
   { if (apno->dir && apno->esq)
     { antecessor(apno->esq);
       apno->info = apaux->info;
     }
     else apaux = apno;
     if (apaux->dir || apaux->esq)
       { if (apaux->dir && pai)
          { if (pai->esq->info == apaux->info)
              pai->esq = apaux->dir;
            else if (pai->dir->info == apaux->info)
              pai->dir = apaux->dir;
          }
         else if (apaux->esq && pai)
          { if (pai->esq == apaux)
              pai->esq = apaux->esq;
            else if (pai->dir == apaux)
              pai->dir = apaux->esq;
          }
         else if (apaux && pai)
          { if (pai->esq == apaux)
              pai->esq = NULL;
            else if (pai->dir == apaux)
              pai->dir = NULL;
          }
       }
     if(apraiz->info == apaux->info)
       apraiz = NULL;
     free (apaux);
     apaux = NULL;
   }
   return apno;
}

void antecessor(no *apno)
{  if(apno->dir)
    {pai = apno;
     antecessor(apno->dir);}
   else apaux = apno;
}
