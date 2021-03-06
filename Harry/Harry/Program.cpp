// Program.cpp : Defines the entry point for the console application.
// "Harry" is a program designed to restore shuffled and noised(black and white) picture to original form.
// It uses either Sum of Squared Differences or Normalised Cross Correlation in order to re-create the picture.
// It also implements simple de-noising technique necessary for the project, as well as Object-Oriented structure of the program.
// Main functionality is contained withing Matrix.h. The application also has simple Controls header and class which is inherited by Matrix.h,
// which is meant for future extensions.

#include "stdafx.h"
#include "Matrix.h" // Matrix 
#include "Controls.h" // Settings
#include "Menu.h"
#include <iostream>

int main() 
{
	// Objects
	// This section is dedicated for initializing objects.
	// NOTE! Settings.SmallSize = 32x32, Settings.LargeSize = 512x512.
	// IMPORTANT! More information about overloading methods for Matrix can be found, in Matrix.h file in "Header Files".
	Controls Settings;
	Menu MainManu;
	Matrix<double> m1("logo_with_noise.txt", Settings.LargeSize(), Settings.LargeSize()); // Noised image
	Matrix<double> m2("logo_shuffled.txt", Settings.LargeSize(), Settings.LargeSize()); // Shuffled image
	Matrix<double> m3(m1); // noised image
	Matrix<double> m4(Settings.LargeSize(), Settings.LargeSize()); // SSD 
	Matrix<double> m5(Settings.LargeSize(), Settings.LargeSize()); // NCC
	Matrix<double> m6(Settings.LargeSize(), Settings.LargeSize()); // Additional Matrix for testing purposes.

	//	Variables
	int input = 0;

	// Main menu
	while (input!=7)		//"7.\tExit" 
	{

			MainManu.DisplayMenu();
			input = MainManu.getUserChoice();
			switch (input)
			{
			case 1:
			{
				MainManu.saveNoised(m1);	//"1.\tSave noised image to root directory" << 
				break;
			}
			case 2:
				MainManu.saveShuffled(m2);		//"2.\tSave shuffled image to root directory" 
				break;
			case 3:
				m3 = m3.denoise();	
				MainManu.saveDenoised(m3);		//"3.\tDenoise the 'noised' image provided" 
				break;
			case 4:
				m3 = m3.denoise();
				m4 = m2.reShuffle(m3);
				MainManu.saveSSD(m4);		//"4.\tUse sum of square differences to un-shuffle the image" 
				break;
			case 5:
				m3 = m3.denoise();
				m5 = m2.normalisedCorrelation(m3);
				MainManu.saveNCC(m5);		//"5.\tUse normalised cross-correlation to un-shuffle the image" 
				break;
			//"6.\tPerform all tasks at once"
			case 6:	
				MainManu.saveNoised(m1);
				MainManu.saveShuffled(m2);
				m3 = m3.denoise();
				MainManu.saveDenoised(m3);
				m4 = m2.reShuffle(m3);
				MainManu.saveSSD(m4);
				m5 = m2.normalisedCorrelation(m3);
				MainManu.saveNCC(m5);
				break;
			default:
				break;
			}

	}
	
	return 0;
}
