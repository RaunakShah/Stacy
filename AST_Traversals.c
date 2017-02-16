/* 

Stacy - A Static Code Analyzer
This file performs the core functionality of our tool.
Input source code to be analyzed is entered into the plug-in. 
The output of the parser is used to form an Abstract Syntax Tree (AST) representation of code.
Core functions are carried out during a depth-first traversal of the AST.

*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"
#include "y.tab.h"

int stacktop=0;
int num_of_nodes=0;
int var_array_count = 0;
int init_array_count=0;
int var_array_stack_count=0;
int init_array_stack_count=0;
int init_var_used_stack_count=0;
int malloc_array_count=0;
int allocation_count=0;
int init_var_used_count=0;
int line_number = 1;
int final_line_count=0;
int first_print=0;
int prev_line = 0;
int mem_path_array_count=0;
int mem_freed_array_count=0;
int first_buff_print=0;
int first_mem_print=0;


//Create new node of the AST
void createNode(char *symbols, int type_of){
    struct node *newNode,*switchNode;
	int loopCounter=0;
	newNode = (struct node*) malloc (sizeof(struct node));	
	/*Initialize new node*/
	newNode->symbol = malloc(sizeof(char *)*10);
	newNode->symbolCount = 0;
	newNode->symbol[newNode->symbolCount++] = strdup(symbols);
	newNode->type = type_of;
	newNode->line = line_number;
	newNode->index = malloc(sizeof(char)*10);
	newNode->indexCount = 0;
	final_line_count = line_number;
	//Outward pointers of node
	for(loopCounter=0;loopCounter<10;loopCounter++){
		newNode->next[loopCounter] = NULL;
	}
	loopCounter=0;
	
	//New node is the start node
	if(startNode == NULL){ 
		startNode = newNode; 
	}
	else
	//Encountered break in source code
	if((strcmp(newNode->symbol[0],"break")==0)){
		currentNode->next[0] = NULL; 
	}
	else{	
		if((strcmp(newNode->symbol[0],"malloc")==0)){
			currentNode->type = 9;
		}
		//Switch case
		if(((strcmp(newNode->symbol[0],"case")==0)||(strcmp(newNode->symbol[0],"default")==0))&&(currentNode->type!=switch_node)){
			if((strcmp(currentNode->symbol[0],"break")!=0)){
				loopCounter=0;
			}
				switchNode = (struct node*) malloc (sizeof(struct node));
				switchNode = stack[stacktop-1];
				loopCounter=0;
				while(switchNode->next[loopCounter]!=NULL){
					loopCounter++;
				}	
				switchNode->next[loopCounter] = newNode;
		}
		loopCounter=0;
		while(currentNode->next[loopCounter]!=NULL)
			loopCounter++;
		currentNode->next[loopCounter] = malloc(sizeof(struct node*));
		currentNode->next[loopCounter] = newNode;
	}	
	num_of_nodes++;
	currentNode = newNode;
	//Initialization complete
	
}
		
//Push onto stack		
void push(struct node *item){ 
	stack[stacktop++] = item;
}

//Pop from stack 
struct node* pop(){ 
	return stack[--stacktop];
}

/*	
Depth-first traversal of AST for detecting usage of uninitialized variables 
Input argument: Each node of the AST	
*/

int traverse_graph_for_init_var(struct node *graph_node){
	int loopCounter;
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	
	/*Identify type of input node*/ 
	
	//If switch case is encountered
	if(graph_node->type==switch_node){ 
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
	}
	//If node is encountered
	if(graph_node->type==if_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
	}
	//For loop is encountered
	if(graph_node->type==for_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
	}
	//While node is encountered
	if(graph_node->type==while_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
	}
	//Function parameter node
	if(graph_node->type==function_parameter){
		var_array_add(graph_node);
		init_array[init_array_count] = var_array_count-1;
		init_array_count++;
	}
	//Declaration node
	if(graph_node->type==declaration){
		var_array_add(graph_node);
	}
	
	
	//Node is the Right Hand Side (RHS) of an expression
	if(graph_node->type==rhs){	
		int valid = check_rhs_validity(graph_node);
	}			
	//Node is the Left Hand Side (LHS) of an expression
	if(graph_node->type==lhs){ 
				check_lhs_for_init_var(graph_node);				
	}
	
	//End of scope
	if((graph_node->next[0]==NULL)){ 
		return 1;
	}
	
	//Recursive call 
	traverse_graph_for_init_var(graph_node->next[next_count++]);
	
	//In case of branch at current node 
	while(graph_node->next[next_count+1]!=NULL){
		interim_count = init_array_count;
		check_for_common = init_array_stack[init_array_stack_count-1]; 
		traverse_graph_for_init_var(graph_node->next[next_count++]);
	}
	
	//At final path of current node
	if(graph_node->next[next_count]!=NULL){
		int loopCounter,innerLoopCounter;
		//Check for variables that have been initialized in all possible paths
		for(loopCounter=check_for_common;loopCounter<interim_count;loopCounter++){
			for(innerLoopCounter=interim_count;innerLoopCounter<init_array_count;innerLoopCounter++){
				if(init_array[loopCounter]==init_array[innerLoopCounter]){
					common_array[common_array_count++] = init_array[loopCounter];
				}
			}
		}
		
		//Return to previous state
		var_array_count = pop_var_array_stack();
		init_array_count = pop_init_array_stack();
		init_var_used_count = pop_init_var_used_stack();
		//If variables initialized in all possible paths
		if(common_array_count>0){
			for(loopCounter=0;loopCounter<common_array_count;loopCounter++){
				init_array[init_array_count++] = common_array[loopCounter];
			}
		}
		
		traverse_graph_for_init_var(graph_node->next[next_count++]);
	}	
}

/*	
Depth-first traversal of AST for detecting presence of potential memory leaks 
Input argument: Each node of the AST	
*/

int traverse_graph_for_mem_leaks(struct node *graph_node){ 
	int loopCounter;
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	
	//Input node allocates memory dynamically
	if(graph_node->type==malloc_node){
		int loopCounter;
		
		//Update the array that tracks memory allocations
		allocation_node[allocation_count] = malloc(sizeof(struct malloc));
		allocation_node[allocation_count]->index = malloc_array_count++;
		allocation_node[allocation_count]->points = malloc(sizeof(int)*10);
		allocation_node[allocation_count]->count = 0;
		allocation_node[allocation_count]->line = graph_node->line;
		allocation_node[allocation_count]->free = 0;
		for(loopCounter=var_array_count-1;loopCounter>=0;loopCounter--){
			if(strcmp(graph_node->symbol[0],var_array[loopCounter])==0)
				break;
		}
		allocation_node[allocation_count]->points[allocation_node[allocation_count]->count++] = loopCounter;
		allocation_count++;
	}
	
	//Branch in AST
	if(graph_node->type==if_node||graph_node->type==switch_node){ 
		push_mem_path_array(mem_freed_array_count);
	}
	//Node is on LHS of an expression
	if(graph_node->type==lhs){  
		check_lhs_for_mem_leaks(graph_node);				
	}
	
	//Dynamically allocated memory is freed by the current node
	if(strcmp(graph_node->symbol[0],"free")==0){
		int index,loopCounter,innerLoopCounter,flag=0;
		//To determine which variable is freed
		for(loopCounter=0;loopCounter<allocation_count;loopCounter++){
			for(innerLoopCounter=0;innerLoopCounter<allocation_node[loopCounter]->count;innerLoopCounter++){
				if(strcmp((graph_node->next[0])->symbol[0],var_array[allocation_node[loopCounter]->points[innerLoopCounter]])==0){
					flag=1;
					break;
				}
			}
			if(flag==1)
				break;
		}
		add_mem_freed_array(allocation_node[loopCounter]->index);
	}		
	
	if((graph_node->next[0]==NULL)){
		return 1;
	}
	
	//Recursive call
	traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	
	//In case of branch at current node
	while(graph_node->next[next_count+1]!=NULL){
		int loopCounter;
		interim_count = mem_freed_array_count;
		check_for_common = mem_path_array[mem_path_array_count-1];
		traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	}
	
	//At final path of current node
	if(graph_node->next[next_count]!=NULL){
		int loopCounter,innerLoopCounter;
		
		//Check for dynamically allocated variables that have been freed at all possible paths
		for(loopCounter=check_for_common;loopCounter<interim_count;loopCounter++){
			for(innerLoopCounter=interim_count;innerLoopCounter<mem_freed_array_count;innerLoopCounter++){
				if(mem_freed_array[loopCounter]==mem_freed_array[innerLoopCounter]){
				common_array[common_array_count++] = mem_freed_array[loopCounter];
				}
			}
		}
		//Return to previous state
		mem_freed_array_count = pop_mem_path_array();
		if(common_array_count>0){
			for(loopCounter=0;loopCounter<common_array_count;loopCounter++){
				mem_freed_array[mem_freed_array_count++] = common_array[loopCounter];
			}
		}
		
		traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	}	
			
}


/*	
Depth-first traversal of AST for detecting presence of potential buffer overflows
Input argument: Each node of the AST	
*/

int traverse_graph_for_buffer_overflow(struct node *graph_node){
	int loopCounter;
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	//Determine type of input node
	if(graph_node->type==if_node||graph_node->type==ifelse_node||graph_node->type==while_node||graph_node->type==switch_node||graph_node->type==for_node){
		int loopCounter;
		struct safeArray *newSafeArray;		//Array of "safe" variables
		struct unsafeArray *newUnsafeArray;	//Array of "unsafe" variables
		
		//Initialize safe array
		newSafeArray = (struct safeArray*) malloc (sizeof(struct safeArray));
		newSafeArray->count = 0;
		for(loopCounter=0;loopCounter<graph_node->symbolCount;loopCounter++){
			newSafeArray->safe[newSafeArray->count++] = strdup(graph_node->symbol[loopCounter]);
		}
		newSafeArray->nextScope = NULL;
		if(currentSafeArray==NULL){
			newSafeArray->prevScope = NULL;
		}
		else{
			newSafeArray->prevScope = currentSafeArray;
		}
		currentSafeArray = newSafeArray;
		
		//Initialize unsafe array
		newUnsafeArray = (struct unsafeArray*) malloc (sizeof(struct unsafeArray));
		newUnsafeArray->nextScope = NULL;
		newUnsafeArray->count = 0;
		if(currentUnsafeArray==NULL){
			newUnsafeArray->prevScope = NULL;
		}
		else{	
			newUnsafeArray->prevScope = currentUnsafeArray;
		}
		currentUnsafeArray = newUnsafeArray;
	}
	//Declared but uninitialized variables are added to unsafe array
	if(graph_node->type==declaration){
		if(currentUnsafeArray==NULL){
			struct unsafeArray *newUnsafeArray;
			newUnsafeArray = (struct unsafeArray*) malloc (sizeof(struct unsafeArray));
			newUnsafeArray->nextScope = NULL;
			newUnsafeArray->count = 0;
			newUnsafeArray->prevScope = NULL;
			currentUnsafeArray = newUnsafeArray;		
		}
		currentUnsafeArray->unsafe[currentUnsafeArray->count++] = strdup(graph_node->symbol[0]);
	}
	
	//Variables initialized and unchecked are added to the unsafe array
	if(graph_node->type==lhs){  
			int loopCounter,flag=0;
			if(currentSafeArray){
			for(loopCounter=0;loopCounter<currentSafeArray->count;loopCounter++){
				if(strcmp(currentSafeArray->safe[loopCounter],graph_node->symbol[0])==0){
					currentUnsafeArray->unsafe[currentUnsafeArray->count] = malloc(sizeof(char));
					strcpy(currentUnsafeArray->unsafe[currentUnsafeArray->count++],currentSafeArray->safe[loopCounter]);
					flag=1;
					break;
				}
			}
			if(flag==1){
				int innerLoopCounter;
				for(innerLoopCounter=loopCounter;innerLoopCounter<currentSafeArray->count-1;innerLoopCounter++){
					currentSafeArray->safe[innerLoopCounter] = currentSafeArray->safe[innerLoopCounter+1]; 
				}
				currentSafeArray->count--;
			}
			}
				
	}
	//Check for potential buffer overflows
	if(graph_node->indexCount>0){
		int loopCounter,innerLoopCounter,flag=0;
		for(loopCounter=0;loopCounter<graph_node->indexCount;loopCounter++){
			flag=0;
			if(currentSafeArray){
				for(innerLoopCounter=0;innerLoopCounter<currentSafeArray->count;innerLoopCounter++){
					if(strcmp(graph_node->index[loopCounter],currentSafeArray->safe[innerLoopCounter])==0){
						flag=1;
						break;
					}			
				}
			}
			// Potential buffer overflow 
			if(flag==0){  
				printf("potential buffer overflow line: %d\n",graph_node->line);
				break;
			}
		}
	}
	if((graph_node->next[0]==NULL)){
		return 1;
	}
	
	//Recursive call
	traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);
	
	while(graph_node->next[next_count+1]!=NULL){
		traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);
	}
	
	//Return to previous state
	if(graph_node->next[next_count]!=NULL){
		currentSafeArray = currentSafeArray->prevScope;
		currentUnsafeArray = currentUnsafeArray->prevScope;
		traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);
	}
	
		
}

void var_array_add(struct node *graph_node){
	var_array[var_array_count++]=graph_node->symbol[0];
}
	
void push_var_array_stack(int count){
	var_array_stack[var_array_stack_count++] = count;
}

void push_init_array_stack(int count){
	init_array_stack[init_array_stack_count++] = count;
}

void push_init_var_used_stack(int count){
		init_var_used_stack[init_var_used_stack_count++] = count;
}

int pop_var_array_stack(){
	--var_array_stack_count;
	return var_array_stack[var_array_stack_count];
}

int pop_init_array_stack(){
	--init_array_stack_count;
	return init_array_stack[init_array_stack_count];
}

int pop_init_var_used_stack(){
	--init_var_used_stack_count;
	return init_var_used_stack[init_var_used_stack_count];
}

void print_init_array(struct node* graph_node){
		int loopCounter;
		FILE *fp;
		if(first_print!=0){
			fp = fopen("c:\\raunak\\static\\init_var.json","a");
			fprintf(fp,",");
			fclose(fp);
		}	
		fp = fopen("c:\\raunak\\static\\init_var.json","a");
		fprintf(fp,"\"%d\":[\"%s\"]", graph_node->line,var_array[init_var_used]);
		prev_line = graph_node->line;
		first_print++;
		fclose(fp);
			
}

void print_mem_leaks(struct node* graph_node){
		int loopCounter;
		FILE *fp;
		loopCounter=0;
		for(loopCounter=0;loopCounter<allocation_count;loopCounter++){
				int innerLoopCounter;
				for(innerLoopCounter=0;innerLoopCounter<allocation_node[loopCounter]->count;innerLoopCounter++){
				}
			
		}
		for(loopCounter=0;loopCounter<mem_freed_array_count;loopCounter++){
			int innerLoopCounter;
			for(innerLoopCounter=0;innerLoopCounter<allocation_count;innerLoopCounter++){
				if(mem_freed_array[loopCounter]==allocation_node[innerLoopCounter]->index){ /* Map to variable array */
						allocation_node[innerLoopCounter]->free = 1;
						break;
					}
			}
		}
		int innerLoopCounter;
		for(innerLoopCounter=0;innerLoopCounter<var_array_count;innerLoopCounter++){
			if(strcmp(var_array[innerLoopCounter],"malloc")==0)
				break;
		}
		fp = fopen("c:\\raunak\\static\\mem_leaks.json","w");
		fprintf(fp,"{");
		fclose(fp);
		for(loopCounter=0;loopCounter<allocation_count;loopCounter++){
			fp = fopen("c:\\raunak\\static\\mem_leaks.json","a");
			
			if((allocation_node[loopCounter]->free==0)&&(allocation_node[loopCounter]->points[allocation_node[loopCounter]->count]!=innerLoopCounter)){
				if(first_mem_print!=0)
					fprintf(fp,",");
				first_mem_print++;
				fprintf(fp,"\"%d\":[\"%s\"]", allocation_node[loopCounter]->line, var_array[allocation_node[loopCounter]->points[0]]);
			}
			fclose(fp);
		}
			fp = fopen("c:\\raunak\\static\\mem_leaks.json","a");
		fprintf(fp,"}");
		fclose(fp);
}

void malloc_array_add(struct node* graph_node){
	malloc_array[malloc_array_count++] = graph_node->symbol[0];
}	

void remove_malloc_array(char* symbol){
	int loopCounter,innerLoopCounter,k,index,flag=0;
	for(loopCounter=var_array_count-1;loopCounter>=0;loopCounter--){
		if(strcmp(var_array[loopCounter],symbol)==0)
			break;
	}
	for(innerLoopCounter=0;innerLoopCounter<allocation_count;innerLoopCounter++){
		for(k=0;k<allocation_node[innerLoopCounter]->count;k++){
			if(allocation_node[innerLoopCounter]->points[k]==loopCounter){
				flag = 1;
				break;
			}
		}
		if(flag==1)
			break;		
	}
	for(loopCounter=innerLoopCounter;loopCounter<allocation_count-1;loopCounter++){
		allocation_node[loopCounter] = allocation_node[loopCounter+1];
	}
	free(allocation_node[loopCounter+1]);
	allocation_count--;
		
}

void check_lhs_for_init_var(struct node * graph_node){
	int loopCounter,index,flag=0,innerLoopCounter=0,repeat=0,valid;
	int isAllocationNode=0;
	if(var_array_count==0){
		var_array_add(graph_node);	
		index = 0;
	}
	innerLoopCounter = var_array_count-1;
	for(loopCounter=innerLoopCounter;loopCounter>=0;loopCounter--){
		if(strcmp(var_array[loopCounter],graph_node->symbol[0])==0){
			flag = 1;
			index = loopCounter;
			break;
		}
	}
	if(flag==0){
		var_array_add(graph_node);
		index = var_array_count-1;			
	}
	if(graph_node->next[0]){
		if((graph_node->next[0])->type==3){
			struct node *temp;
			int loopCounter,innerLoopCounter,k,flag=0;
			temp = graph_node->next[0];
			for(k=var_array_count-1;k>=0;k--){
				if(strcmp(var_array[k],temp->symbol[0])==0){
					break;
				}
			}
		}
	}
	for(loopCounter=0;loopCounter<init_array_count;loopCounter++){ 
		if(init_array[loopCounter] == index){
			break;
		}
	}
	if(repeat==0){	
		init_array[init_array_count] = index;
		init_array_count++;
						
	}				
}

int check_rhs_validity(struct node* graph_node){
	if((strcmp(graph_node->symbol[0],"malloc")!=0)&&(strcmp(graph_node->symbol[0],"scanf")!=0)){			
		int loopCounter,index=101,flag=0;
		for(loopCounter=var_array_count-1;loopCounter>=0;loopCounter--){
			if(strcmp(var_array[loopCounter],graph_node->symbol[0])==0){
				index = loopCounter;
				break;
			}
		}
		for(loopCounter=init_array_count-1;loopCounter>=0;loopCounter--){
			if(init_array[loopCounter]==index){
				flag=1;
				break;
			}
		}
		if(flag==0){
			init_var_used = index;
			print_init_array(graph_node);			
			return 0;
		}
	}
	return 1;
}


void check_lhs_for_mem_leaks(struct node * graph_node){
	int loopCounter,index,flag=0,innerLoopCounter=0,repeat=0,valid;
	int isAllocationNode=0;
	if(var_array_count==0){
		var_array_add(graph_node);	
		index = 0;
	}
	innerLoopCounter = var_array_count-1;
	for(loopCounter=innerLoopCounter;loopCounter>=0;loopCounter--){
		if(strcmp(var_array[loopCounter],graph_node->symbol[0])==0){
			flag = 1;
			index = loopCounter;
			break;
		}
	}
	if(flag==0){
		var_array_add(graph_node);
		index = var_array_count-1;
	}
	if(graph_node->next[0]){
		if((graph_node->next[0])->type==3){
			struct node *temp;
			int loopCounter,innerLoopCounter,k,flag=0;
			temp = graph_node->next[0];
			for(k=var_array_count-1;k>=0;k--){
				if(strcmp(var_array[k],temp->symbol[0])==0){
					break;
				}
			}
			for(loopCounter=0;loopCounter<allocation_count;loopCounter++){
				for(innerLoopCounter=0;innerLoopCounter<allocation_node[loopCounter]->count;innerLoopCounter++){
					if(k == allocation_node[loopCounter]->points[innerLoopCounter]){ //
						allocation_node[loopCounter]->points[allocation_node[loopCounter]->count] = index;
						allocation_node[loopCounter]->count++;
						flag = 1;
						isAllocationNode=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
		}
	}
}

void add_mem_freed_array(int index){
	mem_freed_array[mem_freed_array_count++] = index;
}
void push_mem_path_array(int index){
	mem_path_array[mem_path_array_count++] = index;
}
int pop_mem_path_array(){
	return mem_path_array[--mem_path_array_count];
}

