#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"
#include "y.tab.h"
int stacktop=0;
int num_of_nodes=0;
int cnt=0;
void createGraph(){
	s = malloc (sizeof(struct symtab *)*10);
	/*s[cnt] = malloc (sizeof(struct symtab *));
	s[cnt]->symbol = NULL;
	s[cnt]->init = 0;
	printf("%d %s %d", cnt, s[cnt]->symbol, s[cnt]->init);
	*/
}


void createNode(char *symbols, int type){
	struct node *newNode;
	int i;
	printf("regular node");
	//printf("%d", type);
	newNode = (struct node*) malloc (sizeof(struct node));	
	newNode->symbol = strdup(symbols);
	newNode->next1 = NULL;
	//currentNode = newNode;
	if(startNode == NULL){
		currentNode = newNode;
		startNode = newNode;
	}
	else{	
		currentNode->next1 = newNode;
		currentNode = newNode;
	}
	num_of_nodes++;
	printf("--%s--",currentNode->symbol);
	//printf("%s\n",(startNode->next1)->symbol);
	//printf("%d %s\n	", num_of_nodes,currentNode->symbol);
	//if identifier
	for(i=0;i<cnt;i++){
		//traverse symbol table 
	}
	if(type==declaration){
		printf("symbol ::%s", symbols);
		add_to_symtab(newNode->symbol);
	}
	//if doesnt exist in symtab
	/*s[count].symbol = $$;
	s[count].init = 0;
	count++;*/
}

void add_to_symtab(char *symbol){
	int i;
	printf("symb::%d %s", cnt,symbol);
	s[cnt] = malloc (sizeof(struct symtab));
	s[cnt]->symbol = symbol;
	s[cnt]->init = 0;
	printf("symb2::%d %s %d", cnt,s[cnt]->symbol,s[cnt]->init);
	cnt++;
}

void init_symtab(char *symb){
	int i,flag=0;
	char *str;
	str = strdup(symb);
	printf("matchww %s ",symb);
	for(i=0;i<cnt;i++){
		printf("check %s and %s",str, s[i]->symbol);
		if(strcmp(str,s[i]->symbol)==0){
			printf("match");
			s[i]->init = 1;
		}
	}
}

void createIfNode(){
	struct node *newNode;
	int i,flag; 
	printf(" if node\n");
	newNode = (struct node*) malloc (sizeof(struct node));	
	if(currentNode == NULL){
		newNode->next1 = NULL;
		currentNode = newNode;
	}
	else
	{
		currentNode->next1 = newNode;
		newNode->next1 = NULL;
		currentNode = newNode;
	}
	
	push(currentNode);
	num_of_nodes++;
	
	//printf("%d", num_of_nodes);
	//if identifier
	/*for(i=0;i<cnt;i++){
		//traverse symbol table
		flag = 0;
		if(s[i]->symbol == v){
			flag = 1;
			break;
		}
	}
	if(flag==0){
	//if doesnt exist in symtab/*
	strcpy(s[cnt]->symbol,v);
	s[cnt]->init = 0;
	cnt++;
	}
	for(i=0;i<cnt;i++){
	printf("%s",s[i]->symbol);
	}
	*/
}
/*
void pushSymtab(char *v){
	s = malloc (sizeof(struct symtab *)*10);
	s[cnt] = malloc (sizeof(struct symtab *));
	strcpy(s[cnt]->symbol,v);
	s[cnt]->init = 0;
	cnt++;
	for(i=0;i<cnt;i++){
		printf("%s", s[i]->symbol);
	}
}

	*/
	
char *symbols[100];
int max_symbols = 0;
symtab_add(char *symbol)
{
	if(is_symbol(symbol))
		return;
	printf("\n***adding symbol %s\n", symbol);
	symbols[max_symbols++] = strdup(symbol);	
	int i;
	/*for(i = 0;i<max_symbols;i++){
		printf("%s ", symbols[i]);
	}*/
	
}
	
int
is_symbol(char *symbol)
{
	/*printf("looking for %s\n", symbol);*/
	int i;
	for(i = 0; i < max_symbols; i++){
		if(!strcmp(symbol, symbols[i])){
			printf("true\n");
		return 1;
		}
	}
	return 0;
}
	
void print_symb(){
	int i;
	struct node* printNode;
	/*for(i = 0;i<max_symbols;i++){
		printf("symbols: %s", symbols[i]);
	}*/
	i=0;
	printNode = startNode;
	//printf("%s", startNode->symbol);
	while(printNode!=NULL){
		printf("%d %s\n", i++, printNode->symbol);
		printNode = printNode->next1;
	}
	printf("\nsymtab\n");
	for(i=0;i<cnt;i++){
		printf("%d %s %d\n",i,s[i]->symbol,s[i]->init);
	}
}	
	
void push(struct node *item){
	//printf("%d",stacktop);
	stack[stacktop++] = item;
}

struct node* pop(){
	//printf("returning ");
	return stack[stacktop]--;
}

	
	
	