#pragma once

#include <string>
#include <map>

#include "ATarget.hpp"

class TargetGenerator
{
	private:
		map<string, ATarget*>	targets;

	public:
		TargetGenerator(void);
		virtual ~TargetGenerator(void);

		TargetGenerator(const TargetGenerator& from);

		TargetGenerator&	operator=(const TargetGenerator& from);

		void	learnTargetType(ATarget* target);
		void	forgetTargetType(const string& type);

		ATarget*	createTarget(const string& type);
};
