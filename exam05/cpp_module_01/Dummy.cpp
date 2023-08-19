#include "ATarget.hpp"
#include "Dummy.hpp"

Dummy::Dummy( void ) : ATarget( "Target Practice Dummy" ) {}

Dummy* Dummy::clone( void ) const { return new Dummy(); }
