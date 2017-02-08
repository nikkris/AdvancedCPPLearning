#include"STLtest.h"

/* Generate a vector of type image class
	1. Push values in the vector
	2. Sequential display/ access of the elements using iterator
	3. Random access of elements*/
void vectorDemo()
{
	image_vec Img;
	int num_pixels = 10;

	//1. Push values in the vector
	// generate random pixels
	Img.generate_random(num_pixels);

	
	// 2. Sequential display/ access of the elements using iterator
	Img.display();

	// 3. Random access of elements
	// two ways of accessing randome element
	
	
	// access 6th element
	int loc = 5;
	Img.display(loc);
	loc = 25;
	Img.display(loc);
	loc = 9;
	Img.display(loc);

	// assign

}

image_vec::image_vec()
{
	cout << endl << "Image vector constructor called";
	cout << endl << "Type of iterator = " << typeid(p_no).name();
	cout << endl << "Initial image size = " << image.size();
	cout << endl << "Initial image capacity = " << image.capacity();
}

image_vec::~image_vec()
{
	cout << endl << "Image vector destructor called";
}

int image_vec::generate_random(int num_pixels)
{
	pixel rand_pixel;
	default_random_engine int_gen;
	default_random_engine alpha_gen;
	uniform_int_distribution<int> uni_int_dist(0, 255);
	uniform_real_distribution<float> uni_alpha_dist(0.0, 1.0);
	for (int i = 0; i < num_pixels; i++)
	{
		rand_pixel.red = (unsigned char)uni_int_dist(int_gen);
		rand_pixel.blue = (unsigned char)uni_int_dist(int_gen);
		rand_pixel.green = (unsigned char)uni_int_dist(int_gen);
		rand_pixel.alpha = uni_alpha_dist(alpha_gen);
		image.push_back(rand_pixel);
		cout << endl << "Current image size = " << image.size();
		cout << endl << "Current image capacity = " << image.capacity();
	}

	return 0;
}

int image_vec::display()
{
	int count = 0;
	for (p_no = image.begin(); p_no != image.end(); p_no++)
	{
		cout << endl << "Values inside pixel number " << count;
		cout << endl << "Red = " << (int)p_no->red;
		cout << endl << "Green = " << (int)p_no->green;
		cout << endl << "Blue = " << (int)p_no->blue;
		cout << endl << "Alpha = " << p_no->alpha;
		cout << endl;
		count++;
	}
	return 0;
}

int image_vec::display(int count)
{
	cout << endl;
	try
	{
		// 2) use at(loc)/ [loc]: this returns the object at loc 
		cout << endl << "Values inside pixel number " << count;
		cout << endl << "Red = " << (int)image.at(count).red;
		cout << endl << "Green = " << (int)image.at(count).green;
		cout << endl << "Blue = " << (int)image.at(count).blue;
		cout << endl << "Alpha = " << image.at(count).alpha;
		return 0;
	}
	catch(...)
	{
		cout << endl << "Out of bound exception";
		return -1;
	}
	/*
	// 1) get first pointer + add location
	p_no = image.begin() + count;
	cout << endl << "Values inside pixel number " << count;
	cout << endl << "Red = " << (int)p_no->red;
	cout << endl << "Green = " << (int)p_no->green;
	cout << endl << "Blue = " << (int)p_no->blue;
	cout << endl << "Alpha = " << p_no->alpha;
	*/
}