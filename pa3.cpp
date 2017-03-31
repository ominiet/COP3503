#include <fstream>
#include <string>
#include <iostream>
#include "stack.h"
using namespace std;

string delSpaces(string &str){
    
    // Remove all Kinds of Whitespace
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(remove(str.begin(), str.end(), '\v'), str.end());
    str.erase(remove(str.begin(), str.end(), '\f'), str.end());
    str.erase(remove(str.begin(), str.end(), '\r'), str.end());
    return str;
    
}
string nestCheck(string check, string* keyWords, string (&foundKey)[3]){		//used to check for keywords
	stack <int> depth(15);
	int maxStack = 0;
	string key = "";
	int start = 0;
	int finish = 0;
	bool run = true;
	while (run == true){
		for (int i = 0; i < check.length(); i++){
			if (isupper(check.at(i))){
				start = i;
				break;
			}
		}
		for (int j = start; j < check.length(); j++){
			if (!isupper(check.at(j)) || isalpha(check.at(j) == 0)){
				finish = j;
				break;
			}
			else {
				finish = check.length();
			}
		}
		key = check.substr(start,(finish-start));
		string checking = "";
		int x = 0;
		while (x < 3){
			checking = keyWords[x];
			if (key.length() < 6){ 	//only one key word in string
				if (key == checking){
					if (x == 0) {
						depth.pop();
						foundKey[0]= "END";
					}
					else if (x == 1){
						 depth.push(1);
						 foundKey[1] = "FOR"; 
						}
					else if (x == 2) foundKey[2] = "BEGIN";
					else 
					if (depth.getTop()> maxStack) maxStack = depth.getTop();
				}
			}
			else{
				
				for (int y = 0; y < key.length()-checking.length() + 1; y++){
					if (key.substr(y,checking.length()) == checking){
						if (x == 0) {
							
							depth.pop();
							foundKey[0] = "END";
						}
						else if (x == 1) {
							depth.push(1);
							foundKey[1] = "FOR";
						}
						else foundKey[2] = "BEGIN";
						if (depth.getTop()> maxStack) maxStack = depth.getTop();
					}
				}
			}
			x++;
			
		}
		check = check.substr(0,start) + check.substr((finish), (check.length()- start));
		run = false;
		for (int k = 0; k < check.length(); k++){
			if (isupper(check.at(k))){
				run = true;
				break;
			}
		}
		start = 0;
		finish = 0;
	}
	cout<< "The maximum depth of nested loop(s) is " << maxStack + 1 << endl;
	return check;
}
string findIdent(string check, string (&foundIdent) [20]){
	int count =0;
	int run = true;
	int start = 0;
	int finish = 0;
	bool settable = true;
	while (run == true){
		for (int i = 0; i < check.length(); i++){
			if (islower(check.at(i))){
				start = i;
				break;
			}
		}
		for (int j = start; j < check.length(); j++){
			if (!islower(check.at(j)) || isalpha(check.at(j) == 0)){
				finish = j;
				break;
			}
			else {
				finish = check.length();
			}
		}
		string canSet = check.substr(start,(finish-start));
		settable = true;
		for (int z = 0; z<10;z++){
			if (canSet == foundIdent[z]){
				foundIdent[z] = canSet;
				settable = false;
				break;
			}	
			
		}
		if (settable == true){
			foundIdent [count] = canSet;
		}
		
		check = check.substr(0,start) + check.substr((finish), (check.length()- start));
		run = false;
		for (int k = 0; k < check.length(); k++){
			if (islower(check.at(k))){
				run = true;
				break;
			}
		}
		count ++;
		start = 0;
		finish = 0;
	}
	return check;
}
string findRest(string check, char* Delimiters, string* Operators, char (&foundDelim)[2],string (&foundOp)[6]){
	
	for (int x = 0; x < 2; x++){
		
		for (int i = 0; i < check.length(); i++){
			if (check.at(i) == Delimiters[x]){
				foundDelim[x] = check.at(i);
				check.erase(i,1);
			}
		}
	}
	
	for (int i = 0; i < check.length()-1; i++){
		if (check.substr(i,2) == "++"){
			foundOp[5] = "++";
			check.erase(i,2);
		}
	}
	for (int y = 0; y<5;y++){
		for (int i = 0; i < check.length(); i++){
			if (check.substr(i,1) == Operators[y]){
				foundOp[y] = Operators[y];
				check.erase(i,1);
			}
		}
	}
	
	return check;
}
string findConst(string check, string (&foundConst) [20]){
	int count =0;
	int run = true;
	int start = 0;
	int finish = 0;
	bool settable = true;
	while (run == true){
		for (int i = 0; i < check.length(); i++){
			if (isdigit(check.at(i))){
				start = i;
				break;
			}
		}
		for (int j = start; j < check.length(); j++){
			if (!isdigit(check.at(j))){
				finish = j;
				break;
			}
			else {
				finish = check.length();
			}
		}
		string canSet = check.substr(start,(finish-start));
		settable = true;
		for (int z = 0; z<10;z++){
			if (canSet == foundConst[z]){
				foundConst[z] = canSet;
				settable = false;
				break;
			}	
			
		}
		if (settable == true){
			foundConst [count] = canSet;
		}
		
		check = check.substr(0,start) + check.substr((finish), (check.length()- start));
		run = false;
		for (int k = 0; k < check.length(); k++){
			if (isdigit(check.at(k))){
				run = true;
				break;
			}
		}
		count ++;
		start = 0;
		finish = 0;
	}
	return check;
}
int main(){
	string KeyWords [3] = {"END","FOR","BEGIN"};
	char Delimiters[2] = {',',';'};
	string Operators[6] = {"+","-","*","/","=","++"};
	string foundKey [3];
	string foundIdent[20];
	string foundConst[20];
	char foundDelim[2];
	string foundOp[6];
	
	cout << "Please enter the name of the file! ";
	string filename;
	cin>> filename;
	cout << endl; 
	
	string STRING;
	string wholeString = "";
	ifstream infile;
	string token;
	infile.open (filename);
        while(!infile.eof()) // To get you all the lines.
        {
	        getline(infile,STRING); // Saves the line in STRING.
	        STRING = delSpaces(STRING);
	        wholeString = wholeString + STRING;
        }
        wholeString = nestCheck(wholeString,KeyWords, foundKey);
        wholeString = findIdent(wholeString,foundIdent);
        cout << "Keywords: ";
        for (int i = 0; i < 3; i++){
			if (foundKey[i] != ""){
				cout<< foundKey[i] << " ";
			}
		}
		cout << endl;
		cout << "Identifier: ";
		 for (int i = 0; i < 20; i++){
			if (foundIdent[i] != ""){
				cout<< foundIdent[i] << " ";
			}
		}
		cout << endl;
		wholeString = findConst(wholeString, foundConst);
		cout << "Constant: ";
		 for (int i = 0; i < 20; i++){
			if (foundConst[i] != ""){
				cout<< foundConst[i] << " ";
			}
		}
		cout << endl;
		wholeString = findRest(wholeString,Delimiters,Operators,foundDelim,foundOp);
		cout << "Operator: ";
		 for (int i = 0; i < 6; i++){
			if (foundOp[i] != ""){
				cout<< foundOp[i] << " ";
			}
		}
		cout << endl;
		cout << "Delimiter: ";
		 for (int i = 0; i < 2; i++){
			if (foundDelim[i] != (char) 0){
				cout<< foundDelim[i] << " ";
			}
		}
		cout << endl << endl << "Syntax Error(s)";
		
		
		
		
	infile.close();

	return 0;
	}
