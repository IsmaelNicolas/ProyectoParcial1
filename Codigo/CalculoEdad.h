#ifndef CALCULOEDAD_H  
#define CALCULOEDAD_H

#include <iostream>
#include "Fecha.h"

using namespace std;
class CalculoEdad {
	private:
		int edad_anios;
		int edad_meses;
		int edad_dias;
	public:
		CalculoEdad();
		void calc_edad(Fecha);
		int get_edad_anios();
		int get_edad_meses();
		int get_edad_dias();
		std::string get_edad();
};
#endif;
