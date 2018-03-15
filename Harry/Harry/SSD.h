#pragma once

#include "stdafx.h" 
#include "Matrix.h"


// HEADER
template <class T>
class SSD : public Matrix<T>
{

public:
	using Matrix<T>::Matrix;
	SSD<T>& operator=(const SSD<T>& sourceSSD);
	SSD<T> reShuffle(SSD<T> Goal);
};

