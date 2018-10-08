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

void removeValue(struct BTreeNode *cur, int position) 
{
        int j = position + 1;
        while (j <= cur->count) 
        {
                cur->key[j - 1] = cur->key[j];
                cur->childptr[j - 1] = cur->childptr[j];
                j++;
        }
        cur->count--;
  }

  void doRightShift(struct BTreeNode *cur, int pos) 
  {
        struct BTreeNode *x = cur->childptr[pos];
        int j = x->count;

        while (j > 0) 
        {
                x->key[j + 1] = x->key[j];
                x->childptr[j + 1] = x->childptr[j];
        }
        x->key[1] = cur->key[pos];
        x->childptr[1] = x->childptr[0];
        x->count++;

        x = cur->childptr[pos - 1];
        cur->key[pos] = x->key[x->count];
        cur->childptr[pos] = x->childptr[x->count];
        x->count--;
        return;
  }

  void doLeftShift(struct BTreeNode *cur, int pos) 
  {
        int j = 1;
        struct BTreeNode *x = cur->childptr[pos - 1];

        x->count++;
        x->key[x->count] = cur->key[pos];
        x->childptr[x->count] = cur->childptr[pos]->childptr[0];

        x = cur->childptr[pos];
        cur->key[pos] = x->key[1];
        x->childptr[0] = x->childptr[1];
        x->count--;

        while (j <= x->count) 
        {
                x->key[j] = x->key[j + 1];
                x->childptr[j] = x->childptr[j + 1];
                j++;
        }
        return;
  }

  /* merge nodes */
  void mergeNodes(struct BTreeNode *cur, int pos) 
  {
        int j = 1;
        struct BTreeNode *x1 = cur->childptr[pos], *x2 = cur->childptr[pos - 1];

        x2->count++;
        x2->key[x2->count] = cur->key[pos];
        while (j <= x1->count) {
                x2->count++;
                x2->key[x2->count] = x1->key[j];
                x2->childptr[x2->count] = x1->childptr[j];
                j++;
        }

        j = pos;
        while (j < cur->count) {
                cur->key[j] = cur->key[j + 1];
                cur->childptr[j] = cur->childptr[j + 1];
                j++;
        }
        cur->count--;
        free(x1);
  }

  void adjustBTree(struct BTreeNode *cur, int pos) {
        if (!pos) {
                if (cur->childptr[1]->count > MIN) {
                        doLeftShift(cur, 1);
                } else {
                        mergeNodes(cur, 1);
                }
        } else {
                if (cur->count != pos) {
                        if(cur->childptr[pos - 1]->count > MIN) {
                                doRightShift(cur, pos);
                        } else {
                                if (cur->childptr[pos + 1]->count > MIN) {
                                        doLeftShift(cur, pos + 1);
                                } else {
                                        mergeNodes(cur, pos);
                                }
                        }
                } else {
                        if (cur->childptr[pos - 1]->count > MIN)
                                doRightShift(cur, pos);
                        else
                                mergeNodes(cur, pos);
                }
        }
}

void setSuccessor(struct BTreeNode *cur, int pos) 
{
        struct BTreeNode *temp;
        temp = cur->childptr[pos];

        while(temp->childptr[0] != NULL)
        {
                temp = temp->childptr[0];
        }
        cur->key[pos] = temp->key[1];

}

int deleteValueFromNode(int value, struct BTreeNode *cur) 
{
        int position;
        int fg=0;
        if (cur) 
        {
                if (value < cur->key[1]) 
                {
                        position = 0;fg = 0;
                } 
                else 
                {
                        for (position = cur->count;(value < cur->key[position] && position > 1); position--)
                        {
                                //get correct position
                        }
                        if (value == cur->key[position]) fg = 1;
                        else   fg = 0;

                }
                if (fg) 
                {
                        if (cur->childptr[position - 1]) {
                                setSuccessor(cur, position);
                                fg = deleteValueFromNode(cur->key[position], cur->childptr[position]);
                                if(fg == 0) 
                                        cout<<"\nElement not present in BTree\n"<<endl;
                        } 
                        else 
                        {
                                removeValue(cur, position);
                        }
                } 
                else 
                {
                        fg = deleteValueFromNode(value, cur->childptr[position]);
                }
                if (cur->childptr[position]) 
                {
                        if (cur->childptr[position]->count < MIN)
                                adjustBTree(cur, position);
                }
        }
        return fg;
  }

void deleteElement(int value, struct BTreeNode *cur) 
{
        struct BTreeNode *tt;
        if(!deleteValueFromNode(value, cur)) 
        {
                cout<<"\nElement not Found in BTree\n";
                return;
        } 
        else 
        {
                if (cur->count == 0) 
                {
                        tt = cur;
                        cur = cur->childptr[0];
                        free(tt);
                }
        }
        root = cur;
        return;
  }

int main()
{
        int val, choice;
        int ans;
        while (1)
        {
                printf("\n1. Insertion");
                printf("\n2. Deletion");
                printf("\n3. Search");
                printf("\n4. Traversal");
                printf("\n5. Exit");
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
                        printf("Enter value to be Deleted :");
                        scanf("%d", &val);
                        deleteElement(val, root);
                        break;
                case 3:
                        printf("Enter the value to be search:");
                        scanf("%d", &val);
                        searchElement(val,root);
                        break;
                case 4:
                        cout << "\nInorder Traversal of Btree is : ";
                        inordertraversal(root);
                        break;
                
                case 5:
                        exit(0);

                default:
                        printf("Invalid Argument\n");
                        break;
                }
        }
}
