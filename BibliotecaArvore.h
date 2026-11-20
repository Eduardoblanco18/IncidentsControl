#ifndef BIBLIOTECAARVORE_H_INCLUDED
#define BIBLIOTECAARVORE_H_INCLUDED

typedef struct Incidents
{
    int codUn;
    int codEqp;
    int gravidade;
}Inc;

typedef struct NoArvore
{
    Inc incidente;
    struct NoArvore* esq;
    struct NoArvore* dir;
}NoArv;

typedef struct Arvore
{
    NoArv* raiz;
}Arv;

typedef struct noIncidentes
{
    Inc info;
    struct noIncidentes* prox;
}NoInc;

typedef struct listaIncidentes
{
    NoInc *inicio;
}ListaInc;

typedef struct Equipament
{
    int codEqp;
    char apelido[11];
    ListaInc *incidentes;
}Eqp;

typedef struct NoEquipamento
{
    Eqp equipamento;
    struct NoEquipamento *prox;
}NoEqp;

Arv* CriarArvore()
{
    Arv *aux;
    aux = (Arv*) malloc (sizeof(Arv));
    aux -> raiz = NULL;
    return aux;
}

int ArvVazia(Arv *base)
{
    if (base->raiz == NULL)
    {
        return 1;
    }
    return 0;
}

NoArv* aux_insere(NoArv *no, Inc inc)
{
    int flag;
    NoArv *Pai;
    NoArv *novo = (NoArv*)malloc(sizeof(NoArv));
    novo -> incidente = inc;
    novo -> esq = NULL;
    novo ->dir = NULL;
    if (no == NULL)
    {
        return novo;
    }
    else
    {
        Pai = no;
        flag = 0;
        while (flag != 1)
            {
                if (Pai->incidente.codUn < inc.codUn)
                {
                    if (Pai -> dir == NULL)
                    {
                        Pai->dir = novo;
                        flag = 1;
                    }
                    else
                    {
                        Pai = Pai->dir;
                    }
                }
                else
                {
                    if (Pai -> esq == NULL)
                    {
                        Pai -> esq = novo;
                        flag = 1;
                    }
                    else
                    {
                        Pai = Pai->esq;
                    }
                }
            }
    }
    return no;

}

NoArv* busca (Arv *Arvore, int num)
{
    int flag;
    NoArv *Pai;
    if (ArvVazia(Arvore))
    {
        return NULL;
    }
    Pai = Arvore->raiz;
    flag = 0;
    while (flag == 0)
        {
            if (Pai -> incidente.codUn == num)
            {
                flag = 1;
            }
            else
            {
                if (Pai -> incidente.codUn < num)
                {
                    Pai = Pai->dir;
                }
                else
                {
                    Pai = Pai->esq;
                }
                if (Pai == NULL)
                {
                    flag = 2;
                }
            }
        }
    if (flag == 1)
    {
        return Pai;
    }
    return NULL;
}

int insere (Arv *Arvore, Inc inc)
{
    if (busca(Arvore, inc.codUn)!=NULL)
    {
        return 0;
    }
    Arvore -> raiz = aux_insere(Arvore->raiz, inc);
    return 1;
}

void imprimirIncidente(Inc inc)
{
    switch (inc.gravidade)
    {
         case 1:
            printf("\nIncidente : %d, Equipamento: %d, Gravidade: %d - Baixa.", inc.codUn, inc.codEqp, inc.gravidade);
            break;
        case 2:
            printf("\nIncidente : %d, Equipamento: %d, Gravidade: %d - Media", inc.codUn, inc.codEqp, inc.gravidade);
            break;
        case 3:
            printf("\nIncidente : %d, Equipamento: %d, Gravidade: %d - Alta", inc.codUn, inc.codEqp, inc.gravidade);
            break;
    }
}

void imprimirOrdemArv (NoArv *pai)
{
    if(pai != NULL)
    {
        if(pai->esq != NULL)
        {
            imprimirOrdemArv(pai->esq);
        }
        imprimirIncidente(pai->incidente);
        if(pai->dir != NULL)
        {
            imprimirOrdemArv(pai->dir);
        }
    }
}

void imprimir (Arv *RAIZ)
{
    imprimirOrdemArv(RAIZ->raiz);
}

NoArv* remover_aux(NoArv*pai, int num)
{
    if(pai==NULL)
    {
        printf("\n\n não encontrado na árvore");
    }
    else
    {
        if(num > pai->incidente.codUn)
        {
            pai->dir=remover_aux(pai->dir,num);
        }
        else
        {
          if(num<pai->incidente.codUn)
          {
              pai->esq=remover_aux(pai->esq,num);
          }
          else
          {
              if(pai->dir==NULL&&pai->esq==NULL)
              {
                  free(pai);
                  pai=NULL;
              }
              else
              {
                  if(pai->esq==NULL)
                  {
                      NoArv*aux=pai;
                      pai=pai->dir;
                      free(aux);
                  }
                  else
                  {
                      if(pai->dir==NULL)
                      {
                          NoArv*aux=pai;
                          pai=pai->esq;
                          free(aux);
                      }
                      else
                      {
                          NoArv*aux;
                          Inc temp;
                          aux=pai->esq;
                          while(aux->dir!=NULL)
                          {
                              aux=aux->dir;
                          }
                          temp = pai->incidente;
                          pai->incidente = aux->incidente;
                          aux->incidente = temp;
                          pai->esq=remover_aux(pai->esq,num);
                      }
                  }
              }
          }
        }
    }
    return pai;
}

Arv* remover(Arv* RAIZ, int num)
{
    if (!ArvVazia(RAIZ))
    {
        RAIZ->raiz = remover_aux(RAIZ->raiz, num);
    }
    return RAIZ;
}

void liberarArv (NoArv *pai)
{
    if(pai->dir != NULL)
    {
        liberarArv(pai->dir);
    }
    if(pai->esq != NULL)
    {
        liberarArv(pai->esq);
    }
    free(pai);
}

ListaInc* CriaLista()
{
    ListaInc *aux;
    aux = (ListaInc*)malloc(sizeof(ListaInc));
    aux->inicio = NULL;
    return aux;
}


int ListaVazia(ListaInc *L)
{
    if(L->inicio == NULL)
    {
        return 1;
    }
    return 0;
}

NoInc* AuxInsere(NoInc *antigo, Inc v)
{
    NoInc *novo;
    novo = (NoInc*)malloc(sizeof(NoInc));
    novo->info = v;
    novo->prox = antigo;
    return novo;
}

void InsereL_inicio(ListaInc *velho, Inc valor)
{
    velho->inicio = AuxInsere(velho->inicio, valor);
}


int RemoverLista(ListaInc *L, int valor)
{
    int removeu;
    NoInc *ant, *p;
    ant = NULL;
    p = L->inicio;
    while(p != NULL && p->info.codUn != valor)
    {
        ant = p;
        p = p->prox;
    }
    if(p == NULL)
    {
        removeu = 0;
    }
    else
    {
        if(ant == NULL)
        {
            L->inicio = p->prox;
        }
        else
        {
            ant->prox = p->prox;
        }
        free(p);
        removeu = 1;
    }
    return removeu;
}

ListaInc* LiberarLista(ListaInc *L)
{
    NoInc *apag;
    while(L->inicio != NULL)
    {
        apag = L->inicio;
        L->inicio = L->inicio->prox;
        free(apag);
    }
    free(L);
    return NULL;
}

int buscarLista(ListaInc *L, int valor)
{
    NoInc *aux;
    aux = L -> inicio;
    while (aux!=NULL)
    {
        if (aux->info.codUn == valor)
        {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}



// TABELA HASH AQUI:

#define TAM 47

int funcaoHash (int codigo)
{
    int resto = codigo % TAM;
    return resto;
}

Eqp *BuscaEqp(NoEqp *Hash[], int codigo)
{
    int pos = funcaoHash(codigo);
    NoEqp *posHash = Hash[pos];
    while ((posHash != NULL) && (posHash->equipamento.codEqp != codigo))
    {
        posHash = posHash->prox;
    }
    if (posHash == NULL)
    {
        //printf("\nEquipamento Inexistente.");
        //system("Pause");
        return NULL;
    }

    return &posHash->equipamento;
}

void adicionarEqpNaHash(NoEqp *Hash[], Eqp novoEqp)
{
    NoEqp *novo;
    novo = (NoEqp*)malloc(sizeof(NoEqp));
    novo->equipamento = novoEqp;
    novo->prox = NULL;

    int pos = funcaoHash(novoEqp.codEqp);
    if(Hash[pos] == NULL)
    {
        Hash[pos] = novo;
    }
    else
    {
        NoEqp *aux = Hash[pos];
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void adicionarIncNaHash(NoEqp *Hash[], Inc novoInc)
{
    int pos = funcaoHash(novoInc.codEqp);
    if (Hash[pos] == NULL)
    {
        printf("\nEquipamento inexistente");
        exit(1);
    }
    else
    {
        NoEqp *aux = Hash[pos];
        while((aux->equipamento.codEqp != novoInc.codEqp) && (aux != NULL))
        {
            aux = aux->prox;
        }
        if(aux == NULL)
        {
            printf("\nEquipamento não encontrado");
            exit(1);
        }
        else
        {
            Eqp auxEqp = aux->equipamento;
            InsereL_inicio(auxEqp.incidentes, novoInc);
        }
    }
}







#endif // BIBLIOTECAARVORE_H_INCLUDED
