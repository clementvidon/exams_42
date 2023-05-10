#include <string>
#include <iostream>

#include "Warlock.hpp"

Warlock::Warlock( std::string const& name, std::string const& title ) :
  _name( name ),
  _title( title ) {
  std::cout << _name << ": This look like another boring day.\n";
  return;
}

Warlock::~Warlock( void ) {
  std::cout << _name << ": My job here is done!\n";
  return;
}

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

void Warlock::introduce( void ) const {
  std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
  return;
}
