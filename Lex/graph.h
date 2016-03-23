enum type_of_statement { declaration = 1, lhs = 2, rhs = 3, if_node = 4, for_node = 5, while_node = 6, switch_node = 7, function_parameter = 8, other = 0};
struct node {
	struct node *next[10];
	char *symbol;
	int type;
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
void print_init_array();
void malloc_array_add(struct node* graph_node);
void remove_malloc_array(struct node* graph_node);
struct node *currentNode;
struct symtab **s;
struct node *startNode;
struct node *stack[100];
char *var_array[100];
int init_array[100];
int var_array_stack[100];
int init_array_stack[100];
char *malloc_array[100];