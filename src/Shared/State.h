#pragma once
#include "Transition.h"

#include <set>
#include <cstdio>
#include <iostream>

using namespace std;

class State{
   
   friend ostream& operator<<(ostream &,const State&);
   
   private:
   
   int identifier;
   bool initial;
   bool final;
   
   public:
   
   set<Transition> set_transition;
   
   State();
   
   State(const State&);
   
   ~State();
   
   void clear();
   
   void set_identifier(const int);
   
   void set_initial(const bool);
   
   void set_final(const bool);
   
   void insert_transition(const Symbol&,const int);
   
   int get_identifier() const;
   
   bool get_initial() const;
   
   bool get_final() const;
   
   set<Transition> get_set_transition() const;
   
   void swap_transition(const Transition&, const Transition&);
   
   set<int> get_set_next_state(const Symbol&) const;
   
   int get_next_state(const Symbol&) const;
   
   bool is_death_state() const;
   
   State& operator=(const State &state_in);

   int operator==(const State &state_in) const;

   int operator<(const State &state_in) const;
   
};