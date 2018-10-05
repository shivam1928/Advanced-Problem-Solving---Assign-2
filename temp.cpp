#include<bits/stdc++.h>
using namespace std;
int partitionfunc(vector<int> &arr,int first,int last,int pivot)
{
    int size1=arr.size()-1;
    int i=first;
    int j=last+1;
    cout<<i<<" : "<<j<<endl;
    while(i<j)
    {
        i=i+1;
        while(arr[i]<=pivot)
        {
            if(i==size1)
                break;
            i=i+1;
        }
        j=j-1;
        while(arr[j]>=pivot)
        {
            if(j==0)
                break;
            j=j-1;
        }
        cout<<"swap :"<<i<<":"<<j<<endl;
        if(i<=j)
        {
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }

    int temp=arr[first];
    arr[first]=arr[j];
    arr[j]=temp;
    return first; 
    
}
int main()
{
    int n;
    cin>>n;
    int k;
    cin>>k;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    int index=partitionfunc(arr,0,n-1,arr[0]);
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }

}