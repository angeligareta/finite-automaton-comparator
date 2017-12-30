#pragma once

#include <cstdio>
#include <iostream>
#include <sstream> 

using namespace std;

class Symbol{
   
   friend ostream& operator<<(ostream &output, const Symbol&);   
   
   private:
   
   string sum_;
   
   string symbol_;
   
   public:
   
   Symbol();
   
   explicit Symbol(const char&);
   
   explicit Symbol(const string&);
   
   Symbol(const Symbol&);
   
   ~Symbol();
   
   string get_symbol() const;

   Symbol& operator=(const Symbol&);

   int operator==(const Symbol&) const;

   int operator<(const Symbol&) const;
   
};