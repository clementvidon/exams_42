#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(void)
{}

TargetGenerator::~TargetGenerator(void)
{
	map<string, ATarget*>::iterator it;
	for (it = this->targets.begin(); it != this->targets.end(); it++)
		delete it->second;
}

void	TargetGenerator::learnTargetType(ATarget* target)
{
	this->targets[target->getType()] = target->clone();
}

void	TargetGenerator::forgetTargetType(const string& type)
{
	map<string, ATarget*>::iterator position = this->targets.find(type);
	if (position == this->targets.end()) return;
	delete position->second;
	this->targets.erase(position);
}

ATarget*	TargetGenerator::createTarget(const string& type)
{
	map<string, ATarget*>::iterator position = this->targets.find(type);
	if (position == this->targets.end()) return (NULL);
	return (position->second->clone());
}