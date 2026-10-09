#ifndef AST_H
#define AST_H

// Define the types of nodes in our AST
typedef enum
{
    AST_NUM,
    AST_BINOP
} NodeType;

// The AST Node structure
typedef struct ASTNode
{
    NodeType type;
    union
    {
        int value; // Used if type == AST_NUM
        struct
        {
            int op; // Operator: '+', '-', '*', '/'
            struct ASTNode *left;
            struct ASTNode *right;
        } binop; // Used if type == AST_BINOP
    };
} ASTNode;

// Function prototypes
ASTNode *make_num_node(int val);
ASTNode *make_binop_node(int op, ASTNode *left, ASTNode *right);
void print_ast(ASTNode *node, int level);

#endif