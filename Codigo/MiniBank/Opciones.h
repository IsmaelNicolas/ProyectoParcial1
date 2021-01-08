#include "Lista.h"
#include "Consola.h"

#pragma once

class Opciones
{
public:			
	Cuenta IngresarnuevaCuenta();
	void realizarRetiro(Lista* cuentas);
	void realizarDeposito(Lista* cuentas);
	void mostarCuentas(Lista* cuentas);
	void buscarCuenta(Lista* cuentas);
	Consola pantalla;
};

