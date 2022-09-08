#include <iostream>
#define COUNT 5
int max(int a, int b) {return (a > b) ? a : b;}
struct Node{
    int data;
    Node *left= nullptr;
    Node *right= nullptr;
    int height;
};
int height(Node *node){
    if (node == nullptr)
        return 0;
    return node->height;
}
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *xbc = x->right;
    x->right = y;
    y->left = xbc;
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    return x;
}
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *ysc = y->left;
    y->left = x;
    x->right = ysc;
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}
Node* createNode(int key)
{
    Node* node = new Node();
    node->data = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return(node);
}
int getBalanceFactor(Node *node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
Node* getMin(Node* node){
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return getMin(node->left);
}
Node* insert(Node* node, int key)
{
    if (node == nullptr)
        return(createNode(key));

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = max(height(node->left),height(node->right)) + 1;
    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    if (balance < -1 && key > node->right->data)
        return leftRotate(node);
    if (balance > 1 && key > node->left->data){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->data){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
Node* deleteNode(Node* root, int key)
{
    if (root == nullptr)
        return root;
    if ( key < root->data )
        root->left = deleteNode(root->left, key);
    else if( key > root->data )
        root->right = deleteNode(root->right, key);
    else {
        if((root->left == nullptr) || (root->right == nullptr)){
            Node *temp = root->left ?root->left : root->right;
            if (temp == nullptr){
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            free(temp);
        }
        else{
            Node* temp = getMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == nullptr)
        return root;
    root->height = max(height(root->left),height(root->right)) +1;

    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);


    if (balance > 1 && getBalanceFactor(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 &&getBalanceFactor(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void printTreeUtil(Node *root, int space){
    if (root == nullptr)
        return;
    space += COUNT;
    printTreeUtil(root->right, space);
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<<root->data<<" "<<getBalanceFactor(root) <<"\n";
    printTreeUtil(root->left, space);
}
void printTree(Node *root){
    printTreeUtil(root, 0);
}
int main() {
    Node *root = nullptr;
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    printTree(root);
    root = deleteNode(root, 6);
    printTree(root);
    root = deleteNode(root, 0);
    printTree(root);
}
