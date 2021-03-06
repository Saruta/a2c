#include <stdlib.h>
/* ****************** */
/* VECTEURS D'ENTIERS */
/* ****************** */
typedef int t_vect_entiers[1000];

/* ******************** */
/* VECTEURS DE BOOLEENS */
/* ******************** */
typedef int t_vect_booleens[1000];

typedef struct t_list
{
  t_vect_entiers elts;
  int longueur;
} t_list;

static inline
int supprimer(t_list L, int k)
{
  if((k<1) || (k>L.longueur))
    return 0;
  else {
    for(int i=k; i< L.longueur - 1;i++)
    {
    }
    L.longueur = L.longueur -1;
   return 1;
  }
}

static inline
int inserer(t_list L, int k, int e)
{
  if((L.longueur >= 1000) || (k < 1) || (k>L.longueur + 1))
  {
    return 0;
  }
  else
  {
    for(int i = L.longueur; i > k; i--)
    {
      L.elts[i+1] = L.elts[i];
    }
    L.elts[k] = e;
    L.longueur ++;
    return 1;
  }
}

static inline
void concatener(t_list L1, t_list L2, t_list Lres)
{
  if((L1.longueur + L2.longueur) <= 1000)
  {
    for(int i = 1; i< L1.longueur; i++)
      Lres.elts[i] = L1.elts[i];
    for(int i = L1.longueur +1; i<L1.longueur + L2.longueur; i++)
      Lres.elts[i] = L2.elts[i-L1.longueur];
    Lres.longueur = L1.longueur + L2.longueur;
  }
}

static inline
int est_present(t_list L, int x)
{
  int i =1;
  while((i<= L.longueur) && (x != L.elts[i]))
    i++;
  return(i<=L.longueur);
}

/* ****************** */
/* LISTES DYNAMIQUES */
/* ****************** */
typedef struct t_node t_node;
typedef t_node *t_pList;
struct t_node
{
  int val;
  t_pList suiv;
};

static inline
t_pList ajout_tete(t_pList L, int e)
{
  t_pList new = malloc(sizeof new);
  new->val = e;
  new->suiv = L;
  return new;
}

static inline
int longueur(t_pList L)
{
  int lg = 0;
  while(L != NULL)
  {
    lg++;
    L=L->suiv;
  }
  return lg;
}

static inline
t_pList acces(t_pList L, int k)
{
  while((L != NULL) && (k != 1))
  {
    k--;
    L = L->suiv;
  }
  return L;
}

static inline
t_pList rechercher(t_pList L, int x)
{
  while((L != NULL) && (x != L->val))
  {
    L = L->suiv;
  }
  return L;
}

// void concatener(t_pList L1, t_pList L2)
// {
//   t_pList p;
//   if(L1 == NULL)
//     L1 = L2;
//   else{
//     if(L2 != NULL)
//     {
//       p = L1;
//       while(p->suiv != NULL)
//       {
//        p = p->suiv;
//       }
//       p->suiv = L2;
//     }
//   }
// }

/* PILES DYNAMIQUES */
typedef struct t_node_pile t_node_pile;
typedef t_node_pile *t_pile;
struct t_node_pile
{
  int sommet;
  t_pile suiv;
};

static inline
t_pile pile_vide()
{
  return NULL;
}

static inline
int est_vide(t_pile p)
{
  return (p == NULL);
}

static inline
void empiler(t_pile *pile, int e)
{
  t_pile new = malloc(sizeof(struct t_node_pile));
  if(new != NULL)
  {
    new->sommet = e;
    new->suiv = *pile;
    *pile = new;
  }
}

static inline
int depiler(t_pile *pile)
{
  int r = -1;
  if (*pile != NULL)
  {
    t_pile temp = (*pile)->suiv;
    r = (*pile)->sommet;
    free(*pile);
    *pile = temp;
  }
  return r;
}

static inline
void vide_pile(t_pile *pile)
{
  while(*pile)
  {
    depiler(pile);
  }
}

/* FILES */
typedef struct t_node_file t_node_file;
typedef t_node_file *t_file;
struct t_node_file
{
  int val;
  t_file suiv;
};

static inline
t_file file_vide()
{
  return NULL;
}

static inline
int est_file_vide(t_file f)
{
  return (f == NULL);
}

static inline
void enfiler(t_file *file, int e)
{
  t_file new = malloc(sizeof(struct t_node_file));
  new->val = e;
  if(*file == NULL)
    new->suiv = new;
  else
  {
    new->suiv = (*file)->suiv;
    (*file)->suiv = new;
  }
  *file = new;
}

static inline
int defiler(t_file *file)
{
  int r = -1;
  if (!*file)
    return -1;
  else if ((*file)->suiv == *file)
  {
    r = (*file)->val;
    free(*file);
    *file = NULL;
    return r;
  }
  else
  {
    t_file tmp = (*file)->suiv->suiv;
    r = (*file)->suiv->val;
    free((*file)->suiv);
    (*file)->suiv = tmp;
  }
  return r;
}

static inline
void vide_file(t_file *file)
{
  while(*file)
  {
    defiler(file);
  }
}

/* ARBRES BINAIRES */
typedef struct t_noeud_bin t_noeud_bin;
typedef t_noeud_bin *t_arbre_bin;

struct t_noeud_bin
{
  int cle;
  t_arbre_bin fg;
  t_arbre_bin fd;
};

/* /\* ARBRES GENERAUX DYN *\/ */
/* typedef *t_noeud_ag t_arbre_dyn; */

/* typedef struct t_noeud_ag */
/* { */
/*   int cle; */
/*   t_arbre_dyn fils; */
/*   t_arbre_dyn frere; */
/* } t_noeud_ag; */

/* /\* ARBRES GENERAUX STAT *\/ */
/* typedef *s_som t_listsom; */
/* typedef *s_adj t_listadj; */

/* typedef struct s_som */
/* { */
/*   int som; */
/*   t_listadj succ; */
/*   t_listadj pred; */
/*   t_listsom suiv; */
/* } s_som; */

/* typedef struct s_adj */
/* { */
/*   int nb; */
/*   float cout; */
/*   t_listadj suiv; */
/*   t_listsom som; */
/* } s_adj; */

/* typedef struct t_graph_stat */
/* { */
/*   booleen orient; */
/*   int ordre; */
/*   t_mat_adj adj; */
/*   t_mat_cout cout; */
/* } t_graph_stat; */

/* /\* ARBRES REPRESENTATION NUPLETS *\/ */
/* typedef *t_noeud_nuplet t_arbre_nuplets; */

/* typedef struct t_noeud_nuplet */
/* { */
/*   int cle; */
/*   t_noeud_nuplet fils; */
/*   int nbFils; */
/* } t_noeud_nuplet; */

/* /\* GRAPHES STAT *\/ */
/* const int Max_sommets = 100; */

/* int t_mat_adj[Max_sommets][Max_sommets]; */
/* float t_mat_cout[Max_sommets][Max_sommets]; */

/* typedef struct t_graph_stat */
/* { */
/*   booleen orient; */
/*   int ordre; */
/*   t_mat_adj adj; */
/*   t_mat_cout cout; */
/* } t_graph_stat; */
/*  */
