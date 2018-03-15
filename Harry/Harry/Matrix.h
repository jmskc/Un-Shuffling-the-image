// Main header for the application
// Header is divided into two sections: Header and Class.
// The reason for this solution is to allow the use of templates.

#pragma once

#include "stdafx.h"
#include "Controls.h"
#include <stdexcept>
#include <fstream> 
#include <vector>
#include <iostream>

// Header 
// Stores definitions.
template <class T>
class Matrix : Controls  {
private:
	int numRows,
		numCols;
public:
	T * ptrMatrix;

	// Contructors 
	Matrix(); // default
	Matrix(int rows, int cols); // Initialize with custom size.
	Matrix(const Matrix<T>& sourceMatrix); // Copy sourceMatrix.
	Matrix(const char *fileName, int rows, int cols); // Initialize from file.

	// Desturctor
	~Matrix();

	// Methods
	void fillMatrix(T value);
	void printMatrix();
	void printSubMatrix(int row, int col, int height, int width); 
	void saveImage(const char *fileName, int Q);

	Matrix<T> denoise();
	Matrix<T> subMatrix(int nrow, int ncol, int height, int width); // creates small sub matrix.
	Matrix<T> reShuffle(Matrix<T> Goal); // SSD
	Matrix<T> normalisedCorrelation(Matrix<T> Goal); // NCC

	// Operators
	Matrix<T>& operator=(const Matrix<T>& sourceMatrix);
	Matrix<T> operator-(const Matrix<T>& sourceMatrix);
	Matrix<T> operator*(const Matrix<T>& sourceMatrix);

	// Calculations
	Matrix<T> square();

	T average(int startRow, int startCol, int width, int height);
	T sum(int startRow, int startCol, int width, int height);

	// Vectors
	std::vector<Matrix<T>> split();

	// Getters 
	int getNumRows();
	int getNumCols();

	T getItem(int row, int col);

	// Setters
	void setItem(int row, int col, T value);

};

using namespace std;

template <class T>
Matrix<T>::Matrix()
{
	// Default size.
	this->numRows = 5;
	this->numCols = 5;

	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
}

template<class T>
Matrix<T>::Matrix(int rows, int cols)
{
	this->numRows = rows;
	this->numCols = cols;
	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
}

// Copy constructor.
template <class T>
Matrix<T>::Matrix(const Matrix<T>& sourceMatrix)
{
	numRows = sourceMatrix.numRows;
	numCols = sourceMatrix.numCols;

	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
	else
	{
		// Copy source data to destination
		for (int i = 0; i < this->numRows * this->numCols; i++)
			this->ptrMatrix[i] = sourceMatrix.ptrMatrix[i];
	}
}

template <class T>
Matrix<T>::Matrix(const char *fileName, int rows, int cols)
{
	this->numRows = rows;
	this->numCols = cols;
	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
	else
	{
		int i = 0;

		ifstream readFile(fileName);

		if (readFile.is_open())
		{

			while (readFile.good())
			{
				if (i > rows*cols - 1) break;
				readFile >> ptrMatrix[i];
				i++;
			}
			readFile.close();
		}
		else
			cout << "Unable to open file";
	}
}


//	Deallocate the memory for the matrix.
template <class T>
Matrix<T>::~Matrix()
{
	if (this->ptrMatrix != nullptr) delete[] ptrMatrix;
}



// Return the number of rows in the matrix.
template <class T>
int Matrix<T>::getNumRows()
{
	return this->numRows;
}


//	Return the number of Cols in the matrix.
template <class T>
int Matrix<T>::getNumCols()
{
	return this->numCols;
}

//	Get a single element from the matrix.
template <class T>
T Matrix<T>::getItem(int row, int col)
{
	if (this->ptrMatrix != nullptr)
		return ptrMatrix[row * this->numCols + col];
	else
		throw std::bad_alloc();
}


// Set a single element in the matrix
template <class T>
void Matrix<T>::setItem(int row, int col, T value)
{
	if (this->ptrMatrix != nullptr)
		ptrMatrix[row * this->numCols + col] = value;
	else
		throw std::bad_alloc();
}


//	Fill the matrix with a single value.
template <class T>
void Matrix<T>::fillMatrix(T value)
{
	for (int row = 0; row < this->numRows; ++row)
	{
		for (int col = 0; col < this->numCols; ++col)
			setItem(row, col, value);
	}
}

// Print all values inside matrix.
template <class T>
void Matrix<T>::printMatrix()
{
	for (int row = 0; row < this->numRows; ++row)
	{
		for (int col = 0; col < this->numCols; ++col)
			cout << getItem(row, col) << "\t";
		cout << endl;
	}
	cout << endl;
}

// Prints custom size matrix to the screen.
template <class T>
void Matrix<T>::printSubMatrix(int nrow, int ncol, int height, int width) {
	for (int row = nrow; row < nrow + width; ++row)
	{
		for (int col = ncol; col < ncol + height; ++col)
			cout << getItem(row, col) << "\t";
		cout << endl;
	}
	cout << endl;
}


//	create small matrix using provided size and coordinates.
template <class T>
Matrix<T> Matrix<T>::subMatrix(int nrow, int ncol, int height, int width) {

	Matrix<T> newMatrix(height, width);

	int counter = 0;

	for (int row = nrow; row < nrow + width; ++row)
	{
		for (int col = ncol; col < ncol + height; ++col) {
			newMatrix.setItem(0, counter, getItem(row, col));
			counter++;
		}
	}
	return newMatrix;
}


//	= assignment operator to deep copy the matrix data.
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& sourceMatrix)
{
	// If we are assigning to ourself i.e. m1 = m1
	if (this == &sourceMatrix)
		return *this;  // Return a pointer to ourselves.

	numRows = sourceMatrix.numRows;
	numCols = sourceMatrix.numCols;

	// Clear any already allocated memory.
	if (this->ptrMatrix != nullptr) delete[] ptrMatrix;

	// Allocate the right amount of memory for the deep copy of the data.
	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols];

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure.
	else
	{
		// Copy source data to destination.
		for (int i = 0; i < this->numRows * this->numCols; i++)
			this->ptrMatrix[i] = sourceMatrix.ptrMatrix[i];
	}
	// Return a pointer to the copied matrix object.
	return *this;
}

// * assignment operator to deep copy the matrix data.
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& sourceMatrix)
{

	if (this->numRows != sourceMatrix.numRows || this->numCols != sourceMatrix.numCols)
		throw(std::runtime_error("Subtraction error matrix dimensions do not match!!"));

	// Allocate the right amount of memory for the new matrix of multiplyed data
	Matrix<T> newMatrix(this->numRows, this->numCols);


	for (int row = 0; row < this->numRows; ++row)   
	{
		for (int col = 0; col < this->numCols; ++col)
			newMatrix.ptrMatrix[row * this->numCols + col] = ptrMatrix[row * this->numCols + col] * sourceMatrix.ptrMatrix[row * this->numCols + col];
	}


	// Return a matrix object.
	return newMatrix;
}


//	 - subtraction operator.
template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& sourceMatrix)
{

	if (this->numRows != sourceMatrix.numRows || this->numCols != sourceMatrix.numCols)
		throw(std::runtime_error("Subtraction error matrix dimensions do not match!!"));

	// Allocate the right amount of memory for the new matrix of subtracted data
	Matrix<T> newMatrix(this->numRows, this->numCols);


	for (int row = 0; row < this->numRows; ++row)   // Print the table
	{
		for (int col = 0; col < this->numCols; ++col)
			newMatrix.ptrMatrix[row * this->numCols + col] = ptrMatrix[row * this->numCols + col] - sourceMatrix.ptrMatrix[row * this->numCols + col];
	}


	// Return a matrix object uses copy constructor to do this
	return newMatrix;
}


//	Returns the matrix average.
template <class T>
T Matrix<T>::average(int startRow, int startCol, int width, int height)
{
	T mSum = 0;
	for (int row = startRow; row < width + startRow; ++row)   // Print the table
	{
		for (int col = startCol; col < height + startCol; ++col)
			mSum += getItem(row, col);
	}
	int itemCount = height * width;

	return (T)(mSum / (double)itemCount);
}


//	Returns matrix sum.
template <class T>
T Matrix<T>::sum(int startRow, int startCol, int width, int height)
{
	T mSum = 0;
	for (int row = startRow; row < width + startRow; ++row)   // Print the table
	{
		for (int col = startCol; col < height + startCol; ++col)
			mSum += getItem(row, col);
	}

	return mSum;
}


//	Square method squares each matrix element by its self returning a new matrix with the result.
template <class T>
Matrix<T> Matrix<T>::square()
{
	// Allocate the new matrix for squared data.
	Matrix<T> newMatrix(this->numRows, this->numCols);

	for (int row = 0; row < this->numRows; ++row)   // Print the table.
	{
		for (int col = 0; col < this->numCols; ++col)
			newMatrix.ptrMatrix[row * this->numCols + col] = ptrMatrix[row * this->numCols + col] * ptrMatrix[row * this->numCols + col];
	}

	// Return a matrix object uses copy constructor to do this.
	return newMatrix;
}

//	Saves the image with specified name.
template <class T>
void Matrix<T>::saveImage(const char *fileName, int Q)
{
	int index = 0;

	ofstream myfile;

	int number_of_items = this->getNumRows() * this->getNumCols();

	unsigned char *image;

	image = (unsigned char *) new unsigned char[number_of_items];

	// convert the integer values to unsigned char.

	for (int row = 0; row < this->getNumRows(); row++)   // Print the table.
	{
		for (int col = 0; col < this->getNumCols(); col++)
		{
			image[index] = (unsigned char)this->getItem(row, col);
			index++;
		}
	}


	myfile.open(fileName, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << fileName << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << this->getNumCols() << " " << this->getNumRows() << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), number_of_items * sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << fileName << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;
}

//	Denoising the matrix.
//	Turns all elements with grayscale value smaller than 170 to white pixels and all elements with
//	grayscale value larger or equal to 170 to black pixels.
template <class T>
Matrix<T> Matrix<T>::denoise() {

	Matrix<T> newMatrix(this->numRows, this->numCols);

	for (int row = 0; row < this->numRows; ++row)   // Print the table
	{
		for (int col = 0; col < this->numCols; ++col) {
			if (getItem(row, col)<170) {
				newMatrix.setItem(row, col, 0); // set to black (0).
			}
			if (getItem(row, col) >= 170) {
				newMatrix.setItem(row, col, 255); // set to white (255).
			}
		}
	}

	return newMatrix;
}


//	Devides the image into 16x16 grid containing 256 sub-matrices(32x32).
template <class T>
std::vector<Matrix<T>> Matrix<T>::split() {

	vector<Matrix<T>> newVector;	//	initialize the vector containing of Matrices.

	// Increments by 32 pixels by width and height to right coordinates for subMatrix method.
	for (int row = 0; row < numRows; row += 32)
	{
		for (int col = 0; col < numCols; col += 32)
		{
			newVector.insert(newVector.end(), this->subMatrix(row, col, 32, 32));	//	subMatrix creates small, 32x32 matrix.
		}
	}
	return newVector;	// returns the vector.
}

// Sum of Square Differences
template <class T>
Matrix<T> Matrix<T>::reShuffle(Matrix<T> Goal) {

	// Vectors
	std::vector<Matrix<T>> goalVector;	// How its supposed to look.
	std::vector<Matrix<T>> shuffledVector;	// Current state.
	std::vector<Matrix<T>> reShuffledVector;	//	Reshuffled vector stores subMatrices in right order.

	// Matrices
	Matrix<T> newMatrix(LargeSize(), LargeSize());	// LargeSize() iherited by Controls.h.
	Matrix<T> scoreMatrix(SmallSize(), SmallSize());	// LargeSize() iherited by Controls.h.

	// Variables
	double score = 0;

	// Creates 16x16 grid.
	goalVector = Goal.split();
	shuffledVector = this->split();

	// Comparison
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			scoreMatrix = goalVector[i] - shuffledVector[j];	//	Substract matrices from each other and store in scoreMatrix.

			score = scoreMatrix.square().sum(0, 0, scoreMatrix.numRows, scoreMatrix.numCols);	//	Square the differences and sum the up to form a scalar.

			// The lower the score, the closer the match.
			if (score<5)
			{
				reShuffledVector.insert(reShuffledVector.end(), shuffledVector[j]);	// insert matched matrix at the end of vector.
				break;
			}
		}
	}

	// Restoring back to large Matrix(512,512).
	for (int row = 0; row < newMatrix.getNumRows(); row += 32)	//	increment row by 32.
	{
		for (int col = 0; col < newMatrix.getNumCols(); col += 32)	// increment col by 32.
		{
			// Loop through subMatrix(32x32).
			for (int nrow = 0; nrow < 32; nrow++)
			{
				for (int ncol = 0; ncol < 32; ncol++)
				{
					newMatrix.setItem(row + nrow, col + ncol, reShuffledVector[0].getItem(nrow, ncol));	//	Set values from aproptiate coordinates.
				}
			}
			reShuffledVector.erase(reShuffledVector.begin());	//	Empty first Matrix so we can restore next subMatrix.
		}
	}

	return newMatrix;
}

// Normalised Cross-Correlation.
template <class T>
Matrix<T> Matrix<T>::normalisedCorrelation(Matrix<T> Goal) {

	// Vectors
	vector<Matrix<T>> I;	//	Shuffled image.
	vector<Matrix<T>> X;	//	Denoised-unshuffled image.
	vector<Matrix<T>> reShuffledVector;	// Image put back together into a vector.

	// Matrices
	// Note! LargeSize() is inherited from Controls class.
	Matrix<T> newMatrix(LargeSize(), LargeSize());	// return value (Matrix re-shuffled).
	Matrix<T> tempMatrix(SmallSize(), SmallSize());	// Used for various purpouses in calculations. IMPORTANT! tempMatrix is often over-written.
	Matrix<T> xSubstracted(SmallSize(), SmallSize());	//	Used to substract from its own mean.
	Matrix<T> iSubstracted(SmallSize(), SmallSize());	//	Used to substract from its own mean.

	// Variables
	double NC = 0;	//	Score. Value used to determine the match.
	double SumIX = 0;	//	Upper side of the equation. 
	double xMean = 0;	//	Mean (I).
	double iMean = 0;	//	Mean (X).
	double sqrtIX = 0;	//	Lower side of the equation. Square root.
	double prevNC = 0;	//	Previous score.

	int index = 0;	// Used to determine position of the best match.

	bool flag = false;	// In case no perfect match is found.

	// Creates 16x16 grid.
	X = Goal.split();
	I = this->split();

	// Compare
	for (int i = 0; i < 256; i++)
	{
		// Calculations
		xMean = X[i].average(0, 0, tempMatrix.numRows, tempMatrix.numCols);	// Mean of de-noised subMatrix at position 'i'.
		tempMatrix.fillMatrix(xMean);	//	Fill tempMatrix with xMean.
		xSubstracted = tempMatrix - X[i];	// Substract the subMatrix from its mean.

		//	Changing values.
		prevNC = -1;	//	Smallest value possible set for first iteration of 'j'.
		index = 0;	//	match position.
		flag = false;	// used in case no perfect match found.

		for (int j = 0; j < 256; j++)
		{
			//	Mean
			iMean = I[j].average(0, 0, tempMatrix.numRows, tempMatrix.numCols);	// Mean of shuffled subMatrix at position 'j'.

			//	Substract.
			tempMatrix.fillMatrix(iMean);	//	Fill tempMatrix with iMean.
			iSubstracted = tempMatrix - I[j];	// Substract the subMatrix from its mean.
			
			//	IF XMEAN - IMEAN = 0, THAT MEANS BOTH MATRICES ARE EXATLY THE SAME. NO NEED FOR FURTHER CALCULATIONS.
			if (xMean-iMean==0)
			{
				reShuffledVector.insert(reShuffledVector.end(), I[j]);	//	Store value.
				flag = true;
				break;
			}

			// SUM(I*X). TOP OF THE EQUASION.
			tempMatrix = xSubstracted * iSubstracted;
			SumIX = tempMatrix.sum(0, 0, tempMatrix.numRows, tempMatrix.numCols);

			//RSqr(Sum(Sqr(I))*(Sum(Sqr(X))). BOTTOM OF THE EXUATION.
			sqrtIX = sqrt(xSubstracted.square().sum(0, 0, tempMatrix.numRows, tempMatrix.numCols)*(iSubstracted.square().sum(0, 0, tempMatrix.numRows, tempMatrix.numCols)));
			
			//	IN CASE OF DIVIDE BY ZERO ERROR.
			if (sqrtIX == 0)
			{
				sqrtIX = 0.0001;
			}

			NC = SumIX / sqrtIX;

			//	Perfect match.
			if (NC==1)
			{
				reShuffledVector.insert(reShuffledVector.end(), I[j]);	// store value.
				flag = true;
				break;
			}

			//	Used to determine closest match possible, given that previous conditions have not been matched.
			if (NC > prevNC) {
				index = j;
				prevNC = NC;
			}

			
		}
		//reShuffledVector.insert(reShuffledVector.end(), I[index]);
		if (flag==false)
		{
			reShuffledVector.insert(reShuffledVector.end(), I[index]);
		}
	}

	// Restoring back to large Matrix(512,512).
	for (int row = 0; row < newMatrix.getNumRows(); row += 32)
	{
		for (int col = 0; col < newMatrix.getNumCols(); col += 32)
		{
			// Loop through subMatrix(32x32).
			for (int nrow = 0; nrow < 32; nrow++)
			{
				for (int ncol = 0; ncol < 32; ncol++)
				{
					newMatrix.setItem(row + nrow, col + ncol, reShuffledVector[0].getItem(nrow, ncol));	//	Set values from aproptiate coordinates.
				}
			}
			reShuffledVector.erase(reShuffledVector.begin());	//	Empty first Matrix so we can restore next subMatrix.
		}
	}

	return newMatrix;
}


