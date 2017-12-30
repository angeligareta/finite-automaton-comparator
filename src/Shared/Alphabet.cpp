#include "Alphabet.h"

Alphabet::Alphabet(){
}

Alphabet::~Alphabet(){
    clear();
}

void Alphabet::insert(Symbol character){
    alphabet_.insert(character);
}

void Alphabet::clear(){
    alphabet_.clear();
}

set<Symbol> Alphabet::get_alphabet() const{
    return alphabet_;
}

int Alphabet::size() const{
    return alphabet_.size();
}

bool Alphabet::it_belongs(const Symbol& symbol_in) const{
    
    for(set<Symbol>::iterator it=alphabet_.begin();it!=alphabet_.end();++it){
        Symbol symbol_temp=*it;
        if(symbol_temp==symbol_in)
            return true;
    }
    
    return false;
}

void Alphabet::erase(const Symbol& symbol_in){
    alphabet_.erase(symbol_in);    
}

ostream &operator<<(ostream &output,const Alphabet &alphabet_){
    output << endl << "Su alfabeto es: { ";
    set<Symbol>::iterator it=alphabet_.alphabet_.begin();
    while(it!=alphabet_.alphabet_.end()){
        output << *it;
        ++it;
        if(it!=alphabet_.alphabet_.end())
            output << " , ";
        else
            output << " }" << endl;
    }    
}

