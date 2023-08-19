#include "ASpell.hpp"
#include "Polymorph.hpp"

Polymorph::Polymorph( void ) : ASpell( "Polymorph", "turned into critter" ) {}

Polymorph* Polymorph::clone( void ) const { return new Polymorph(); }
