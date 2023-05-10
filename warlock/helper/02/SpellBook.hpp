#pragma once

#include <string>
#include <map>

#include "ASpell.hpp"

class SpellBook
{
	private:
		map<string, ASpell*>	spells;

	public:
		SpellBook(void);
		virtual ~SpellBook(void);

		SpellBook(const SpellBook& from);

		SpellBook& operator=(const SpellBook& from);

		void	learnSpell(ASpell* spell);
		void	forgetSpell(const string& name);

		ASpell*	createSpell(const string& name);
};