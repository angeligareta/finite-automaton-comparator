#include "Transition.h"

Transition::Transition(){
    set_next_state.clear();
}

Transition::Transition(const Symbol &symbol_in,const int num_in):
symbol_entry(symbol_in){
    set_next_state.insert(num_in);
}

Transition::Transition(const Transition &transition_in):
set_next_state(transition_in.set_next_state),
symbol_entry(transition_in.symbol_entry){}
   
Transition::~Transition(){
    set_next_state.clear();
}

void Transition::add_next_state(const int next_state){
    set_next_state.insert(next_state);
}

void Transition::swap_next_state(const int next_state){
    set_next_state.clear();
    set_next_state.insert(next_state);
}
   
void Transition::swap_symbol_entry(const Symbol &symbol_in){
    symbol_entry=symbol_in;    
}

set<int> Transition::get_set_next_state() const{
    return set_next_state;    
}

//Devuelvo solo 1 para el DFA
int Transition::get_next_state() const{
    
    int next_state;
    
    if(!set_next_state.empty()){
        set<int>::iterator next_state_it= set_next_state.begin();
        next_state=*next_state_it;
    }
    
    return next_state;    
}

Symbol Transition::get_symbol_entry() const{
    return symbol_entry;
}

Transition& Transition::operator=(const Transition &transition_in){
    this->symbol_entry= transition_in.symbol_entry;
    this->set_next_state= transition_in.set_next_state;
    return *this;
}

int Transition::operator==(const Transition &transition_in) const{
    if( this->set_next_state  != transition_in.set_next_state) return 0;
    if( !(this->symbol_entry       == transition_in.symbol_entry)) return 0;
    return 1;
}

int Transition::operator<(const Transition &transition_in) const{
    return (symbol_entry < transition_in.symbol_entry);
}

ostream& operator<<(ostream& output,const Transition& transition){
    for(set<int>::iterator iter=transition.set_next_state.begin();iter!=transition.set_next_state.end();++iter)
        output << " " << transition.symbol_entry << " " << *iter;
    return output;
}