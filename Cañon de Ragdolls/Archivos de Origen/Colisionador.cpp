#include "Colisionador.h"

//Se llama cuando un objeto entra el contacto
void Colisionador::BeginContact(b2Contact *contact) {

	//Obtiene el Fixture de los cuerpos
	b2Fixture* F1 = contact->GetFixtureA();
	b2Fixture* F2 = contact->GetFixtureB();

	//Obtiene el Body de los cuerpos
	b2Body* B1 = F1->GetBody();
	b2Body* B2 = F2->GetBody();

	//Corrobora que sean los cuerpos que me interesan
	if (Ragdoll* O1 = (Ragdoll*)B1->GetUserData()) {
		if (Objetos* O2 = (Objetos*)B2->GetUserData()) {

			if (O2->VerID() == identificador::Calabza) O1->Win(); //Gana el juego
		}
	}
	else if (Ragdoll* O2 = (Ragdoll*)B1->GetUserData()) {
		if (Objetos* O1 = (Objetos*)B2->GetUserData()) {

			if (O1->VerID() == identificador::Calabza) O2->Win(); //Gana el juego
		}
	}
}
