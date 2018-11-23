#include<bits/stdc++.h>
using namespace std;


int main(){
    FILE* in = fopen("input.txt", "w");
    srand(time(NULL));
    //fprintf(in, "%d\n", 50000000 );
    //fprintf(in, "%d\n", 9878 );
    for (long long i = 0; i < 50000 ; i++)
    {
        fprintf(in, "1 %d %d\n", rand(),rand() );
    }
    
    // for (long long i = 0; i < 1000 ; i++)
    // 	fprintf(in, "%d\n", 1 + (rand()) % (100000) ); 
    fclose(in);
    return 0;
}