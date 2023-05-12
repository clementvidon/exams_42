#include <string>

#include "TargetGenerator.hpp"
#include "ATarget.hpp"

TargetGenerator::TargetGenerator( void ) {
  return;
}

TargetGenerator::~TargetGenerator( void ) {
  std::map<std::string, ATarget*>::iterator it;

  for (it = _targets.begin(); it != _targets.end(); ++it) {
    delete it->second;
  }
  return;
}

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

ATarget* TargetGenerator::createTarget( std::string const & targetName ) {
  std::map<std::string, ATarget*>::iterator it;

  it = _targets.find( targetName );
  if ( it == _targets.end() ) {
    return NULL;
  }
  return it->second->clone();
}
