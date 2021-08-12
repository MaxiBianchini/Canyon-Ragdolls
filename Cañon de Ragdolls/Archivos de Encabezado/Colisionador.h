#include "Ragdoll.h"

class Colisionador : public b2ContactListener {
public:

	void BeginContact(b2Contact *contact);
};

