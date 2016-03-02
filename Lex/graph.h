struct node {
	struct node *next;
};

struct symtab{
	char *symbol;
	int init;
};

void createGraph();
void createIfNode();
void createNode();