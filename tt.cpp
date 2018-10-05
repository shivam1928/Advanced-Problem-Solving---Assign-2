#include<bits/stdc++.h>
using namespace std;
#define SIZE 100005
#define X 31

// struct node<T,U>* getnewNode(int key1,int value1)
// {
//     struct node* new_node =(struct node*) malloc(sizeof(struct node));
//     new_node->kunique = key1;
//     new_node->val=value1;
//     return new_node;
// }

template <class T, class U>
class Unordered_map
{
    public:
    struct node{
        T kunique;
        U val;
        struct node *next;
    };
    //vector<struct node<T,U>*> hashtable(SIZE);

    long long getHashIndex(T key)
    {
        ostringstream str1;
        str1 << key; 
        string str = str1.str();
        //cout<<str<<endl;
        long long result=str[0];
        for(long long i=1;i<str.length();i++)
        {
             result = result*X + str[i];
        }
        long long index=result%SIZE;
        return index;
    }
   
    void insertintohash(T key,U value)
    {
        long long index=getHashIndex(key);
        cout<<"Hash Index : "<<index<<endl;
        // if(hashtable[index]==NULL)
        // {
        //     hashtable[index]=getnewNode();
        //     cout<<"hii"<<endl;
        // }
    }
};
int main()
{
    string key;
    int value;
    Unordered_map<string,int> mp;
    while(1)
    {
        cin>>key;
        cin>>value;
        mp.insertintohash(key,value);
    }
    return 0;
}