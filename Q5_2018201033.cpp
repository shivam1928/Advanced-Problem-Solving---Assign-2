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
//class StringBuilder which store total string length and head pointer of all string node
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

//append string s2 to s1 and returns new object
stringBuilder stringAppend(stringBuilder s1, stringBuilder s2)
{
    if (s1.head == NULL & s2.head == NULL)
    {
        return stringBuilder();
    }
    stringBuilder s3;
    struct node *cur, *pre, *newhead = NULL;
    //append all string node from s1
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
    //append all string node from s2
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

//merge multiple string node of s1 to single string node
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

void preKMPcompute(const char *sub, int patlen, int *kmpNext)
{
    int len = 0; 
    kmpNext[0] = 0; 
    int i = 1; 
    while (i < patlen) 
    { 
        if (sub[i] == sub[len]) { 
            len++; 
            kmpNext[i] = len; 
            i++; 
        } 
        else 
        { 
            if(len != 0) 
                len = kmpNext[len - 1];
            else
            { 
                kmpNext[i] = 0; 
                i++; 
            } 
        } 
    }
}

// find substr from source string s1 and return index founded
// if substr not found then return -1
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

        int i = 0; // to keep track of sourcestring
        int j = 0; // to keep track of substr 
        int kmpNext[patlen];
        preKMPcompute(substr, patlen, kmpNext); 
        while (i < sourcelen) 
        { 
            //when sourcestr and substr match incremeent both index i,j
            if (substr[j] == sourcestr[i]) 
            { 
                j++; 
                i++; 
            } 
            // when j reached to its length means substr found and return
            if (j == patlen) 
            { 
                return (i-j);
            } 
            //when sourcestr[i] and substr[j] doesn't match
            else if (i < sourcelen && substr[j] != sourcestr[i]) 
            { 

                //if J is not first index(0) then assigned previous index kmpNext
                 if (j != 0) 
                    j = kmpNext[j - 1]; 
                // if j is 0 then increment i by 1
                else
                    i = i + 1; 
            } 
        }
        // if pattern not found in soucestr then return -1
         if(i==sourcelen)
            return -1;  


    }
}

int main()
{
    stringBuilder s1 = stringInitialize("hello");
    stringBuilder s2 = stringInitialize("World");
    stringBuilder s4 = stringInitialize("dofeshjbjvs");
    stringBuilder s5 = stringInitialize("IamDk");
    stringBuilder s3=stringAppend(s1,s2);
    printall(s3);
    s1=stringAppend(s3,s4);
    s1=stringAppend(s1,s5);
    printall(s3);
    printall(s1);
    int ind;
    if((ind=findSubstring(s1,"of")) != -1)
    {
        cout<<"\nPattern found at index : "<<ind<<endl;
    }
    else
    {
        cout<<"\nPattern not Found !!!"<<endl;
    }

    //printall(s3);
}