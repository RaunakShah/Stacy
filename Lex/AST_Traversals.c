/* Graph traversal for Stacy */
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

void createNode(char *symbols, int type_of){
    struct node *newNode,*switchNode;
	int i=0;
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
	
	for(i=0;i<10;i++){
		newNode->next[i] = NULL;
	}
	i=0;
	if(startNode == NULL){ /*New node is the start node*/
		startNode = newNode; 
	}
	else
	if((strcmp(newNode->symbol[0],"break")==0)){ /*Encountered break in source code*/
		currentNode->next[0] = NULL; 
	}
	else{	
		if((strcmp(newNode->symbol[0],"malloc")==0)){
			currentNode->type = 9;
		}
		if(((strcmp(newNode->symbol[0],"case")==0)||(strcmp(newNode->symbol[0],"default")==0))&&(currentNode->type!=switch_node)){ /*switch case*/
			if((strcmp(currentNode->symbol[0],"break")!=0)){
				i=0;
			}
				switchNode = (struct node*) malloc (sizeof(struct node));
				switchNode = stack[stacktop-1];
				i=0;
				while(switchNode->next[i]!=NULL){
					i++;
				}	
				switchNode->next[i] = newNode;
		}
		i=0;
		while(currentNode->next[i]!=NULL)
			i++;
		currentNode->next[i] = malloc(sizeof(struct node*));
		currentNode->next[i] = newNode;
	}	
	num_of_nodes++;
	currentNode = newNode; /* Initialization complete*/
	
}
		
void push(struct node *item){ /* Push onto stack */
	stack[stacktop++] = item;
}

struct node* pop(){ /* Pop from stack */
	return stack[--stacktop];
}

int traverse_graph_for_init_var(struct node *graph_node){
	int i;
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	
	if(graph_node->type==switch_node){ /* If switch case is encountered */
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);

	}
	if(graph_node->type==if_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
	}
	if(graph_node->type==for_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
	}
	if(graph_node->type==while_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
	}
	if(graph_node->type==function_parameter){
		var_array_add(graph_node);
		init_array[init_array_count] = var_array_count-1;
		init_array_count++;
						
	}
	if(graph_node->type==declaration){
		var_array_add(graph_node);
	}
	
	if(graph_node->type==rhs){	
		int valid = check_rhs_validity(graph_node);
	}			
	if(graph_node->type==lhs){ 
				check_lhs_for_init_var(graph_node);				
	}
	
	if((graph_node->next[0]==NULL)){ /*End of scope */
		return 1;
	}

	traverse_graph_for_init_var(graph_node->next[next_count++]); /* Recursive call */

	while(graph_node->next[next_count+1]!=NULL){
		int i;
		interim_count = init_array_count;
		check_for_common = init_array_stack[init_array_stack_count-1]; 
		traverse_graph_for_init_var(graph_node->next[next_count++]);
	}
	if(graph_node->next[next_count]!=NULL){
		int i,j;
		for(i=check_for_common;i<interim_count;i++){
			for(j=interim_count;j<init_array_count;j++){
				if(init_array[i]==init_array[j]){
					common_array[common_array_count++] = init_array[i];
				}
			}
		}
		var_array_count = pop_var_array_stack();
		init_array_count = pop_init_array_stack();
		init_var_used_count = pop_init_var_used_stack();
		if(common_array_count>0){
			for(i=0;i<common_array_count;i++){
				init_array[init_array_count++] = common_array[i];
			}
		}
		
		traverse_graph_for_init_var(graph_node->next[next_count++]);
	}
	
		
}

int traverse_graph_for_mem_leaks(struct node *graph_node){ 
	int i;
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	if(graph_node->type==malloc_node){
		int i;
		allocation_node[allocation_count] = malloc(sizeof(struct malloc));
		allocation_node[allocation_count]->index = malloc_array_count++;
		allocation_node[allocation_count]->points = malloc(sizeof(int)*10);
		allocation_node[allocation_count]->count = 0;
		allocation_node[allocation_count]->line = graph_node->line;
		allocation_node[allocation_count]->free = 0;
		for(i=var_array_count-1;i>=0;i--){
			if(strcmp(graph_node->symbol[0],var_array[i])==0)
				break;
		}
		allocation_node[allocation_count]->points[allocation_node[allocation_count]->count++] = i;
		allocation_count++;
	}
	
	if(graph_node->type==if_node||graph_node->type==switch_node){ 
		push_mem_path_array(mem_freed_array_count);
	}
	if(graph_node->type==lhs){  
		check_lhs_for_mem_leaks(graph_node);				
	}
	if(strcmp(graph_node->symbol[0],"free")==0){
		int index,i,j,flag=0;
		for(i=0;i<allocation_count;i++){
			for(j=0;j<allocation_node[i]->count;j++){
				if(strcmp((graph_node->next[0])->symbol[0],var_array[allocation_node[i]->points[j]])==0){
					flag=1;
					break;
				}
			}
			if(flag==1)
				break;
		}
		add_mem_freed_array(allocation_node[i]->index);
	}		
	
	if((graph_node->next[0]==NULL)){
		return 1;
	}
	
	traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	
	while(graph_node->next[next_count+1]!=NULL){
		int i;
		interim_count = mem_freed_array_count;
		check_for_common = mem_path_array[mem_path_array_count-1];
		traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	}
	
	if(graph_node->next[next_count]!=NULL){
		int i,j;
		for(i=check_for_common;i<interim_count;i++){
			for(j=interim_count;j<mem_freed_array_count;j++){
				if(mem_freed_array[i]==mem_freed_array[j]){
				common_array[common_array_count++] = mem_freed_array[i];
				}
			}
		}
		mem_freed_array_count = pop_mem_path_array();
		if(common_array_count>0){
			for(i=0;i<common_array_count;i++){
				mem_freed_array[mem_freed_array_count++] = common_array[i];
			}
		}
		
		traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	}	
			
}

char *buff_overflow_json = "c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\buff.json";
void init_buffer_overflow(){
	unlink(buff_overflow_json);
}
void prepare_buffer_overflow()
{
	FILE *fp = fopen(buff_overflow_json,"w"); fprintf(fp,"{"); fclose(fp);
	currentSafeArray = NULL;
	currentUnsafeArray = NULL;
 
}

void clean_buffer_overflow()
{
	FILE *fp = fopen(buff_overflow_json,"a"); 
	fprintf(fp,"}"); 
	fclose(fp);
}
int traverse_graph_for_buffer_overflow(struct node *graph_node){
	int i;
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	if(graph_node->type==if_node||graph_node->type==ifelse_node||graph_node->type==while_node||graph_node->type==switch_node||graph_node->type==for_node){
		int i;
		struct safeArray *newSafeArray;
		struct unsafeArray *newUnsafeArray;
		
		newSafeArray = (struct safeArray*) malloc (sizeof(struct safeArray));
		newSafeArray->count = 0;
		for(i=0;i<graph_node->symbolCount;i++){
			newSafeArray->safe[newSafeArray->count++] = strdup(graph_node->symbol[i]);
		}
		newSafeArray->nextScope = NULL;
		if(currentSafeArray==NULL){
			newSafeArray->prevScope = NULL;
		}
		else{
			newSafeArray->prevScope = currentSafeArray;
		}
		currentSafeArray = newSafeArray;
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
	
	if(graph_node->type==lhs){  
			int i,flag=0;
			if(currentSafeArray){
			for(i=0;i<currentSafeArray->count;i++){
				if(strcmp(currentSafeArray->safe[i],graph_node->symbol[0])==0){
					currentUnsafeArray->unsafe[currentUnsafeArray->count] = malloc(sizeof(char));
					strcpy(currentUnsafeArray->unsafe[currentUnsafeArray->count++],currentSafeArray->safe[i]);
					flag=1;
					break;
				}
			}
			if(flag==1){
				int j;
				for(j=i;j<currentSafeArray->count-1;j++){
					currentSafeArray->safe[j] = currentSafeArray->safe[j+1]; 
				}
				currentSafeArray->count--;
			}
			}
				
	}
	if(graph_node->indexCount>0){
		int i,j,flag=0;
		for(i=0;i<graph_node->indexCount;i++){
			flag=0;
			if(currentSafeArray){
			for(j=0;j<currentSafeArray->count;j++){
				if(strcmp(graph_node->index[i],currentSafeArray->safe[j])==0){
					flag=1;
					break;
				}			
			}
			}
			if(flag==0){  /* Potential buffer overflow */
				FILE *fp;
				fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\buff.json","a");
				if(first_buff_print!=0)
					fprintf(fp,",");
				fprintf(fp,"\"%d\":[\"%s\"]", graph_node->line,graph_node->index[i]);
				fclose(fp);
				first_buff_print++;
				printf("potential buffer overflow line: %d\n",graph_node->line);
				break;
				}
			
		}
	}
	if((graph_node->next[0]==NULL)){
		return 1;
	}
	
	traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);

	while(graph_node->next[next_count+1]!=NULL){
		traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);
	}
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
		int i;
		FILE *fp;
		if(first_print!=0){
			fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","a");
			fprintf(fp,",");
			fclose(fp);
		}	
		fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","a");
		fprintf(fp,"\"%d\":[\"%s\"]", graph_node->line,var_array[init_var_used]);
		prev_line = graph_node->line;
		first_print++;
		fclose(fp);
			
}

void print_mem_leaks(struct node* graph_node){
		int i;
		FILE *fp;
		i=0;
		for(i=0;i<allocation_count;i++){
				int j;
				for(j=0;j<allocation_node[i]->count;j++){
				}
			
		}
		for(i=0;i<mem_freed_array_count;i++){
			int j;
			for(j=0;j<allocation_count;j++){
				if(mem_freed_array[i]==allocation_node[j]->index){ /* Map to variable array */
						allocation_node[j]->free = 1;
						break;
					}
			}
		}
		int j;
		for(j=0;j<var_array_count;j++){
			if(strcmp(var_array[j],"malloc")==0)
				break;
		}
		fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\mem_leaks.json","w");
		fprintf(fp,"{");
		fclose(fp);
		for(i=0;i<allocation_count;i++){
			fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\mem_leaks.json","a");
			
			if((allocation_node[i]->free==0)&&(allocation_node[i]->points[allocation_node[i]->count]!=j)){
				if(first_mem_print!=0)
					fprintf(fp,",");
				first_mem_print++;
				fprintf(fp,"\"%d\":[\"%s\"]", allocation_node[i]->line, var_array[allocation_node[i]->points[0]]);
			}
			fclose(fp);
		}
			fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\mem_leaks.json","a");
		fprintf(fp,"}");
		fclose(fp);
}

void malloc_array_add(struct node* graph_node){
	malloc_array[malloc_array_count++] = graph_node->symbol[0];
}	

void remove_malloc_array(char* symbol){
	int i,j,k,index,flag=0;
	for(i=var_array_count-1;i>=0;i--){
		if(strcmp(var_array[i],symbol)==0)
			break;
	}
	for(j=0;j<allocation_count;j++){
		for(k=0;k<allocation_node[j]->count;k++){
			if(allocation_node[j]->points[k]==i){
				flag = 1;
				break;
			}
		}
		if(flag==1)
			break;		
	}
	for(i=j;i<allocation_count-1;i++){
		allocation_node[i] = allocation_node[i+1];
	}
	free(allocation_node[i+1]);
	allocation_count--;
		
}

void check_lhs_for_init_var(struct node * graph_node){
	int i,index,flag=0,j=0,repeat=0,valid;
	int isAllocationNode=0;
	if(var_array_count==0){
		var_array_add(graph_node);	
		index = 0;
	}
	j = var_array_count-1;
	for(i=j;i>=0;i--){
		if(strcmp(var_array[i],graph_node->symbol[0])==0){
			flag = 1;
			index = i;
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
			int i,j,k,flag=0;
			temp = graph_node->next[0];
			for(k=var_array_count-1;k>=0;k--){
				if(strcmp(var_array[k],temp->symbol[0])==0){
					break;
				}
			}
		}
	}
	for(i=0;i<init_array_count;i++){ 
		if(init_array[i] == index){
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
		int i,index=101,flag=0;
		for(i=var_array_count-1;i>=0;i--){
			if(strcmp(var_array[i],graph_node->symbol[0])==0){
				index = i;
				break;
			}
		}
		for(i=init_array_count-1;i>=0;i--){
			if(init_array[i]==index){
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
	int i,index,flag=0,j=0,repeat=0,valid;
	int isAllocationNode=0;
	if(var_array_count==0){
		var_array_add(graph_node);	
		index = 0;
	}
	j = var_array_count-1;
	for(i=j;i>=0;i--){
		if(strcmp(var_array[i],graph_node->symbol[0])==0){
			flag = 1;
			index = i;
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
			int i,j,k,flag=0;
			temp = graph_node->next[0];
			for(k=var_array_count-1;k>=0;k--){
				if(strcmp(var_array[k],temp->symbol[0])==0){
					break;
				}
			}
			for(i=0;i<allocation_count;i++){
				for(j=0;j<allocation_node[i]->count;j++){
					if(k == allocation_node[i]->points[j]){ //
						allocation_node[i]->points[allocation_node[i]->count] = index;
						allocation_node[i]->count++;
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

