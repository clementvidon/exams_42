#pragma once

#include "ATarget.hpp"

class BrickWall: public ATarget
{
	public:
		BrickWall(void);
		virtual ~BrickWall(void);

		BrickWall*	clone(void) const;
};