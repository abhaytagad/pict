#include<iostream>
using namespace std;
#include<bits/stdc++.h>

map<string,pair<int,int>> MNT;
map<int,string> MDT;
map<string,int> ALA;
map<string,string> KPTAB;
int MDTCounter = 0;
int ALACounter = 0;

void pass1(){

    ifstream file1("input.txt");
    string line;
    int count = 0;

    while(getline(file1,line)){
        string word;
        vector<string> words;
        istringstream iss(line);
        string result = "";
        while(iss >> word){
            words.push_back(word);
        }

        if(words[0] == "MACRO"){
            count++;
           getline(file1,line);
           istringstream iss1(line);
           words.clear();
            while(iss1 >> word){
                words.push_back(word);
            }
           
            MNT[words[0]] = {MDTCounter,ALACounter};

            for(int i =1 ; i < words.size(); i++){
                auto pos = words[i].find('=');

                if(pos != string::npos){
                    string temp1 = "";
                    temp1 = words[i].substr(0,pos );
                    string temp2  = "";
                    temp2 = words[i].substr(pos+1,words[i].length() - pos-1);
                    ALA[temp1] = ALACounter ;
                    KPTAB[temp1] = temp2;
                }
                else{
                    ALA[words[i]] = ALACounter ;
                }

                ALACounter++;
            }

        }
        else if(words[0] == "MEND"){
            result += "MEND";
            count --;
        }
        else if(count > 0 ){
            
            for(auto i : words){
                if(i[0] != '&'){
                    result +=  " " +i;
                }
                else{
                    result += " #" + to_string(ALA[i]);
                }
            }
        }
        if(result != ""){
            MDT[MDTCounter] = result;
            MDTCounter++; 
        }
       
    }
}
 
int main(){ 
 
    pass1();
   
    ofstream file1("KPTAB.txt");

    for(auto i : KPTAB){
        file1<<i.first<<' '<<i.second<<endl;
    }

    ofstream file2("ALA.txt");

    for(auto i : ALA){
        file2<<i.first<<' '<<i.second<<endl;
    }

    ofstream file3("MDT.txt");

    for(auto i : MDT){
        file3<<i.first<<' '<<i.second<<endl;
    }

    ofstream file4("MNT.txt");

    for(auto i : MNT){
        file4<<i.first<<' '<<i.second.first <<' '<<i.second.second<<endl;
    }
    

 
} 