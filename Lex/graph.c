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
	printf("regular node %s\n",symbols);
	//printf("type of %d\n", type_of);
	printf("1\n");
	newNode = (struct node*) malloc (sizeof(struct node));	
	printf("2\n");
	newNode->symbol = malloc(sizeof(char *)*10);
	printf("3");
	newNode->symbolCount = 0;
	printf(" %d ",newNode->symbolCount);
	newNode->symbol[newNode->symbolCount++] = strdup(symbols);
	newNode->type = type_of;
	newNode->line = line_number;
	newNode->index = malloc(sizeof(char)*10);
	newNode->indexCount = 0;
	final_line_count = line_number;
	if(newNode->symbol[0]!=NULL){
		printf("%s\n",newNode->symbol[0]);
	}
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
	if((strcmp(newNode->symbol[0],"break")==0)){
		currentNode->next[0] = NULL;
	}
	
	else{
		
		if((strcmp(newNode->symbol[0],"malloc")==0)){
			currentNode->type = 9;
		}
		if((strcmp(newNode->symbol[0],"case")==0)&&(currentNode->type!=switch_node)){
			//printf("case found\n");
			if((strcmp(currentNode->symbol[0],"break")!=0)){
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
	printf("%d ihere ", i);
	printf("%s",currentNode->symbol[0]);
	while(currentNode->next[i]!=NULL)
			i++;
		printf("%d", i);
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
	
	////printf("%d %s %s", currentNode->symbol, currentNode->next1, currentNode->next2);
	num_of_nodes++;
	currentNode = newNode;
	////printf("%s\n",(startNode->next1)->symbol);
	////printf("%d %s\n	", num_of_nodes,currentNode->symbol);
	//if identifier
	if(type_of==declaration){
		////printf("symbol ::%s", symbols);
		add_to_symtab(newNode->symbol[0]);
	}
	//if doesnt exist in symtab
	/*s[count].symbol = $$;
	s[count].init = 0;
	count++;*/
}
void add_to_symtab(char *symbol){
	//int i;
	////printf("symb::%d %s", cnt,symbol);
	s[cnt] = malloc (sizeof(struct symtab));
	s[cnt]->symbol = symbol;
	s[cnt]->init = 0;
	////printf("symb2::%d %s %d", cnt,s[cnt]->symbol,s[cnt]->init);
	cnt++;
}

void init_symtab(char *symb){
	int k,flag=0,j;
	char *str;
	str = strdup(symb);
	////printf("matchww %s ",symb);
	////printf("%d", scope_stack[scope_count]);
	if(scope_count==0)
		j=0;
	else
		j=scope_stack[scope_count-1];
	for(k=j;k<cnt;k++){
		////printf("check %s and %s",str, s[i]->symbol);
		////printf("init smy %d %d %d", k,j,cnt);
		if(strcmp(str,s[k]->symbol)==0){
			////printf("match");
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
	////printf(" count %d scope_stack[scope count]= %d = %d",scope_count,scope_stack[scope_count],cnt);
	scope_count++;
	////printf(" %d\n", scope_count);
}

void pop_scope(){
	int i,k;
	i = scope_stack[--scope_count];
	////printf("%d scop",i);
	for(k=i;k<cnt;k++){
		////printf("here!! %d %d %s %d %d\n",i,k,s[k]->symbol,s[k]->init,cnt);
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
		//printf("%s", s[i]->symbol);
	}
}
*/
	
char *symbols[100];
int max_symbols = 0;
symtab_add(char *symbol)
{
	if(is_symbol(symbol))
		return;
	////printf("\n***adding symbol %s\n", symbol);
	symbols[max_symbols++] = strdup(symbol);	
	int i;
	/*for(i = 0;i<max_symbols;i++){
		//printf("%s ", symbols[i]);
	}*/
	
}
	
int
is_symbol(char *symbol)
{
	/*//printf("looking for %s\n", symbol);*/
	int i;
	for(i = 0; i < max_symbols; i++){
		if(!strcmp(symbol, symbols[i])){
			////printf("true\n");
		return 1;
		}
	}
	return 0;
}
	
void push(struct node *item){
	////printf("st %d",stacktop);
	stack[stacktop++] = item;
}

struct node* pop(){
	////printf("returning ");
	return stack[--stacktop];
}

int traverse_graph_for_init_var(struct node *graph_node){
	int i;
	for(i=0;i<graph_node->symbolCount;i++){
		printf("%s ",graph_node->symbol[i]);
	}
	for(i=0;i<graph_node->indexCount;i++){
			printf("index%s \n\n\n",graph_node->index[i]);
		}
		
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	//printf("graph symb %s type %d var arr cnt%d\n",graph_node->symbol,graph_node->type,var_array_count);
	while(graph_node->next[next_count++]!=NULL){
		printf("nc%d", next_count);
	}
	next_count=0;
	if(graph_node->type==switch_node){
		push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);

	}
	if(graph_node->type==if_node){
		//printf("1 push %d %d", var_array_count,init_array_count);
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
		//add to var array
		//printf("cnt3: %d ",var_array_count);
		var_array_add(graph_node);
	}
	/*if(graph_node->type==malloc_node){
		int i;
		allocation_node[allocation_count] = malloc(sizeof(struct malloc));
		allocation_node[allocation_count]->index = malloc_array_count++;
		allocation_node[allocation_count]->points = malloc(sizeof(int)*10);
		allocation_node[allocation_count]->count = 0;
		for(i=var_array_count-1;i>=0;i--){
			if(strcmp(graph_node->symbol,var_array[i])==0)
				break;
		}
		allocation_node[allocation_count]->points[allocation_node[allocation_count]->count++] = i;
		allocation_count++;
	}*/
	if(graph_node->type==rhs){
		
		int valid = check_rhs_validity(graph_node);
	}			
		//	init_symtab(graph_node->symbol);
	if(graph_node->type==lhs){  //needs altering
				//printf("lhs\n");
				/*if(strcmp((graph_node->next[0])->symbol,"malloc")==0){
					//printf("malloc here\n");
				}*/
				
				check_lhs_for_init_var(graph_node);
				
	}
	/*if(strcmp(graph_node->symbol,"free")==0){
		remove_malloc_array(graph_node->next[0]);
	}*/
	
	if((graph_node->next[0]==NULL)){
		// return uninitialised variables
		//printf("end of path %s\n",graph_node->symbol);
		//print_init_array(graph_node);
		//pop_scope();
		return 1;
	}
	//recursive call to graph_node->next1
	//printf("next0 %s %d\n",graph_node->symbol,next_count);
	traverse_graph_for_init_var(graph_node->next[next_count++]);
	//recursive call to graph_node->next1

	while(graph_node->next[next_count+1]!=NULL){
		int i;
		//printf("next[%d] %s\n",next_count,graph_node->symbol);	
		interim_count = init_array_count;
		check_for_common = init_array_stack[init_array_stack_count-1]; // does this work for switch?
		//printf("%d %d", interim_count,check_for_common);
		traverse_graph_for_init_var(graph_node->next[next_count++]);
	}
	if(graph_node->next[next_count]!=NULL){
		//printf("next[%d] %s\n",next_count,graph_node->symbol);	
		int i,j;
		for(i=check_for_common;i<interim_count;i++){
			//printf("i %d %d %d",i,interim_count,init_array_count);
			for(j=interim_count;j<init_array_count;j++){
				//printf("j %d",j);
				if(init_array[i]==init_array[j]){
					//printf("comm%d",init_array[i]);
					common_array[common_array_count++] = init_array[i];
				}
			}
		}
		var_array_count = pop_var_array_stack();
		//printf("returned var aray coun %d next count = %d \n", var_array_count,next_count);
		init_array_count = pop_init_array_stack();
		//printf("initarra %d",init_array_count);
		init_var_used_count = pop_init_var_used_stack();
		if(common_array_count>0){
			for(i=0;i<common_array_count;i++){
				init_array[init_array_count++] = common_array[i];
			}
		}
		
		//printf("\ninitarra %d",init_array_count);
		/*push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
		*/
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
	
	if(graph_node->type==if_node){ //still need to work on this!!
		//push_mem_path_array(
	}
	
	/*if(graph_node->type==rhs){
		//printf("in mem");
		int valid = check_rhs_validity(graph_node);
	}*/			
		//	init_symtab(graph_node->symbol);
	if(graph_node->type==lhs){  //needs altering
				//printf("lhs\n");
				/*if(strcmp((graph_node->next[0])->symbol,"malloc")==0){
					//printf("malloc here\n");
				}*/
				
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
		print_mem_leaks(graph_node);
		return 1;
	}
	
	//recursive call to graph_node->next1
	//printf("next0 %s %d\n",graph_node->symbol,next_count);
	traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	//recursive call to graph_node->next1

	while(graph_node->next[next_count+1]!=NULL){
		int i;
		//printf("next[%d] %s\n",next_count,graph_node->symbol);	
		interim_count = mem_freed_array_count;
		check_for_common = mem_path_array[mem_path_array_count-1];
		//printf("%d %d", interim_count,check_for_common);
		traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	}
	if(graph_node->next[next_count]!=NULL){
		//printf("next[%d] %s\n",next_count,graph_node->symbol);	
		int i,j;
		for(i=check_for_common;i<interim_count;i++){
			//printf("i %d %d %d",i,interim_count,init_array_count);
			for(j=interim_count;j<mem_freed_array_count;j++){
				//printf("j %d",j);
				if(mem_freed_array[i]==mem_freed_array[j]){
					//printf("comm%d",init_array[i]);
					common_array[common_array_count++] = mem_freed_array[i];
				}
			}
		}
		mem_freed_array_count = pop_mem_path_array();
		if(common_array_count>0){
			for(i=0;i<common_array_count;i++){
				//printf("%d", i);
				mem_freed_array[mem_freed_array_count++] = common_array[i];
			}
		}
		
		//printf("\ninitarra %d",init_array_count);
		/*push_var_array_stack(var_array_count);
		push_init_array_stack(init_array_count);
		push_init_var_used_stack(init_var_used_count);
		*/
		traverse_graph_for_mem_leaks(graph_node->next[next_count++]);
	}
			
}

int traverse_graph_for_buffer_overflow(struct node *graph_node){
	int i;
	for(i=0;i<graph_node->symbolCount;i++){
		printf("\nsymb%s ",graph_node->symbol[i]);
	}
	for(i=0;i<graph_node->indexCount;i++){
			printf("%dindex%s \n\n\n",i,graph_node->index[i]);
		}
	printf("before");
	int type,next_count=0,interim_count=0,check_for_common=0,common_array[10],common_array_count=0;
	type = graph_node->type;
	//printf("graph symb %s type %d var arr cnt%d\n",graph_node->symbol,graph_node->type,var_array_count);
	if(graph_node->type==if_node||graph_node->type==ifelse_node){
		int i;
		struct safeArray *newSafeArray;
		struct unsafeArray *newUnsafeArray;
		
		newSafeArray = (struct safeArray*) malloc (sizeof(struct safeArray*));
		newSafeArray->count = 0;
		for(i=0;i<graph_node->symbolCount;i++){
			newSafeArray->safe[newSafeArray->count++] = strdup(graph_node->symbol[i]);
			//strcpy(newSafeArray->safe[newSafeArray->count++],graph_node->symbol[i]);
			printf("NEW %s\n",graph_node->symbol[i]);
		}
		newSafeArray->nextScope = NULL;
		if(currentSafeArray==NULL){
			newSafeArray->prevScope = NULL;
		}
		else{
			newSafeArray->prevScope = currentSafeArray;
		}
		currentSafeArray = newSafeArray;
		
		newUnsafeArray = (struct unsafeArray*) malloc (sizeof(struct unsafeArray*));
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
	printf("after");
	/*if(graph_node->type==switch_node){
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
	*/
	printf("before dec");
	if(graph_node->type==declaration){
		printf("in dec %s",graph_node->symbol[0]);
		if(currentUnsafeArray==NULL){
			struct unsafeArray *newUnsafeArray;
			printf("here");
			newUnsafeArray = (struct unsafeArray*) malloc (sizeof(struct unsafeArray*));
			printf("here1");
			newUnsafeArray->nextScope = NULL;
			printf("here2");
			newUnsafeArray->count = 0;
			printf("here3");
			newUnsafeArray->prevScope = NULL;
			printf("here4");
			currentUnsafeArray = newUnsafeArray;
		printf("here5");
			
		}
		printf("here2");
		currentUnsafeArray->unsafe[currentUnsafeArray->count++] = strdup(graph_node->symbol[0]);
		//strcpy(currentUnsafeArray->unsafe[currentUnsafeArray->count++],graph_node->symbol[0]);
	}
	printf("after dec");
	
	if(graph_node->type==lhs){  //does not appreciate local variable of same name 
			int i,flag=0;
			printf("in lhs");
			if(currentSafeArray){
				printf("in current safe array%d\n ",currentSafeArray->count);
			for(i=0;i<currentSafeArray->count;i++){
				printf("%s %s\n",currentSafeArray->safe[i],graph_node->symbol[0]);
				if(strcmp(currentSafeArray->safe[i],graph_node->symbol[0])==0){
					printf("uh oh %d %s",currentUnsafeArray->count,currentSafeArray->safe[i]);
					currentUnsafeArray->unsafe[currentUnsafeArray->count] = malloc(sizeof(char));
					strcpy(currentUnsafeArray->unsafe[currentUnsafeArray->count++],currentSafeArray->safe[i]);
					printf("oh");
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
		printf(" in index count %d",graph_node->indexCount);
		for(i=0;i<graph_node->indexCount;i++){
			flag=0;
			if(currentSafeArray){
			for(j=0;j<currentSafeArray->count;j++){
				printf("matching %s %s\n",graph_node->index[i],currentSafeArray->safe[j]);
				if(strcmp(graph_node->index[i],currentSafeArray->safe[j])==0){
					flag=1;
					break;
				}			
			}
			}
		}
		if(flag==0){
			printf("potential buffer overflow line: %d\n",graph_node->line);
		}
	}
	/*if(graph_node->type==rhs){
		
		int valid = check_rhs_validity(graph_node);
	}			
		//	init_symtab(graph_node->symbol);
	*/
	/*if(strcmp(graph_node->symbol,"free")==0){
		remove_malloc_array(graph_node->next[0]);
	}*/
	printf("herewhar");
	if((graph_node->next[0]==NULL)){
		
		printf("here2");return 1;
	}
	//recursive call to graph_node->next1
	//printf("next0 %s %d\n",graph_node->symbol,next_count);
	
	printf("here3");
	traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);
	//recursive call to graph_node->next1

	while(graph_node->next[next_count+1]!=NULL){
		int i;
		printf("safe variables: ");
		for(i=0;i<currentSafeArray->count;i++){
			//printf("%s ",currentSafeArray->safe[i]);
		}
		/*currentSafeArray = currentSafeArray->prevScope;
		currentUnsafeArray = currentUnsafeArray->prevScope;*/
		//free(currentSafeArray->nextScope);
		//free(currentUnsafeArray->nextScope);
		traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);
	}
	if(graph_node->next[next_count]!=NULL){
		currentSafeArray = currentSafeArray->prevScope;
		currentUnsafeArray = currentUnsafeArray->prevScope;
			traverse_graph_for_buffer_overflow(graph_node->next[next_count++]);

	}
	
		
}

void var_array_add(struct node *graph_node){
	int i;
	//printf("adding %s to var array\n",graph_node->symbol);
	//var_array[var_array_count] = malloc(sizeof(char *));
	var_array[var_array_count++]=graph_node->symbol[0];
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

void push_init_var_used_stack(int count){
		init_var_used_stack[init_var_used_stack_count++] = count;
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

int pop_init_var_used_stack(){
	--init_var_used_stack_count;
	return init_var_used_stack[init_var_used_stack_count];
}

void print_init_array(struct node* graph_node){
		int i;
		FILE *fp;
		/*fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","w");
		printf("34");	
		//printf("%d",prev_line);
		if(first_print==0){
						printf("1");
						uninitVarUsed = malloc(sizeof(char));
						strcpy(uninitVarUsed,"{");
						}
					if(graph_node->line==prev_line){
					//remove ]} and replace with ," "]}
					}
					else{
					//if(first_print!=0), remove } and replace with ,
					printf("#");
					//cat "line":["var"]}
					int lineAdded = graph_node->line;
					char *varAdded=malloc(sizeof(char));
					strcpy(varAdded, var_array[init_var_used]);
					strcat(uninitVarUsed,"\"lineAdded\":[\"varAdded\"");
				s	}
					fprintf(fp,uninitVarUsed);
					prev_line = graph_node->line;
					first_print++;
					fclose(fp);
					//printf("%s\n",uninitVarUsed);
				*/
		if(first_print==0){
			fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","w");
			fprintf(fp,"{");
			fclose(fp);
		}	
		//printf("%d %d\n", graph_node->line,prev_line);
		fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\init_var.json","a");
		if(graph_node->line==prev_line){
				fprintf(fp,",\"%s\"",var_array[init_var_used]);
			}
		else{
				if(first_print!=0)
					fprintf(fp,",");
		fprintf(fp,"\"%d\":[\"%s\"]", graph_node->line,var_array[init_var_used]);
		}
		//printf("\t fn%d %d", graph_node->line, final_line_count);
		if(graph_node->line==final_line_count){
			fprintf(fp,"]}");
		}
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
					//printf("i:%d j:%d %d ",i,j,allocation_node[i]->points[j]);
				}
				//printf("%d\n", allocation_count);
			
		}
		//printf("freed\n");
		for(i=0;i<mem_freed_array_count;i++){
			int j;
			//printf("%d hello ",mem_freed_array[i]);
			for(j=0;j<allocation_count;j++){
				int k;
				//for(k=0;k<allocation_node[j]->count;k++){
					//if(strcmp(var_array[mem_freed_array[i]],var_array[allocation_node[j]->points[k]])==0){ //figure all_node->points mapping to var array
						if(mem_freed_array[i]==allocation_node[j]->index){
						//printf("freeing %s",var_array[allocation_node[j]->points[0]]);
						allocation_node[j]->free = 1;
						break;
					}
				//}
			}
		}
		fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\mem_leaks.json","w");
		fprintf(fp,"{");
		fclose(fp);
		for(i=0;i<allocation_count;i++){
			fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\mem_leaks.json","a");
			
			if(allocation_node[i]->free==0){
				if(i>0)
					fprintf(fp,",");
				fprintf(fp,"\"%d\":[\"%s\"]", allocation_node[i]->line, var_array[allocation_node[i]->points[i]]);
			}
			fclose(fp);
		}
			fp = fopen("c:\\pcs\\rohan\\back up\\return to pendrive\\xampp-win32-1.7.5-beta2-VC9\\xampp\\htdocs\\static\\mem_leaks.json","a");
		fprintf(fp,"}");
		fclose(fp);
}
/*
void add_mem_alloc_path_array(struct node* graph_node){
	int i,j,k,index,flag=0;
	for(i=var_array_count-1;i>=0;i--){
		if(strcmp(var_array[i],graph_node->symbol)==0)
			break;
	}
	for(j=0;j<allocation_count;j++){
			//printf("j %d",j);
			for(k=0;k<allocation_node[j]->count;k++){
				//printf("K %d",k);
				if(allocation_node[j]->points[k]==i){
					//printf("found");
					flag = 1;
					break;
				}
			}
			if(flag==1)
				break;
			
	}
	//printf("allocation_node[j]->count = %d",allocation_node[j]->count);
	//if((allocation_node[j]->count)-1==0){
		mem_path_array[mem_path_count++] = allocation_node[j]->points[k];
		printf("%d in paht\n",allocation_node[j]->points[k]);
		
}
*/

void malloc_array_add(struct node* graph_node){
	//printf("\nadding to malloc array %s\n",graph_node->symbol);
	malloc_array[malloc_array_count++] = graph_node->symbol[0];
}	

void remove_malloc_array(char* symbol){
	int i,j,k,index,flag=0;
	for(i=var_array_count-1;i>=0;i--){
		if(strcmp(var_array[i],symbol)==0)
			break;
	}
	for(j=0;j<allocation_count;j++){
			//printf("j %d",j);
			for(k=0;k<allocation_node[j]->count;k++){
				//printf("K %d",k);
				if(allocation_node[j]->points[k]==i){
					//printf("found");
					flag = 1;
					break;
				}
			}
			if(flag==1)
				break;
			
	}
	//printf("allocation_node[j]->count = %d",allocation_node[j]->count);
	//if((allocation_node[j]->count)-1==0){
		//printf("freed");
		for(i=j;i<allocation_count-1;i++){
			//printf("i: %d\n",i);
			allocation_node[i] = allocation_node[i+1];
		}
		free(allocation_node[i+1]);
		allocation_count--;
		
	//}
	/*	else{//change
		printf("SS");
			for(i=k;i<allocation_node[j]->count;i++){
				printf("entered");
				allocation_node[j]->points[i] = allocation_node[j]->points[i+1];
		}
	}*/
}

void check_lhs_for_init_var(struct node * graph_node){
	int i,index,flag=0,j=0,repeat=0,valid;
	int isAllocationNode=0;
	if(var_array_count==0){
		var_array_add(graph_node);	
		index = 0;
	}
	//valid = check_rhs_validity(graph_node->next[0]);
	//if(valid!=0){
	j = var_array_count-1;
				//printf("cnt: %d ", var_array_count);
	for(i=j;i>=0;i--){
					//printf("%d lhsfor %s %s \n",i,var_array[i],graph_node->symbol	);
					if(strcmp(var_array[i],graph_node->symbol[0])==0){
						flag = 1;
						index = i;
						//printf("%d",index);
						break;
					}
				}
				if(flag==0){
						//printf("3 %d",var_array_count);
						var_array_add(graph_node);
						index = var_array_count-1;
						/*init_array[init_array_count] = var_array_count-1;
						init_array_count++;*/
				
				}
				if(graph_node->next[0]){
				//printf("type %d\n", (graph_node->next[0])->type);//problem
				if((graph_node->next[0])->type==3){
					struct node *temp;
					int i,j,k,flag=0;
					//printf("type 3!");
					//printf("%d\n",index);
					temp = graph_node->next[0];
					for(k=var_array_count-1;k>=0;k--){
						//printf("%s %s", var_array[k],temp->symbol);
						if(strcmp(var_array[k],temp->symbol[0])==0){
							//printf("%d",index);
							break;
						}
					}
					//printf("%d %d\n",k,index);
					/*for(i=0;i<allocation_count;i++){
						//printf("1");
						for(j=0;j<allocation_node[i]->count;j++){
							//printf("2 %d\n",allocation_node[i]->count);
								if(k == allocation_node[i]->points[j]){ //
									//printf("done");
									allocation_node[i]->points[allocation_node[i]->count] = index;
									allocation_node[i]->count++;
									//printf("%d %d %d",index,allocation_node[i]->count,allocation_node[i]->points[allocation_node[i]->count-1]);
									flag = 1;
									isAllocationNode=1;
									break;
								}
						}
						if(flag==1)
								break;
					}*/
				}
				}
				//printf("2 %d ",var_array_count);
				for(i=0;i<init_array_count;i++){ //should it be backwards?
							if(init_array[i] == index){
							//repeat = 1;
							//printf("repeat %d %d\n",init_array[i],index);
							break;
							}
				}
				if(repeat==0){	
							//printf("not rep %d \n",index);
							init_array[init_array_count] = index;
							init_array_count++;
						
						}				
				
	//}
}

int check_rhs_validity(struct node* graph_node){
	//printf("%s",graph_node->symbol);
	if(strcmp(graph_node->symbol[0],"malloc")!=0){
					
				int i,index=101,flag=0;
				//printf("rhs \n");
				for(i=var_array_count-1;i>=0;i--){
					//printf("%d ",i);
					//printf("%s %s\n",var_array[i], graph_node->symbol);
					if(strcmp(var_array[i],graph_node->symbol[0])==0){
						//printf("found %s %s \n",var_array[i],graph_node->symbol);
						index = i;
						break;
					}
				}
				for(i=init_array_count-1;i>=0;i--){
					//printf("%d %d ", i,index);
					if(init_array[i]==index){
						//printf("index: %d\n",index);
						flag=1;
						break;
					}
				}
				if(flag==0){
					//printf("index: %d\n",index);
					//printf("error\n");
					init_var_used = index;
					//printf("printing");
					print_init_array(graph_node);
		
					/*if(first_print==0)
						strcpy(uninitVarUsed,"{");
					
					if(graph_node->line==prev_line){
					//remove ]} and replace with ," "]}
					}
					else{
					//if(first_print!=0), remove } and replace with ,
			
					//cat "line":["var"]}
					int lineAdded = graph_node->line;
					char *varAdded;
					strcpy(varAdded, var_array[init_var_used]);
					strcat(uninitVarUsed,"\"lineAdded\":[\"varAdded\"");
					}
					prev_line = graph_node->line;
					first_print++;
					//printf("%s\n",uninitVarUsed);
					
					*/
					
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
	//valid = check_rhs_validity(graph_node->next[0]);
	//if(valid!=0){
	j = var_array_count-1;
				//printf("cnt: %d ", var_array_count);
	for(i=j;i>=0;i--){
					//printf("%d lhsfor %s %s \n",i,var_array[i],graph_node->symbol	);
					if(strcmp(var_array[i],graph_node->symbol[0])==0){
						flag = 1;
						index = i;
						//printf("%d",index);
						break;
					}
				}
				if(flag==0){
						//printf("3 %d",var_array_count);
						var_array_add(graph_node);
						index = var_array_count-1;
						/*init_array[init_array_count] = var_array_count-1;
						init_array_count++;*/
				
				}
				if(graph_node->next[0]){
				//printf("type %d\n", (graph_node->next[0])->type);//problem
				if((graph_node->next[0])->type==3){
					struct node *temp;
					int i,j,k,flag=0;
					//printf("type 3!");
					//printf("%d\n",index);
					temp = graph_node->next[0];
					for(k=var_array_count-1;k>=0;k--){
						//printf("%s %s", var_array[k],temp->symbol);
						if(strcmp(var_array[k],temp->symbol[0])==0){
							//printf("%d",index);
							break;
						}
					}
					//printf("%d %d\n",k,index);
					for(i=0;i<allocation_count;i++){
						//printf("1");
						for(j=0;j<allocation_node[i]->count;j++){
							//printf("2 %d\n",allocation_node[i]->count);
								if(k == allocation_node[i]->points[j]){ //
									//printf("done");
									allocation_node[i]->points[allocation_node[i]->count] = index;
									allocation_node[i]->count++;
									//printf("%d %d %d",index,allocation_node[i]->count,allocation_node[i]->points[allocation_node[i]->count-1]);
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
				/*if(isAllocationNode==0){
				//printf("2 %d ",var_array_count);
				for(i=0;i<init_array_count;i++){ //should it be backwards?
							if(init_array[i] == index){
							repeat = 1;
							//printf("repeat %d %d\n",init_array[i],index);
							break;
							}
				}
				if(repeat==0){	
							//printf("not rep %d \n",index);
							init_array[init_array_count] = index;
							init_array_count++;
						
						}				
				}
	//}*/
}

void add_mem_freed_array(int index){
	mem_freed_array[mem_freed_array_count++] = index;
}

int pop_mem_path_array(){
	return mem_path_array[--mem_path_array_count];
}


//add case for c=a to malloc nodes - done
//print at error statement in rhs validity not end of scope

/*if(){
	b=1;
}
else{
	b=3;
}
error! - done*/

// scanf should be taken as initialized
// b=a c=b no error