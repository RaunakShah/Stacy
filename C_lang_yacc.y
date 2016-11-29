/*YACC File*/
%{
#include<stdio.h>
#include<string.h>
#include "graph.h"
#define YYDEBUG 1
extern char yytext[];
extern int line_number;
int selectionFlag=0; 
int flagCount=0;
char *indexVar;
int indexFlag=0;
int andOp=0;
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
%type<text> declaration_specifiers declaration_list external_declaration if_statement statement expression expression_statement declaration init_declarator primary_expression postfix_expression unary_expression assignment_expression conditional_expression initializer struct_declaration struct_declarator_list struct_declarator	relational_expression shift_expression logical_and_expression inclusive_or_expression equality_expression
%type<integer> storage_class_specifier

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start translation_unit

%%

primary_expression: IDENTIFIER  { 
		if(andOp==1){ 
			createNode($1,lhs); andOp=0;
		}
		if(selectionFlag==1){
			currentSelectionNode->symbol[currentSelectionNode->symbolCount++] = strdup($1);
		} 
	}
	| CONSTANT { $$=NULL;}
	| STRING_LITERAL { $$=NULL; }
	| '(' expression ')'
	;
	
postfix_expression
	: primary_expression 
	| postfix_expression '[' expression ']'  {  indexVar = strdup($3); indexFlag = 1;}
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'  { if(strcmp($1,"free")==0){ createNode($1,other); createNode($3,other);	}}
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER  {  $$=$3;}
	| postfix_expression INC_OP  
	| postfix_expression DEC_OP
	;
argument_expression_list
	: assignment_expression  {  	 }
	| argument_expression_list ',' assignment_expression
	 {  	 }
	;
unary_expression
	: postfix_expression 
	| INC_OP unary_expression 
	| DEC_OP unary_expression 
	| unary_operator cast_expression 
	| SIZEOF unary_expression 
	| SIZEOF '(' type_name ')'
	;
unary_operator
	: '&' {  andOp=1; }
	| '*' {  	 }
	| '+' {  	 }
	| '-' {  	 }
	| '~' {  	 }
	| '!'
	 {  	 }
	;
cast_expression
	: unary_expression 
	| '(' type_name ')' cast_expression
	;
multiplicative_expression
	: cast_expression 
	| multiplicative_expression '*' cast_expression 
	| multiplicative_expression '/' cast_expression 
	| multiplicative_expression '%' cast_expression
	;
additive_expression
	: multiplicative_expression 
	| additive_expression '+' multiplicative_expression 
	| additive_expression '-' multiplicative_expression
	;
shift_expression
	: additive_expression 
	| shift_expression LEFT_OP additive_expression 
	| shift_expression RIGHT_OP additive_expression
	;
relational_expression
	: shift_expression 
	| relational_expression '<' shift_expression 
	| relational_expression '>' shift_expression 
	| relational_expression LE_OP shift_expression 
	| relational_expression GE_OP shift_expression
	;
equality_expression
	: relational_expression  
	| equality_expression EQ_OP relational_expression 
	| equality_expression NE_OP relational_expression
	;
and_expression
	: equality_expression 
	| and_expression '&' equality_expression
	;
exclusive_or_expression
	: and_expression 
	| exclusive_or_expression '^' and_expression
	;
inclusive_or_expression
	: exclusive_or_expression 
	| inclusive_or_expression '|' exclusive_or_expression
	;
logical_and_expression
	: inclusive_or_expression 
	| logical_and_expression AND_OP inclusive_or_expression
	;
logical_or_expression
	: logical_and_expression 
	| logical_or_expression OR_OP logical_and_expression
	;
conditional_expression
	: logical_or_expression 
	| logical_or_expression '?' expression ':' conditional_expression
	;
assignment_expression
	: conditional_expression {   
		if($1&&(strcmp($1,"scanf")==0)){
			createNode("scanf",rhs);if(indexFlag==1) indexFlag=0;
		}
	}
	| unary_expression assignment_operator assignment_expression{
		createNode($1,lhs); 
		if((indexFlag==1)&&(indexVar!=NULL)){ 
			indexFlag=0; 
			currentNode->index[currentNode->indexCount]=indexVar; 
		}
		if($3!=NULL){
			createNode($3,rhs);
		}
	}
	;
assignment_operator
	: '=' 
	| MUL_ASSIGN 
	| DIV_ASSIGN 
	| MOD_ASSIGN 
	| ADD_ASSIGN 
	| SUB_ASSIGN 
	| LEFT_ASSIGN 
	| RIGHT_ASSIGN 
	| AND_ASSIGN 
	| XOR_ASSIGN 
	| OR_ASSIGN
	;
expression
	: assignment_expression 
	| expression ',' assignment_expression
	;
constant_expression
	: conditional_expression
	;
declaration
	: declaration_specifiers ';' 
	| declaration_specifiers init_declarator_list ';'   
	;
declaration_specifiers
	: storage_class_specifier 
	| storage_class_specifier declaration_specifiers 
	| type_specifier
	| type_specifier declaration_specifiers 
	| type_qualifier 
	| type_qualifier declaration_specifiers
	;
init_declarator_list
	: init_declarator 
	| init_declarator_list ',' init_declarator 
	;
init_declarator
	: declarator {	createNode($1,declaration); }
	| declarator '=' initializer { 
		createNode($1,lhs); 
		if($3!=NULL){ 
			createNode($3,rhs);
		}	  
	}
	;
storage_class_specifier
	: EXTERN 
	| STATIC 
	| AUTO 
	| REGISTER 
	| TYPEDEF 
	;
type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG 
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED 
	| struct_or_union_specifier 
	| enum_specifier 
	| TYPE_NAME
	;
struct_or_union_specifier
	: struct_or_union IDENTIFIER  '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}' 
	| struct_or_union IDENTIFIER
	;
struct_or_union
	: STRUCT 
	| UNION
	;
struct_declaration_list
	: struct_declaration 
	| struct_declaration_list struct_declaration
	;
struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' {$$=$2;}
	;
specifier_qualifier_list
	: type_specifier specifier_qualifier_list 
	| type_specifier 
	| type_qualifier specifier_qualifier_list 
	| type_qualifier
	;
struct_declarator_list
	: struct_declarator { $$=$1; 	 }
	| struct_declarator_list ',' struct_declarator
	;
struct_declarator
	: declarator  { $$=$1; createNode($1,declaration);}
	| ':' constant_expression 
	| declarator ':' constant_expression
	;
enum_specifier
	: ENUM '{' enumerator_list '}' 
	| ENUM IDENTIFIER '{' enumerator_list '}' 
	| ENUM IDENTIFIER
	;
enumerator_list
	: enumerator 
	| enumerator_list ',' enumerator
	;
enumerator
	: IDENTIFIER 
	| IDENTIFIER '=' constant_expression		
	;
type_qualifier
	: CONST 
	| VOLATILE
	;
declarator
	: pointer direct_declarator { $$ = $2; }
	| direct_declarator
		 {  $$ = $1; }
	;
direct_declarator
	: IDENTIFIER {  $$=$1; }
	| '(' declarator ')' 
	| direct_declarator '[' constant_expression ']' 
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')' { $$ = $1;	 }
	| direct_declarator '(' identifier_list ')' 
	| direct_declarator '(' ')'
	;
pointer
	: '*' 
	| '*' type_qualifier_list 
	| '*' pointer 
	| '*' type_qualifier_list pointer
	;
type_qualifier_list
	: type_qualifier 
	| type_qualifier_list type_qualifier
	;
parameter_type_list
	: parameter_list 
	| parameter_list ',' ELLIPSIS
	;
parameter_list
	: parameter_declaration 
	| parameter_list ',' parameter_declaration
	;
parameter_declaration
	: declaration_specifiers declarator {  createNode($2,function_parameter);	 }
	| declaration_specifiers abstract_declarator 
	| declaration_specifiers
	;
identifier_list
	: IDENTIFIER 
	| identifier_list ',' IDENTIFIER
	;
type_name
	: specifier_qualifier_list 
	| specifier_qualifier_list abstract_declarator
	;
abstract_declarator
	: pointer 
	| direct_abstract_declarator 
	| pointer direct_abstract_declarator
	;
direct_abstract_declarator
	: '(' abstract_declarator ')' 
	| '[' ']' 
	| '[' constant_expression ']' 
	| direct_abstract_declarator '[' ']' 
	| direct_abstract_declarator '[' constant_expression ']' 
	| '(' ')' 
	| '(' parameter_type_list ')' 
	| direct_abstract_declarator '(' ')' 
	| direct_abstract_declarator '(' parameter_type_list ')'
	;
initializer
	: assignment_expression 
	| '{' initializer_list '}' 
	| '{' initializer_list ',' '}'
	;
initializer_list
	: initializer 
	| initializer_list ',' initializer
	;
statement
	: labeled_statement { indexVar = NULL; }
	| compound_statement { indexVar = NULL;}
	| expression_statement { indexVar = NULL;}
	| selection_statement { indexVar = NULL;}
	| iteration_statement { indexVar = NULL; }
	| jump_statement		 { indexVar = NULL; }
;
labeled_statement
	: IDENTIFIER ':' statement {  	 }
	| CASE {
		int i;
		currentNode=pop(); 
		push(currentNode); 
		createNode("case",ifelse_node);
		for(i=0;i<currentSelectionNode->symbolCount;i++){
			currentNode->symbol[currentNode->symbolCount++] = strdup(currentSelectionNode->symbol[i]);
		} 
	} constant_expression ':' statement 
	| DEFAULT { 
		int i;
		currentNode=pop(); 
		push(currentNode); 
		createNode("default",ifelse_node); 
		for(i=0;i<currentSelectionNode->symbolCount;i++){
			currentNode->symbol[currentNode->symbolCount++] = strdup(currentSelectionNode->symbol[i]);
		}
	} ':' statement
	;
curly_brace
	: '{' 
	;
compound_statement
	: curly_brace '}' {  pop_scope();	 }
	| curly_brace statement_list '}' 
	| curly_brace declaration_list '}' 
	| curly_brace declaration_list statement_list '}' 
	;
declaration_list
	: declaration 
	| declaration_list declaration 
	;
statement_list
	: statement 
	| statement_list statement 
	;
expression_statement
	: ';' 
	| expression ';'
	;
if_statement
	: IF {
		createNode("if",if_node);
		selectionFlag=1;
		currentSelectionNode = currentNode; 
		currentSelectionNode->symbolCount=0;
	} '(' expression ')' { 
		selectionFlag=0; 
		push(currentNode);
	}
	;
selection_statement
	: if_statement statement { currentNode = pop();	}
	| if_statement statement ELSE { 
		int i;
		currentNode=pop(); 
		push(currentNode); 
		createNode("else",ifelse_node); 
		for(i=0;i<currentSelectionNode->symbolCount;i++){
			currentNode->symbol[currentNode->symbolCount++] = strdup(currentSelectionNode->symbol[i]);
		}
	} statement { currentNode = pop(); 	 }
	| switch_statement statement {currentNode = pop(); }
	;
switch_statement
	: SWITCH {
		createNode("switch",switch_node);
		selectionFlag=1;
		currentSelectionNode = currentNode; 
		currentSelectionNode->symbolCount=0;
	}  '(' expression ')' { selectionFlag=0;  push(currentNode);}
	;
for_identifier
	: FOR '(' expression_statement { 
		createNode("for",for_node);
		selectionFlag=1; 
		currentSelectionNode = currentNode; 
		currentSelectionNode->symbolCount=0;
	}
	;
for_statement
	: for_identifier expression_statement ')' {selectionFlag=0; }
	;
for_statement_extended
	: for_identifier expression_statement { selectionFlag=0;} expression ')' {  push(currentNode);}
	;
while_statement
	: WHILE {
		createNode("while",while_node); 
		selectionFlag=1;
		currentSelectionNode = currentNode; 
		currentSelectionNode->symbolCount=0;
	}'(' expression ')' { selectionFlag=0; push(currentNode);}
	;
iteration_statement
	: while_statement statement {  currentNode = pop();	 }
	| DO statement WHILE '(' expression ')' ';' 
	| for_statement statement { currentNode = pop(); }
	| for_statement_extended statement
		 { currentNode = pop(); }
	;
jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';' { createNode("break",other); }
	| RETURN ';' 
	| RETURN expression ';'
	;
translation_unit
	: external_declaration { 
		FILE *fp;  
		fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","w"); fprintf(fp,"{"); 
		fclose(fp); 
		int a = traverse_graph_for_init_var(startNode); 
		fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","a"); fprintf(fp,"}"); 
		fclose(fp);
		int b = traverse_graph_for_mem_leaks(startNode); 
		print_mem_leaks(currentNode); 		 
		prepare_buffer_overflow(); 
		int c = traverse_graph_for_buffer_overflow(startNode);
		clean_buffer_overflow();
	}
	| translation_unit external_declaration { 
		FILE *fp;  fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\output.json","w"); 
		fprintf(fp,"{"); 
		fclose(fp); 
		int a = traverse_graph_for_init_var(startNode); 
		int b = traverse_graph_for_mem_leaks(startNode); 
		print_mem_leaks(currentNode); 		 
		prepare_buffer_overflow();  
		int c = traverse_graph_for_buffer_overflow(startNode); 
		clean_buffer_overflow();		
		fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\output.json","a"); fprintf(fp,";a;a"); 
		fclose(fp);
	}
	;
external_declaration
	: function_definition 
	| declaration 
	;
function_definition
	: declaration_specifiers declarator declaration_list { createGraph(); } compound_statement
	| declaration_specifiers declarator {createGraph(); createNode($2,other);} compound_statement 
	| declarator declaration_list { createGraph(); } compound_statement 
	| declarator { createGraph(); } compound_statement 
	;
%%
extern int column;
main() {
/*extern int yydebug;
yydebug = 1;*/
	init_buffer_overflow();
    yyparse();
 }
yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
