#include<string>
#include <memory>
#include <iostream>

using namespace std;

namespace fstjam001{


	class Image{

	public:

		int width, height;
		int range;
		std::unique_ptr<unsigned char[]> data;//pointer for the underlying array

		Image();
		~Image();

		Image(const Image& oldImage);
		Image operator =(Image&& oldImage);//overloaded operators for the image class
		Image operator +(Image& otherImage);
		Image operator -(Image& otherImage);
		Image operator !();
		Image operator /(Image& otherImage);
		Image operator *(int f);
		bool operator ==(Image& otherImage); 

		void load(string name);
		void save(string name);

		class iterator//iterator to move through data from image
		{
		private:
			unsigned char *ptr;
			friend class Image;

			iterator(unsigned char *p) : ptr(p) {}

		public:
			iterator(const iterator & rhs) : ptr(rhs.ptr) {}

			iterator & operator=(unsigned char newchar) 
			{
				ptr = &newchar;
				return *this;
			}
			unsigned char & operator*() const
			{
				return *ptr;
			}
			iterator & operator++()
			{
				++ptr;
				return *this;
			}
			iterator & operator--()
			{
				--ptr;
				return *this;
			}
			bool operator!=(const iterator & rhs)
			{
				if (rhs.ptr == ptr){
					return false;
				}
				else{
					return true;
				}
			}
		};

		iterator begin(void) { 
			return iterator(data.get());
		} 
		iterator end(void) {
			return iterator((data.get()+(height*width)));
		} 
	};


}
