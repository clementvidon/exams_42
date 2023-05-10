#pragma once

#include "ASpell.hpp"

class Fwoosh: public ASpell
{
	public:
		Fwoosh(void);
		virtual ~Fwoosh(void);

		Fwoosh*	clone(void) const;
};