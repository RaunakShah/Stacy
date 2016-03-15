enum type_of_statement {declaration = 1, lhs = 2, rhs = 3, other = 0};
struct node {
	struct node *next1;
	struct node *next2;
	struct node *next3;
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
struct node *currentNode;
struct symtab **s;
struct node *startNode;
struct node *stack[100];
char *var_array[100];
int init_array[100];

