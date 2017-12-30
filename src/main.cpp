#include "DFA/Dfa.h"
#include "NFA/Nfa.h"

#include <cstdio>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool is_dfa(const string& string_in){
    string string_aux="";
    for(int i=string_in.size()-3;i<string_in.size();i++)
        string_aux+=string_in[i];
    return (string_aux=="dfa");
}

int main(int argc, char *argv[]){
	
    if(argc!=3)
        return 0;
                
    ifstream file_1; file_1.open(argv[1]); 
    ifstream file_2; file_2.open(argv[2]); 
    
    Dfa dfa_1; Dfa dfa_2;
	
	if(is_dfa(argv[1]))
		file_1 >> dfa_1;
	else{
		Nfa nfa_1; file_1 >> nfa_1; 
		dfa_1 = nfa_1.convert2DFA(0);
	}
	
	if(is_dfa(argv[2]))
		file_2 >> dfa_2;
		
	else{
		Nfa nfa_2; file_2 >> nfa_2;
		dfa_2 = nfa_2.convert2DFA(0);
	}
	
	bool EsEquivalente=dfa_1.compareDFAmin(dfa_2);
	
	if(EsEquivalente)
	    cout << "EQUIVALENT" << endl;
	else
	    cout << "NON_EQUIVALENT" << endl;
	
	file_1.close();
	file_2.close();
}