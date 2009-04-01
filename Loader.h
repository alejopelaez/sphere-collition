#ifndef IMAGE_LOADER
#define IMAGE_LOADER

#include <assert.h>
#include <fstream>

//Represents an image
class Image {
private:
    char* pixels;
    int width;
    int height;
public:
		Image(char* ps, int w, int h);
		~Image();
};

//Reads a bitmap image from file.
Image* loadBMP(const char* filename);

#endif
