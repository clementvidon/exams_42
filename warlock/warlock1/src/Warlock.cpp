#include <iostream>
#include <string>

#include "Warlock.hpp"

/*  STANDARD
------------------------------------------------- */

/**
 * @brief       Parametric Constructor
 */

Warlock::Warlock( std::string const& name, std::string const& title )
  : _name( name ),
    _title( title ) {
  std::cout << _name;
  std::cout << ": This looks like another boring day.";
  std::cout << std::endl;
  return;
}

/**
 * @brief       Destructor
 */

Warlock::~Warlock( void ) {
  std::cout << _name;
  std::cout << ": My job here is done!";
  std::cout << std::endl;
  return;
}

/* ---------------------------------------------- */

void Warlock::introduce( void ) const {
  std::cout << _name;
  std::cout << ": I am ";
  std::cout << _name;
  std::cout << ", ";
  std::cout << _title;
  std::cout << "!" << std::endl;
  return;
}

/*  GETTER SETTER
------------------------------------------------- */

std::string const& Warlock::getName( void ) const {
  return _name;
}

std::string const& Warlock::getTitle( void ) const {
  return _title;
}

void Warlock::setTitle( std::string const& title ) {
  _title = title;
  return;
}
