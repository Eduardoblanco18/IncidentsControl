#ifndef BIBLIOTECAARVORE_H_INCLUDED
#define BIBLIOTECAARVORE_H_INCLUDED

typedef struct Equipament
{
    int codEqp;
    char apelido[11];
}Eqp;

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

NoArv*remover_aux(NoArv*pai, int num)
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
                          aux=pai->esq;
                          while(aux->dir!=NULL)
                          {
                              aux=aux->dir;
                          }
                          pai->incidente.codUn=aux->incidente.codUn;
                          aux->incidente.codUn=num;
                          pai->esq=remover_aux(pai->esq,num);
                      }
                  }
              }
          }
        }
    }
    return pai;
}

Arv*remover( Arv*RAIZ, int num)
{
    NoArv*aux=RAIZ->raiz;
    if(aux->incidente.codUn == num && aux->dir == NULL && aux->esq == NULL)
    {
        free(aux);
        free(RAIZ);
        return NULL;
    }
    RAIZ->raiz=remover_aux(RAIZ->raiz,num);
    return RAIZ;
}



#endif // BIBLIOTECAARVORE_H_INCLUDED
