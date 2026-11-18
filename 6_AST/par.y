%{
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char op;            
    int val;            
    struct Node *left;  
    struct Node *right; 
} Node;


Node* make_num(int val);
Node* make_op(char op, Node *left, Node *right);
void preorder(Node *root);
int yylex(void);
void yyerror(const char *s);

Node *root;
%}

/* YACC Union for handling values during parsing */
%union {
    int val;
    struct Node *node;
}

%token <val> NUMBER
%type <node> expr term factor

%%

program:
    expr '\n' { root = $1; return 0; }
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
  ;

%%

Node* make_num(int val) {
    Node *n = malloc(sizeof(Node));
    n->op = 0;   
    n->val = val;
    n->left = n->right = NULL;
    return n;
}


Node* make_op(char op, Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    n->op = op;  
    n->left = left;
    n->right = right;
    return n;
}

void preorder(Node *root) {
    if (!root) return;

    if (root->op == 0)
        printf("%d ", root->val);
    else
        printf("%c ", root->op);

    preorder(root->left);
    preorder(root->right);
}

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter expression: ");
    if (yyparse() == 0) {
        printf("Preorder: ");
        preorder(root);
        printf("\n");
    }
    return 0;
}