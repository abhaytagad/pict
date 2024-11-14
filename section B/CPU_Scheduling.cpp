#include<iostream>
using namespace std;
#include<bits/stdc++.h>

vector<pair<int,int>> data1;
bool comp(pair<int,int> a , pair<int,int> b ,int time){

    if((a.first <= time && b.first <= time) || (a.first == b.first)){
        return a.second < b.second;
    }
    
    return a.first < b.first;
}
void FCFS(){

    sort(data1.begin(),data1.end());

    vector<vector<int>> result(data1.size());
    int currentTime = 0;

    for(int i = 0; i < data1.size(); i++){
        int arr = data1[i].first;
        int burst = data1[i].second;
        currentTime = max(currentTime,arr);
        result[i].push_back(arr);
        result[i].push_back(burst);
        result[i].push_back(currentTime + burst);
        result[i].push_back(result[i].back() - arr);
        result[i].push_back(result[i].back() - burst);
        currentTime = currentTime + burst;
    }

    for(auto i : result){
        cout<<i[0]<<' '<<i[1]<<' '<<i[2]<<' '<<i[3]<<' '<<i[4]<<'\n';
    }
}

void SJF(){
    int currentTime = 0;
    sort(data1.begin(),data1.end(), [currentTime] (pair<int,int> &a , pair<int,int> & b){
        return comp(a,b,currentTime);
    });

    vector<vector<int>> result(data1.size());
    int i = 0;

    while(!data1.empty()){
        int arr = data1[0].first;
        int burst = data1[0].second;
        currentTime = max(currentTime,arr);
        result[i].push_back(arr);
        result[i].push_back(burst);
        result[i].push_back(currentTime + burst);
        result[i].push_back(result[i].back() - arr);
        result[i].push_back(result[i].back() - burst);
        currentTime = currentTime + burst;
        i++;
        data1.erase(data1.begin());
        sort(data1.begin(),data1.end(), [currentTime] (pair<int,int> &a , pair<int,int> & b){
            return comp(a,b,currentTime);
        });
    }

    for(auto i : result){
        cout<<i[0]<<' '<<i[1]<<' '<<i[2]<<' '<<i[3]<<' '<<i[4]<<'\n';
    }
}

class proccess{

    public:

    int id ;
    int arrival;
    int burst;
    int remaining ;
    
};
 
int main(){ 
 
    int n;
    cout << "entr the number of proceses:";
    cin>>n;
    while(n > 0){
        int a;
        int b;
        cout<<"enter the arrival time and burst time:";
        cin >> a >> b;
        data1.push_back({a,b});
        n--;

    }
    SJF();
} 