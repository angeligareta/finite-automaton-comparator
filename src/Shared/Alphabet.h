#pragma once

#include "Symbol.h"
#include <set>
#include <cstdio>
#include <iostream>

using namespace std;

class Alphabet{
   
   friend ostream &operator<<(ostream &,const Alphabet &);
   
   private:
   
   set<Symbol> alphabet_;
   
   public:
   
   Alphabet();
   
   ~Alphabet();
   
   void clear();
   
   void insert(Symbol);
   
   set<Symbol> get_alphabet() const;
   
   int  size() const;
   
   bool it_belongs(const Symbol&) const;
   
   void erase(const Symbol& symbol_in);
   
};