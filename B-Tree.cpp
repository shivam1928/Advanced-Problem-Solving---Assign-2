#include <bits/stdc++.h>
using namespace std;

#define ORDER 4            // Order of BTree
const int MAX = ORDER - 1; //MAX number of keys
const int MIN = MAX / 2; //MIN number of keys

//*****************************************************************************
// Btree Node structure
//*****************************************************************************
struct BTreeNode
{
        int count;
        int key[MAX + 1];                    //keys start inserted from 1st index, thats why MAX+1 size
        struct BTreeNode *childptr[MAX + 1]; //child ptr stored from 0th index only
};

//*****************************************************************************
// All the function declaration
//*****************************************************************************
struct BTreeNode *root;
struct BTreeNode *createNewNode(int val, struct BTreeNode *child);
void insertvalueIntoNode(int value, int position, struct BTreeNode *node, struct BTreeNode *child);
void splitNode(int value, int *pval, int position, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newBTN);
int get_set_AtCorrectNode(int value, int *preval, struct BTreeNode *node, struct BTreeNode **child);
void inordertraversal(struct BTreeNode *myNode);
void searchElement(int value, struct BTreeNode *myNode);

//*****************************************************************************
// create new Root node and assigned its leftchild and rightchild
//*****************************************************************************
struct BTreeNode *createNewNode(int val, struct BTreeNode *child)
{
        //create new root node and assigned leftlink to its old root and
        // rightlink to child(right slplitted node)
        struct BTreeNode *newNode;
        newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
        newNode->key[1] = val;
        newNode->count = 1;
        newNode->childptr[0] = root;
        newNode->childptr[1] = child;
        return newNode;
}

//*****************************************************************************
// Insert value into its correct position by moving all its right element
// to its next position
//*****************************************************************************
void insertvalueIntoNode(int value, int position,
                         struct BTreeNode *node, struct BTreeNode *child)
{
        int j = node->count;
        //move all element & its pointer from "nodecount(last node)" to "position+1" index, one step next
        // to make space for node to be inserted at "position+1"
        while (j > position)
        {
                node->key[j + 1] = node->key[j];
                node->childptr[j + 1] = node->childptr[j];
                j--;
        }

        //inserted that new node at index "positinon+1" index
        node->key[j + 1] = value;
        node->childptr[j + 1] = child;
        (node->count)++;
}

//***********************************************************************
// Insert value into BTree
//***********************************************************************
void insertion(int val)
{
        int flag, i;
        struct BTreeNode *child;
        //find correct position of node to be inserted
        flag = get_set_AtCorrectNode(val, &i, root, &child);
        //If flag==1 then create new node as root because of split
        if (flag)
        {
                root = createNewNode(i, child);
        }
}

//*****************************************************************************
// Split node into left and right subpart
//*****************************************************************************
void splitNode(int value, int *pval, int position,
               struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newBTN)
{

        int med, j;
        //to find in which part(after split) "position ele" goes
        if (position > MIN)
                med = MIN + 1;
        else
                med = MIN;

        // create new BTN(right split node)
        *newBTN = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
        j = med + 1;
        //copy all element from mid+1 to MAX into newBTN
        while (j <= MAX)
        {
                (*newBTN)->key[j - med] = node->key[j];
                (*newBTN)->childptr[j - med] = node->childptr[j];
                j++;
        }
        //node is left splitted node after splitting
        //update count of left splitted node
        node->count = med;
        //update count of right splitted node
        (*newBTN)->count = MAX - med;

        if (position <= MIN)
                insertvalueIntoNode(value, position, node, child);

        else
                insertvalueIntoNode(value, position - med, *newBTN, child);

        *pval = node->key[node->count];
        //right child of leftsplitted node is assigned as leftchild(0) of rightsplitted node
        (*newBTN)->childptr[0] = node->childptr[node->count];
        (node->count)--;
}

//*****************************************************************************
// Recursively find correct position of node to be inserted and set its value
//*****************************************************************************
int get_set_AtCorrectNode(int value, int *preval,
                          struct BTreeNode *node, struct BTreeNode **child)
{

        int position;
        //if given_node is null
        if (!node)
        {
                *preval = value;
                *child = NULL;
                return 1;
        }
        //if value of key is less than first key of Btree node
        if (value < node->key[1])
        {
                position = 0;
        }
        else
        {       // find position such that all index > position ==> "value" < arr[index]
                // all element after position are greater than "value" to be inserted
                for (position = node->count; (value < node->key[position] && position > 1); position--)
                {
                        // to getting correct position
                }

                if (value == node->key[position])
                {
                        printf("Duplicate Element Found ...\n");
                        return 0;
                }
        }

        //recursively go one-leve down the tree to get correct position of node to be inserted
        if (get_set_AtCorrectNode(value, preval, node->childptr[position], child))
        {
                //If we have enough space to insert one element <--> not required to split the node
                if (node->count < MAX)
                {
                        insertvalueIntoNode(*preval, position, node, *child);
                }
                //If our node count==MAX capacity then required to split the node
                else
                {
                        splitNode(*preval, preval, position, node, *child, child);
                        return 1;
                }
        }
        return 0;
}

// **********************************************************************
// search perticular element into Btree
// **********************************************************************
void searchElement(int value, struct BTreeNode *myNode)
{
        int position;
        //If we reach to empty node while searching means value is not present in BTree
        if (!myNode)
        {
                cout << "\nElement -" << value << " - is NOT Present into BTree\n";
                return ;
        }

        if (value < myNode->key[1])
        {
                position = 0;
        }
        else
        {
                // find position such that all index > position ==> "value" < arr[index]
                // all element after position are greater than "value" to be inserted
                for (position = myNode->count; (value < myNode->key[position] && position > 1); (position)--)
                {
                        //find correct position
                }
                //if Value is present in that node then return ans;
                if (value == myNode->key[position])
                {
                        cout << "\nElement -" << value << " - is Present into BTree\n";
                        return ;
                }
        }
        //If element not found then goto rightchild to find value recursively
        searchElement(value, myNode->childptr[position]);

    return;
}

// **********************************************************************
// Do inorder traversal of BTree
// **********************************************************************
void inordertraversal(struct BTreeNode *myNode)
{
        int i;
        if (myNode)
        {
                for (i = 0; i < myNode->count; i++)
                {
                        inordertraversal(myNode->childptr[i]);
                        cout << (myNode->key[i + 1]) << " ";
                }
                inordertraversal(myNode->childptr[i]);
        }
}

int main()
{
        int val, choice;
        int ans;
        while (1)
        {
                printf("\n1. Insertion");
                printf("\n2. Search");
                printf("\n3. Traversal");
                printf("\n4. Exit");
                printf("\nEnter your choice:");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                        printf("Enter value to be inserted :");
                        scanf("%d", &val);
                        insertion(val);
                        break;
                case 2:
                        printf("Enter the value to be search:");
                        scanf("%d", &val);
                        searchElement(val,root);
                        break;
                case 3:
                        cout << "\nInorder Traversal of Btree is : ";
                        inordertraversal(root);
                        break;
                
                case 4:
                        exit(0);

                default:
                        printf("Invalid Argument\n");
                        break;
                }
        }
}
