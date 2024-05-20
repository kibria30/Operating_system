#include<bits/stdc++.h>
using namespace std;

#define NUMBER_OF_PROCESS 5
#define NUMBER_OF_RESOURCE 3

int work[NUMBER_OF_RESOURCE] = {3, 3, 2};
int maxi[NUMBER_OF_PROCESS][NUMBER_OF_RESOURCE]={{7, 5, 3}, 
                                                {3, 2, 2}, 
                                                {9, 0, 2},
                                                {2, 2, 2},
                                                {4, 3, 3}};

int allocation[NUMBER_OF_PROCESS][NUMBER_OF_RESOURCE]={{0, 1, 0}, 
                                                        {2, 0, 0}, 
                                                        {3, 0, 2},
                                                        {2, 1, 1},
                                                        {0, 0, 2}};

bool isFinished[NUMBER_OF_PROCESS];

int main(){
    int need[NUMBER_OF_PROCESS][NUMBER_OF_RESOURCE];
    vector<int> sequence; 
    

    for(int i=0; i<NUMBER_OF_PROCESS; i++){
        for(int j=0; j<NUMBER_OF_RESOURCE; j++){
            need[i][j] = maxi[i][j] - allocation[i][j];
        }
    }

    int newCount=0, oldCount=0;
    int maxloop = NUMBER_OF_PROCESS;
    while(maxloop--){
        for(int i=0; i<NUMBER_OF_PROCESS; i++){
            bool found = true;
            for(int j=0; j<NUMBER_OF_RESOURCE; j++){
                
                if(need[i][j]<=work[j] && !isFinished[i]){
                    found = found && true;
                }
                else{
                    found = found && false;
                }
            }
            if(found){
                isFinished[i] = true;
                sequence.push_back(i);
                for(int j=0; j<NUMBER_OF_RESOURCE; j++){
                    work[j] += allocation[i][j];
                    // cout<<work[j]<<" ";
                }
                // cout<<endl;
                newCount++;
            }

        }
        if(newCount==oldCount){
            if(newCount<NUMBER_OF_PROCESS)  
                cout<<"Deadlock will be happened"<<endl;
            break;
        }
        else{
            oldCount = newCount;
        }
    }

    cout<<"The sequence will be: ";
    for(auto i: sequence){
        cout<<"P"<<i<<"->";
    }
    cout<<endl;
    return 0;
}
