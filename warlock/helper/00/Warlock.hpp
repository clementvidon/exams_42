#pragma once

#include <string>

using namespace std;

class Warlock
{
	private:
		string	name;
		string	title;

	public:
		Warlock(void);
		virtual ~Warlock(void);

		Warlock(const Warlock& from);

		Warlock&	operator=(const Warlock& from);

		const string&	getName() const;
		const string&	getTitle() const;

		void	setTitle(const string& title);

		Warlock(string name, string title);

		void	introduce(void) const;
};
