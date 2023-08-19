#include "ASpell.hpp"
#include "Fwoosh.hpp"

Fwoosh::Fwoosh( void ) : ASpell( "Fwoosh", "fwooshed" ) {}

Fwoosh* Fwoosh::clone( void ) const { return new Fwoosh(); }
