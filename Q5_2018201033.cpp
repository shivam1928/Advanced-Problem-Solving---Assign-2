#include <bits/stdc++.h>
using namespace std;

//Linked list node structure
struct node
{
    const char *str; // store pointer to string
    struct node *next; // store pointer to node
};

//create new node by allocating memory
struct node *getnode(const char *s)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->str = s;
    newnode->next = NULL;
}
//class StringBuilder which store head pointer of all string node and length
class stringBuilder
{
  public:
    int len;
    struct node *head;

    //Default constructor
    stringBuilder()
    {
        len = 0;
        head = NULL;
    }

    //Parameterised contructor
    stringBuilder(const char *s)
    {
        len = strlen(s);
        head = getnode(s);
    }
};

//Intialised stringBuilder object with given string
stringBuilder stringInitialize(const char *str)
{
    stringBuilder sobj(str);
    return sobj;
}

//print all node of stringBuilder which append to it.
void printall(stringBuilder ss)
{
    struct node *tt = ss.head;
    while (tt)
    {
        printf("%s-", tt->str);
        tt = tt->next;
    }
    cout<<" :::: length : "<<ss.len<<endl;
}

stringBuilder stringAppend(stringBuilder s1, stringBuilder s2)
{
    if (s1.head == NULL & s2.head == NULL)
    {
        return stringBuilder();
    }
    stringBuilder s3;
    struct node *cur, *pre, *newhead = NULL;
    if (s1.head != NULL)
    {
        cur = s1.head;
        pre = (struct node *)malloc(sizeof(struct node));
        pre->str = s1.head->str;
        pre->next = NULL;
        newhead = pre;
        cur = cur->next;
        while (cur != NULL)
        {
            struct node *new_node = (struct node *)malloc(sizeof(struct node));
            new_node->str = cur->str;
            new_node->next = NULL;
            pre->next = new_node;
            pre = new_node;
            cur = cur->next;
        }
    }
    if(s2.head != NULL)
    {
        cur = s2.head;
        struct node *firofs2 = (struct node *)malloc(sizeof(struct node));
        firofs2->str = cur->str;
        firofs2->next = NULL;
        if(s1.head==NULL)
        {
            pre=firofs2;
            newhead=pre;
        }
        else{
            pre->next = firofs2;
            pre = firofs2;
        }
        cur = cur->next;
        while (cur != NULL)
        {
            struct node *new_node = (struct node *)malloc(sizeof(struct node));
            new_node->str = cur->str;
            new_node->next = NULL;
            pre->next = new_node;
            pre = new_node;
            cur = cur->next;
        }
    }

    s3.head = newhead;
    s3.len = s1.len + s2.len;

    return s3;
}
void mergeallnodestring(stringBuilder &s1)
{
        struct node *pre;
        struct node *cur=s1.head;
        char *finalstr= new char[s1.len];
        int finallen=s1.len;
        while(cur!=NULL)
        {
            strcat(finalstr,cur->str);
            pre=cur;
            cur=cur->next;
            free(pre);
        }
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        //printf("\nfinal string  : %s",finalstr);
        //cout<<endl;
        new_node->str=finalstr;
        new_node->next=NULL;
        s1.head=new_node;
        s1.len=finallen;

}

void preKMPcompute(const char* sub, int patlen, int *lps)
{
    int len = 0; 
    lps[0] = 0; 
    int i = 1; 
    while (i < patlen) 
    { 
        if (sub[i] == sub[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else 
        { 
            if(len != 0) 
                len = lps[len - 1];
            else
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    }
}
int findSubstring(stringBuilder &s1,const char *substr)
{
    if(s1.head==NULL)
    {
        cout<<"Your Source string is empty !!!"<<endl;
        return -1;
    }
    else if(strlen(substr)==0)
    {
        cout<<"Your Pattern is empty !!!"<<endl;
        return -1;
    }
    else
    {
        if((s1.head)->next!=NULL)
            mergeallnodestring(s1);
        //printall(s1);
        const char *sourcestr=(s1.head)->str;
        int patlen = strlen(substr); 
        int sourcelen = strlen(sourcestr); 
        int lps[patlen];

        preKMPcompute(substr, patlen, lps); 
        int i = 0; 
        int j = 0;
        while (i < sourcelen) 
        { 
            if (substr[j] == sourcestr[i]) { 
                j++; 
                i++; 
            } 
    
            if (j == patlen) 
            { 
                return (i-j);
            } 
            else if (i < sourcelen && substr[j] != sourcestr[i]) 
            { 

                if (j != 0) 
                    j = lps[j - 1]; 
                else
                    i = i + 1; 
            } 
        }

        if(i==sourcelen)
            return -1;  

    }
}

int main()
{
    stringBuilder s1 = stringInitialize("hello");
    stringBuilder s2 = stringInitialize("World");
    stringBuilder s4 = stringInitialize("dofeshjbjvs");
    stringBuilder s3=stringAppend(s1,s2);
    printall(s3);
    s1=stringAppend(s3,s4);
    s1=stringAppend(s1,s2);
    printall(s1);
    
    
    cout<<"\nPattern found at index : "<<findSubstring(s1,"World");

    //printall(s3);
}