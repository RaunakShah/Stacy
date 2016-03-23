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
int var_array_stack_count=0;
int init_array_stack_count=0;
int malloc_array_count=0;

void createGraph(){
	s = malloc (sizeof(struct symtab *)*10);
	/*s[cnt] = malloc (sizeof(struct symtab *));
	s[cnt]->symbol = NULL;
	s[cnt]->init = 0;
	printf("%d %s %d", cnt, s[cnt]->symbol, s[cnt]->init);
	*/
}

void createNode(char *symbols, int type_of){
    struct node *newNode,*switchNode;
	int i=0;
	//printf("regular node");
	//printf("%d", type);
	newNode = (struct node*) malloc (sizeof(struct node));	
	newNode->symbol = strdup(symbols);
	newNode->type = type_of;
	//printf("%s",newNode->symbol);
	//newNode->next1 = NULL;
	//newNode->next2 = NULL;
	for(i=0;i<10;i++){
		newNode->next[i] = NULL;
	}
	i=0;
	//currentNode = newNode;
	if(startNode == NULL){
		startNode = newNode;
	}
	else
	if((strcmp(newNode->symbol,"break")==0)){
		currentNode->next[0] = NULL;
	}
	else{
		if((strcmp(newNode->symbol,"case")==0)&&(currentNode->type!=switch_node)){
			//printf("case found\n");
			if((strcmp(currentNode->symbol,"break")!=0)){
				//printf("break not found");
				i=0;
				/*while(currentNode->next[i]!=NULL){
					i++;printf("%d",i);
				}*/
				//printf("malloc");
				//currentNode->next[i] = malloc(sizeof(struct node*));
				//currentNode->next[i] = newNode;
			}
				//printf("switch");
				switchNode = (struct node*) malloc (sizeof(struct node));
				switchNode = stack[stacktop-1];
				//printf("switch node symb %s\n",switchNode->symbol);
				i=0;
				while(switchNode->next[i]!=NULL){
					i++;//printf("%d",i);
				}	
				switchNode->next[i] = newNode;
				//printf("switchnode->next[%d]->symbol = %s",i,(switchNode->next[i])->symbol);
		}
	i=0;
	while(currentNode->next[i]!=NULL)
			i++;
		currentNode->next[i] = malloc(sizeof(struct node*));
		currentNode->next[i] = newNode;
	}	/*
		if(currentNode->next1==NULL){
			currentNode->next1 = newNode;
			//printf("--%s--%s__",currentNode->symbol,(currentNode->next1)->symbol);
			}
		else{
			currentNode->next2 = newNode;
			//printf("--%s--%s__",currentNode->symbol,(currentNode->next2)->symbol);
			}*/	
	
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
		//printf("here!! %d %d %s %d %d\n",i,k,s[k]->symbol,s[k]->init,cnt);
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
	//printf("\n***adding symbol %s\n", symbol);
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
			//printf("true\n");
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
/*	while(printNode->next[i]!=NULL){
		//printf("%d %s\n", i++, (printNode->next1)->symbol);
		if(printNode->next2){
			//printf("2: %s \n",(printNode->next2)->symbol);
		}
		printNode = printNode->next[i];
	}
	//printf("\nsymtab\n");
	for(i=0;i<cnt;i++){
		printf("%d %s %d\n",i,s[i]->symbol,s[i]->init);
	}*/
}	
	
void push(struct node *item){
	//printf("st %d",stacktop);
	stack[stacktop++] = item;
}

struct node* pop(){
	//printf("returning ");
	return stack[--stacktop];
}

int traverse_graph(struct node *graph_node){
	int i;
	int type,next_count=0;
	type = graph_node->type;
	//printf("graph symb %s type %d var arr cnt%d\n",graph_node->symbol,graph_node->type,var_array_count);
	if(graph_node->type==switch_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);

	}
	if(graph_node->type==if_node){
		//printf("1 push %d %d", var_array_count,init_array_count);
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
	}
	if(graph_node->type==for_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
	}
	if(graph_node->type==while_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
	}
	if(graph_node->type==function_parameter){
		var_array_add(graph_node);
		init_array[init_array_count] = var_array_count-1;
		init_array_count++;
						
	}
	if(graph_node->type==declaration){
		//add to var array
		//printf("cnt3: %d ",var_array_count);
		var_array_add(graph_node);
	}
	if(graph_node->type==rhs){
				if(strcmp(graph_node->symbol,"malloc")!=0){
					
				int i,index=101,flag=0;
				//printf("rhs \n");
				for(i=var_array_count-1;i>=0;i--){
					//printf("%d ",i);
					//printf("%s %s\n",var_array[i], graph_node->symbol);
					if(strcmp(var_array[i],graph_node->symbol)==0){
						//printf("found %s %s \n",var_array[i],graph_node->symbol);
						index = i;
						break;
					}
				}
				for(i=init_array_count-1;i>=0;i--){
					//printf("%d %d ", i,index);
					if(init_array[i]==index){
						printf("index: %d\n",index);
						flag=1;
						break;
					}
				}
				if(flag==0){
					printf("index: %d\n",index);
					printf("error\n");
				}
				}
	}			
		//	init_symtab(graph_node->symbol);
	if(graph_node->type==lhs){  //needs altering
				int i,index,flag=0,j=0,repeat=0;
				//print("lhs\n");
				/*if(strcmp((graph_node->next[0])->symbol,"malloc")==0){
					printf("malloc here\n");
				}*/
				
				if(var_array_count==0){
					var_array_add(graph_node);
					
				}
				j = var_array_count-1;
				//print("cnt: %d ", var_array_count);
				for(i=j;i>=0;i--){
					//print("%d lhsfor \n",i);
					if(strcmp(var_array[i],graph_node->symbol)==0){
						flag = 1;
						index = i;
						//print("%d",index);
						break;
					}
				}
				if(flag==0){
						//print("3 %d",var_array_count);
						var_array_add(graph_node);
						index = var_array_count-1;
						/*init_array[init_array_count] = var_array_count-1;
						init_array_count++;*/
				
				}
				if(strcmp((graph_node->next[0])->symbol,"malloc")==0){
					malloc_array_add(graph_node);
				}
				else{
				//print("2 %d ",var_array_count);
				for(i=0;i<init_array_count;i++){ //should it be backwards?
							if(init_array[i] == index){
							repeat = 1;
							printf("repeat %d %d\n",init_array[i],index);
							break;
							}
						}
						if(repeat==0){	
							printf("not rep %d \n",index);
							init_array[init_array_count] = index;
							init_array_count++;
						
						}				
				}
	}
	if(strcmp(graph_node->symbol,"free")==0){
		remove_malloc_array(graph_node->next[0]);
	}
	
	if((graph_node->next[0]==NULL)){
		// return uninitialised variables
		printf("end of path %s\n",graph_node->symbol);
		print_init_array();
		//pop_scope();
		return 1;
	}
	//recursive call to graph_node->next1
	//print("next0 %s\n",graph_node->symbol);
	traverse_graph(graph_node->next[next_count++]);
	//recursive call to graph_node->next1

	while(graph_node->next[next_count]!=NULL){
		int i;
		//print("next[%d] %s\n",next_count,graph_node->symbol);	
		var_array_count = pop_var_array_stack();
		//print("returned var aray coun %d next count = %d \n", var_array_count,next_count);
		init_array_count = pop_init_array_stack();
		
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
	
		traverse_graph(graph_node->next[next_count++]);
	}
	
		
}
	
void var_array_add(struct node *graph_node){
	int i;
	printf("adding %s to var array\n",graph_node->symbol);
	//var_array[var_array_count] = malloc(sizeof(char *));
	var_array[var_array_count++]=graph_node->symbol;
	//var_array_count++;
	//print("cnt2: %d",var_array_count);
	/*printf("var array\n");
	for(i=0;i<var_array_count;i++){
		printf("%d %s ",i,var_array[i]);
		}*/
}
	
void push_var_array_stack(int count){
	var_array_stack[var_array_stack_count++] = count;
	//print("var array count in push=  %d\n", var_array_count);
}

void push_init_array_stack(int count){
	init_array_stack[init_array_stack_count++] = count;
	//print("init array count in puah = %d and count = %d\n", init_array_count,count);
}

int pop_var_array_stack(){
	--var_array_stack_count;
	//print("returnng %d var arr count\n",var_array_stack[var_array_stack_count]);
	return var_array_stack[var_array_stack_count];
	//--var_array_stack_count;
}

int pop_init_array_stack(){
	--init_array_stack_count;
	//print("returning %d ini aar count\n",init_array_stack[init_array_stack_count]);
	return init_array_stack[init_array_stack_count];
}

void print_init_array(){
		int i;
		printf("var array:\n");
		for(i=0;i<var_array_count;i++){
			printf("|	|	|\n");
			printf("    %d	    %s\n",i, var_array[i]);
			printf("|	|	|\n");
			printf("_________________\n");
		}
		printf("init array:\n");
		for(i=0;i<init_array_count;i++){
			printf("|	|	|\n");
			printf("    %d	    %d \n",i, init_array[i]);
			printf("|	|	|\n");
			printf("_________________\n");
		}
		printf("malloc array:\n");
		for(i=0;i<malloc_array_count;i++){
			printf("|	|	|\n");
			printf("    %d	    %s\n",i, malloc_array[i]);
			printf("|	|	|\n");
			printf("_________________\n");
		}
		
}

void malloc_array_add(struct node* graph_node){
	printf("\nadding to malloc array %s\n",graph_node->symbol);
	malloc_array[malloc_array_count++] = graph_node->symbol;
}	

void remove_malloc_array(struct node* graph_node){
	int i,index;
	printf("\nremoving from malloc array %s\n",graph_node->symbol);
	for(i=0;i<malloc_array_count;i++){
		if(strcmp(malloc_array[i],graph_node->symbol)==0){
			index = i;
			break;
		}
	}
	for(i=index;i<malloc_array_count-1;i++){
		malloc_array[i] = malloc_array[i+1];
	}
	malloc_array_count--;
}