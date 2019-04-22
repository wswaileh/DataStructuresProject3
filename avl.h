#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED


typedef struct Node * AVL;

struct Node{
    char countryName[51];
    int height;
    AVL left;
    AVL right;
    float numOfTourists;
    city cities;
};
typedef struct Node * AVL;


AVL insert(AVL , char*);
AVL deleteNode(AVL , char *);


// A utility function to right rotate subtree rooted with y
// See the diagram given above.
AVL rightRotate(AVL k1)
{
    AVL k2 = k1->left;
    AVL A = k2->right;

    // Perform rotation
    k2->right = k1;
    k1->left = A;

    // Update heights
    k1->height = max(height(k1->left), height(k1->right))+1;
    k2->height = max(height(k2->left), height(k2->right))+1;

    // Return new root
    return k2;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
AVL leftRotate(AVL k1)
{
    AVL k2 = k1->right;
    AVL A = k2->left;

    // Perform rotation
    k2->left = k1;
    k1->right = A;

    //  Update heights
    k1->height = max(height(k1->left), height(k1->right))+1;
    k2->height = max(height(k2->left), height(k2->right))+1;

    // Return new root
    return k2;
}

// Get Balance factor of node N
int getBalance(AVL N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert countryName  in subtree rooted
// with node and returns new root of subtree.
// A utility function to get maximum of two integers
int max(int a, int b)
{
    if (a>b)
        return a;
    return b;
}

/* Helper function that allocates a new node with the given countryName  and
    NULL left and right pointers. */
AVL newNode(char *countryName1)
{
    AVL node = (AVL)  malloc(sizeof(struct Node));
    strcpy(node->countryName,countryName1);
    node->left   = node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return node;
}
AVL insert(AVL  node, char *countryName)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(countryName));

    if (  strcmp(countryName,node->countryName) < 0 ) //country name < node country name
        node->left  = insert(node->left, countryName);
    else if (  strcmp(countryName,node->countryName) >  0 ) //country name > node country name
        node->right = insert(node->right, countryName);
    else // Equal countryName s are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(countryName,node->left->countryName) < 0 )
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(countryName,node->right->countryName) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(countryName,node->left->countryName) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(countryName,node->right->countryName) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}



// A utility function to get height of the tree
int height(AVL N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

AVL minValueNode(AVL node)
{
    AVL current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given countryName
// from subtree with given root. It returns root of
// the modified subtree.
AVL deleteNode(AVL root, char *countryName )
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the countryName  to be deleted is smaller than the
    // root's countryName , then it lies in left subtree
    if ( strcmp(countryName,root->countryName) < 0)
        root->left = deleteNode(root->left, countryName );

    // If the countryName  to be deleted is greater than the
    // root's countryName , then it lies in right subtree
    else if( strcmp(countryName,root->countryName) > 0  )
        root->right = deleteNode(root->right, countryName );

    // if countryName  is same as root's countryName , then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            AVL temp;

            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AVL temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            strcpy(root->countryName,temp->countryName );

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->countryName );
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int isCountryInTree(AVL tree,char *country)
{
    if (tree == NULL)
        return 0;
    else if (strcmp(tree ->countryName,country) == 0 )
        return 1;
    else
        return (isCountryInTree(tree->right,country)||isCountryInTree(tree->left,country));
}

AVL findCountryInTree(AVL tree,char *country)
{
    if (tree == NULL || strcmp(tree ->countryName,country) == 0 )
        return tree;
    else if (strcmp(tree->countryName,country) < 0 && tree->right != NULL)
        return findCountryInTree(tree->right,country);
    else if (strcmp(tree->countryName,country) > 0 && tree->left != NULL)
        return findCountryInTree(tree->left,country);
    else
        return tree;
}

unsigned int countNodes(AVL T)
{
    unsigned int Count = 1;
    if (T==NULL)
        return 0;
    else
    {
        if (T->right != NULL)
            Count += countNodes(T->right);
        if (T->left != NULL)
            Count += countNodes(T->left);
    }
    return Count;
}

void inOrder(AVL tree)
{   //pre order
    if (tree!=NULL)
    {
        inOrder(tree->left);
        printf("%s | ",tree->countryName);
        inOrder(tree->right);
    }
}

#endif // AVL_H_INCLUDED
