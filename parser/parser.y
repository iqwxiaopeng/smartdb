%{
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1
%}
%union {
  const Smartdb::Ast::SelectList *select_list_v;
  const Smartdb::Ast::OrderByClause *order_by_clause_v;
  const std::vector<const Smartdb::Ast::OrderSpecification *> *sort_specification_list_v;
  const Smartdb::Ast::SortSpecification *sort_specification_v;
  unsigned int ordering_specification_v;
  const Smartdb::Ast::Column *column_v;
  std::vector<std::string> string_list_v; //これがstringだと、termとかの計算結果を表現できない
  std::string string_v;
}

%token ASC BY COMMA DESC ORDER SELECT
%token <string_v> COLUMN_NAME

%type <select_list_v> select_list
%type <order_by_clause_v> order_by_clause
%type <sort_specification_list_v> sort_specification_list
%type <sort_specification_v> sort_specification
%type <ordering_specification_v> ordering_specification
%type <column_v> sort_key column_name
%type <string_list_v> select_sublist
%type <string_v> identifier

%%
query_expression
  : query_expression
  ;
query_specification
  : SELECT select_list table_expression
  ;
select_list
  :  select_sublist {
       $$ = new Smartdb::Ast::SelectList;
       $$->columns = $1;
     }
     /* [TODO] - asterisk support */
  ;
select_sublist
  : derived_column COMMA select_sublist {
      $$->push_back($3);
    }
  | derived_column {
      $$ = new std::vector<std::string>;
      $$->push_back($1);
    }
  ;
derived_column
  : value_expression
    /* [TODO] - AS support */
  ;
value_expression
  : numeric_value_expression
  | general_literal
  ;
numeric_value_expression
  : term
    /* [TODO] - +, - support */
  ;
term
  : factor
    /* [TODO] - *, / support */
  ;
factor
  : value_expression_primary
    /* [TODO] +- support */
  ;
value_expression_primary
  : unsigned_value_expression
  | column_reference
  | LEFT_PAREN value_expression RIGHT_PAREN {
      $$ = $2;
    }
  ;
unsigned_value_expression
  : unsigned_literal
  ;
unsigned_literal
  : unsigned_numeric_literal
  | general_literal
  ;
column_reference
  : column_name
  ;
order_by_clause
  : { $$ = NULL; }
  | ORDER BY sort_specification_list {
      $$ = new Smartdb::Ast::OrderByClause;
      order_by_clause->sort_specification_list = $3;
    }
  ;
sort_specification_list
  : sort_specification_list COMMA sort_specification {
      $$->push_back($3);
    }
  | sort_specification {
      $$ = new std::vector<const Smartdb::Ast::SortSpecification *>;
      $$->push_back($1);
    }
  ;
sort_specification
  : sort_key ordering_specification {
      $$ = new Smartdb::Ast::SortSpecification;
      switch ($2) {
      case ASC: $$->asc = true;
      case DESC: $$->asc = false;
      }
      $$->column = $1;
    }
  ;
sort_key
  : column_name
  /* [TODO] - integer column spec */
  ;
ordering_specification
  : { $$ = ASC; } /* default */
  | ASC { $$ = ASC; }
  | DESC { $$ = DESC; }
  ;
column_name
  : identifier {
      $$ = new Smartdb::Ast::Column;
      $$->name = $1;
    }
  ;
identifier
  : COLUMN_NAME

/* line_list */
/*     : line */
/*     | line_list line */
/*     ; */
/* line */
/*     : expression CR */
/*     { */
/*         printf(">>%lf\n", $1); */
/*     } */
/* expression */
/*     : term */
/*     | expression ADD term */
/*     { */
/*         $$ = $1 + $3; */
/*     } */
/*     | expression SUB term */
/*     { */
/*         $$ = $1 - $3; */
/*     } */
/*     ; */
/* term */
/*     : primary_expression */
/*     | term MUL primary_expression  */
/*     { */
/*         $$ = $1 * $3; */
/*     } */
/*     | term DIV primary_expression */
/*     { */
/*         $$ = $1 / $3; */
/*     } */
/*     ; */
/* primary_expression */
/*     : DOUBLE_LITERAL */
/*     ;                  */
%%
int
yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int main(void)
{
    extern int yyparse(void);
    extern FILE *yyin;

    yyin = stdin;
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}
