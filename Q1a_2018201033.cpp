#include<bits/stdc++.h>
using namespace std;
int *finalsuffixans;
struct suffixArray{
    int index;
    int tuple[2];
};

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

    for(int j=4;j<(2*size1);j=j*2)
    {   
        int curRank=0;
        int preRank=suffobj[0].tuple[0];
        suffobj[0].tuple[0]=curRank;
        suffInd[suffobj[0].index]=0;

        for(int k=1;k<size1;k++)
        {
            int curtuple1=suffobj[k].tuple[0];
            int curtuple2=suffobj[k].tuple[1];
            int pretuple2=suffobj[k-1].tuple[1];
            if(curtuple1==preRank && curtuple2==pretuple2)
            {
                preRank=suffobj[k].tuple[0];
                suffobj[k].tuple[0]= curRank;
            }
            else{
                preRank=suffobj[k].tuple[0];
                suffobj[k].tuple[0]=++curRank;
            }
            suffInd[suffobj[k].index]=k;
        }

        for (int i=0;i<size1;i++) 
        { 
            int nextind = suffobj[i].index + j/2; 
            if(nextind < size1){
                suffobj[i].tuple[1]=suffobj[suffInd[nextind]].tuple[0];
            }
            else{
                 suffobj[i].tuple[1]=-1;
            }
        } 
  
        sort(suffobj, suffobj+size1, comfun); 

    }

     // Store indexes of all sorted suffixes in the suffix array 
    finalsuffixans = new int[size1]; 
    for (int i=0;i<size1;i++)
    {
        finalsuffixans[i] = suffobj[i].index; 
    } 
    
}

int main()
{
    string s;
    cin>>s;
    createsufficArray(s);
    cout<<"Suffix Array for given string : ";
    int len=s.length();
    for(int i=0;i<len;i++)
    {
        cout<< finalsuffixans[i]<<" ";
    }
    int small=finalsuffixans[0];
    string nextsub=s.substr(small);
    //cout<<nextsub<<endl;
    string presub=s.substr(0,small);
    //cout<<presub<<endl;
    string lexsmallstr=nextsub+presub;

    cout<<"\nMinimum Lexicographic rotation : "<<lexsmallstr<<endl;

    return 0;

}