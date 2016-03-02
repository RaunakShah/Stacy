#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"
#include "y.tab.h"
int cnt = 0;
struct node *currentNode;
struct symtab **s;
int num_of_nodes = 0;

void createGraph(){
	s = malloc (sizeof(struct symtab *)*10);
	s[cnt] = malloc (sizeof(struct symtab *));
	s[cnt]->symbol = NULL;
	s[cnt]->init = 0;
	printf("%d %s %d", cnt, s[cnt]->symbol, s[cnt]->init);
}

void createNode(){
	printf("regular node");
}

void createIfNode(){
	struct node *newNode;
	int i,flag; 
	printf(" if node\n");
	newNode = (struct node*) malloc (sizeof(struct node));	
	if(currentNode == NULL){
		newNode->next = NULL;
		currentNode = newNode;
	}
	else
	{
		currentNode->next = newNode;
		newNode->next = NULL;
		currentNode = newNode;
	}
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
	
	
	
	
	
	
	
	
	
	