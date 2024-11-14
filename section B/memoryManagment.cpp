#include<iostream>
using namespace std;
#include<bits/stdc++.h>
class block{

public:
    int blockId;
    int maxSize;
    int currentSize;
    block(int id,int maxSize){
        this->maxSize = maxSize;
        this->blockId = id;
        this->currentSize = maxSize;
    }
};

class proccess{

public:
    int maxSize;
    int id ;
    int alocatedBlockId ;
    proccess(int maxSize, int id){
        this->maxSize = maxSize;
        this->id = id;
        alocatedBlockId = -1;
    }
    void alocate(int id){
        this->alocatedBlockId = id;
    }
};


void firstFit(vector<block*> blocks,vector<proccess*> processes){

    for(auto i : processes ){
        for(auto j : blocks){
            if(i->maxSize <= j->currentSize){
                i->alocate(j->blockId);
                j->currentSize -= i->maxSize;
                break;
            }
        }
    }
    for(auto i : processes){
        if(i->alocatedBlockId != -1){
            cout<<i->id <<"  "<<i->maxSize<<"   "<<i->alocatedBlockId<<'\n';
        }
        else{
            cout<<i->id <<"  "<<i->maxSize<<"   Space not Alocated"<<'\n';
        }
    }
}

void nextFit(vector<block*> blocks,vector<proccess*> processes){
    int j = 0;
    for(auto i : processes ){
        bool flag = false;
        for( ; j < blocks.size(); j++){
            if(i->maxSize <= blocks[j]->currentSize){
                i->alocate(blocks[j]->blockId);
                blocks[j]->currentSize -= i->maxSize;
                flag = true;
                break;
            }
        }
        if(!flag){
            j = 0;
            for(   ; j < blocks.size(); j++){
                if(i->maxSize <= blocks[j]->currentSize){
                    i->alocate(blocks[j]->blockId);
                    blocks[j]->currentSize -= i->maxSize;
                    flag = true;
                    break;
                }
            }
        }
    }
    for(auto i : processes){
        if(i->alocatedBlockId != -1){
            cout<<i->id <<"  "<<i->maxSize<<"   "<<i->alocatedBlockId<<'\n';
        }
        else{
            cout<<i->id <<"  "<<i->maxSize<<"   Space not Alocated"<<'\n';
        }
    }
}

void bestFit(vector<block*> blocks,vector<proccess*> processes){
    
    for(auto i : processes ){
        block * temp = NULL;
        for( int j = 0; j < blocks.size(); j++){
            if(i->maxSize <= blocks[j]->currentSize && temp != NULL  && temp->currentSize >= blocks[j]->currentSize){
                temp = blocks[j];
            }
        }
        if(temp){
            i->alocate(temp->blockId);
            temp->currentSize -= i->maxSize;
        }
    }
    for(auto i : processes){
        if(i->alocatedBlockId != -1){
            cout<<i->id <<"  "<<i->maxSize<<"   "<<i->alocatedBlockId<<'\n';
        }
        else{
            cout<<i->id <<"  "<<i->maxSize<<"   Space not Alocated"<<'\n';
        }
    }
}

void worstFit(vector<block*> blocks,vector<proccess*> processes){
    
    for(auto i : processes ){
        block * temp = NULL;
        for( int j = 0; j < blocks.size(); j++){
            if(i->maxSize <= blocks[j]->currentSize && temp != NULL  && temp->currentSize <= blocks[j]->currentSize){
                temp = blocks[j];
            }
        }
        if(temp){
            i->alocate(temp->blockId);
            temp->currentSize -= i->maxSize;
        }
    }
    for(auto i : processes){
        if(i->alocatedBlockId != -1){
            cout<<i->id <<"  "<<i->maxSize<<"   "<<i->alocatedBlockId<<'\n';
        }
        else{
            cout<<i->id <<"  "<<i->maxSize<<"   Space not Alocated"<<'\n';
        }
    }
}



 
int main(){ 
 
    vector<block*> blocks;

    int n;
    cout<<"enter the number of blocks:";
    cin>> n;
    while(n >0){
        int n1,n2;
        cout<<"Enter the block number and Size of Block :";
        cin>>n1>>n2;
        block  *B = new block(n1,n2);
        blocks.push_back(B);
        n--;
    }

    vector<proccess*> processes;
    cout<<"Enter the number of proccess:";
    cin>>n;
    while(n > 0){
        int n1,n2;
        cout<<"Enter the proccess number and Size of proccess :";
        cin>>n1>>n2;
        proccess  *B = new proccess(n2,n1);
        processes.push_back(B);
        n--;
    }
    firstFit(blocks,processes);
} 