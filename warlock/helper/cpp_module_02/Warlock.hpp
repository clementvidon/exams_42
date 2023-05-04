#pragma once

#include <string>
#include <map>

#include "ASpell.hpp"
#include "SpellBook.hpp"

using namespace std;

class Warlock
{
	private:
		string	name;
		string	title;

		SpellBook	spells;
	
	public:
		Warlock(void);
		virtual ~Warlock(void);

		Warlock(const Warlock& from);

		Warlock&	operator=(const Warlock& from);

		const string&	getName() const;
		const string&	getTitle() const;

		void	setTitle(const string& title);

		Warlock(string name, string title);

		void	introduce(void) const;

		void	learnSpell(ASpell* spell);
		void	forgetSpell(string name);
		void	launchSpell(string name, ATarget& target);
};
