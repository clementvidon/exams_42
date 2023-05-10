#pragma once

#include <string>

class ASpell;

#include "ATarget.hpp"

using namespace std;

class ASpell
{
	protected:
		string	name;
		string	effects;

	public:
		ASpell(void);
		virtual ~ASpell(void);

		ASpell(const ASpell& from);

		ASpell&	operator=(const ASpell& from);

		string	getName(void) const;
		string	getEffects(void) const;

		virtual ASpell*	clone(void) const = 0;

		ASpell(string name, string effects);

		void	launch(const ATarget& target) const;
};
