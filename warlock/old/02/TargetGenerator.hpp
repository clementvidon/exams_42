#pragma once

#include <string>
#include <map>

class ATarget;

class TargetGenerator {
  public:
    TargetGenerator( void );
    TargetGenerator( TargetGenerator const& src );
    ~TargetGenerator( void );
    TargetGenerator& operator=( TargetGenerator const& rhs );

    void learnTargetType( ATarget* target );
    void forgetTargetType( std::string const& targetName );
    ATarget* createTarget( std::string const & targetName );

  private:
    std::map<std::string, ATarget*> _targets;
};
