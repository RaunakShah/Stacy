%{
#include<stdio.h>
#include<string.h>
#include "graph.h"
#define YYDEBUG 1

extern char yytext[];
%}

%union{
  int integer;
  char *text;
  struct {
    char *variable;
	char *type;
  } symtab_entry;
};

%token<text> IDENTIFIER

%token CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type<text> declarator direct_declarator 
%type<text> declaration_specifiers declaration_list external_declaration if_statement statement expression expression_statement declaration init_declarator primary_expression postfix_expression unary_expression assignment_expression
%type<integer> storage_class_specifier

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start translation_unit

%%

primary_expression: IDENTIFIER  { $$=$1; }
	| CONSTANT { }
	| STRING_LITERAL { }
	| '(' expression ')'
		 {  	 }
	;
	
postfix_expression
	: primary_expression {  /*printf("post1"); */ $$ = $1;	 }
	| postfix_expression '[' expression ']'  {  	 }
	| postfix_expression '(' ')'  {  	 }
	| postfix_expression '(' argument_expression_list ')'  {  	 }
	| postfix_expression '.' IDENTIFIER  {  	 }
	| postfix_expression PTR_OP IDENTIFIER  {  	 }
	| postfix_expression INC_OP  {  	 }
	| postfix_expression DEC_OP
	 {  	 }
	;
argument_expression_list
	: assignment_expression  {  	 }
	| argument_expression_list ',' assignment_expression
	 {  	 }
	;
unary_expression
	: postfix_expression {  /*printf("unary");	*/ $$=$1; }
	| INC_OP unary_expression {  	printf("unary2"); }
	| DEC_OP unary_expression {  	printf("unary3"); }
	| unary_operator cast_expression {  	 printf("unary4");}
	| SIZEOF unary_expression {  	 printf("assignment");}
	| SIZEOF '(' type_name ')'
	 {  	 }
	;
unary_operator
	: '&' {  	 }
	| '*' {  	 }
	| '+' {  	 }
	| '-' {  	 }
	| '~' {  	 }
	| '!'
	 {  	 }
	;
cast_expression
	: unary_expression {  	 }
	| '(' type_name ')' cast_expression
		 {  	 }
	;
multiplicative_expression
	: cast_expression {  	 }
	| multiplicative_expression '*' cast_expression {  	 }
	| multiplicative_expression '/' cast_expression {  	 }
	| multiplicative_expression '%' cast_expression
	 {  	 }
	;
additive_expression
	: multiplicative_expression {  	 }
	| additive_expression '+' multiplicative_expression {  	 }
	| additive_expression '-' multiplicative_expression
	 {  	 }
	;
shift_expression
	: additive_expression {  	 }
	| shift_expression LEFT_OP additive_expression {  	 }
	| shift_expression RIGHT_OP additive_expression
		 {  	 }
	;
relational_expression
	: shift_expression {  	 }
	| relational_expression '<' shift_expression {  	 }
	| relational_expression '>' shift_expression {  	 }
	| relational_expression LE_OP shift_expression {  	 }
	| relational_expression GE_OP shift_expression
		 {  	 }
	;
equality_expression
	: relational_expression  {  	 }
	| equality_expression EQ_OP relational_expression {  	 }
	| equality_expression NE_OP relational_expression
	 {  	 }
	;
and_expression
	: equality_expression {  	 }
	| and_expression '&' equality_expression
		 {  	 }
	;
exclusive_or_expression
	: and_expression {  	 }
	| exclusive_or_expression '^' and_expression
	 {  	 }
	;
inclusive_or_expression
	: exclusive_or_expression {  	 }
	| inclusive_or_expression '|' exclusive_or_expression
	 {  	 }
	;
logical_and_expression
	: inclusive_or_expression {  	 }
	| logical_and_expression AND_OP inclusive_or_expression
	 {  	 }
	;
logical_or_expression
	: logical_and_expression {  	 }
	| logical_or_expression OR_OP logical_and_expression
	 {  	 }
	;
conditional_expression
	: logical_or_expression {  	 }
	| logical_or_expression '?' expression ':' conditional_expression
	 {  	 }
	;
assignment_expression
	: conditional_expression {  printf("assignment_exp1");	 }
	| unary_expression assignment_operator assignment_expression
	 {   init_symtab($1);	 }
	;
assignment_operator
	: '=' {  	 }
	| MUL_ASSIGN {  	 }
	| DIV_ASSIGN {  	 }
	| MOD_ASSIGN {  	 }
	| ADD_ASSIGN {  	 }
	| SUB_ASSIGN {  	 }
	| LEFT_ASSIGN {  	 }
	| RIGHT_ASSIGN {  	 }
	| AND_ASSIGN {  	 }
	| XOR_ASSIGN {  	 }
	| OR_ASSIGN
	 {  	 }
	;
expression
	: assignment_expression { printf("assignment"); }
	| expression ',' assignment_expression
	 { 	 }
	;
constant_expression
	: conditional_expression
	 {  	 }
	;
declaration
	: declaration_specifiers ';' { }
	| declaration_specifiers init_declarator_list ';' { printf("D"); }  
	;
	

declaration_specifiers
	: storage_class_specifier {  }
	| storage_class_specifier declaration_specifiers {  printf("\n***%s***\n",	$2); 	 }
	| type_specifier {  	 }
	| type_specifier declaration_specifiers {	 }
	| type_qualifier {  	 }
	| type_qualifier declaration_specifiers
		 {  	 }
	;
init_declarator_list
	: init_declarator {  createNode($1,declaration); printf("%s", $1);	 }
	| init_declarator_list ',' init_declarator { printf("%s", $3);createNode($3,declaration);}
	;
init_declarator
	: declarator {	$$=$1; }
	| declarator '=' initializer
	 {  printf("sssSS");	  }
	;
storage_class_specifier
	: EXTERN {  	 }
	| STATIC {  	 }
	| AUTO {	 }
	| REGISTER {}
	| TYPEDEF {}
	;
	
type_specifier
	: VOID 			{	  }
	| CHAR {  	 }
	| SHORT {  	 }
	| INT {  	 }
	| LONG {  	 }
	| FLOAT {  	 }
	| DOUBLE {  	 }
	| SIGNED {  	 }
	| UNSIGNED {  	 }
	| struct_or_union_specifier {  	 }
	| enum_specifier {  	 }
	| TYPE_NAME
		 {  	 }
	;
struct_or_union_specifier
	: struct_or_union IDENTIFIER  '{' struct_declaration_list '}' {  symtab_add($2); printf("a");	 }
	| struct_or_union '{' struct_declaration_list '}' {  printf("b");	 }
	| struct_or_union IDENTIFIER
		 { symtab_add($2); 	 }
	;
struct_or_union
	: STRUCT {  	 }
	| UNION
			 {  	 }
	;
struct_declaration_list
	: struct_declaration {  printf("bb");	 }
	| struct_declaration_list struct_declaration
		 {  printf("bb87");	 }
	;
struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' {printf("S");}
	;
	
specifier_qualifier_list
	: type_specifier specifier_qualifier_list {  printf("1");	 }
	| type_specifier {  	 }
	| type_qualifier specifier_qualifier_list {  	 }
	| type_qualifier
		 {  	 }
	;
struct_declarator_list
	: struct_declarator {  	 }
	| struct_declarator_list ',' struct_declarator
		 {  	 }
	;
struct_declarator
	: declarator  {  	 }
	| ':' constant_expression {  	 }
	| declarator ':' constant_expression
		 {  	 }
	;
enum_specifier
	: ENUM '{' enumerator_list '}' {  createNode("ENUM1");	 }
	| ENUM IDENTIFIER '{' enumerator_list '}' {  createNode("ENUM2");	 }
	| ENUM IDENTIFIER
		 {  createNode("ENUM3");	 }
	;
enumerator_list
	: enumerator {  	 }
	| enumerator_list ',' enumerator
		 {  	 }
	;
enumerator
	: IDENTIFIER {  	 }
	| IDENTIFIER '=' constant_expression
			 {  	 }
	;
type_qualifier
	: CONST {  	 }
	| VOLATILE
		 {  	 }
	;
declarator
	: pointer direct_declarator {  	$$ = $2; }
	| direct_declarator
		 {  	$$ = $1; }
	;
direct_declarator
	: IDENTIFIER {  $$=$1;  }
	| '(' declarator ')' {  	 }
	| direct_declarator '[' constant_expression ']' {  	 }
	| direct_declarator '[' ']' {  	 }
	| direct_declarator '(' parameter_type_list ')' {  $$ = $1;	 }
	| direct_declarator '(' identifier_list ')' {  	 }
	| direct_declarator '(' ')'
		 {  	 }
	;
pointer
	: '*' {  	 }
	| '*' type_qualifier_list {  	 }
	| '*' pointer {  	 }
	| '*' type_qualifier_list pointer
		 {  	 }
	;
type_qualifier_list
	: type_qualifier {  	 }
	| type_qualifier_list type_qualifier
			 {  	 }

	;
parameter_type_list
	: parameter_list {  	 }
	| parameter_list ',' ELLIPSIS
		 {  	 }
	;
parameter_list
	: parameter_declaration {  	 }
	| parameter_list ',' parameter_declaration
		 {  	 }
	;
parameter_declaration
	: declaration_specifiers declarator {  	 }
	| declaration_specifiers abstract_declarator {  	 }
	| declaration_specifiers
		 {  	 }
	;
identifier_list
	: IDENTIFIER {  	 }
	| identifier_list ',' IDENTIFIER
		 {  	 }
	;
type_name
	: specifier_qualifier_list {  	 }
	| specifier_qualifier_list abstract_declarator
			 {  	 }
	;
abstract_declarator
	: pointer {  	 }
	| direct_abstract_declarator {  	 }
	| pointer direct_abstract_declarator
		 {  	 }
	;
direct_abstract_declarator
	: '(' abstract_declarator ')' {  	 }
	| '[' ']' {  	 }
	| '[' constant_expression ']' {  	 }
	| direct_abstract_declarator '[' ']' {  	 }
	| direct_abstract_declarator '[' constant_expression ']' {  	 }
	| '(' ')' {  	 }
	| '(' parameter_type_list ')' {  	 }
	| direct_abstract_declarator '(' ')' {  	 }
	| direct_abstract_declarator '(' parameter_type_list ')'
		 {  	 }
	;
initializer
	: assignment_expression {  	 }
	| '{' initializer_list '}' {  	 }
	| '{' initializer_list ',' '}'
			 {  	 }
	;
initializer_list
	: initializer {  	 }
	| initializer_list ',' initializer
		 {  	 }

	;
statement
	: labeled_statement {  createNode("labeled_statement");printf("label");	 }
	| compound_statement {  /*printf("compound");*/	 }
	| expression_statement {  createNode($1,other);printf("\nexpression %s\n",$1);}
	| selection_statement { }
	| iteration_statement { /*printf("iteration");*/  }
	| jump_statement		 {  printf("h");	createNode("jump_statement");printf("jjmp"); }
	
;
labeled_statement
	: IDENTIFIER ':' statement {  	 }
	| CASE constant_expression ':' statement {  	 }
	| DEFAULT ':' statement
		 {  	 }
	;
	
curly_brace
	: '{' { printf("befr");add_scope();}
	;
compound_statement
	: curly_brace '}' {  pop_scope();	 }
	| curly_brace statement_list '}' { pop_scope();/* printf("cmp1");	*/ }
	| curly_brace declaration_list '}' { pop_scope();/*printf("cmp2");*/  	 }
	| curly_brace declaration_list statement_list '}' { pop_scope();/*printf("cmp3");*/}
	
	;
declaration_list
	: declaration { }
	| declaration_list declaration { }
	;
	
statement_list
	: statement { /* printf("state1");	*/ }
	| statement_list statement { /*printf("state2");*/}
		
	;
expression_statement
	: ';' {  	 }
	| expression ';'
		 {  	 }
	;
if_statement
	: IF '(' expression ')' { createNode($3); push(currentNode);}
	
selection_statement
	: if_statement statement { printf("if");currentNode = pop();	}
	| if_statement statement ELSE { push(currentNode); } statement { currentNode = pop(); 	 }
	| switch_statement statement { }
	;
switch_statement
	: SWITCH '(' expression ')' { createNode($3);}
	;
for_statement
	: FOR '(' expression_statement expression_statement ')' { }
	;
for_statement_extended
	: FOR '(' expression_statement expression_statement expression ')' { }
	;
iteration_statement
	: WHILE '(' expression ')' statement {  	 }
	| DO statement WHILE '(' expression ')' ';' {  	 }
	| for_statement statement 
	| for_statement_extended statement
		 { }
	;
jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';' { printf("hello");	 }
	| RETURN ';' {	 }
	| RETURN expression ';'
		 {  	 }
	;
translation_unit
	: external_declaration {   }
	| translation_unit external_declaration { }
	;
external_declaration
	: function_definition {	printf("hello");  int a = traverse_graph(startNode); print_symb(); }
	| declaration { }

	;
function_definition
	: declaration_specifiers declarator declaration_list {createGraph();printf("1.%s 2.%s 3.%s",$1,$2,$3);} compound_statement {	}
	| declaration_specifiers declarator {createGraph(); createNode($2,other);} compound_statement {	 }
	| declarator declaration_list {createGraph();} compound_statement {		 }
	| declarator{createGraph();} compound_statement {}
	;
%%

extern int column;
main() {
/*extern int yydebug;
yydebug = 1;*/
    yyparse();
 }
yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

