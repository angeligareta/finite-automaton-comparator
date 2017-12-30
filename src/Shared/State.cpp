#include "State.h"

State::State():
identifier(-1),
initial(0),
final(0), 
set_transition(){}

State::State(const State& state_in):
identifier(state_in.identifier),
initial(state_in.initial),
final(state_in.final), 
set_transition(state_in.set_transition){}
   
State::~State(){
    clear();
}

void State::clear(){
    set_transition.clear();
}

void State::insert_transition(const Symbol& symbol_in,const int num_in){
    
    // Inicializamos duplicate a 0
    bool duplicate=0;
    
    //Vemos a ver si ya hay una transicion para el simbolo
    for(set<Transition>::iterator it=set_transition.begin(); it!=set_transition.end();++it){
        Transition transition_temp= *it;
        if(transition_temp.get_symbol_entry()==symbol_in){ // Si encuentro una transicion con el mismo simbolo, le inserto otro elemento
            duplicate=1;
            transition_temp.add_next_state(num_in);
            swap_transition(*it,transition_temp);
        }
    }
           
    if (duplicate==0){
        Transition transition_temp(symbol_in,num_in);  
        set_transition.insert(transition_temp);    
    }
    
}
   
void State::set_identifier(const int identifier_in){
    identifier=identifier_in;
}
   
void State::set_initial(const bool initial_in){
    initial=initial_in;
}
   
void State::set_final(const bool final_in){
    final = final_in;
}

int State::get_identifier() const{
    return identifier;
}
   
bool State::get_initial() const{
    return initial;
}
   
bool State::get_final() const{
    return final;
}

set<Transition> State::get_set_transition() const{
    return set_transition;
}

set<int> State::get_set_next_state(const Symbol& symbol_in) const{
    set<int> set_int_aux;
    
    for(set<Transition>::iterator it=set_transition.begin(); it!=set_transition.end();++it)
        if((*it).get_symbol_entry()==symbol_in)
            return (*it).get_set_next_state();
            
    return set_int_aux;        
}

int State::get_next_state(const Symbol& symbol_in) const{
    
    for(set<Transition>::iterator it=set_transition.begin(); it!=set_transition.end();++it)
        if((*it).get_symbol_entry()==symbol_in)
            return (*it).get_next_state();    
}

void State::swap_transition(const Transition& transition_1, const Transition& transition_2){
    set_transition.erase(transition_1);
    set_transition.insert(transition_2);    
}

bool State::is_death_state() const{
    
    if(final!=true){
        for(set<Transition>::iterator it=set_transition.begin(); it!=set_transition.end();++it)
            for(set<int>::iterator it2=(*it).get_set_next_state().begin(); it2!=(*it).get_set_next_state().end();++it2)
                if(*it2!=identifier)
                    return false;
        return true;
    }
    else 
        return false;
        
}

ostream& operator<<(ostream &output,const State& state){
    output << state.identifier << " ";
    output << state.final << " ";
    output << state.set_transition.size();
    for(set<Transition>::iterator it=state.set_transition.begin(); it!=state.set_transition.end();++it)
        output << *it;
    output << endl;
    return output;
}

State& State::operator=(const State &state_in){
    this->identifier= state_in.identifier;
    this->initial= state_in.initial;
    this->final=state_in.final;
    this->set_transition = state_in.set_transition;
        
    return *this;
}

int State::operator==(const State &state_in) const{
    if(this->identifier != state_in.identifier) return 0;
    if(this->initial != state_in.initial) return 0;
    if(this->final != state_in.final) return 0;
    if(this->set_transition.size() != state_in.set_transition.size()) return 0;
    
    set<Transition>::iterator iter1=set_transition.begin();
    set<Transition>::iterator iter2=state_in.set_transition.begin();
    while(iter1!=set_transition.end()){
        if(!(*iter1 ==*iter2))
            return 0;
        ++iter1; ++iter2;
    }
    return 1;
}

int State::operator<(const State &state_in) const{
    return (identifier < state_in.identifier);
}