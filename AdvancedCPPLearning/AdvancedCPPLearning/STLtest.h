#pragma once

#include<vector>
#include<iostream>
using namespace std;

#include<random>
#include<typeinfo>

void vectorDemo();

class pixel
{
public:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	float alpha;			// min = 0; max = 1

};

class image_vec
{
	vector<pixel> image;
	vector <pixel> ::iterator p_no;
	int num_pixels;

public:
	image_vec();
	~image_vec();
	int generate_random(int);
	int display();
	int display(int);


};
