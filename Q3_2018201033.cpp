#include<bits/stdc++.h>
#include <time.h>
using namespace std;

//swap two element of array
void swap(long long* a, long long* b)
{
    long long t = *a;
    *a = *b;
    *b = t;
}

//selecting any random pivot element
//partition function move pivot to its correct position and return its index
long long partition (vector<long long> &arr,long long start ,long long end) 
{
    long long randNum = (rand()%(end-start+1)) + start;
    //cout<<"Random : "<<randNum<<endl;
    swap(arr[start],arr[randNum]);
    long long i = start + 1;
    long long piv = arr[start] ;    //make the first element as pivot element.
    for(long long j =start + 1; j <= end ; j++ )  
    {
        if ( arr[ j ] < piv) 
        {
            swap (arr[ i ],arr[ j ]);
            i += 1;
        }
   }
   swap(arr[start],arr[i-1] ) ;  //put the pivot element in its proper place.
   return i-1;                      //return the position of the pivot
}

//find kth samllest element using partion function
long long findNthSmallest(vector<long long> &arr,long long start,long long end,long long k)
{
    long long size1=arr.size();
    if(k>size1)
    {
        return -1;
    }
    long long index;
    while(start<=end)
    {
        index=partition(arr,start,end);
        if(k-1<index)
        {
            end=index-1;
        }
        else if(k-1>index)
        {
            start=index+1;
        }
        else{
            return arr[index];
        }
    }
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    ios_base::sync_with_stdio(false);
    long long n;
    cin>>n;
    long long k;
    cin>>k;
    vector<long long> arr(n);
    for(long long i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    start = clock();
    cout<<"\nMy Nth-Smallest : "<<findNthSmallest(arr,0,n-1,k);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout<<"\nMy time: "<<cpu_time_used;
    vector<long long> arr1(arr.begin(),arr.end());
    start = clock();
    nth_element(arr1.begin(), arr1.begin()+k-1, arr1.end()); 
    end = clock();
    cout<<"\nbuilt in funct Smallest : "<<arr1[k-1];
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout<<"\nbuilt in funct time: "<<cpu_time_used;

    return 0;
}