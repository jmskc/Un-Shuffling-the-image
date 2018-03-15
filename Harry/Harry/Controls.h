// Controls.h is designed to safely store static variables.
// It was created with inheritence in mind, so that it can be utilised with various classes.
// Idea is to centralize variables that are re-used in many classes.
// Declaring variables as private allows for less user/developer error.

#pragma once
#include <string>
class Controls
{
private:
	// Matrix sizes
	static const int small = 32; 
	static const int large = 512;

public:
	// Consturctor and destructor
	Controls();
	~Controls();

	// Getters
	const int& SmallSize() const { return small; }
	const int& LargeSize() const { return large; }

};

