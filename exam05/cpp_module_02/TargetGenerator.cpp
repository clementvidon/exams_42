#include <map>
#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"
#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator( void ) {}

TargetGenerator::~TargetGenerator( void ) {}

void TargetGenerator::learnTargetType( ATarget* target ) {
  if( target != NULL ) {
    std::string                               targetType = target->getType();
    std::map<std::string, ATarget*>::iterator it = _targets.find( targetType );

    if( it == _targets.end() ) {
      _targets[targetType] = target;
    }
  }
}

void TargetGenerator::forgetTarget( std::string const& targetType ) {
  std::map<std::string, ATarget*>::iterator it = _targets.find( targetType );

  if( it != _targets.end() ) {
    _targets.erase( it );
  }
}

ATarget* TargetGenerator::createTarget( std::string const& targetType ) {
  std::map<std::string, ATarget*>::iterator it = _targets.find( targetType );

  if( it != _targets.end() ) {
    return it->second->clone();
  }
  return NULL;
}

/* TargetGenerator& operator=( TargetGenerator const& rhs ); */

/* TargetGenerator( TargetGenerator const& src ); */
