#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"
#include "y.tab.h"
int stacktop=0;
int num_of_nodes=0;
int cnt=0;
int var_array_count = 0;
int init_array_count=0;
int scope_count=0;
void createGraph(){
	s = malloc (sizeof(struct symtab *)*10);
	/*s[cnt] = malloc (sizeof(struct symtab *));
	s[cnt]->symbol = NULL;
	s[cnt]->init = 0;
	printf("%d %s %d", cnt, s[cnt]->symbol, s[cnt]->init);
	*/
}


void createNode(char *symbols, int type_of){
struct node *newNode;
	int i;
	printf("regular node");
	//printf("%d", type);
	newNode = (struct node*) malloc (sizeof(struct node));	
	newNode->symbol = strdup(symbols);
	newNode->type = type_of;
	newNode->next1 = NULL;
	newNode->next2 = NULL;
	//currentNode = newNode;
	if(startNode == NULL){
		startNode = newNode;
	}
	else{
		if(currentNode->next1==NULL){
			currentNode->next1 = newNode;
			}
		else{
			currentNode->next2 = newNode;
			}
	printf("--%s--%s__",currentNode->symbol,(currentNode->next1)->symbol);
	
	}
	//printf("%d %s %s", currentNode->symbol, currentNode->next1, currentNode->next2);
	num_of_nodes++;
	currentNode = newNode;
	//printf("%s\n",(startNode->next1)->symbol);
	//printf("%d %s\n	", num_of_nodes,currentNode->symbol);
	//if identifier
	if(type_of==declaration){
		//printf("symbol ::%s", symbols);
		add_to_symtab(newNode->symbol);
	}
	//if doesnt exist in symtab
	/*s[count].symbol = $$;
	s[count].init = 0;
	count++;*/
}
/*
void createIfNode(){
	struct node *newNode;
	int i;
	printf("regular node");
	//printf("%d", type);
	newNode = (struct node*) malloc (sizeof(struct node));	
	newNode->symbol = strdup(symbols);
	newNode->next1 = NULL;
	newNode->next2 = NULL;
	//currentNode = newNode;
	//if(startNode == NULL){
		//currentNode = newNode;
		//startNode = newNode;
	//}
	if(currentNode->next1==NULL){
		currentNode->next1 = newNode;
		currentNode = newNode;
	}
	else{
		currentNode->next2 = newNode;
		currentNode = newNode;
	}
	num_of_nodes++;
	//push(currentNode);
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
	
}*/
void add_to_symtab(char *symbol){
	//int i;
	//printf("symb::%d %s", cnt,symbol);
	s[cnt] = malloc (sizeof(struct symtab));
	s[cnt]->symbol = symbol;
	s[cnt]->init = 0;
	//printf("symb2::%d %s %d", cnt,s[cnt]->symbol,s[cnt]->init);
	cnt++;
}

void init_symtab(char *symb){
	int k,flag=0,j;
	char *str;
	str = strdup(symb);
	//printf("matchww %s ",symb);
	//printf("%d", scope_stack[scope_count]);
	if(scope_count==0)
		j=0;
	else
		j=scope_stack[scope_count-1];
	for(k=j;k<cnt;k++){
		//printf("check %s and %s",str, s[i]->symbol);
		//printf("init smy %d %d %d", k,j,cnt);
		if(strcmp(str,s[k]->symbol)==0){
			//printf("match");
			flag = 1;
			s[k]->init = 1;
			break;
		}
	}
	if(flag==0){
		for(k=0;k<j;k++){
			if(strcmp(str,s[k]->symbol)==0){
				s[k]->init = 1;
				break;
			}
		}
	}
}

void add_scope(){
	//push_scope(cnt);
	scope_stack[scope_count] = cnt;
	//printf(" count %d scope_stack[scope count]= %d = %d",scope_count,scope_stack[scope_count],cnt);
	scope_count++;
	//printf("%d", scope_count);
}

void pop_scope(){
	int i,k;
	i = scope_stack[--scope_count];
	//printf("%d scop",i);
	for(k=i;k<cnt;k++){
		printf("here!! %d %d %s %d %d\n",i,k,s[k]->symbol,s[k]->init,cnt);
	}
	cnt = i;
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
	while(printNode->next1!=NULL){
		printf("%d %s\n", i++, (printNode->next1)->symbol);
		if(printNode->next2){
			printf("2: %s \n",(printNode->next2)->symbol);
		}
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
	return stack[--stacktop];
}

int traverse_graph(struct node *graph_node){
	int i;
	int type;
	type = graph_node->type;
	if(graph_node->type==declaration){
		//add to var array
		var_array_add(graph_node);
	}
	else
	if(graph_node->type==rhs){
				int i,index=101,flag=0;
				printf("rhs \n");
				for(i=var_array_count-1;i>=0;i--){
					printf("%d ",i);
					printf("%s %s\n",var_array[i], graph_node->symbol);
					if(strcmp(var_array[i],graph_node->symbol)==0){
						//printf("IT WORKS");
						index = i;
						break;
					}
				}
				for(i=init_array_count-1;i>=0;i--){
					printf("%d %d ", i,index);
					if(init_array[i]==index){
						flag=1;
						break;
					}
				}
				if(flag==0)
					printf("error\n");
	}			
	else
		//	init_symtab(graph_node->symbol);
	if(graph_node->type==lhs){
				printf("lhs\n");
				int i,index,flag;
				for(i=var_array_count-1;i>=0;i--){
					printf("%d lhsfor \n",i);
					if(strcmp(var_array[i],graph_node->symbol)==0){
						flag = 1;
						index = i;
						break;
					}
				}
				if(flag==1){
					init_array[init_array_count] = index;
					init_array_count++;
				}
				else{
					var_array_add(graph_node);
					init_array[init_array_count] = var_array_count-1;
					init_array_count++;
									
				}
	}	
	
	if((graph_node->next1==NULL)&&(graph_node->next2==NULL)){
		// return uninitialised variables
		printf("end of path %s",graph_node->symbol);
		//pop_scope();
		return 0;
	}
	
	//recursive call to graph_node->next1
	printf("next1 %s\n",graph_node->symbol);
	traverse_graph(graph_node->next1);
	//recursive call to graph_node->next1
	
	if(graph_node->next2!=NULL){
		printf("next2 %s\n",graph_node->symbol);	
		traverse_graph(graph_node->next2);
	}
}
	
void var_array_add(struct node *graph_node){
	int i;
	printf("adding %s to var array\n",graph_node->symbol);
	//var_array[var_array_count] = malloc(sizeof(char *));
	var_array[var_array_count]=graph_node->symbol;
	var_array_count++;
	printf("var array\n");
	for(i=0;i<var_array_count;i++){
		printf("%d %s ",i,var_array[i]);
		}
}
	