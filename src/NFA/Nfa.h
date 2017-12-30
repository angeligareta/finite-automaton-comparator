#pragma once

#include "../Shared/Alphabet.h"
#include "../Shared/Symbol.h"
#include "../Shared/State.h"
#include "../DFA/Dfa.h"

#include <set>
#include <cctype> // is digit
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

/** Tipo de dato que contiene un set de estados. Le llamamos SetState.*/
typedef set<State> SetState;
/** Tipo de dato que contiene un SetInt. Le llamamos SetState.*/
typedef set<int> SetInt;

using namespace std;

class Nfa{
   
//========================================================================================
// Métodos amigos.
//========================================================================================   
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	   Leo por pantalla el NFA
*/

   friend istream& operator>>(istream&,Nfa&);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	   Leo por pantalla el NFA
*/   

   friend ostream& operator<<(ostream&,Nfa&);
   
   private:
   set<State> set_state; /*< Conjunto de estados del NFA. **/
   Alphabet alphabet_;   /**< Alfabeto del NFA. Es un conjunto de simbolos.*/
   
   public:
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Creo el Nfa.
*/
   Nfa();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Destruyo el NFA.
*/
   ~Nfa();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Devuelvo si se ha creado el Nfa o no
*/
   bool empty() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Devuelvo el estado con la id de entrada.
*/   
   
   State get_state_with_id(const int state_id) const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Devuelvo Devuelvo el estado inicial en forma de conjunto.
*/

   State get_initial_state() const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Devuelvo el conjunto de estados finales.
*/

   SetState get_final_state() const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Imprimo los estados de muerte.
*/

   void show_death_state() const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Analiza la cadena y llama a analyze_string_rec para 
	               formar caminos recursivamente.
*/

   bool analyze_string(const string&) const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Compruebo si el Nfa es dfa (si para cada simbolo del 
	               alfabeto tiene una y solo una transición)
*/

   bool is_dfa() const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Convierto el Nfa en dfa. Puedo enseñar el proceso o no.
*/

   SetState convert2DFA(const bool&);
   
   private:
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Destruyo el vector de estados.
*/

   void clear();

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Va formando caminos si hay un estado con mas de una transición
                  para una cadena de entrada y muestra si para ese camino se acepta.
*/   

   bool analyze_string_rec(int&,int,const string&,int,string&) const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Devuelve el conjunto al que podemos llegar con epsilon_transition.
*/   

   set<int> epsilon_transition(const SetInt&) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Imprimo el camino.
*/   

   void print_way(int&,const string&) const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Imprimo el set_int.
*/ 

   void print_set_int(const SetInt&,const int& i) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Imprimo si esta aceptado o no y lo devuelvo.
*/

   bool is_way_accepted(const int&) const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Devuelvo si pertenece o no a la division y a cual.
	   
	   * @return   Int que me indica donde está la division.
*/

   int it_belongs_division(const SetInt &,const vector<SetInt>&) const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Devuelvo la union de los SetInt pasados
	   
	   * @return 	Union de los SetInt pasados
*/

   set<int> merge_division(const SetInt &,const SetInt &) const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Funcion que devuleve en un set de int todos los estados a los que
	   podemos llegar con el símbolo.
	   
	   * @return 	Devuelvo los estados a los que podemos llegar.
*/

   set<int> get_reachable_state(const SetInt&,const Symbol&) const;

};