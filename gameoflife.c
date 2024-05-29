/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Image *images = image;
	Color **images_0 = images->image;
	Color *images_1 = *images_0;
	int R = 0, G = 0, B = 0;
	int image_col = image->cols;
	int k = image_col*row + col;
	R = (images_1+k)->R, G = (images_1+k)->G, B = (images_1+k)->B;
	Color neighbor[8];
	Color *color_new = (Color*)malloc(sizeof(Color));
	//the first neighbor
	k = image_col*(row - 1) + col - 1;
	if(k >= 0) {
		neighbor[0].R = (images_1+k)->R;
		neighbor[0].G = (images_1+k)->G;
		neighbor[0].B = (images_1+k)->B;}
	else {
		neighbor[0].R = 0;
		neighbor[0].G = 0;
		neighbor[0].B = 0;
	}
	//the second neighbor
	k = image_col*(row - 1) + col;
	if(k >= 0) {
		neighbor[1].R = (images_1+k)->R;
		neighbor[1].G = (images_1+k)->G;
		neighbor[1].B = (images_1+k)->B;}
	else {
		neighbor[1].R = 0;
		neighbor[1].G = 0;
		neighbor[1].B = 0;
	}
	//the third neighbor
	k = image_col*(row - 1) + col + 1;
	if(k >= 0) {
		neighbor[2].R = (images_1+k)->R;
		neighbor[2].G = (images_1+k)->G;
		neighbor[2].B = (images_1+k)->B;}
	else {
		neighbor[2].R = 0;
		neighbor[2].G = 0;
		neighbor[2].B = 0;
	}
	//the fourth neighbor
	k = image_col*row + col - 1;
	if(k >= 0) {
		neighbor[3].R = (images_1+k)->R;
		neighbor[3].G = (images_1+k)->G;
		neighbor[3].B = (images_1+k)->B;}
	else {
		neighbor[3].R = 0;
		neighbor[3].G = 0;
		neighbor[3].B = 0;
	}
	//the fifth neighbor
	k = image_col*row + col + 1;
	if(k >= 0) {
		neighbor[4].R = (images_1+k)->R;
		neighbor[4].G = (images_1+k)->G;
		neighbor[4].B = (images_1+k)->B;}
	else {
		neighbor[4].R = 0;
		neighbor[4].G = 0;
		neighbor[4].B = 0;
	}
	//the sixth neighbor
	k = image_col*(row + 1) + col - 1;
	if(k >= 0) {
		neighbor[5].R = (images_1+k)->R;
		neighbor[5].G = (images_1+k)->G;
		neighbor[5].B = (images_1+k)->B;}
	else {
		neighbor[5].R = 0;
		neighbor[5].G = 0;
		neighbor[5].B = 0;
	 }
	//the seventh neighbor
	k = image_col*(row + 1) + col;
	if(k >= 0) {
		neighbor[6].R = (images_1+k)->R;
		neighbor[6].G = (images_1+k)->G;
		neighbor[6].B = (images_1+k)->B;}
	else {
		neighbor[6].R = 0;
		neighbor[6].G = 0;
		neighbor[6].B = 0;
	}
	//the eighth neighbor
	k = image_col*(row + 1) + col + 1;
	if(k >= 0) {
		neighbor[7].R = (images_1+k)->R;
		neighbor[7].G = (images_1+k)->G;
		neighbor[7].B = (images_1+k)->B;}
	else {
		neighbor[7].R = 0;
		neighbor[7].G = 0;
		neighbor[7].B = 0;
	}
	//iterate the neighbor[] to calculate the sum of neighbor
	
	//generate the color
	int R_new = 0, G_new = 0, B_new = 0;
	int R_sum[8] = {}, G_sum[8] = {}, B_sum[8] = {};
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			R_sum[i] = ((neighbor[j].R >> i)&1) + R_sum[i];
			G_sum[i] = ((neighbor[j].G >> i)&1) + G_sum[i];
			B_sum[i] = ((neighbor[j].B >> i)&1) + B_sum[i];
		}
	}
	//R
	for(int i = 0; i < 8; i++) {
		if(((R>>i)&1) == 1 && ((rule>>(9+R_sum[i])&1) == 1)) {
			int p = 1, q = 2;
			for(int j = 0; j < i; j++) {
				p = p * q;
			}
			R_new = R_new | p;
			}
		else if(((R>>i)&1) == 0 && (((rule>>R_sum[i])&1) == 1)) {
			int p = 1, q = 2;
                        for(int j = 0; j < i; j++) {
                                p = p * q;
                        }
			R_new = R_new | p;
			}
		else {
			R_new = R_new | 0x0000;
			}
		}
	//G
	for(int i = 0; i < 8; i++) {
		if(((G>>i)&1) == 1 && ((rule>>(9+G_sum[i])&1) == 1)) {
			int p = 1, q = 2;
                        for(int j = 0; j < i; j++) {
                                p = p * q;
                        }
			G_new = G_new | p;
			}
		else if(((G>>i)&1) == 0 && (((rule>>G_sum[i])&1) == 1)) {
			int p = 1, q = 2;
                        for(int j = 0; j < i; j++) {
                                p = p * q;
                        }
			G_new = G_new | p;
			}
		else {
			G_new = G_new | 0x0000;
			}
		}
	//B
	for(int i = 0; i < 8; i++) {
		if(((B>>i)&1) == 1 && ((rule>>(9+B_sum[i])&1) == 1)) {
			int p = 1, q = 2;
                        for(int j = 0; j < i; j++) {
                                p = p * q;
                        }
			B_new = B_new | p;
			}
		else if(((B>>i)&1) == 0 && (((rule>>B_sum[i])&1) == 1)) {
			int p = 1, q = 2;
                        for(int j = 0; j < i; j++) {
                                p = p * q;
                        }
			B_new = B_new | p;
			}
		else {
			B_new = B_new | 0x0000;
			}
		}
	//set new color
	color_new->R = R_new;
	color_new->G = G_new;
	color_new->B = B_new;
	return color_new;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
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
			Color *color = evaluateOneCell(images, i, j, rule);
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
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		return -1;
	}
	Image *image = readData(argv[1]);
	char *example;
	int num = strtol(argv[2], &example, 0);
	Image *image_new = life(image, num);
	writeData(image_new);
	freeImage(image);
	freeImage(image_new);
	return 0;

}
