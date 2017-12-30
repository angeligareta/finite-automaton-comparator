#include "Nfa.h"

//Leo por pantalla el NFA y si no tiene errores lo abro
istream& operator>>(istream& input,Nfa& nfa_){
    
    nfa_.clear();
    
    int state_count=0;
    
    int state_number; input >> state_number;
    
    int initial_state; input >> initial_state;
    
    int id; bool final; int num_transition;
    
    while(state_count < state_number){
        
        State state_temp;
        
        input >> id;
        
        state_temp.set_identifier(id);
        
        if(id==initial_state)
            state_temp.set_initial(true);
        
        input >> final;
        
        if(final==true)
            state_temp.set_final(true);
        
        input >> num_transition;
        
        string symbol_string; int next_state;
        
        for(int i=0;i<num_transition;i++){
            input >> symbol_string;
            input >> next_state;
            Symbol symbol_(symbol_string);
            nfa_.alphabet_.insert(symbol_);
            state_temp.insert_transition(symbol_,next_state);
        }
        
        nfa_.set_state.insert(state_temp);
        
        state_count++;
    }
    
    return input;
    
}

//Imprimo el nfa
ostream& operator<<(ostream& output,Nfa& nfa_){
    
    output << nfa_.set_state.size() << endl;
    
    output << nfa_.get_initial_state().get_identifier() << endl;
    
    for(set<State>::iterator it=nfa_.set_state.begin(); it!=nfa_.set_state.end();++it)
        output << *it;
        
    return output;    
    
}

//Constructor por defecto
Nfa::Nfa(){}

//Destructor por defecto
Nfa::~Nfa(){
    clear();
}

//Destruyo el vector de estados
void Nfa::clear(){
    set_state.clear();
}

//Devuelvo si se ha creado el Nfa o no
bool Nfa::empty() const{
    return set_state.empty();
}

//Devuelvo el estado con el identificador enviado
State Nfa::get_state_with_id(const int state_id) const{
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).get_identifier()==state_id)
            return (*it);
}

State Nfa::get_initial_state() const{
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).get_initial()==true)
            return (*it);
}

SetState Nfa::get_final_state() const{
    SetState set_state_aux;
    
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).get_final())
            set_state_aux.insert(*it);
            
    return set_state_aux;
}

//Imprimo los estados de muerte
void Nfa::show_death_state() const{
    cout << "\nLos estados de muerte son: " << endl;
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).is_death_state()==true)
            cout << "Estado numero " << (*it).get_identifier() << endl;
}

//Analiza la cadena y llama a analyze_string_rec para formar caminos recursivamente
bool Nfa::analyze_string(const string& string_in) const {
    
    // Si ha introducido una cadena con un simbolo que no pertenezca al alfabeto salgo
    for(int i=0;i<string_in.length();i++){
        Symbol symbol_entry(string_in[i]); 
        if(!(alphabet_.it_belongs(symbol_entry)))
            return 1;
    }
    
    cout << "\nCadena de entrada: " << string_in << endl << endl;
    
    int initial_state=get_initial_state().get_identifier(); //Me coloco en el primer estado
        
    int way_counter=0;
        
    string string_out="";
    //Empiezo a pasar de estado a estado dependiendo de la entrada
    bool accepted= analyze_string_rec(way_counter,initial_state,string_in,0,string_out);
    
    cout << endl << "Decisión final:" << endl;
    
    if(accepted==true)
        cout << endl << "\t\t¡LA CADENA ESTA ACEPTADA!" << endl;
    else
        cout << endl << "\t\tLA CADENA NO ESTA ACEPTADA" << endl;
        
    return 0;
    
}

//Va formando caminos si hay un estado con mas de una transicion para una cadena de entrada y muestra si para ese camino se acepta
bool Nfa::analyze_string_rec(int& way_counter,int number_actual_state, const string& string_in,int counter,string& string_out) const{
    
    //Usamos este bool para la decisión final
    bool total_accepted=0;
    
    // Voy leyendo la cadena y haciendo caminos que guardamos en string
    while(counter < string_in.length() && (number_actual_state!=-1)){
        
        set<int> set_int_aux; set_int_aux.insert(number_actual_state);
        
        //Hacemos epsilon_transition, si podemos llegar a algun sitio nuevo creamos otro camino
        set<int> set_epsilon_transition = epsilon_transition(set_int_aux);
        
        //Por cada epsilon_transition que nos lleve a otro estado hacemos un camino
        for(set<int>::iterator iter=set_epsilon_transition.begin();iter!=set_epsilon_transition.end();++iter){
            string string_temp=string_out;
            string_temp+=to_string(number_actual_state) + "~" + to_string(*iter);
            total_accepted+=analyze_string_rec(way_counter,*iter,string_in,counter,string_temp);
        }
        
        Symbol symbol_entry(string_in[counter]);
        
        //Aqui añadimos el estado y simbolo actual
        string_out+= to_string(number_actual_state) + symbol_entry.get_symbol();
        
        set<int> vector_next_state = get_state_with_id(number_actual_state).get_set_next_state(symbol_entry);
        
        //Si esta vacío es que va a null      
        if(vector_next_state.empty()){
            number_actual_state=-1; string_out+= "-";     
        }
        else{
            int next_counter=1;
            for(set<int>::iterator iter=vector_next_state.begin();iter!=vector_next_state.end();++iter){
                if(next_counter==1)
                    number_actual_state=*iter;
                else{
                    string string_temp= string_out + to_string(*iter);
                    total_accepted+=analyze_string_rec(way_counter,*iter,string_in,counter+1,string_temp);  
                }
                next_counter++; 
            }
            string_out += to_string(number_actual_state);
        }
        counter++;
    }
    
    set<int> set_int_aux; set_int_aux.insert(number_actual_state);
    // Volvemos a hacer epsilon_transition cuando hayamos terminado, si podemos llegar a algun sitio nuevo creamos otro camino
    set<int> set_epsilon_transition = epsilon_transition(set_int_aux);
        
    //Por cada epsilon_transition que nos lleve a otro estado hacemos un camino
    for(set<int>::iterator iter=set_epsilon_transition.begin();iter!=set_epsilon_transition.end();++iter){
        string string_temp=string_out;
        string_temp+=to_string(number_actual_state) + "~" + to_string(*iter);
        total_accepted+=analyze_string_rec(way_counter,*iter,string_in,counter,string_temp);
    }
    
    print_way(way_counter,string_out);
    
    total_accepted+=is_way_accepted(number_actual_state);
    
    return total_accepted;
}

//Devuelve el conjunto al que podemos llegar con epsilon_transition
set<int> Nfa::epsilon_transition(const SetInt& set_number_actual_state) const{
    
    Symbol symbol_epsilon('~');
    
    set<int> set_int_aux, set_int_aux_2=set_number_actual_state;
    
    do{
        set_int_aux=set_int_aux_2;
        
        for(set<int>::iterator it=set_int_aux.begin();it!=set_int_aux.end();++it)
            set_int_aux_2= merge_division(set_int_aux_2, get_state_with_id(*it).get_set_next_state(symbol_epsilon));
            
    }while(set_int_aux!=set_int_aux_2); //Hasta que no haya cambios
    
    return set_int_aux;
}

//Imprimo el camino
void Nfa::print_way(int& way_counter,const string& string_out) const{
    
    cout << endl << "\n\t\t\tCAMINO " << ++way_counter << endl << endl;
    
    cout << "Estado actual\t\t" << "Entrada\t\t" << "Siguiente estado" << endl;
    
    for(int i=0;i<string_out.size();i++){
        cout << string_out[i];
        if((i+1)%3!=0)
            cout << "\t\t\t";
        else
            cout << endl;
    }  
}

void Nfa::print_set_int(const SetInt& set_int_in, const int& i) const{
    
    cout << "Grupo numero " << i+1 << ": { ";
    if(set_int_in.size()>0){
        set<int>::iterator it=set_int_in.begin();
        while(it!=set_int_in.end()){
            cout << *it; ++it;
            if(it!=set_int_in.end())
                cout << " ,";
            else
                cout << " }" << endl;
        }
    }
    else
        cout << " }" << endl;    
}

//Imprimo si esta aceptado o no y lo devuelvo
bool Nfa::is_way_accepted(const int& number_actual_state) const{
    
    bool accepted=0;
    
    // Miro si para el estado que estoy la cadena esta aceptada
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it){
        State state_temp=*it;
        if(state_temp.get_identifier()==number_actual_state) //Veo en que estado me he quedado
            if(state_temp.get_final()) //Si me he quedado en un estado de aceptación devuelvo true
                accepted=true;
    }
    
    if(accepted==true)
        cout << endl << "\t\t¡LA CADENA ESTA ACEPTADA!" << endl;
    else
        cout << endl << "\t\tLA CADENA NO ESTA ACEPTADA" << endl;
    
    return accepted;
        
}

//Convierto el Nfa en dfa
SetState Nfa::convert2DFA(const bool& show){
    
    SetState dfa_set_state;
    
    vector<SetInt> vector_set_int;
    
    //Inserto el estado inicial
    SetInt set_int_aux; set_int_aux.insert(get_initial_state().get_identifier());
    //Hago epsilon transition en el primero y lo inserto en el vector de set de estados
    vector_set_int.push_back(epsilon_transition(set_int_aux));
    
    Symbol symbol_aux('~'); alphabet_.erase(symbol_aux);
    
    for(int i=0;i<vector_set_int.size();++i){
        State state_aux; state_aux.set_identifier(i); if(i==0) state_aux.set_initial(1); 
        
        for(SetInt::iterator it=vector_set_int[i].begin();it!=vector_set_int[i].end();++it)
            if(get_state_with_id(*it).get_final()==1)
                state_aux.set_final(1);  
                
        set<Symbol> alphabet_aux = alphabet_.get_alphabet();
        
        for(set<Symbol>::iterator alphabet_iterator=alphabet_aux.begin(); alphabet_iterator!=alphabet_aux.end();++alphabet_iterator){
            SetInt actual_division=epsilon_transition(get_reachable_state(vector_set_int[i],*alphabet_iterator));
            int position_number=it_belongs_division(actual_division,vector_set_int);
            
            if(position_number==-1){ // Si no está el estado
                vector_set_int.push_back(actual_division); //Lo introduzco
                position_number=it_belongs_division(actual_division,vector_set_int); //Cojo la posicion
                state_aux.insert_transition(*alphabet_iterator,position_number); // Inserto la transicion       
            }
    
            else
                state_aux.insert_transition(*alphabet_iterator,position_number);
        }
        
        dfa_set_state.insert(state_aux); // Insertamos el estado
        
        if(show!=0)
            print_set_int(vector_set_int[i],i);
    }
    
    return dfa_set_state;
    
}

set<int> Nfa::get_reachable_state(const SetInt& set_int_in,const Symbol& symbol_in) const{
    set<int> set_reachable_state;
    
    for(set<int>::iterator it=set_int_in.begin();it!=set_int_in.end();++it)
        set_reachable_state=merge_division(set_reachable_state,get_state_with_id(*it).get_set_next_state(symbol_in));
    
    return set_reachable_state;    
}

set<int> Nfa::merge_division(const SetInt &division_1,const SetInt &division_2) const{
    
    set<int> division;
    
    set_union(division_1.begin(), division_1.end(), division_2.begin(), division_2.end(), inserter(division, division.begin()));
    
    return division;
}

//Devuelve la posicion si la encuentra, si no -1
int Nfa::it_belongs_division(const SetInt &actual_division,const vector<SetInt>& vector_set_division) const{
    
    for(int i=0;i<vector_set_division.size();i++)
        if(vector_set_division[i]==actual_division)
            return i;
            
    return -1;
    
}

//Compruebo si el Nfa es dfa(si para cada simbolo del alfabeto tiene una y solo una transición)
bool Nfa::is_dfa() const{
    //Para cada estado y letra del alfabeto compruebo que solo tenga una transición
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        for(set<Symbol>::iterator it2=alphabet_.get_alphabet().begin();it2!=alphabet_.get_alphabet().end();++it2)
            if((*it).get_set_next_state(*it2).size()!=1)
                return false;
    return true;
}
