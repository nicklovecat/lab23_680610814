#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string line;
    while(getline(source, line)){
        size_t colonPos = line.find(':');
        if(colonPos == string::npos) continue;
        string name = line.substr(0, colonPos);
        string scorePart = line.substr(colonPos + 1);
        int s1, s2, s3;
        sscanf(scorePart.c_str(), "%d %d %d", &s1, &s2, &s3);
        int totalScore = s1 + s2 + s3;
        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: \n";
    string input;
    getline(cin, input);
    size_t spacePos = input.find(' ');
    if(spacePos != string::npos){
        command = input.substr(0, spacePos);
        key = input.substr(spacePos + 1);
    } else {
        command = input;
        key = "";
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    string upperKey = toUpperStr(key);
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == upperKey){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    string upperKey = toUpperStr(key);
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(grades[i] == upperKey[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command, key);
        string cmdUpper = toUpperStr(command);
        if(cmdUpper == "EXIT") break;
        else if(cmdUpper == "GRADE") searchGrade(names, scores, grades, key);
        else if(cmdUpper == "NAME") searchName(names, scores, grades, key);
        else {
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    } while(true);
    
    return 0;
}