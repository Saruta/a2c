#ifndef STDLIBALGO_H_
#define STDLIBALGO_H_

# include "a2c.h"

enum e_types
{
  E_TYPE_INT  =   0 ,
  E_TYPE_CHAR =   1 ,
  E_TYPE_REAL       ,
  E_TYPE_BOOLEAN    ,
  E_TYPE_STRING     ,
  E_TYPE_INT_VECT   ,
  E_TYPE_BOOL_VECT
};

static char *types_str[2][7] = 
  { {"entier", "caractere", "reel", "booleen", "chaine", 
      "t_vect_entiers", "t_vect_booleens"},
    {"int", "char", "real", "boolean", "string", 
      "t_int_vect", "t_bool_vect"} };

/* types */
#  define TYPE_INT          types_str[current_lang][E_TYPE_INT]
#  define TYPE_CHAR         types_str[current_lang][E_TYPE_CHAR]
#  define TYPE_REAL         types_str[current_lang][E_TYPE_REAL]
#  define TYPE_BOOLEAN      types_str[current_lang][E_TYPE_BOOLEAN]
#  define TYPE_STRING       types_str[current_lang][E_TYPE_STRING]
#  define TYPE_INT_VECT     types_str[current_lang][E_TYPE_INT_VECT]
#  define TYPE_BOOL_VECT    types_str[current_lang][E_TYPE_BOOL_VECT] 


void fill_std_types(struct symtable *syms);
void fill_std_fun(struct symtable *syms);

#endif
