#ifndef BIBLIOTECAARVORE_H_INCLUDED
#define BIBLIOTECAARVORE_H_INCLUDED

typedef struct Equipament
{
    int codEqp;
    char[11] apelido;
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
                    if () //direita ou esq
                    {
                        
                    }
                    else
                    {

                    }
                }
                else
                {
                    if (Pai->incidente.codUn > inc.codUn)
                    {
                        if ()
                        {

                        }
                        else
                        {
                            
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


#endif // BIBLIOTECAARVORE_H_INCLUDED
