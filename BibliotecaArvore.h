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

#endif // BIBLIOTECAARVORE_H_INCLUDED
