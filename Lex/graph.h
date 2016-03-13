enum type_of_statement {declaration = 1, other = 0};
struct node {
	struct node *next1;
	struct node *next2;
	struct node *next3;
	char *symbol;
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

struct node *currentNode;
struct symtab **s;
struct node *startNode;
struct node *stack[100];


