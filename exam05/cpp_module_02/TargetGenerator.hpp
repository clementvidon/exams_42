#pragma once

#include <map>
#include <string>

class ASpell;
class ATarget;

class TargetGenerator {
 public:
  TargetGenerator( void );
  ~TargetGenerator( void );

  void     learnTargetType( ATarget* target );
  void     forgetTarget( std::string const& targetType );
  ATarget* createTarget( std::string const& targetType );

 private:
  TargetGenerator( TargetGenerator const& src );
  TargetGenerator& operator=( TargetGenerator const& rhs );

  std::map<std::string, ATarget*> _targets;
};
