#include<iostream>
using namespace std;
#include<bits/stdc++.h>


map<string, pair<string, string>> opcode = {
   
    {"START", {"AD", "01"}},
    {"END", {"AD", "02"}},
    {"STOP", {"IS", "00"}},
    {"LTORG", {"AD", "03"}},
    {"ORIGIN", {"AD", "04"}},

    // Input/Output Operations
    {"READ", {"IS", "05"}},
    {"PRINT", {"IS", "06"}},

    // Data Transfer Instructions
    {"MOVER", {"IS", "07"}},
    {"MOVEM", {"IS", "08"}},
    {"MOVEL", {"IS", "09"}},

    // Arithmetic Instructions
    {"ADD", {"IS", "10"}},
    {"SUB", {"IS", "11"}},
    {"MULT", {"IS", "12"}},
    {"DIV", {"IS", "13"}},

    // Comparison and Branching
    {"COMP", {"IS", "14"}},
    {"BC", {"IS", "15"}}, // Branch Control (BC with condition codes like LE)

    // Declarative Statements
    {"DS", {"DL", "16"}},
    {"DC", {"DL", "17"}},
    {"EQU", {"AD", "19"}},
};

map<string,string> registers = {
    {"BREG","17"},
    {"AREG","18"},
    {"CREG","19"},
};

map<string,string> symbolTAB;
map<string,string> literalTAB;
map<string,string> poolTAB;
int LC = 0;
void pass1(){

    ifstream file1("input.txt");
    ofstream file2("output.txt");
    string line;
    while(getline(file1,line)){

        vector<string> words;
        string word;
        istringstream iss(line);
        while (iss >> word)
        {
            words.push_back(word);
        }
        string result ;
        if(words[0] == "STOP"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
        }
        else if(words[0] == "START"){
            if(words.size() == 2){
                LC = stoi(words[1]);
            }
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
        }
        else if(words[0] == "END"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
        }
        else if(words[0] == "READ"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
            
        }
        else if(words[0] == "PRINT"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
        }
        else if(words[0] == "ORIGIN"){
            string str = "";
            string temp = "";
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
            int i = 0;
            for(; i < words[1].length();i++ ){
                if(words[1][i] == '+'){
                    break;
                }
                str += words[1][i];
            }
            for(; i < words[1].length();i++ ){
                
                temp += words[1][i];
            }
            if(temp== ""){
                LC = (stoi(str));
            }
            else{
                LC = (stoi(symbolTAB[str]) + stoi(temp));
            }

        }
        else if(words[0] == "LTORG"){
            int count = poolTAB.size();
            for(auto i = literalTAB.begin(); i != literalTAB.end(); i++ ){
                result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+") (DL,16) (c," + i->first.substr(1,i->first.length()-1)+")";
                poolTAB["#" + to_string(count)] = to_string(LC);
                LC++;
                count++;
                file2<<result<<endl;
                cout<<line <<"                  -->   "<<result<<endl;
                result = "";
            }
            literalTAB.clear();
        }
        else{
            if(opcode.find(words[0]) != opcode.end()){
                result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
                if(registers.find(words[1]) != registers.end()){
                    result += +" ("+registers[words[1]] +")";
                }
                else{
                    if(words[1][0] == '='){
                        literalTAB[words[1]] = to_string(LC);
                    }
                    
                }
                if(words.size() >= 3){
                        if(registers.find(words[2]) != registers.end()){
                            result += +" ("+registers[words[2]] +")";
                        }
                        else{
                            if(words[2][0] == '='){
                                literalTAB[words[2]] = to_string(LC);
                            }
                           
                        }
                    }
            }
            
            else{
                if(words[1] == "DC" || words[1] == "DS"){
                    result += to_string(LC)+" ("+ opcode[words[1]].first+","+opcode[words[1]].second+") (c," + words[2]+ ")";
                    symbolTAB[words[0]] = to_string(LC);
                }
                else{
                   
                    result += to_string(LC)+" ("+ opcode[words[1]].first+","+opcode[words[1]].second+")";
                    symbolTAB[words[0]] = to_string(LC);
                    if(words.size() >= 3){
                        if(registers.find(words[2]) != registers.end()){
                            result += +" ("+registers[words[2]] +")";
                        }
                        else{
                            if(words[2][0] == '='){
                                literalTAB[words[2]] = to_string(LC);
                            }
                            
                        }
                    }
                    if(words.size() >= 4){
                        if(registers.find(words[3]) != registers.end()){
                            result += +" ("+registers[words[3]] +")";
                        }
                        else{
                            
                            if(words[3][0] == '='){
                                
                                literalTAB[words[3]] = to_string(LC);
                            }
                        }
                    }
                }
            }
        }  
        
        
        if(result != ""){
            LC++;
            file2<<result<<endl;
            cout<<line <<"                  -->  "<<result<<endl;
        }
    }
}


void pass2(){
    LC = 0;
    literalTAB.clear();
    ifstream file1("input.txt");
    ofstream file2("finalOutput.txt");
    string line;
    while(getline(file1,line)){

        vector<string> words;
        string word;
        istringstream iss(line);
        while (iss >> word)
        {
            words.push_back(word);
        }
        string result ;
        if(words[0] == "STOP"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
        }
        else if(words[0] == "START"){
            if(words.size() == 2){
                LC = stoi(words[1]);
            }
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
        }
        else if(words[0] == "END"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
        }
        else if(words[0] == "READ"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+") " + symbolTAB[words[1]];
            
        }
        else if(words[0] == "PRINT"){
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+") " + symbolTAB[words[1]];
        }
        else if(words[0] == "ORIGIN"){
            string str = "";
            string temp = "";
            result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
            int i = 0;
            for(; i < words[1].length();i++ ){
                if(words[1][i] == '+'){
                    break;
                }
                str += words[1][i];
            }
            for(; i < words[1].length();i++ ){
                
                temp += words[1][i];
            }
            if(temp== ""){
                LC = (stoi(str));
            }
            else{
                LC = (stoi(symbolTAB[str]) + stoi(temp));
            }

        }
        else if(words[0] == "LTORG"){
            int count = poolTAB.size();
            for(auto i = literalTAB.begin(); i != literalTAB.end(); i++ ){
                result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+") (DL,16) (c," + i->first.substr(1,i->first.length()-1)+")";
                poolTAB["#" + to_string(count)] = to_string(LC);
                LC++;
                count++;
                file2<<result<<endl;
                cout<<line <<"                  -->  "<<result<<endl;
                result = "";
            }
            literalTAB.clear();
        }
        else{
            if(opcode.find(words[0]) != opcode.end()){
                result += to_string(LC)+" ("+ opcode[words[0]].first+","+opcode[words[0]].second+")";
                if(registers.find(words[1]) != registers.end()){
                    result += +" ("+registers[words[1]] +")";
                }
                else{
                    if(words[1][0] == '='){
                        literalTAB[words[1]] = to_string(LC);
                    }
                    else{
                        result += " "+ symbolTAB[words[1]];
                    }
                }
                if(words.size() >= 3){
                        if(registers.find(words[2]) != registers.end()){
                            result += +" ("+registers[words[2]] +")";
                        }
                        else{
                            if(words[2][0] == '='){
                                literalTAB[words[2]] = to_string(LC);
                            }
                            else{
                                result += " "+ symbolTAB[words[2]];
                            }
                        }
                    }
            }
            
            else{
                if(words[1] == "DC" || words[1] == "DS"){
                    result += to_string(LC)+" ("+ opcode[words[1]].first+","+opcode[words[1]].second+") (c," + words[2]+ ")";
                }
                else{
                   
                    result += to_string(LC)+" ("+ opcode[words[1]].first+","+opcode[words[1]].second+")";
                    if(words.size() >= 3){
                        if(registers.find(words[2]) != registers.end()){
                            result += +" ("+registers[words[2]] +")";
                        }
                        else{
                            if(words[2][0] == '='){
                                literalTAB[words[2]] = to_string(LC);
                            }
                            else{
                                result += " "+ symbolTAB[words[2]];
                            }
                        }
                    }
                    if(words.size() >= 4){
                        if(registers.find(words[3]) != registers.end()){
                            result += +" ("+registers[words[3]] +")";
                        }
                        else{
                            if(words[3][0] == '='){
                                literalTAB[words[3]] = to_string(LC);
                            }
                            else{
                                result += " "+ symbolTAB[words[3]];
                            }
                            
                        }
                    }
                }
            }
        }  
        
        
        if(result != ""){
            LC++;
            file2<<result<<endl;
            cout<<line <<"                  -->  "<<result<<endl;
        }
    }
}


int main(){ 
 
    pass1();
    ofstream file1("poolTAB.txt");
    for(auto i : poolTAB){
        file1<< i.first<<" "<<i.second<<endl;
    }

    ofstream file2("sybolTAB.txt");
    for(auto i : symbolTAB){
        file2<< i.first<<" "<<i.second<<endl;
    }
    cout<<'\n';
    cout<<'\n';
    cout<<'\n';
    cout<<'\n';
    pass2();
 
} 