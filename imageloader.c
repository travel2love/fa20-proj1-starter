/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	char name[20];
	int cols = 0, rows = 0, number = 0;
	fscanf(fp, "%s\n%d %d\n%d", name, &cols, &rows, &number);
	Image *images = (Image *)malloc(sizeof(Color*)*rows*cols);
	images->rows = rows;
	images->cols = cols;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			Color *colorptr, color;
			colorptr = &color;
			fscanf(fp, "%hhd %hhd %hhd", &color.R, &color.G, &color.B);
			images->image = &color;
		}
	}
	return images;
	fclose(fp);
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
		
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	free(image);
}
