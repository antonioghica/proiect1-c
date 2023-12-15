#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct nod{//structura pentru momentul cand a sunat sau a fost sunat un anumit numar
    int ora;
    int minut;
    int secunda;
    struct nod* left;
    struct nod* right;
};
struct monitorizare {//lista dublu inlantuita pentru cele doua tipuri de apeluri
    char nr_telefon[11];
    struct nod* gestiune;
    struct monitorizare* prev, * urm;
};
struct monitorizare* new_m(char s[]) {
    struct monitorizare* p = (struct monitorizare*)malloc(sizeof(struct monitorizare));
    strcpy(p->nr_telefon, s);
    p->prev = NULL;
    p->urm = NULL;
    return p;
}
struct nod* new_nod(int o, int m, int s) {
    struct nod* h = (struct nod*)malloc(sizeof(struct nod));
    h->ora = o;
    h->minut = m;
    h->secunda = s;
    h->left = NULL;
    h->right = NULL;
    return h;
}
struct nod* cautare(struct nod* r, int o, int m, int s) {
    int t1, t2;
    if (r == NULL) {
        return new_nod(o, m, s);
    } else {
        t1 = (r->ora)*3600+(r->minut)*60+r->secunda;
        t2 = o * 3600 + m * 60 + s;
        if (t2 < t1)
            r->left = cautare(r->left, o, m, s);
        if (t2 > t1)
            r->right = cautare(r->right, o, m, s);
        return r;
    }
}
struct monitorizare* adauga1(struct monitorizare* p, char s[], char tip[], int o, int m, int sec) {
    if (p == NULL) {
        p = new_m(s);
        p->gestiune=NULL;
        p->gestiune = cautare(p->gestiune, o, m, sec);
        return p;
    } else {
        if (strcmp(tip, "primit") == 0) {
            if (strcmp(p->nr_telefon, s) == 0) {
                p->gestiune=cautare(p->gestiune,o,m,sec);
                return p;
            } else
                p->urm = adauga1(p->urm, s, tip, o, m, sec);
        }
        if (strcmp(tip, "efectuat") == 0) {
            if (strcmp(p->nr_telefon, s) == 0) {
                printf("\n%s ", p->nr_telefon);
                p->gestiune=cautare(p->gestiune,o,m,sec);
                return p;
            } else
                p->prev = adauga1(p->prev, s, tip, o, m, sec);
        }
        return p;
    }
}
void afis1(struct nod* h) {
    if (h != NULL) {
        afis1(h->left);
        printf("%d %d %d\n", h->ora, h->minut, h->secunda);
        afis1(h->right);
    }
}
void afis(struct monitorizare* p) {
    if (p != NULL) {
        while(p->urm!=NULL)
        {
            p=p->urm;
            printf("%s\n",p->nr_telefon);
            afis1(p->gestiune);
        }
    }
}
void afis2(struct monitorizare *p)
{
    if(p!=NULL)
    {
        while(p->prev!=NULL)
        {
            p=p->prev;
            printf("%s\n",p->nr_telefon);
            afis1(p->gestiune);
        }
    }
}

int main() {
    struct monitorizare* p;
    p = NULL;
    char s[11], tip[15];
    int o,m,sec,k=1,a;
    p=adauga1(p,"radacina","radacina",0,0,0);
    do{
        printf("Daca nu mai doriti sa introduceti un apel apasati tasta 0(apasati orice tasta de la 1 la 9)");
        scanf("%d",&a);
        if(a==0)
            k=0;
        else
        {
            printf("\nIntroduceti numarul de telefon: ");
            scanf("%s", s);
            printf("\nIntroduceti tipul apelului(primit/efectuat):");
            scanf("%s",tip);
            printf("\nIntroduceti ora apelului:");
            scanf("%d",&o);
            printf("\nIntroduceti minutul apelului:");
            scanf("%d",&m);
            printf("\nIntroduceti secunda apelului:");
            scanf("%d",&sec);
            p = adauga1(p, s,tip,o,m,sec);
        }
    }while(k);
    printf("\nApeluri primite:\n");
    afis(p);
    printf("\nApeluri efectuate:\n");
    afis2(p);
    free(p);
    return 0;
}
