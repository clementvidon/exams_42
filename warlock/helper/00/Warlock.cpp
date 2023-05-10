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