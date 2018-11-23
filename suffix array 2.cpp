#include<bits/stdc++.h>
using namespace std;
int *finalsuffixans;


struct suffixArray{
    int index; // to keep track of original index of suffix
    int tuple[2]; //maintain "rank" and "next rank" 
};

//comparator for comparing two tuple
bool comfun(struct suffixArray obj1, struct suffixArray obj2)
{
    if(obj1.tuple[0]==obj2.tuple[0])
    {
        if(obj1.tuple[1]<obj2.tuple[1])
            return true;
        else
            return false;
    }
    else if(obj1.tuple[0]<obj2.tuple[0])
    {
        return true;
    }
    else
    {
        return false;
    }
}

//create suffix array of given string
void createsufficArray(string str)
{
    int size1=str.length();
    struct suffixArray suffobj[size1];
    int suffInd[size1];

    // Intitialisation of tuple w.r.t first two character
    for(int i=0;i<size1;i++)
    {
        suffobj[i].index=i;
        suffobj[i].tuple[0]=str[i]-'0';
        if(i<size1-1)
        {
            suffobj[i].tuple[1]=str[i+1]-'0';
        }
        else{
             suffobj[i].tuple[1]=-1;
        }

    }

    //sort according to tuple;
    sort(suffobj,suffobj+size1, comfun);

    for(int j=2;j<size1;j=j*2)
    {   
        //initialised rank and index of first suffix;
        int curRank=0;
        int preRank=suffobj[0].tuple[0];
        suffobj[0].tuple[0]=curRank;
        suffInd[suffobj[0].index]=0;

        //compute new rank and index for all suffix
        for(int k=1;k<size1;k++)
        {
            int curtuple1=suffobj[k].tuple[0];
            int curtuple2=suffobj[k].tuple[1];
            int pretuple2=suffobj[k-1].tuple[1];
            // if cur tuple/rank is same as previous tuple/rank then assigned same rank to suffix
            if(curtuple1==preRank && curtuple2==pretuple2)
            {
                preRank=suffobj[k].tuple[0];
                suffobj[k].tuple[0]= curRank;
            }
            //else increment rank by 1 and then assigned to suffix
            else{
                preRank=suffobj[k].tuple[0];
                suffobj[k].tuple[0]=++curRank;
            }
            suffInd[suffobj[k].index]=k;
        }

        //compute "next rank/tuple" for all suffix
        for (int i=0;i<size1;i++) 
        { 
            int nextind = suffobj[i].index + j; 
            if(nextind < size1){
                suffobj[i].tuple[1]=suffobj[suffInd[nextind]].tuple[0];
            }
            else{
                 suffobj[i].tuple[1]=-1;
            }
        } 
  
        //sort all suffix 
        sort(suffobj, suffobj+size1, comfun); 

    }

    // Store all indexes of sorted suffixes in the suffix array 
    finalsuffixans = new int[size1]; 
    for (int i=0;i<size1;i++)
    {
        finalsuffixans[i] = suffobj[i].index; 
    } 
    
}

int getLongestCommonPrefix(string s1,string s2)
{
    int l1=s1.length();
    int l2=s2.length();
    int count=0;
    for(int i=0;i<l1 && i<l2;i++)
    {
        if(s1[i]==s2[i])
            count++;
        else
            break;
    }
    return count;
}

int main()
{
    string s;
    cin>>s;
    int k;
    cin>>k;
    long int len=s.length();
    //create suffix array on double_string
    createsufficArray(s);

    cout<<"Suffix Array for given string : ";
    for(int i=0;i<len;i++)
    {
        cout<< finalsuffixans[i]<<" ";
    }

    int maxLCPlength=-1;;
    int curLCPlen;

    for(long int i=0;i<=len-k;i++)
    {
        string s1=s.substr(finalsuffixans[i]);
        string s2=s.substr(finalsuffixans[i+k-1]);
        curLCPlen=getLongestCommonPrefix(s1,s2);
        if(maxLCPlength<curLCPlen)
        {
            maxLCPlength=curLCPlen;
        }

    }

    if(maxLCPlength==0)
        maxLCPlength=-1;

    cout<<"MAX length : "<<maxLCPlength<<endl;   

    return 0;

}