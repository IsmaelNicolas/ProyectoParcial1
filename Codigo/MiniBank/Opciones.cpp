#include "Opciones.h"
#include "IngresoDatos.h"
#include "Generador.h"
#include "Deposito.h"
#include "Retiro.h"
#include "CalculoEdad.h"
#include <iostream>

#define DEPOSITO_INICIAL_CORRIENTE  50.0f  
#define DEPOSITO_INICIAL_AHORROS  0.0f  
#define DEPOSITO_MINIMO 5.0f

using namespace std;


Cuenta Opciones::IngresarnuevaCuenta(Lista* cuentas) {

	system("cls");


	Fecha fechaNacimiento;
	Cuenta cuenta;
	IngresoDatos ingreso;

	Persona persona;
	CalculoEdad edad;
	Generador generador;
	string dato = "";
	int tipoCuenta = 0;
	string dia, mes, anio;
	int diaEspecial = 28;
	bool bandera = false;
	int dias_meses[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


	system("cls");
	do {
		pantalla.gotoxy(4, 4);
		dato = ingreso.IngresoTexto("Ingrese el nombre:     \b\b\b\b\b ");
		persona.setNombre(dato);
	} while (dato == "");

	do
	{
		pantalla.gotoxy(4, 5);
		dato = ingreso.IngresoTexto("Ingrese el apellido:    \b\b\b\b\b");
		persona.setApellido(dato);
	} while (dato == "");

	do
	{
		pantalla.gotoxy(4, 6);
		dato = ingreso.IngresoNumero("Ingrese numero de cedula:               \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		persona.setCedula(dato);

	} while (dato == "" || dato.size() != 10 || !ingreso.validarCedula(dato));

	do
	{
		do {
			pantalla.gotoxy(4, 7);
			anio = ingreso.IngresoNumero("Ingrese su anio de nacimiento: (AAAA):      \b\b\b\b\b\b");
		} while (!edad.validar_anio(stoi(anio)));
	} while (anio.size() != 4);

	if (ingreso.anioBisiesto(stoi(anio))) {
		diaEspecial = 29;
	}

	do
	{
		pantalla.gotoxy(4, 8);
		mes = ingreso.IngresoNumero("Ingrese su mes de nacimiento: (mm):     \b\b\b\b\b");

	} while (mes.size() != 2 || stoi(mes) <= 0 || stoi(mes) > 12);

	
	do
	{
		pantalla.gotoxy(4, 9);
		dia = ingreso.IngresoNumero("Ingrese su dia de nacimiento (dd):     \b\b\b\b\b ");
		if (ingreso.anioBisiesto(stoi(anio)) && stoi(mes)==2) {
			diaEspecial = 29;
		}
		else
		{
			diaEspecial = dias_meses[stoi(mes)-1];
		}

	} while (dia.size() != 2 || stoi(dia) <= 0 || stoi(dia) > diaEspecial);

	
	fechaNacimiento.setDia(stoi(dia)); // = new Fecha(stoi(dia), stoi(mes), stoi(anio));
	fechaNacimiento.setMes(stoi(mes));
	fechaNacimiento.setAnio(stoi(anio));
	persona.setEdad(edad.calc_edad(fechaNacimiento));

	dato = generador.crearCorreo(persona.getApellido(), persona.getNombre(), cuentas);
	cout << "\n\t Correo: " << dato;
	persona.setCorreo(dato);



	pantalla.gotoxy(4, 13);
	cout << "\t Tipo de cuenta: \n";
	cout << "\t   1. Corriente\n";
	cout << "\t   2. Ahorros\n";

	do
	{
		pantalla.gotoxy(4, 17);
		try
		{
			tipoCuenta = stoi(ingreso.IngresoNumero("Digite una opcion:     \b\b\b\b\b "));
		}
		catch (const std::exception&)
		{
			tipoCuenta = 0;
		}
		
		//if(tipoCuenta != 1 && tipoCuenta != 2)cout << "\033[B";
		//if (tipoCuenta == NULL) 

	} while (tipoCuenta != 1 && tipoCuenta != 2 );


	switch (tipoCuenta) {
	case cuenta.Ahorros:
		cuenta.setTipoDeCuenta(cuenta.Ahorros);
		break;
	case cuenta.Corriente:
		cuenta.setTipoDeCuenta(cuenta.Corriente);
		break;
	}

	dato = generador.generarNumeroDeCuenta(persona.getCedula(), cuenta.getTipoDeCuenta());
	cuenta.setId(dato);
	cout << "\n\n\tNumero de cuenta: "<<dato<< endl;
	cuenta.setPersona(persona);


	cout << endl << "\t";

	system("pause");


	return cuenta;

}

void Opciones::realizarDeposito(Lista* cuentas) {

	system("cls");
	IngresoDatos ingreso;
	Deposito deposito;
	string dato;
	

	do
	{
		system("cls");
		pantalla.gotoxy(2, 3);
		dato = ingreso.IngresoNumero("Ingrese numero de cuenta:  ");
		deposito.movimiento(cuentas, dato);

	} while (dato == "" || dato.size() != 12);


	cout << endl << "\t";
	system("pause");


}

void Opciones::realizarRetiro(Lista* cuentas) {

	system("cls");
	IngresoDatos ingreso;
	Retiro retiro;
	string dato;


	do
	{
		pantalla.gotoxy(2, 3);
		dato = ingreso.IngresoNumero("Ingrese numero de cuenta:                   \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		retiro.movimiento(cuentas, dato);

	} while (dato == "" || dato.size() != 12);


	cout << "\n\t";
	system("pause");

}

void Opciones::buscarCuenta(Lista* cuentas) {
	string cuenta;
	Cuenta cuenta1;

	system("cls");

	cout << "Ingrese su numero de cuenta" << endl;
	cin >> cuenta;
	cuenta1 = buscarYTraer(cuentas,cuenta);


	if (cuenta1.getId() != ""){
		cuenta1.mostrarInformacion();
	}
	else
	{
		cout << "No existe el numero de cuenta...." << endl;
	}

	cout << "\n\t";
	system("pause");
}

void Opciones::mostarCuentas(Lista* cuentas) {

	system("cls");
	cuentas->toString();
	cout << "\n\t";
	cout << "\n\t";
	system("pause");

}
bool Opciones::buscar(Lista* cuentas,string id) {
	
	Nodo* aux = new Nodo();
	Nodo* aux1 = new Nodo();

	aux = cuentas->getNodo();

	bool respuesta = false;
	while (aux != NULL)
	{
		if (aux->getCuenta().getId() == id) {
			respuesta = true;

		}

		aux1 = aux;
		aux = aux->getSiguiente();
	}

	return respuesta;
}

Cuenta Opciones::buscarYTraer(Lista* cuentas,string id) {
	Nodo* aux = new Nodo();
	Cuenta auxCuenta;
	aux = cuentas->getNodo();

	while (aux != NULL)
	{

		if (id == aux->getCuenta().getId()) {
			auxCuenta = aux->getCuenta();
			//auxCuenta.mostrarInformacion();
			return auxCuenta;
		}

		aux = aux->getSiguiente();
	}

	return auxCuenta;
}