#include "stdafx.h"
#include "SSD.h"
#include <stdexcept>
#include <fstream> 
#include <vector>
#include <iostream>

using namespace std;

template <class T>
SSD<T>& SSD<T>::operator=(const SSD<T>& sourceMatrix)
{
	// If we are assigning to ourself i.e. m1 = m1
	if (this == &sourceMatrix)
		return *this;  // Return a pointer to ourselves (why copy yourself to yourself)

	numRows = sourceMatrix.numRows;
	numCols = sourceMatrix.numCols;

	// Clear any already allocated memory
	if (this->ptrMatrix != nullptr) delete[] ptrMatrix;

	// Allocate the right amount of memory for the deep copy of the data
	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols];

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
	else
	{
		// Copy source data to destination
		for (int i = 0; i < this->numRows * this->numCols; i++)
			this->ptrMatrix[i] = sourceMatrix.ptrMatrix[i];
	}
	// Return a pointer to the copied matrix object
	return *this;
}

template <class T>
SSD<T> SSD<T>::reShuffle(SSD<T> Goal) {
	vector<SSD<T>> goalVector;
	vector<SSD<T>> shuffledVector;
	vector<SSD<T>> reShuffledVector;
	SSD<T> newMatrix(512, 512);
	SSD<T> scoreMatrix(32, 32);
	double score = 0;

	goalVector = Goal.split();
	shuffledVector = this->split();

	/*
	*	ReShuffle
	*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			scoreMatrix = goalVector[i] - shuffledVector[j];
			score = scoreMatrix.square().sum(0, 0, scoreMatrix.numRows, scoreMatrix.numCols);
			if (score<5)
			{
				reShuffledVector.insert(reShuffledVector.end(), shuffledVector[j]);
				break;
			}
		}
	}
	/*
	*	Restore vector to Matrix(512,512)
	*/
	for (int row = 0; row < newMatrix.getNumRows(); row += 32)
	{
		for (int col = 0; col < newMatrix.getNumCols(); col += 32)
		{
			for (int nrow = 0; nrow < 32; nrow++)
			{
				for (int ncol = 0; ncol < 32; ncol++)
				{
					newMatrix.setItem(row + nrow, col + ncol, reShuffledVector[0].getItem(nrow, ncol));
				}
			}
			reShuffledVector.erase(reShuffledVector.begin());
		}
	}

	return newMatrix;
}