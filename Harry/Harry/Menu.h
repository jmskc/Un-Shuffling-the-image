#pragma once
#include "Matrix.h"

class Menu : public Matrix<double>
{
private:
	string success;	// used for confirming successful operation

public:

	// Constructor and destructor
	Menu();
	~Menu();

	// Getters
	const std::string& getSuccess() const { return success; }
	
	// Setters
	void setSuccess(const std::string& _success) { success = _success; }
	
	// Methods
	void saveNoised(Matrix<double> Matrix);
	void saveDenoised(Matrix<double> Matrix);
	void saveShuffled(Matrix<double> Matrix);
	void saveSSD(Matrix<double> Matrix);
	void saveNCC(Matrix<double> Matrix);
	void DisplayMenu();
	int getUserChoice();

	// Additional options NOT USED WITHIN THE ASSESSMENT!
	Matrix<double> startDenoise(Matrix<double> Matrix);
	Matrix<double> startSSD(Matrix<double> newMatrix, Matrix<double> Shuffled, Matrix<double> Reshuffled);
	Matrix<double> startNCC(Matrix<double> newMatrix, Matrix<double> Shuffled, Matrix<double> Reshuffled);

};

