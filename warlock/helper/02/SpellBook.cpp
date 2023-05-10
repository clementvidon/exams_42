#include "SpellBook.hpp"

SpellBook::SpellBook(void)
{}

SpellBook::~SpellBook(void)
{
	map<string, ASpell*>::iterator it;
	for (it = this->spells.begin(); it != this->spells.end(); it++)
		delete it->second;
}

void	SpellBook::learnSpell(ASpell* spell)
{
	this->spells[spell->getName()] = spell->clone();
}

void	SpellBook::forgetSpell(const string& name)
{
	map<string, ASpell*>::iterator position = this->spells.find(name);
	if (position == this->spells.end()) return;
	delete position->second;
	this->spells.erase(position);
}

ASpell*	SpellBook::createSpell(const string& name)
{
	map<string, ASpell*>::iterator position = this->spells.find(name);
	if (position == this->spells.end()) return (NULL);
	return (position->second->clone());
}