#pragma once

#include "ATarget.hpp"

class Dummy: public ATarget
{
	public:
		Dummy(void);
		virtual ~Dummy(void);

		Dummy*	clone(void) const;
};