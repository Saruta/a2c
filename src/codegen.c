#include <stdio.h>
#include "grammar.h"
#include "codegen.h"
#include "parser.h"

char *getopstr(int op)
{
  switch (op)
  {
    case PLUS:
      return "+";
    case MINUS:
      return "-";
    case STAR:
      return "*";
    case SLASH:
      return "/";
    case DIV:
      return "div";
    case OR:
      return "||";
    case AND:
      return "&&";
    case MOD:
      return "%";
    case EQ:
      return "=";
    case NEQ:
      return "<>";
    default:
      return NULL;
  }
}

void print_single_var_decl(struct single_var_decl *single_var_decl)
{
  printf("%s ", single_var_decl->type_ident);
  unsigned i = 0;
  for (; i + 1 < single_var_decl->var_idents->list.size; ++i)
    printf("%s, ", list_nth(single_var_decl->var_idents->list, i));
  printf("%s;\n", list_nth(single_var_decl->var_idents->list, i));
}

void print_var_decl(struct var_decl *var_decl)
{
  for (unsigned i = 0; i < var_decl->decls.size; ++i)
    print_single_var_decl(list_nth(var_decl->decls, i));
}

void print_decls(struct declarations *declarations)
{
  print_var_decl(declarations->var_decl);
}

void print_prog(struct prog *prog)
{
  print_var_decl(prog->entry_point->var_decl);
  print_algo(prog->algo);
  printf("int main(void) {\n");
  print_instructions(prog->entry_point->instructions);
  printf("}\n");
}

void print_algo(struct algo *algo)
{
  printf("void ");
  printf("%s(void)\n{\n", algo->ident);
  print_decls(algo->declarations);
  print_instructions(algo->instructions);
  printf("}\n");
}

void free_single_var_decl(struct single_var_decl *single_var_decl)
{
  free(single_var_decl->type_ident);
  for (unsigned i = 0; i < single_var_decl->var_idents->list.size; ++i)
    free(list_nth(single_var_decl->var_idents->list, i));
  list_free(single_var_decl->var_idents->list);
  free(single_var_decl->var_idents);
  free(single_var_decl);
}

void free_var_decl(struct var_decl *var_decl)
{
  for (unsigned i = 0; i < var_decl->decls.size; ++i)
    free_single_var_decl(list_nth(var_decl->decls, i));
  list_free(var_decl->decls);
  free(var_decl);
}

void free_decls(struct declarations *declarations)
{
  free_var_decl(declarations->var_decl);
  free(declarations);
}

void free_algo(struct algo *algo)
{
  free_instructions(algo->instructions);
  free_decls(algo->declarations);
  free(algo->ident);
  free(algo);
}

void print_instructions(struct block *instructions)
{
  for (unsigned i = 0; i + 1 < instructions->list.size; ++i)
    print_instruction(list_nth(instructions->list, i));
  print_instruction(list_nth(instructions->list, instructions->list.size - 1));
}

void print_exprlist(struct exprlist *l)
{
  unsigned i = 0;
  for (; i + 1 < l->list.size; ++i)
  {
    print_expression(list_nth(l->list, i));
    printf(", ");
  }
  print_expression(list_nth(l->list, i));
}

void print_instruction(struct instruction *i)
{
  switch (i->kind)
  {
    case assignment:
      print_expression(i->instr.assignment.e1);
      printf(" = ");
      print_expression(i->instr.assignment.e2);
      printf(";\n");
      break;
    case whiledo:
      printf("while (");
      print_expression(i->instr.whiledo.cond);
      printf(") {\n");
      print_instructions(i->instr.whiledo.instructions);
      printf("}\n");
      break;
    case dowhile:
      printf("do {\n");
      print_instructions(i->instr.dowhile.instructions);
      printf("} while (");
      print_expression(i->instr.dowhile.cond);
      printf(");\n");
      break;
    case forloop:
      printf("for (; ");
      print_expression(i->instr.forloop.assignment->e1);
      if (i->instr.forloop.decreasing)
        printf(" >= ");
      else
        printf(" <= ");
      print_expression(i->instr.forloop.upto);
      if (i->instr.forloop.decreasing)
        printf("; --(");
      else
        printf("; ++(");
      print_expression(i->instr.forloop.assignment->e1);
      printf(")) {\n");
      print_instructions(i->instr.forloop.instructions);
      printf("}\n");
      break;
    case funcall:
      printf("%s(", i->instr.funcall.fun_ident);
      print_exprlist(i->instr.funcall.args);
      printf(");\n");
      break;
    default:
      printf("instruction not handled yet\n");
  }
}

void free_instructions(struct block *instructions)
{
  for (unsigned i = 0; i < instructions->list.size; ++i)
    free_instruction(list_nth(instructions->list, i));
  list_free(instructions->list);
  free(instructions);
}

void free_instruction(struct instruction *i)
{
  switch (i->kind)
  {
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
      free_expression(i->instr.dowhile.cond);
      free_instructions(i->instr.dowhile.instructions);
      break;
    case whiledo:
      free_expression(i->instr.whiledo.cond);
      free_instructions(i->instr.whiledo.instructions);
      break;
    case forloop:
      free_expression(i->instr.forloop.assignment->e1);
      free_expression(i->instr.forloop.assignment->e2);
      free(i->instr.forloop.assignment);
      free_instructions(i->instr.forloop.instructions);
      free_expression(i->instr.forloop.upto);
      break;
    case funcall:
      free_expressions(i->instr.funcall.args);
      free(i->instr.funcall.fun_ident);
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
      // TODO handle the XOR case here, because there is no corresponding
      // operator in C.
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
    case arrayexprtype:
      print_expression(e->val.arrayexpr.e1);
      for (unsigned i = 0; i < e->val.arrayexpr.indices->list.size; ++i)
      {
        printf("[");
        print_expression(list_nth(e->val.arrayexpr.indices->list, i));
        printf("]");
      }
      break;
    case identtype:
      printf("%s", e->val.ident);
      break;
    case stringtype:
      printf("%s", e->val.stringval);
      break;
    case booltype:
      printf("%d", e->val.boolval == true);
      break;
    case dereftype:
      printf("*");
      print_expression(e->val.deref.e);
      break;
    case funcalltype:
      printf("%s(", e->val.funcall.fun_ident);
      print_exprlist(e->val.funcall.args);
      printf(")");
      break;
    default:
      printf("expr not handled yet\n");
  }
}

void free_expressions(struct exprlist *l)
{
  for (unsigned i = 0; i < l->list.size; ++i)
    free_expression(list_nth(l->list, i));
  list_free(l->list);
  free(l);
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
    case arrayexprtype:
      free_expression(e->val.arrayexpr.e1);
      free_expressions(e->val.arrayexpr.indices);
      break;
    case identtype:
      free(e->val.ident);
      break;
    case stringtype:
      free(e->val.stringval);
      break;
    case dereftype:
      free_expression(e->val.deref.e);
      break;
    case funcalltype:
      free_expressions(e->val.funcall.args);
      free(e->val.funcall.fun_ident);
      break;
    case inttype:
    case booltype:
    default:
      break;
  }
  free(e);
}

void free_prog(struct prog *prog)
{
  free_var_decl(prog->entry_point->var_decl);
  free_instructions(prog->entry_point->instructions);
  free(prog->entry_point);
  free_algo(prog->algo);
}
