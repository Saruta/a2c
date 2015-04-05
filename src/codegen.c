#include <stdio.h>
#include "grammar.h"
#include "codegen.h"

void print_algo(struct algo *algo)
{
  printf("void ");
  printf("%s(void)\n{\n", algo->ident);
  print_instructions(algo->instructions);
  printf("}");
}

void free_algo(struct algo *algo)
{
  free_instructions(algo->instructions);
  free(algo);
}

void print_instructions(struct block instructions)
{
  for (unsigned i = 0; i < instructions.list.size - 1; ++i)
  {
    print_instruction(list_nth(instructions.list, i));
  }
  print_instruction(list_nth(instructions.list, instructions.list.size - 1));
}

void print_instruction(struct instruction *i)
{
  switch (i->kind)
  {
    case assignment:
      print_expression(i->instr.assignment.e1);
      printf(" = ");
      print_expression(i->instr.assignment.e2);
      break;
    default:
      printf("instruction not handled yet\n");
  }
  printf(";\n");
}

void free_instructions(struct block instructions)
{
  for (unsigned i = 0; i < instructions.list.size; ++i)
    free_instruction(list_nth(instructions.list, i));
  list_free(instructions.list);
}

void free_instruction(struct instruction *i)
{
  switch (i->kind)
  {
    case funcall:
      // TODO
      break;
    case assignment:
      free_expression(i->instr.assignment.e1);
      free_expression(i->instr.assignment.e2);
      break;
    case ifthenelse:
      // TODO
      break;
    case switchcase:
      // TODO free list of instructions once lists are implemented
      break;
    case dowhile:
      // TODO free list of instructions once lists are implemented
      break;
    case whiledo:
      // TODO free list of instructions once lists are implemented
      break;
    case forloop:
      // TODO free list of instructions once lists are implemented
      break;
    case returnstmt:
      break;
  }
  free(i);
}

void print_expression(struct expr *e)
{
  switch (e->exprtype)
  {
    case inttype:
      printf("%d", e->val.intval);
      break;
    case binopexprtype:
      printf("(");
      print_expression(e->val.binopexpr.e1);
      printf(" %s ", getopstr(e->val.binopexpr.op));
      print_expression(e->val.binopexpr.e2);
      printf(")");
      break;
    case unopexprtype:
      printf("(");
      printf("%s ", getopstr(e->val.unopexpr.op));
      print_expression(e->val.unopexpr.e);
      printf(")");
      break;
    case identtype:
      printf("%s", e->val.ident);
      break;
    case funcalltype:
      printf("%s(", e->val.funcall.fun_ident);
      print_expression(list_nth(e->val.funcall.args->list, 0));
      printf(")");
      break;
    default:
      printf("expr not handled yet\n");
  }
}

void free_expression(struct expr *e)
{
  switch (e->exprtype)
  {
    case binopexprtype:
      free_expression(e->val.binopexpr.e1);
      free_expression(e->val.binopexpr.e2);
      break;
    case unopexprtype:
      free_expression(e->val.unopexpr.e);
      break;
    default:
      break;
  }
  free(e);
}
