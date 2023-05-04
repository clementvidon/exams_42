#include "Dummy.hpp"

Dummy::Dummy(void):
	ATarget("Target Practice Dummy")
{}

Dummy::~Dummy(void)
{}

Dummy*	Dummy::clone(void) const
{
	return (new Dummy());
}