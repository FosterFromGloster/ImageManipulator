#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>
#include "ImageHeader.h"


using namespace fstjam001;
using namespace std;

Image fstjam001::Image::operator=(Image&& oldImage){//copy constructor

	if (this == &oldImage){
		return *this;
	}
	else{
		width = oldImage.width;
		height = oldImage.height;
		Image::iterator beg = this->begin();
		Image::iterator end = this->end();
		Image::iterator inStart = oldImage.begin();
		Image::iterator inEnd = oldImage.end();
		while (beg != end) {
			++beg;
			++inStart;
		}
	}
	cout << "Finished" << endl;
	return *this;
}

bool fstjam001::Image::operator==(Image& otherImage){//equals constructor to check if images are the same
	
	Image::iterator beg = this->begin();//retrieve iterator containing pointer to the first char
	Image::iterator end = this->end();
	Image::iterator inStart = otherImage.begin();//get the second iterator
	Image::iterator inEnd = otherImage.end();

	bool checker = false;
	
	while (beg != end) {//loop over the char array/ image data
		if(*beg == *inStart){//check the chars are equivilant
			checker = true;		
		}
		else{
			return false; 		
		}
		++beg;
		++inStart;
	
	}
	
	return checker;
}

fstjam001::Image::Image(const Image& oldImage){//move constructor

}

Image fstjam001::Image::operator*(int t){//threshold function
	cout << "threshold" << endl;
	Image::iterator beg = this->begin(), end = this->end();
	int count = 0;
	while (beg != end) {
		count = count + 1;
		int pixelValueA = *beg;//get the value of the char
		if (pixelValueA > t){
			unsigned char c = (unsigned char)255;
			*beg=c;
		}
		else{
			unsigned char c = (unsigned char)0;
			*beg=c;
		}
		++beg;
	}                              
	cout << "Finished" << endl;
	return *this;
}

Image fstjam001::Image::operator-(Image& otherImage){//subtract function
	cout << "subtracting" << endl;
	Image::iterator beg = this->begin(), end = this->end();
	Image::iterator inStart = otherImage.begin(), inEnd = otherImage.end();
	int count = 0;
	while (beg != end) {
		count = count + 1;
		int pixelValueA = *beg;
		int pixelValueB = *inStart;
		int diff = pixelValueA - pixelValueB;
		if(diff<0){//clamp the lower point no need to do the higher value
			diff = 0;		
		}
		unsigned char c = (unsigned char)(diff);//get the difference in pixel values back to a cha
		*beg=c;// change the value of the underlying data for which the iterator pointer points to
		++beg;
		++inStart;
	}
	cout << "Finished" << endl;
	return *this;
}

Image fstjam001::Image::operator/(Image& otherImage){//mask function
	cout << "Masking" << endl;
	Image::iterator beg = this->begin(), end = this->end();
	Image::iterator inStart = otherImage.begin(), inEnd = otherImage.end();
	int count = 0;
	while (beg != end) {
		count = count + 1;//just for my own reference no use in program. used to track data
		int pixelValueA = *beg;
		int pixelValueB = *inStart;

		if (pixelValueB == 255){//if the value lies within the mask
			unsigned char c = (unsigned char) pixelValueA;
			*beg=c;
		}
		else{
			unsigned char c = (unsigned char)0;
			*beg=c;
		}
		++beg;
		++inStart;
	}
	cout << "Finished" << endl;
	return *this;
}

Image fstjam001::Image::operator+(Image& otherImage){//addition operator
	cout << "Adding" << endl;
	Image::iterator beg = this->begin(), end = this->end();
	Image::iterator inStart = otherImage.begin(), inEnd = otherImage.end();
	int count = 0;
	while (beg != end) {
		count = count + 1;
		int pixelValueA = *beg;
		int pixelValueB = *inStart;
		int newPixalValue = int(pixelValueA + pixelValueB);
		if (newPixalValue < 0){//clamp the values based on 0 and range read in from the header 
			newPixalValue = 0;
		}
		else if (newPixalValue > range){
			newPixalValue = 255;
		}
		unsigned char c = (unsigned char) newPixalValue;
		*beg=c;
		++beg;
		++inStart;
	}
	cout << "Finished" << endl;
	return *this;
}
Image fstjam001::Image::operator!(){// invert operator
	cout << "inverting" << endl;
	Image::iterator beg = this->begin();
	Image::iterator end = this->end();
	int count = 0;
	while (beg != end) {
		count = count + 1;
		int pixelValue = (int)*beg;//cast to get the integer value of the char
		if (pixelValue < 0){
			pixelValue = 0;
		}
		else if (pixelValue > range){//clamping again
			pixelValue = 255;
		}
		unsigned char c = (unsigned char)(255 - pixelValue);//invert
		*beg=c;
		++beg;//move to next value
	}
	cout << "Finished" << endl;
	return *this;
}

fstjam001::Image::Image(){//default constructor

}

fstjam001::Image::~Image(){//destructor no need as memory freed when image goes out of scope it is deleted
//unique pointers delete themselves
}

Image & operator>>(ifstream & ifstr, Image & image){//overloaded >> operator to load in data from file to image.
	string line = "";
	int counter = 0;
	string name;
	int rows;
	int columns;
	int theLength =0 ;

	if (ifstr.is_open())
	{
		while (getline(ifstr, line))
		{
			if (line.at(0) == '#'){//skip commentted lines
				continue;
			}
			else if (counter == 0){//get the name default P5
				name = line;
				counter = counter + 1;
			}
			else if (counter == 1){//get the width/rows and columns/height
				std::istringstream buffer(line);
				buffer>>rows>>std::ws>>columns;
				image.height =columns;
				image.width = rows;
				counter = counter + 1;
			}
			else if (counter == 2){//get the range
				image.range = atoi(line.c_str());//convert to int
				counter = counter + 1;
				break;
			}
		}

		int size = rows*columns;
		image.data = unique_ptr<unsigned char[]>(new unsigned char[size]);//set the unique pointer to point to an underlying array
		ifstr.read((char *)image.data.get(), size);//read in the rest of the file and apply pointer

		ifstr.close();
	}
	else{
		cout<<"Failed to load the file"<<endl;	
	}
	cout<<"Loaded"<<endl;
	return image;
}

ofstream & operator<<(ofstream & ostr, Image & image){//overloaded operator to save the image
	cout << "Saving" << endl;
	ostr<<"P5"<<endl;//next 3 lines are for the header
	ostr<<image.width <<" "<< image.height<<endl;
	ostr<<image.range<<endl;
	ostr.write(reinterpret_cast<const char*> (image.data.get()),((image.width)*(image.height)));//write the underlying char array  to file
	cout << "Saved" << endl;
	return ostr;
}

void fstjam001::Image::load(std::string file){
	ifstream imageFile(file, ios::binary);
	imageFile >> *this;
}

void fstjam001::Image::save(std::string file){
	ofstream outfile(file.c_str(),ios::out | ios::binary);
	outfile << *this;
}



