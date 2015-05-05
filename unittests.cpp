#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ImageHeader.h"

using namespace fstjam001;

TEST_CASE( "Testing equals overloaded operator method to use in proceeding tests", "[Image]" ) {
	Image LennaOne;
    	LennaOne.load("Lenna");
	Image LennaTwo;
    	LennaTwo.load("Lenna");
	REQUIRE(LennaOne  == LennaTwo);
}

TEST_CASE( "Testing clamping", "[Image]" ) {
	bool checker = false;
	Image Lenna;
	Lenna.load("Lenna");
	Image LennaTwo;
	LennaTwo.load("Lenna_hat_mask");
	Lenna+LennaTwo;
	Image::iterator beg = Lenna.begin();
	Image::iterator end = Lenna.end();
	while (beg != end) {
		if(((int)*beg)>255){
			checker = true;		
		}
		else if(((int)*beg)<0){
			checker = true;		
		}
		++beg;
	
	}
        REQUIRE(checker  == false);
}

TEST_CASE( "Testing image transformations", "[Image]" ) {

    Image Lenna;
    Lenna.load("Lenna");

    SECTION( "Threshold 100" ) {
	Image ThresholdLenna;
	ThresholdLenna.load("Lennathreshold");
	Lenna * 100;
        REQUIRE(ThresholdLenna  == Lenna);
    }
    SECTION( "Inversion" ) {
        Image InversionLenna;
	InversionLenna.load("LennaInversion");
	!Lenna;
        REQUIRE(InversionLenna  == Lenna);
    }
    SECTION( "Masking" ) {
        Image MaskLenna;
	MaskLenna.load("LennaMask");
	Image mask;
	mask.load("Lenna_hat_mask");
	Lenna/mask;
        REQUIRE(MaskLenna  == Lenna);
    }
    SECTION( "Addition" ) {
        Image AdditionLenna;
	AdditionLenna.load("LennaAddition");
	Image LennaTwo;
	LennaTwo.load("Lenna_hat_mask");
	Lenna+LennaTwo;
        REQUIRE(AdditionLenna  == Lenna);
    }
    SECTION("Subtraction" ) {
        Image SubtractionLenna;
	SubtractionLenna.load("LennaSubtraction");
	Image LennaTwo;
	LennaTwo.load("Lenna_hat_mask");
	Lenna-LennaTwo;
        REQUIRE(SubtractionLenna  == Lenna);
    }
}






