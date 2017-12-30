#include "Dfa.h"

ostream& operator<<(ostream &output, const Dfa &dfa_){
    
    if(!dfa_.empty()){

    output << dfa_.set_state.size() << endl;
    
    output << dfa_.get_initial_state().get_identifier() << endl;
    
    for(set<State>::iterator it=dfa_.set_state.begin(); it!=dfa_.set_state.end();++it)
        output << *it;
    }
    
    return output;
}

istream& operator>>(istream& input,Dfa& dfa_){
    
    dfa_.clear();
    
    bool error=0;
    
    int state_number; input >> state_number;
    
    set<int> set_state_number; // Creo un set de int para introducir todos los estados posibles a los que podemos ir
    for(int i=0;i<state_number;i++)
        set_state_number.insert(i);
        
    int initial_state; input >> initial_state;
    
    int state_count=0,id,transition_number,max_transition_number; bool final;
    
    while(state_count < state_number){
        
        State state_temp;
        
        input >> id;
        
        state_temp.set_identifier(id);
        
        if(id==initial_state) state_temp.set_initial(true);
        
        input >> final;
        
        if(final==true) state_temp.set_final(true);
        
        input >> transition_number;
        
        if(state_count==0) max_transition_number=transition_number;
        else if(transition_number!=max_transition_number) error=1; // Salgo si hay distinto numero de transiciones entre estados
        
        string symbol_string; int next_state;
        
        for(int i=0;i<transition_number;i++){
            input >> symbol_string; input >> next_state;
            
            Symbol symbol_(symbol_string);
            if(state_count==0)
                dfa_.alphabet_.insert(symbol_);
            else if(!dfa_.alphabet_.it_belongs(symbol_)) // Salgo si el simbolo no pertenece al alfabeto
                error=1;
            state_temp.insert_transition(symbol_,next_state);
        }
        
        dfa_.set_state.insert(state_temp);
        
        state_count++;
    }
    
    if(!input.eof()) error=1;   // Salgo si todavia queda cadena de entrada
    
    if(error==1)
        dfa_.clear();
    
    return input;
    
}

Dfa::Dfa(){}

Dfa::Dfa(const SetState& set_state_in):
set_state(set_state_in){update_alphabet();}

Dfa::~Dfa(){
    clear();
}

bool Dfa::empty() const{
    return set_state.empty();
}

void Dfa::clear(){
    set_state.clear();
    alphabet_.clear();
}
   
void Dfa::show_death_state() const{
    
    cout << "\nLos estados de muerte son: " << endl;
    
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).is_death_state()==true)
            cout << "Estado numero " << (*it).get_identifier() << endl;
}

void Dfa::swap_state(const State& state_1,const State& state_2){
    set_state.erase(state_1);
    set_state.insert(state_2);    
}

void Dfa::update_alphabet(){
    SetState::iterator state_aux=set_state.begin();
    for(set<Transition>::iterator it=(*state_aux).set_transition.begin();it!=(*state_aux).set_transition.end();++it){
        Symbol symbol_=(*it).get_symbol_entry();
        alphabet_.insert(symbol_);
    }
}

State Dfa::get_state_with_id(const int state_id) const{
    
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).get_identifier()==state_id)
            return (*it);
}

State Dfa::get_initial_state() const{
    
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).get_initial()==true)
            return (*it);
            
}

SetState Dfa::get_final_state() const{
    SetState division_;
    
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it)
        if((*it).get_final())
            division_.insert(*it);
            
    return division_;
}

Alphabet Dfa::get_alphabet() const{
    return alphabet_;
}

bool Dfa::analyze_string(const string& string_in) const{
    
    // Si ha introducido una cadena con un simbolo que no pertenezca al alfabeto salgo
    for(int i=0;i<string_in.length();i++){
        Symbol symbol_entry(string_in[i]); 
        if(!(alphabet_.it_belongs(symbol_entry)))
            return 1;
    }
    
    cout << "\nCadena de entrada: " << string_in << endl << endl;
    
    cout << "Estado actual\t\t" << "Entrada\t\t" << "Siguiente estado" << endl;
    
    // Me coloco en el estado actual
    
    int number_actual_state=get_initial_state().get_identifier();
    
    //Empiezo a pasar de estado a estado dependiendo de la entrada
    for(int i=0;i<string_in.length();i++){
        cout << number_actual_state << "\t\t\t";
    
        Symbol symbol_entry(string_in[i]);
        cout << symbol_entry << "\t\t\t";
        
        //Saltamos al siguiente estado
        number_actual_state=get_state_with_id(number_actual_state).get_next_state(symbol_entry);
        
        cout << number_actual_state << endl;
    }
    
    if(get_state_with_id(number_actual_state).get_final())
        cout << endl << "¡LA CADENA ESTA ACEPTADA!" << endl;
    else
        cout << endl << "LA CADENA NO ESTA ACEPTADA" << endl;

    return 0;
}

void Dfa::print_set_state(const SetState& vector_state_in) const{
    
    set<State>::iterator it=vector_state_in.begin();
    
    cout << " { ";
    while(it!=vector_state_in.end()){
        cout << (*it).get_identifier();
        ++it;
        if(it!=vector_state_in.end())
            cout << " , ";
        else
            cout << " } ";
    }
}

void Dfa::print_set_division(const vector<SetState> &vector_division) const{
    
    //Imprimimos el vector_division actual
    cout << "{ ";
    for(int i=0; i<vector_division.size();i++){
        print_set_state(vector_division[i]);
        cout << " ";
    }
    cout << "}\n" << endl;
}

vector<SetState> Dfa::merge_vector_division(const vector<SetState> &vector_division_1,const vector<SetState> &vector_division_2) const{
    
    vector<SetState> vector_division;
    
    set_union(vector_division_1.begin(), vector_division_1.end(), vector_division_2.begin(), vector_division_2.end(), inserter(vector_division, vector_division.begin()));
    
    return vector_division;
}

bool Dfa::it_belongs_division(const SetState &actual_division,const int &actual_state) const{
    
    for(SetState::iterator it=actual_division.begin();it!=actual_division.end();++it)
        if(actual_state==(*it).get_identifier())
            return 1;
    return 0;
    
}

// Cambiamos el identificador viejo por el nuevo
void Dfa::change_value_set_state(const int old_value,const int new_value){
    
    set<State> initial_set_state=set_state;
    
    for(set<State>::iterator it=initial_set_state.begin(); it!=initial_set_state.end();++it){
        State state_aux=*it;
        // Cambiamos el identificador viejo por el nuevo
        if((*it).get_identifier()==old_value)
            state_aux.set_identifier(new_value);
        // Para todos los estados y transiciones cambiamos donde aparezca old_value a new_value    
        for(set<Transition>::iterator it2=(*it).set_transition.begin();it2!=(*it).set_transition.end();++it2){
            Transition transition_aux=*it2;
            if(transition_aux.get_next_state()==old_value)
                transition_aux.swap_next_state(new_value);
            state_aux.swap_transition(*it2,transition_aux);
        }
        swap_state(get_state_with_id((*it).get_identifier()),state_aux);
    }
}

//Método de la burbuja
void Dfa::swap_value_set_state(const int value_1,const int value_2){
    
    const int temp_int = set_state.size()+1;
    
    change_value_set_state(value_2,temp_int);
    change_value_set_state(value_1,value_2);
    change_value_set_state(temp_int,value_1);
}

void Dfa::update(const vector<SetState> &vector_division){
    
    //Eliminamos los repetidos y las transiciones que los tengan las cambiamos a correctas
    for(int i=0;i<vector_division.size();i++){
        if(vector_division[i].size()>1){
            SetState::iterator it=vector_division[i].begin(); ++it;
            int correct_state=(*it).get_identifier();
            while(it!=vector_division[i].end()){
                int wrong_value=(*it).get_identifier();
                change_value_set_state(wrong_value,correct_state);
                ++it;        
            }
        }
    }
    
    int identifier=0;
    
    // Ordenamos los vectores de 0 a n-1
    for(set<State>::iterator it=set_state.begin(); it!=set_state.end();++it){
        if(identifier!=(*it).get_identifier())
            change_value_set_state((*it).get_identifier(),identifier);    
        ++identifier;
    }
    
}

void Dfa::custom_sort(){

    // Intercambiamos el identificador de inicial y 0
    if(get_initial_state().get_identifier()!=0)
        swap_value_set_state(get_initial_state().get_identifier(),0); 
    
    set<int> set_next_identifier;
    
    for(int i=1;i<set_state.size();++i)
        set_next_identifier.insert(i);
    
    // Los ordenamos empezando por el inicial y ordenando las transiciones
    for(set<State>::iterator state_iterator=set_state.begin(); state_iterator!=set_state.end();++state_iterator){
        
        set<Symbol> alphabet_aux = alphabet_.get_alphabet();
        
        if(!set_next_identifier.empty()){
            
            for(set<Symbol>::iterator alphabet_iterator=alphabet_aux.begin();alphabet_iterator!=alphabet_aux.end();++alphabet_iterator){
                
                int actual_identifier= (*state_iterator).get_next_state(*alphabet_iterator);
                set<int>::iterator correct_identifier=set_next_identifier.begin();
                
                if(set_next_identifier.count(actual_identifier)!=0 && !set_next_identifier.empty()){ 
                    swap_value_set_state(actual_identifier,*correct_identifier);
                    set_next_identifier.erase(actual_identifier);
                }
                
            }
        }
    }
}

void Dfa::minimize(const bool show){
    
    vector<SetState> vector_division;
    
    bool no_final_state=0;
    //Introducimos los estados finales
    vector_division.push_back(get_final_state());
    if(vector_division[0].empty()) no_final_state=1;
    
    //Introducimos el resto de estados
    SetState division_aux;
    set_difference(set_state.begin(), set_state.end(), vector_division[0].begin(), vector_division[0].end(), inserter(division_aux, division_aux.begin()));
    vector_division.push_back(division_aux);
    
    //Cambiamos de orden los dos
    swap(vector_division[0],vector_division[1]); if(no_final_state) vector_division.pop_back();
    
    if(show!=0){ 
        cout << "Grupo Inicial\n" << endl; 
        print_set_division(vector_division);
    }
    
    vector<SetState> vector_division_old;
    
    do{
        vector_division_old = vector_division;
        vector_division = create_new_partition(vector_division_old,show);
    }while(vector_division!=vector_division_old);
    
    if(show!=0) 
        cout << "FIN\n" << endl;
        
    update(vector_division);
    custom_sort();
    
}

vector<SetState> Dfa::create_new_partition(const vector<SetState> &vector_division_old,const bool show) const{
    
    vector<SetState> vector_division=vector_division_old;
    
    set<Symbol> alphabet_aux = alphabet_.get_alphabet();
    
    for(set<Symbol>::iterator it=alphabet_aux.begin();it!=alphabet_aux.end();++it){
        vector<SetState> vector_division_aux;
        
        for(int i=0; i<vector_division.size();i++){
            if(vector_division[i].size()>1)
                vector_division_aux=merge_vector_division(vector_division_aux,part(vector_division[i],*it,vector_division_old));
            else
                vector_division_aux.push_back(vector_division[i]);
        }
        
        vector_division=vector_division_aux;   
        
        if(show!=0){
            cout << "Para " << *it << ":\n"<< endl;
            print_set_division(vector_division);
        }
    }
    
    return vector_division;
}

vector<SetState> Dfa::part(const SetState& actual_division, const Symbol& actual_symbol,const vector<SetState> &vector_division_old) const{
    
    vector<SetState> vector_division;
    
    for(int i=0;i<vector_division_old.size();i++){
        SetState temp_division;
        for(SetState::iterator it=actual_division.begin();it!=actual_division.end();++it){
            int actual_state=(*it).get_next_state(actual_symbol);
            if(it_belongs_division(vector_division_old[i],actual_state)) // La funcion me dice si el estado siguiente esta en la SetState
                temp_division.insert(*it);        
        }
        if(!temp_division.empty()) // Si no ponemos esto bucle infinito
            vector_division.push_back(temp_division); 
    }
    
    return vector_division;
    
}

bool Dfa::compareDFAmin(Dfa& dfa_in){
    minimize(0);  dfa_in.minimize(0);//Minimizamos los dos estados
    if(set_state==dfa_in.set_state)
        return 1;
        
    return 0;
}