%{
#include<stdio.h>
#include<string.h>
#include "graph.h"
#define YYDEBUG 1
extern char yytext[];
extern int line_number;
int ifFlag=0; 
int flagCount=0;
char *indexVar;
int indexFlag=0;
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

%type<text> declarator direct_declarator argument_expression_list
%type<text> declaration_specifiers declaration_list external_declaration if_statement statement expression expression_statement declaration init_declarator primary_expression postfix_expression unary_expression assignment_expression conditional_expression initializer struct_declaration struct_declarator_list struct_declarator	relational_expression shift_expression
%type<integer> storage_class_specifier

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start translation_unit

%%

primary_expression: IDENTIFIER  {/*printf("primat %s",$1);/*/ if(ifFlag==1){ currentIfNode->symbol[currentIfNode->symbolCount++] = strdup($1);} }
	| CONSTANT { $$=NULL;}
	| STRING_LITERAL { $$=NULL; }
	| '(' expression ')'
		 { /*printf("DD");/*/ 	 }
	;
	
postfix_expression
	: primary_expression {  printf("post1");   }
	| postfix_expression '[' expression ']'  { printf("1here %s %d",$3,indexFlag); indexVar = strdup($3); printf("%s", indexVar);  indexFlag = 1;}
	| postfix_expression '(' ')'  {  printf("2here");	 }
	| postfix_expression '(' argument_expression_list ')'  {printf("3here"); /* printf("post22 %s",$1);/*/ if(strcmp($1,"free")==0){ createNode($1,other); createNode($3,other);	}}
	| postfix_expression '.' IDENTIFIER  {  	 }
	| postfix_expression PTR_OP IDENTIFIER  {  $$=$3;	/*createNode($3,lhs);*/ /*printf("11/%s",$$);/*/ }
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
	: postfix_expression {  /*printf("unary1 %s",$1);/*/	/* $$=$1;*/ }
	| INC_OP unary_expression {  	/*printf("unary2");/*/ }
	| DEC_OP unary_expression {  	/*printf("unary3");/*/ }
	| unary_operator cast_expression {  /*	printf("unary4");/*/}
	| SIZEOF unary_expression {  	/* printf("signment");/*/}
	| SIZEOF '(' type_name ')'
	 {  	 }
	;
unary_operator
	: '&' {  	 }
	| '*' {  	 }
	| '+' {  printf("D1");	 }
	| '-' {  	 }
	| '~' {  	 }
	| '!'
	 {  	 }
	;
cast_expression
	: unary_expression { /* printf("D2");	*/ }
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
	| relational_expression '>' shift_expression { 	printf("S %s %s",$1,$3); }
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
	: conditional_expression {  printf("assignment_exp1 %s ",$1);	 }
	| unary_expression assignment_operator assignment_expression
	 {   printf("2");printf("%s",$1);createNode($1,lhs); if((indexFlag==1)&&(indexVar!=NULL)){ printf("%s %d ",indexVar,currentNode->indexCount); currentNode->index[currentNode->indexCount]=indexVar; printf("indec%s\n",currentNode->index[currentNode->indexCount++]); indexFlag=0;} if($3!=NULL){createNode($3,rhs);}/*init_symtab($1); /*printf("assiexp2 %s",$3);	/*/ }
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
	: assignment_expression {/*printf("assignment3 %s ",$1);/*/ }
	| expression ',' assignment_expression
	 { 	 }
	;
constant_expression
	: conditional_expression
	 {  	 }
	;
declaration
	: declaration_specifiers ';' { }
	| declaration_specifiers init_declarator_list ';' { /*printf("D");/*/ }  
	;
	

declaration_specifiers
	: storage_class_specifier {  }
	| storage_class_specifier declaration_specifiers { /* printf("\n***%s***\n",	$2); */	 }
	| type_specifier {  	 }
	| type_specifier declaration_specifiers {	 }
	| type_qualifier {  	 }
	| type_qualifier declaration_specifiers
		 {  	 }
	;
init_declarator_list
	: init_declarator {  /*createNode($1,declaration); printf("init+Dec1");	*/ }
	| init_declarator_list ',' init_declarator { /*printf("init_Dec2");createNode($3,declaration);*/}
	;
init_declarator
	: declarator {	printf("here 4");createNode($1,declaration);  /*$$=$1; printf("initdec1 ");/*/}
	| declarator '=' initializer
	 { printf("lhsS %s",$1);printf("here 5");createNode($1,lhs); if($3!=NULL){ /*printf(" rhs %s",$3);/*/createNode($3,rhs);}/*printf("=init %s",$3); /*rhs value*/	  }
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
	: struct_or_union IDENTIFIER  '{' struct_declaration_list '}' {  symtab_add($2); /*printf("a");/*/	 }
	| struct_or_union '{' struct_declaration_list '}' {  /*printf("b");/*/	 }
	| struct_or_union IDENTIFIER
		 { symtab_add($2); 	 }
	;
struct_or_union
	: STRUCT {  	 }
	| UNION
			 {  	 }
	;
struct_declaration_list
	: struct_declaration { /* printf("bb"); /*/createNode($1,declaration);	 }
	| struct_declaration_list struct_declaration
		 { /* printf("bb87");/*/	createNode($2,declaration); }
	;
struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' {$$=$2;}
	;
	
specifier_qualifier_list
	: type_specifier specifier_qualifier_list { /* printf("1");/*/	 }
	| type_specifier {  	 }
	| type_qualifier specifier_qualifier_list {  	 }
	| type_qualifier
		 {  	 }
	;
struct_declarator_list
	: struct_declarator { $$=$1; 	 }
	| struct_declarator_list ',' struct_declarator
		 {  	 }
	;
struct_declarator
	: declarator  {  $$=$1;	 }
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
	: IDENTIFIER {  $$=$1; /* printf("1");/*/}
	| '(' declarator ')' {  /*printf("2");/*/	 }
	| direct_declarator '[' constant_expression ']' {printf("3"); 	 }
	| direct_declarator '[' ']' {  	 /*printf("4");/*/}
	| direct_declarator '(' parameter_type_list ')' {/*printf("5");/*/  $$ = $1;	 }
	| direct_declarator '(' identifier_list ')' {  	/*printf("6"); /*/}
	| direct_declarator '(' ')'
		 {  	 /*printf("7");/*/}
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
	: declaration_specifiers declarator { /*/ printf("1");	/*/createNode($2,function_parameter);	 }
	| declaration_specifiers abstract_declarator {  /*printf("2");/*/	 }
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
	: assignment_expression {   }
	| '{' initializer_list '}' { /*printf("ini2");/*/ 	 }
	| '{' initializer_list ',' '}'
			 {  /*	printf("ini3");/*/ }
	;
initializer_list
	: initializer {  	 }
	| initializer_list ',' initializer
		 {  	 }

	;
statement
	: labeled_statement {  /*createNode("labeled_statement");*/printf("label");	 }
	| compound_statement {  /*printf("compound");*/	 }
	| expression_statement {  /*createNode($1,other);/*printf("\nexpression %s\n",$1);/*/}
	| selection_statement { }
	| iteration_statement { /*printf("iteration");*/  }
	| jump_statement		 { /* printf("h");/*/	/*createNode("jump_statement");*//*printf("jjmp");/*/ }
	
;

labeled_statement
	: IDENTIFIER ':' statement {  	 }
	| CASE {createNode("case",other);}constant_expression ':' statement {  	 }
	| DEFAULT ':' statement
		 {  	 }
	;
	
curly_brace
	: '{' { /*printf("befr");/*add_scope();*/}
	;
compound_statement
	: curly_brace '}' {  pop_scope();	 }
	| curly_brace statement_list '}' { /*pop_scope();/*//*printf("cmp1");/*/	 }
	| curly_brace declaration_list '}' { /*pop_scope();/*//*printf("cmp2"); 	/*/ }
	| curly_brace declaration_list statement_list '}' {/* pop_scope();/*//*printf("cmp3");/*/}
	
	;
declaration_list
	: declaration {/* printf("decl1");/*/}
	| declaration_list declaration { /*printf("decl1");//*/}
	;
	
statement_list
	: statement { /* printf("state1");/*/	 }
	| statement_list statement { /*printf("state2");/*/}
		
	;
expression_statement
	: ';' {  }
	| expression ';'
		 { /* printf("exp");/*/	 }
	;
if_statement
	: IF {createNode("if",if_node);ifFlag=1;currentIfNode = currentNode; currentIfNode->symbolCount=0;} '(' expression ')' { ifFlag=0; currentIfNode=NULL;/*printf("if-expression-%s ", $3);/*/ /*printf("6 %s",currentNode->symbol);/*/ push(currentNode);}
	
selection_statement
	: if_statement statement { /*printf("if");/*/ currentNode = pop();/* printf("current node pop = %s",currentNode->symbol);/*/	}
	| if_statement statement ELSE { createNode("else",ifelse_node);/*printf("current node pop = %s",currentNode->symbol);/*/ currentNode = pop(); /*createNode("else",other);/*/ push(currentNode);  } statement { currentNode = pop(); 	 }
	| switch_statement statement {currentNode = pop(); }
	;
switch_statement
	: SWITCH '(' expression ')' { createNode($3,switch_node);push(currentNode);}
	;
for_statement
	: FOR '(' expression_statement expression_statement ')' { }
	;
for_statement_extended
	: FOR '(' expression_statement expression_statement expression ')' { createNode($3,for_node); push(currentNode);/*printf("%s %s %s",$3,$4,$5);*/ }
	;
while_statement
	: WHILE '(' expression ')' { createNode($3,while_node); push(currentNode);}
	;
iteration_statement
	: while_statement statement {  currentNode = pop();	 }
	| DO statement WHILE '(' expression ')' ';' {  	 }
	| for_statement statement { currentNode = pop(); }
	| for_statement_extended statement
		 { }
	;
jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';' { /*printf("hello");/*/	createNode("break",other); }
	| RETURN ';' {	 }
	| RETURN expression ';'
		 {  	 }
	;
translation_unit
	: external_declaration {   }
	| translation_unit external_declaration { }
	;
external_declaration
	: function_definition {	/*printf("hello");/*/ FILE *fp; int a = traverse_graph_for_init_var(startNode);fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","a"); fprintf(fp,"}"); fclose(fp);
		int b = traverse_graph_for_mem_leaks(startNode); int c = traverse_graph_for_buffer_overflow(startNode);}
	| declaration { }

	;
function_definition
	: declaration_specifiers declarator declaration_list {createGraph();/*printf("1.%s 2.%s 3.%s",$1,$2,$3);/*/} compound_statement {	}
	| declaration_specifiers declarator {createGraph(); printf("here%s",$2);createNode($2,other);} compound_statement {	 }
	| declarator declaration_list {createGraph();/*printf("@");/*/} compound_statement {		 }
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