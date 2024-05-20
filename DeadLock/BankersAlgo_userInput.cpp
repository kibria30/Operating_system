#include<bits/stdc++.h>
using namespace std;

#define MAX 1000

int work[MAX];
int maxi[MAX][MAX];
int allocation[MAX][MAX];
int need[MAX][MAX];
bool isFinished[MAX];
int total_process, total_resource;
vector<int> sequence;

void getInput(){
    freopen("BankerInput.txt", "r", stdin);
    cin>>total_process>>total_resource;

    for(int i=0; i<total_resource; i++){
        cin>>work[i];
    }

    for(int i=0; i<total_process; i++){
        for(int j=0; j<total_resource; j++){
            cin>>maxi[i][j];
        }
    }

    for(int i=0; i<total_process; i++){
        for(int j=0; j<total_resource; j++){
            cin>>allocation[i][j];
        }
    }

    for(int i=0; i<total_process; i++){
        for(int j=0; j<total_resource; j++){
            need[i][j] = maxi[i][j] - allocation[i][j];
        }
    }
}

void printInput(){

    cout<<"Available resource: ";
    for(int i=0; i<total_resource; i++){
        cout<<work[i]<<" ";
    }
    cout<<endl;

    cout<<"Max need:"<<endl;
    for(int i=0; i<total_process; i++){
        for(int j=0; j<total_resource; j++){
            cout<<maxi[i][j] <<" ";
        }
        cout<<endl;
    }

    cout<<endl<<"Allocated: "<<endl;
    for(int i=0; i<total_process; i++){
        for(int j=0; j<total_resource; j++){
            cout<<allocation[i][j] <<" ";
        }
        cout<<endl;
    }

    cout<<endl<<"Need: "<<endl;
    for(int i=0; i<total_process; i++){
        for(int j=0; j<total_resource; j++){
            cout<<need[i][j] <<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    
    getInput();
    printInput();

    int newCount=0, oldCount=0;
    int maxloop = total_process;

    while(maxloop--){
        for(int i=0; i<total_process; i++){
            bool found = true;
            for(int j=0; j<total_resource; j++){
                
                if(need[i][j]<=work[j] && !isFinished[i]){
                    found = found && true;
                }
                else{
                    found = found && false;
                }
            }
            if(found){
                // cout<<i<<endl;
                isFinished[i] = true;
                sequence.push_back(i);
                for(int j=0; j<total_resource; j++){
                    work[j] += allocation[i][j];
                    // cout<<work[j]<<" ";
                }
                // cout<<endl;
                newCount++;
            }

        }
        if(newCount==oldCount){
            if(newCount<total_process)  
                cout<<"Deadlock will be happened"<<endl;
            break;
        }
        else{
            oldCount = newCount;
        }
    }

    cout<<"The sequence is: ";
    for(auto i: sequence){
        cout<<"P"<<i<<"->";
    }
    cout<<endl;
    return 0;
}
