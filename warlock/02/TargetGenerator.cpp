#include <string>
#include <iostream>

#include "ATarget.hpp"
#include "ATarget.hpp"

#include "TargetGenerator.hpp"

/* TargetGenerator( void ) { */
/*   return; */
/* } */

TargetGenerator::TargetGenerator( void ) {
    return;
}

/* TargetGenerator( TargetGenerator const& src ) { */
/*   return; */
/* } */

TargetGenerator::~TargetGenerator( void ) {
  std::map<std::string, ATarget*>::iterator it;

  for ( it = _targets.begin(); it != _targets.end(); ++it ) {
    delete it->second; // TODO why "->" ? un iterateur est un pointeur
  }
  return;
}

/* TargetGenerator& operator=( TargetGenerator const& src) { */
/*   return; */
/* } */


void TargetGenerator::learnTargetType( ATarget* target ) {
  _targets[target->getType()] = target->clone();
  return;
}

void TargetGenerator::forgetTargetType( std::string const& targetName ) {
  std::map<std::string, ATarget*>::iterator it;

  it = _targets.find( targetName );
  if ( it == _targets.end() ) {
    return;
  }
  delete it->second;
  _targets.erase( it );
  return;
}

ATarget* TargetGenerator::createTarget( std::string const& targetName ) {
  std::map<std::string, ATarget*>::iterator it;

  it = _targets.find( targetName );
  if ( it == _targets.end() ) {
    return NULL;
  }
  return it->second->clone();
}
