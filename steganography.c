/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *color = (Color*)malloc(sizeof(Color));
	Image *images = image;
	Color **images_0 = images->image;
	Color *images_1 = *images_0;
	int B = 0, image_col = image->cols;
	int k = image_col*row + col;
	B = (images_1+k)->B;
	B = B&1;
	if(B == 0) {
		color->R = 0;
		color->G = 0;
		color->B = 0;
	} else {
		color->R = 255;
		color->G = 255;
		color->B = 255;
	}
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *images = image;
	int rows = images->rows;
	int cols = images->cols;
	Image *new_image = (Image *)malloc(sizeof(Color *)*rows*cols);
	new_image->rows = rows;
	new_image->cols = cols;
	Color **color_star;
	new_image->image = color_star;
	Color *new_colorptr[cols*rows], new_color[cols*rows];
       	int k = 0;	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			Color *color = evaluateOnePixel(images, i, j);
			color_star = &color;
//			*color_star += 1;
			new_color[k] = *color;
			new_colorptr[k] = &new_color[k];
			k += 1;
		}
	}
	new_image->image = &new_colorptr;
	return new_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		return -1;
	}
	Image *image = readData(argv[1]);
	Image *image_new = steganography(image);
	writeData(image_new);
	freeImage(image);
	freeImage(image_new);
	return 0;
	
}
