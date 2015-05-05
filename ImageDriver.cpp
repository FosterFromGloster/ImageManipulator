#include "ImageHeader.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;
using namespace fstjam001;

int main(int argc, char** argv){

	Image imageOne;
	Image imageTwo;
	int imageCounter = 0;
	string outputImageName;
	bool add = false;
	bool subtract = false;
	bool invert = false;
	bool mask = false;
	bool threshold = false;
	int thresholdInteger = 0;
	cout<<argc<<endl;
	if (argc < 1){
		std::cout << "An incorrect number of parameters have been entered" << std::endl;
	}
	else{
		for (int i = 0; i < argc; ++i) {
			if (i == 0){
			}
			else if (i == 1){						
				if (string(argv[i]) == "-a"){
					cout<<"Add"<<endl;
					add = true;
				}
				else if (string(argv[i]) == "-s"){
					cout<<"Subtract"<<endl;
					subtract = true;
				}
				else if (string(argv[i]) == "-i"){
					cout<<"Invert"<<endl;
					invert = true;
				}
				else if (string(argv[i]) == "-l"){
					cout<<"Mask"<<endl;
					mask = true;
				}
				else if (string(argv[i]) == "-t"){
					cout<<"Threshold"<<endl;
					threshold = true;
				}
			}
			else if(i == 3 && threshold){
				cout<<"Threshold: "<<argv[i]<<endl;
				thresholdInteger = stoi(argv[i]);			
			}
			else if (i == 2){
				cout<<"Loading.."<<string(argv[i])<<endl;
				imageCounter = imageCounter + 1;
				imageOne.load(string(argv[i]));
				cout<<"Here"<<endl;
			}
			else if (i == 3){
				cout<<"Loading.."<<string(argv[i])<<endl;
				imageCounter = imageCounter + 1;
				imageTwo.load(string(argv[i]));
			}
		}
		cout<<imageCounter<<endl;
		if (add && imageCounter == 2){
			imageOne + imageTwo;
			imageOne.save("EdittedAddition.PGN");
		}
		else if (subtract && imageCounter == 2){
			imageOne - imageTwo;	
			imageOne.save("EdittedSubtraction.PGN");
		}
		else if (invert && imageCounter == 1){
			cout<<"Attempting to invert"<<endl;
			!imageOne;	
			imageOne.save("EdittedInvertion.PGN");
		}
		else if (mask && imageCounter == 2){
			cout<<"Attempting to mask"<<endl;
			imageOne/imageTwo;	
			imageOne.save("Mask.PGN");
		}
		else if (threshold && imageCounter == 1){
			cout<<"Attempting to thresh"<<endl;
			imageOne * thresholdInteger;
			imageOne.save("threshold.PGN");
		}
		else{
			cout<<"Incorrect flag format inputted"<<endl;		
		}
	
	}
}
