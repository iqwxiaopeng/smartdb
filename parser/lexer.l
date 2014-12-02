%{
/*
 * AT&T lex can't handle this lexer due to lex bugs.  It works with flex
 * 2.3.7, pclex 2.0.5, and MKS lex 3.1a.
 */


#include "parser.hpp"
#include <string.h>

int yywrap() { return 1; }

int lineno = 1;
extern void yyerror(const char *s);

%}
	/* MKS needs the next line to increase the NFA table */
%e 1200

%%

	/* literal keyword tokens */

(?I:ADA)		{ return ADA; }
(?I:ALL)		{ return ALL; }
(?I:AND)		{ return AND; }
(?I:AVG)		{ return AMMSC; }
(?I:MIN)		{ return AMMSC; }
(?I:MAX)		{ return AMMSC; }
(?I:SUM)		{ return AMMSC; }
(?I:COUNT)		{ return AMMSC; }
(?I:ANY)		{ return ANY; }
(?I:AS)		{ return AS; }
(?I:ASC)		{ return ASC; }
(?I:AUTHORIZATION)	{ return AUTHORIZATION; }
(?I:BETWEEN)		{ return BETWEEN; }
(?I:BY)		{ return BY; }
(?I:CHAR(ACTER)?)	{ return CHARACTER; }
(?I:CHECK)		{ return CHECK; }
(?I:CLOSE)		{ return CLOSE; }
(?I:COBOL)		{ return COBOL; }
(?I:COMMIT)		{ return COMMIT; }
(?I:CONTINUE)	{ return CONTINUE; }
(?I:CREATE)		{ return CREATE; }
(?I:CURRENT)		{ return CURRENT; }
(?I:CURSOR)		{ return CURSOR; }
(?I:DECIMAL)		{ return DECIMAL; }
(?I:DECLARE)		{ return DECLARE; }
(?I:DEFAULT)		{ return DEFAULT; }
(?I:DELETE)		{ return DELETE; }
(?I:DESC)		{ return DESC; }
(?I:DISTINCT)	{ return DISTINCT; }
(?I:DOUBLE)		{ return DOUBLE; }
(?I:ESCAPE)		{ return ESCAPE; }
(?I:EXISTS)		{ return EXISTS; }
(?I:FETCH)		{ return FETCH; }
(?I:FLOAT)		{ return FLOAT; }
(?I:FOR)		{ return FOR; }
(?I:FOREIGN)		{ return FOREIGN; }
(?I:FORTRAN)		{ return FORTRAN; }
(?I:FOUND)		{ return FOUND; }
(?I:FROM)		{ return FROM; }
(?i:GO[ \t]*TO)	{ return GOTO; }
(?I:GRANT)		{ return GRANT; }
(?I:GROUP)		{ return GROUP; }
(?I:HAVING)		{ return HAVING; }
(?I:IN)		{ return IN; }
(?I:INDICATOR)	{ return INDICATOR; }
(?I:INSERT)		{ return INSERT; }
(?I:INT(EGER)?)	{ return INTEGER; }
(?I:INTO)		{ return INTO; }
(?I:IS)		{ return IS; }
(?I:KEY)		{ return KEY; }
(?I:LANGUAGE)	{ return LANGUAGE; }
(?I:LIKE)		{ return LIKE; }
(?I:MODULE)		{ return MODULE; }
(?I:NOT)		{ return NOT; }
(?I:NULL)		{ return NULLX; }
(?I:NUMERIC)		{ return NUMERIC; }
(?I:OF)		{ return OF; }
(?I:ON)		{ return ON; }
(?I:OPEN)		{ return OPEN; }
(?I:OPTION)		{ return OPTION; }
(?I:OR)		{ return OR; }
(?I:ORDER)		{ return ORDER; }
(?I:PASCAL)		{ return PASCAL; }
(?I:PLI)		{ return PLI; }
(?I:PRECISION)	{ return PRECISION; }
(?I:PRIMARY)		{ return PRIMARY; }
(?I:PRIVILEGES)	{ return PRIVILEGES; }
(?I:PROCEDURE)	{ return PROCEDURE; }
(?I:PUBLIC)		{ return PUBLIC; }
(?I:REAL)		{ return REAL; }
(?I:REFERENCES)	{ return REFERENCES; }
(?I:ROLLBACK)	{ return ROLLBACK; }
(?I:SCHEMA)		{ return SCHEMA; }
(?i:SELECT)		{ return SELECT; }
(?I:SET)		{ return SET; }
(?I:SMALLINT)	{ return SMALLINT; }
(?I:SOME)		{ return SOME; }
(?I:SQLCODE)		{ return SQLCODE; }
(?I:TABLE)		{ return TABLE; }
(?I:TO)		{ return TO; }
(?I:UNION)		{ return UNION; }
(?I:UNIQUE)		{ return UNIQUE; }
(?I:UPDATE)		{ return UPDATE; }
(?I:USER)		{ return USER; }
(?I:VALUES)		{ return VALUES; }
(?I:VIEW)		{ return VIEW; }
(?I:WHENEVER)	{ return WHENEVER; }
(?I:WHERE)		{ return WHERE; }
(?I:WITH)		{ return WITH; }
(?I:WORK)		{ return WORK; }

	/* punctuation */

"="	|
"<>" 	|
"<"	|
">"	|
"<="	|
">="		{ return COMPARISON; }

[-+*\/:(),.;] { return yytext[0]; }

	/* names */

[A-Za-z][A-Za-z0-9_]* {
  yylval.strval = yytext;
  return IDENTIFIER;
}

	/* numbers */

[0-9]+	|
[0-9]+"."[0-9]* |
"."[0-9]*	{ return INTNUM; }

[0-9]+[eE][+-]?[0-9]+	|
[0-9]+"."[0-9]*[eE][+-]?[0-9]+ |
"."[0-9]*[eE][+-]?[0-9]+	{ return APPROXNUM; }

	/* strings */

'[^'\n]*'	{
		int c = input();

		unput(c);	/* just peeking */
		if(c != '\'') {
			return STRING;
		} else
			yymore();
	}
		
'[^'\n]*$	{ yyerror("Unterminated string"); }

\n		lineno++;

[ \t\r]+	;	/* white space */

"--".*$		;	/* comment */

%%

extern
void yyerror(const char *s)
{
	fprintf(stderr, "%d: %s at %s\n", lineno, s, yytext);
}

/* int main() */
/* { */
/* 	if(!yyparse()) */
/* 		printf("SQL parse worked\n"); */
/* 	else */
/* 		printf("SQL parse failed\n"); */
/* 	return 0; */
/* } */
