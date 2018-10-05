#include <bits/stdc++.h>
using namespace std;
#define SIZE 3
#define X 31

template <class T, class U>
class Unordered_map
{
    class node
    {
      public:
        T kunique;
        U val;
        node *next;
    };

    node *hashtable[SIZE];

  public:
    //Constructor
    Unordered_map()
    {
        for (int i = 0; i < SIZE; i++)
        {
            hashtable[i] = NULL;
        }
    }

    void printall()
    {
        cout << "\n*********************" << endl;
        for (int i = 0; i < SIZE; i++)
        {
            cout << hashtable[i] << " ";
            if (hashtable[i] != NULL)
            {
                node *cur = hashtable[i];
                while (cur != NULL)
                {
                    cout << cur->kunique << " : ";
                    cout << cur->val << " || ";
                    cur = cur->next;
                }
            }
            cout << endl;
        }
        cout << "\n*********************" << endl;
    }

    node *getnewNode(T key1, U value1)
    {
        node *new_node = new node;
        new_node->kunique = key1;
        new_node->val = value1;
        new_node->next = NULL;
        //cout << "\nNode created successfully";
        return new_node;
    }

    long long getHashIndex(T key)
    {
        ostringstream str1;
        str1 << key;
        string str = str1.str();
        //cout<<str<<endl;
        long long result = str[0];
        for (long long i = 1; i < str.length(); i++)
        {
            result = result * X + str[i];
        }
        long long index = result % SIZE;
        return index;
    }

    void insertintohash(T key, U value)
    {
        printall();
        long long index = getHashIndex(key);
        cout << "Hash Index : " << index << endl;
        if (hashtable[index] == NULL)
        {
            hashtable[index] = getnewNode(key, value);
            cout << "Node inserted Succesfully" << endl;
        }
        else
        {
            node *cur = hashtable[index];
            int flag = 0;
            while (cur->next != NULL)
            {
                if (cur->kunique == key)
                {
                    flag = 1;
                    break;
                }
                cur = cur->next;
            }
            if (!flag && cur->kunique!=key)
            {
                cur->next = getnewNode(key, value);
                cout << "Node inserted Succesfully" << endl;
            }
            else
            {
                cout << "Key Already present in map" << endl;   
            }
        }
        printall();
    }
    U searchvalue(T key)
    {
        long long index = getHashIndex(key);
        //cout << "Hash Index : " << index << endl;
        if (hashtable[index] == NULL)
            return "-1";
        else
        {
            node *cur = hashtable[index];
            while (cur != NULL && cur->kunique != key)
            {
                cur = cur->next;
            }
            if (cur == NULL)
                return "-1";
            else
            {
                return cur->val;
            }
        }
    }
    void deletekey(T key)
    {
        printall();
        long long index = getHashIndex(key);
        cout<<"in delete Hash Index : "<<index<<endl;
        if (hashtable[index] == NULL)
        {
            printf("\nKey not found in Map");
            return;
        }
        else
        {
            node *head = hashtable[index];
            node *tra = head;
            if (head->kunique == key)
            {
                tra = head;
                head = head->next;
                free(tra);
                hashtable[index] = head;
                printall();
                return;
            }
            else
            {
                node *pre;
                while (tra->next != NULL && tra->kunique != key)
                {
                    pre = tra;
                    tra = tra->next;
                }
                if (tra->next == NULL && tra->kunique != key)
                {
                    printf("\nKey not found in Map");
                    return;
                }
                else //tra->data==ele
                {
                    pre->next = tra->next;
                    free(tra);
                }
                printall();
            }
        }
    }
};
int main()
{
    string key;
    string value;
    Unordered_map<string, string> mp;
    int ch;
    do
    {
        cout << "\n1.insert";
        cout << "\n2.search";
        cout << "\n3.Delete";
        cout << "\nEnter You choice : ";
        cin >> ch;
        if (ch == 1)
        {
            cin >> key;
            cin >> value;
            mp.insertintohash(key, value);
        }
        else if (ch == 2)
        {
            cin >> key;
            cout << "Value : " << mp.searchvalue(key);
        }
        else if (ch == 3)
        {
            cin >> key;
            mp.deletekey(key);
        }
        else
        {
            cout << "Invalid Argument";
        }

    } while (ch != 0);

    return 0;
}