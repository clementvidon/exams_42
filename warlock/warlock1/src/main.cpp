#include <iostream>
#include "Warlock.hpp"

#include "ASpell.hpp"
#include "ATarget.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"
#include "Warlock.hpp"

int main( void ) {

  // ex00
  // a
  /* Warlock bob;                            //Does not compile */
  /* Warlock bob("Bob", "the magnificent");  //Compiles */
  /* Warlock jim("Jim", "the nauseating");   //Compiles */
  /* bob = jim;                              //Does not compile */
  /* Warlock jack(jim);                      //Does not compile */

  // b
  /* Warlock const richard( "Richard", "Mistress of Magma" ); */
  /* richard.introduce(); */
  /* std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;
   */
  /* Warlock* jack = new Warlock( "Jack", "the Long" ); */
  /* jack->introduce(); */
  /* jack->setTitle( "the Mighty" ); */
  /* jack->introduce(); */

  /* delete jack; */

  // ex01
  Warlock richard( "Richard", "the Titled" );
  Dummy   bob;
  Fwoosh* fwoosh = new Fwoosh();
  richard.learnSpell( fwoosh );
  richard.introduce();
  richard.launchSpell( "Fwoosh", bob );
  richard.forgetSpell( "Fwoosh" );
  richard.launchSpell( "Fwoosh", bob );
  delete fwoosh;

  return ( 0 );
}
