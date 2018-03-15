#pragma once
template <class T>
class ImageControls
{
public:
	ImageControls();
	~ImageControls();

	void saveImage(const char *fileName, int Q);
};

