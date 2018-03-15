#include "stdafx.h"
#include "Menu.h"

// Constructor
Menu::Menu()
{
	this->setSuccess("Operation successful");
}

// Destructor
Menu::~Menu()
{
}

// Save noised image
void Menu::saveNoised(Matrix<double> Matrix) {
	Matrix.saveImage("noised.pgm", 1);
	std::cout << "Saving noised image:\t" << this->getSuccess() << endl;
}

// Save denoised image
void Menu::saveDenoised(Matrix<double> Matrix) {
	Matrix.saveImage("denoised.pgm", 1);
	std::cout << "Saving denoised image:\t" << this->getSuccess() << endl;
}

// Save Shuffled image
void Menu::saveShuffled(Matrix<double> Matrix) {
	Matrix.saveImage("shuffled.pgm", 1);
	std::cout << "Saving shuffled image:\t" << this->getSuccess() << endl;
}

// Save SSD
void Menu::saveSSD(Matrix<double> Matrix) {
	Matrix.saveImage("SSD.pgm", 1);
	std::cout << "Saving SSD image:\t" << this->getSuccess() << endl;
}

// Save NNC
void Menu::saveNCC(Matrix<double> Matrix) {
	Matrix.saveImage("NCC.pgm", 1);
	std::cout << "Saving NNC image:\t" << this->getSuccess() << endl;
}

// Denoise
Matrix<double> Menu::startDenoise(Matrix<double> Matrix) {
	Matrix = Matrix.denoise();
	std::cout << "Denoising:\t" << this->getSuccess() << endl;
	return Matrix;
}

// Initialise SSD
Matrix<double> Menu::startSSD(Matrix<double> newMatrix, Matrix<double> Shuffled, Matrix<double> Reshuffled) {
	newMatrix = Shuffled.reShuffle(Reshuffled);
	std::cout << "Sum of Squared Differences:\t" << this->getSuccess() << endl;
	return newMatrix;
}

// Initialise NCC
Matrix<double> Menu::startNCC(Matrix<double> newMatrix, Matrix<double> Shuffled, Matrix<double> Reshuffled) {
	newMatrix = Shuffled.normalisedCorrelation(Reshuffled);
	std::cout << "Normalised Cross-Correlation:\t" << this->getSuccess() << endl;
	return newMatrix;
}

void Menu::DisplayMenu() {
	std::cout << "\nWelcome to \"Harry\" - my image unshuffling application!" << endl << endl;
	std::cout << "Please choose one of the following by entering coresponding number into console application and pressing enter..." << endl << endl;
	std::cout << "1.\tSave noised image to root directory" << endl;
	std::cout << "2.\tSave shuffled image to root directory" << endl;
	std::cout << "3.\tDenoise the 'noised' image provided" << endl;
	std::cout << "4.\tUse sum of square differences to un-shuffle the image" << endl;
	std::cout << "5.\tUse normalised cross-correlation to un-shuffle the image" << endl;
	std::cout << "6.\tPerform all tasks at once" << endl;
	std::cout << "7.\tExit" << endl;
}

// User choice for the menu.
int Menu::getUserChoice() {
	int input = 0;
	// Making sure input is an int.
	while (std::cout << "Enter a number:\t" && !(std::cin >> input)) {
		std::cin.clear(); //clear bad input 
		std::cout << "Invalid input; please re-enter.\n";
	}
	std::cout << endl;
	return input;
}
