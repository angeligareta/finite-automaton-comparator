#pragma once
#include <set>
#include "Symbol.h"

using namespace std;


class Transition{
   
   friend ostream& operator<<(ostream &,const Transition &);
   
   private:
   
   set<int> set_next_state; //Numero del siguiente estado
   Symbol symbol_entry; // Simbolo del estado
   
   public:
   
   Transition();
   
   Transition(const Symbol&,const int);
   
   Transition(const Transition&);
   
   ~Transition();
   
   void swap_next_state(const int);
   
   void swap_symbol_entry(const Symbol &);
   
   void add_next_state(const int);
   
   set<int> get_set_next_state() const;
   
   //Devuelvo solo 1 para el DFA
   
   int get_next_state() const;
   
   Symbol get_symbol_entry() const;
   
   Transition& operator=(const Transition&);

   int operator==(const Transition&) const;

   int operator<(const Transition&) const;
};