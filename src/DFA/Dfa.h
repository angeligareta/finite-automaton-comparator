#pragma once

#include "../Shared/Alphabet.h"
#include "../Shared/Symbol.h"
#include "../Shared/State.h"

#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

#define MAXINT 32767

using namespace std;

/** Tipo de dato que contiene un set de estados. Le llamamos SetState.*/
typedef set<State> SetState;

class Dfa{

//========================================================================================
// Métodos amigos.
//========================================================================================

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función sobrecargada con el operador << . Imprime el DFA en lo que este a la izquierda del << .

       * @param  	dfa_.set_state.size() Numero de estados del DFA.
       * @param  	dfa_.get_initial_state().get_identifier() Estado inicial del DFA.
       * @param  	*it  Cada uno de los estados. Los muestro por pantalla en el formato predefinido.
       * @return 	output Devuelve lo que ha leido con el ostream output.
*/

   friend ostream &operator<<(ostream &, const Dfa &);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función sobrecargada con el operador >> . Lee el DFA en lo que este a la izquierda del >> .

       * @param  	error Tipo Booleano. Si al acabar es 1 es que el fichero introducido es incorrecto
       * @param  	state_number Número de estados.
       * @param  	initial_state Estado inicial del DFA.
       * @param   state_temp Estado actual que va leyendo.
       * @return 	input Devuelve input.
*/   
   
   friend istream& operator>>(istream &, Dfa &);
   
//========================================================================================
// Métodos públicos.
//========================================================================================   
   private:
   
   Alphabet alphabet_; /**< Alfabeto del DFA. Es un conjunto de simbolos.*/
   set<State> set_state; /**< Conjunto de estados del DFA. Cada estado tiene una transición por simbolo del alfabeto.*/
   
   public:
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Constructor del DFA. No hace nada.
*/

   Dfa();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Constructor del DFA. Recibe un vector de estados.
*/   
   Dfa(const SetState&);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Destructor del dfa. Limpia el set_state y Alphabet.
*/
   
   ~Dfa();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Destructor del dfa. Llama al metodo clear
	   
	   *@return set_state.empty() Devuelve si el conjunto de estados está vacío.
	   
*/
   
   bool empty() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Muestra por pantalla los estados de muerte
*/

   void show_death_state() const;   
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

   	\details 	Analiza una cadena introducida por el usario.

       * @param  	number_actual_state Número de estado actual.
       * @param  	symbol_entry Símbolo de entrada de la cadena
       * @return 	Si la cadena introducida pertenece o no al DFA.
*/   
   
   bool analyze_string(const string&) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Minimiza el DFA actual.
	1º Creamos un conjunto de divisiones de estados. Le insertamos los estados finales y el resto.
	2º Llamamos a create_new_partition para que cree nuevas particiones.
	3º Paramos cuando veamos que la particion actual es igual a la anterior.
	4º Llamamos a update para que nos actualize el DFA.

       * @param   vector_division Conjunto de divisiones actual.
       * @param   vector_division_old Conjunto de divisiones anterior.
*/     
   
   void minimize(const bool);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Compara los dos DFA y devuelve si son equivalentes.
*/

   bool compareDFAmin(Dfa&);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Devuelve el alfabeto del DFA.
*/ 
   Alphabet get_alphabet() const;
   
//========================================================================================
// Métodos privados.
//========================================================================================   
   
   private:
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Destruye el set_state. Llama al destructor de la clase set.

       * @param  	set_state.clear() Llamada al destructor de la clase set.
*/

   void clear();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Cambia un estado del conjunto de estados por otro.
*/   
   
   void swap_state(const State& state_1,const State& state_2);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Actualizo el alfabeto del DFA.
*/      
   
   void update_alphabet();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Devuelve el estado con el id que se recibe.
	
	   * @param    state_id Id del estado.
*/
   
   State get_state_with_id(const int) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Devuelve el estado inicial.
*/
   
   State get_initial_state() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Devuelve el estado final.
*/ 
   
   SetState get_final_state() const;

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details 	Muestra por pantalla el conjunto de estados con {}
*/
   
   void print_set_state(const SetState &) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Muestra por pantalla la divisón actual de set_state. Es decir el subconjunto de estados.
*/   
   
   void print_set_division(const vector<SetState> &) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Devuelve la unión del conjunto de divisiones.

       * @param  	vector_division_1 Conjunto de divisiones primero.
       * @param  	vector_division_2 Conjunto de divisiones segundo.
       * @return 	Unión conjunto de divisiones.
*/   
   
   vector<SetState> merge_vector_division(const vector<SetState> &,const vector<SetState> &) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Devuelve si el estado que se le pasa pertenece a la divisón que se le pasa

       * @param  	actual_division Divisón del conjunto de estados actual.
       * @param  	actual_state Estado que queremos ver si pertenece.
       * @return 	Bool que devuelvesi el estado que se le pasa pertenece a la divisón que se le pasa.
*/   
   
   bool it_belongs_division(const SetState &,const int &) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Cambia el dfa actual por el mínimo que se le envia en un conjunto de divisiones de estados.

       * @param  	Conjunto de divisiones de estados.
*/  
   
   void update(const vector<SetState> &);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	Ordena el DFA actual segun un orden establecido.
*/    
   void custom_sort();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Cambia el valor actual que la pasamos por los nuevos en el vector de estados.

*/   
   
   void change_value_set_state(const int,const int);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Cambia el valor actual que la pasamos por los nuevos en el vector de estados.

*/   
   
   void swap_value_set_state(const int,const int);   

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Descompone, si se puede, las divisiones actuales por símbolo si hay estados no distinguibles.

       * @param  	alphabet_ Alfabeto donde tenemos los simbolos del DFA.
       * @param  	vector_division_old Conjunto de divisiones π que le pasamos para particionar.
       * @param  	vector_division Conjunto de divisiones. Lo igualaremos a vector_division_aux.
       * @param   vector_division_aux Conjunto de divisiones actual para ir uniendo las particiones para cada símbolo.
       * @return 	Devuelvo el nuevo conjunto de divisiones.
*/   

   vector<SetState> create_new_partition(const vector<SetState> &,const bool) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details 	   Descompone la división actual de π, para el símbolo que se le envía y para cada subconjunto de la SetState actual.
	Finalmente va uniendo estas descomposiciones y las devuelve.

       * @param  	actual_division División atual. La que descomponemos.
       * @param  	actual_symbol Símbolo de entrada que le pasamos.
       * @param   vector_division Conjunto de divisiones donde iremos insertando las nuevas.
       * @param	temp_division División temporal que voy insertando en el vector_division
       * @return 	Devuelvo el nuevo conjunto de divisiones.
*/      
   
   vector<SetState> part(const SetState &, const Symbol &,const vector<SetState> &) const;
   
};