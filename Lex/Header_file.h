/* Header file */
enum type_of_statement { declaration = 1, lhs = 2, rhs = 3, if_node = 4, for_node = 5, while_node = 6, switch_node = 7, function_parameter = 8, malloc_node = 9, ifelse_node=10, other = 0};		//Identify different statement types
struct node {		//Node structure
	struct node *next[10];
	char **symbol;
	int type;
	int line;
	int symbolCount;
	char **index;
	int indexCount;
};
struct safeArray{
	char *safe[10];
	struct safeArray* nextScope;
	struct safeArray* prevScope;
	int count;
};
struct unsafeArray{
	char *unsafe[10];
	int count;
	struct unsafeArray* nextScope;
	struct unsafeArray* prevScope;
};

struct malloc {
	int index;
	int *points;
	int count;
	int line;
	int free;
};

struct symtab{
	char *symbol;
	int init;
};

struct stack{
	struct node *item;
};
int scope_stack[100];

void createGraph();
void createIfNode();
void createNode();
void push(struct node *item);
struct node* pop();
void add_to_symtab(char *symbol);
void init_symtab(char *symbol);
void add_scope();
void pop_scope();
void var_array_add(struct node* node);
void push_var_array_stack(int count);
void push_init_array_stack(int count);
int pop_var_array_stack();
int pop_init_array_stack(); 
void print_init_array(struct node * graph_node);
void print_mem_leaks(struct node* graph_node);
void malloc_array_add(struct node* graph_node);
void remove_malloc_array(char* graph_node);
void check_lhs_for_init_var(struct node* graph_node);
void check_lhs_for_mem_leaks(struct node* graph_node);
int pop_init_var_used_stack();
void push_init_var_used_stack(int var_array_count);
void add_mem_alloc_path_array(struct node* graph_node);
void add_mem_freed_array(int index);
void push_mem_path_array(int index);
int pop_mem_path_array();
void prepare_buffer_overflow();
void clean_buffer_overflow();
void init_buffer_overflow();


struct malloc* allocation_node[10];	
struct node *currentNode;
struct safeArray *currentSafeArray;
struct unsafeArray *currentUnsafeArray;
struct node *currentSelectionNode;
extern int ifFlag;
struct symtab **s;
struct node *startNode;
struct node *stack[100];
char *var_array[100];
int init_array[100];
int var_array_stack[100];
int init_array_stack[100];
int init_var_used_stack[100];
char *malloc_array[100];
extern int line_number;
int init_var_used;
int mem_freed_array[100];
int mem_path_array[100];
char *uninitVarUsed;

