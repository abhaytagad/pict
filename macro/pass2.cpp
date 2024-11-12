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

map<int , string> values;
void pass2(){

    ifstream file1("input.txt");
    ofstream file2("output.txt");
    string line;
    string prev = "";
    while(getline(file1,line)){
        string word;
        vector<string> words;
        istringstream iss(line);
        while(iss>> word){
            words.push_back(word);
        }

        if(MNT.find(words[0]) != MNT.end() && prev != "MACRO"){
            
            
            for(int i = 1; i <  words.size(); i++){
                values[i-1] = words[i];
            }
            int ALAidx = MNT[words[0]].second;
            int MDTidx = MNT[words[0]].first;
            while(true){
                string result = "";
                string i = MDT[MDTidx];
                istringstream iss1(i);
                while(iss1 >> word ){

                    if(word == "MEND"){
                        break;
                    }
                    if(word[0] == '#'){
                        
                        int val =  stoi(word.substr(1,word.length()-1)) - ALAidx;
                        if(values.find(val) != values.end()){
                            result += values[val] + " "  ;
                        }
                        else{
                            for(auto k : ALA){
                                if(k.second == stoi(word.substr(1,word.length()-1))){
                                    result += KPTAB[k.first] + " ";
                                }
                            }
                        }
                    }
                    else{
                        result +=   word+" ";
                    }
                }
                if(word == "MEND"){
                    break;
                }
                file2 << result<<endl;
                MDTidx++;
                for(auto j : MNT){
                    if(j.second.first == MDTidx ){
                        while(MDT[MDTidx] != "MEND"){
                            MDTidx++;
                        }
                        MDTidx++;
                        break;
                    }
                }
            }
        }
        else{
            prev = words[0];
            file2 << line<<endl;
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
    
    pass2();
} 