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

int insere (Arv *Arvore, Inc inc)
{
    if (busca(Arvore, inc.codUn)!=NULL)
    {
        return 0;
    }
    Arvore -> raiz = aux_insere(Arvore->raiz, inc);
    return 1;
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
        while (flag ==0)
            {
                if (Pai->incidente.codUn < inc.codUn)
                {
                    if (Pai -> dir == NULL) //direita ou esq
                    {
                        Pai->dir = novo;
                        flag = 1;
                    }
                    else
                    {
                        Pai = Pai -> dir;
                    }
                }
                else
                {
                    if (Pai->incidente.codUn > inc.codUn)
                    {
                        if (Pai -> esq = NULL)
                        {
                            Pai -> esq = novo;
                            flag = 1;
                        }
                        else
                        {
                            Pai = Pai->esq;
                            
                        }
                    }
                    else
                    {
                        flag = 1;
                        free (novo);
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

void imprimirIncidente(Inc inc) 
{
    switch (inc.gravidade):
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

void imprimirOrdemArv (NoArv *pai)
{
    if (pai != NULL)
    {
        immprimirOrdemArv(pai->esq);
        imprimirIncidente(pai->incidente);
        imprimirOrdemArv(pai->dir);
    }
        
}


#endif // BIBLIOTECAARVORE_H_INCLUDED
