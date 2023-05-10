#pragma once

#include "ASpell.hpp"

class Fireball: public ASpell
{
	public:
		Fireball(void);
		virtual ~Fireball(void);

		Fireball*	clone(void) const;
};