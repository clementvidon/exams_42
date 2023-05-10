#pragma once

#include "ASpell.hpp"

class Polymorph: public ASpell
{
	public:
		Polymorph(void);
		virtual ~Polymorph(void);

		Polymorph*	clone(void) const;
};