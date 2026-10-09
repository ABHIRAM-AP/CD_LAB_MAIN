%{
#include <stdio.h>
#include <stdlib.h>

/* Simplified Node Structure (No unions, no header files) */
typedef struct Node {
    char op;            /* Stores '+', '-', '*', '/' (or 0 if it is a number) */
    int val;            /* Stores the number value if op == 0 */
    struct Node *left;  /* Left child pointer */
    struct Node *right; /* Right child pointer */
} Node;

/* Function prototypes */
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

/* Helper function: Create a leaf node for numbers */
Node* make_num(int val) {
    Node *n = malloc(sizeof(Node));
    n->op = 0;   /* 0 means this node is a number, not an operator */
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

/* Helper function: Create a branch node for operators */
Node* make_op(char op, Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    n->op = op;  /* Stores the operator character like '+' */
    n->left = left;
    n->right = right;
    return n;
}

/* Preorder Traversal: Root -> Left -> Right */
void preorder(Node *root) {
    if (!root) return;

    /* 1. Visit Root */
    if (root->op == 0)
        printf("%d ", root->val);
    else
        printf("%c ", root->op);

    /* 2. Visit Left, 3. Visit Right */
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