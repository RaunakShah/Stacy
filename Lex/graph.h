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
void createGraph();
void createIfNode();
void createNode();
void push(struct node *item);
void pop();