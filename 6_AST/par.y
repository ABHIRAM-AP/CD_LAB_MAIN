
%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(char *s);
    int yylex();

    typedef struct Node {
        int val;
        char var;
        char op;
        struct Node *left, *right;
    } Node;

    Node *root;

    Node *make_num(int val);
    Node *make_var(char var);
    Node *make_op(char op, Node *left, Node *right);

    void levelorder(Node *root);
%}

%union {
    int val;
    char var;
    struct Node *node;
}

%token <val> NUMBER
%token <var> ID

%type <node> expr term factor

%%

input:
    expr '\n' {
        root = $1;
        return 0;
    }
    ;

expr:
      expr '+' term { $$ = make_op('+', $1, $3); }
    | expr '-' term { $$ = make_op('-', $1, $3); }
    | term          { $$ = $1; }
    ;

term:
      term '*' factor { $$ = make_op('*', $1, $3); }
    | term '/' factor { $$ = make_op('/', $1, $3); }
    | factor          { $$ = $1; }
    ;

factor:
      '(' expr ')' { $$ = $2; }
    | NUMBER       { $$ = make_num($1); }
    | ID           { $$ = make_var($1); }
    ;

%%

Node *make_num(int val)
{
    Node *n = malloc(sizeof(Node));
    n->left = n->right = NULL;
    n->val = val;
    n->var = 0;
    n->op = 0;
    return n;
}

Node *make_var(char var)
{
    Node *n = malloc(sizeof(Node));
    n->left = n->right = NULL;
    n->val = 0;
    n->var = var;
    n->op = 0;
    return n;
}

Node *make_op(char op, Node *left, Node *right)
{
    Node *n = malloc(sizeof(Node));
    n->left = left;
    n->right = right;
    n->val = 0;
    n->var = 0;
    n->op = op;
    return n;
}

/* Level Order Traversal */

void levelorder(Node *root)
{
    if (root == NULL)
        return;

    Node *queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        Node *temp = queue[front++];

        if (temp->op != 0)
            printf("%c ", temp->op);
        else if (temp->var != 0)
            printf("%c ", temp->var);
        else
            printf("%d ", temp->val);

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }
}

void yyerror(char *s)
{
    printf("Error: %s\n", s);
}

int main()
{
    printf("Enter expression: ");

    if (yyparse() == 0)
    {
        printf("Level Order Traversal:\n");
        levelorder(root);
        printf("\n");
    }

    return 0;
}
