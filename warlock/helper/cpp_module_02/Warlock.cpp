#include "Warlock.hpp"

#include <iostream>

using namespace std;

Warlock::~Warlock(void)
{
	cout << this->name << ": My job here is done!\n";
}

const string&	Warlock::getName(void) const
{
	return (this->name);
}

const string&	Warlock::getTitle(void) const
{
	return (this->title);
}

void	Warlock::setTitle(const string& title)
{
	this->title = title;
}

Warlock::Warlock(string name, string title):
	name(name),
	title(title)
{
	cout << this->name << ": This looks like another boring day.\n";
}

void	Warlock::introduce(void) const
{
	cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

void	Warlock::learnSpell(ASpell* spell)
{
	this->spells.learnSpell(spell);
}

void	Warlock::forgetSpell(string name)
{
	this->spells.forgetSpell(name);
}

void	Warlock::launchSpell(string name, ATarget& target)
{
	ASpell* spell = this->spells.createSpell(name);
	if (!spell) return ;
	spell->launch(target);
	delete spell;
}