
#include <iostream>
using namespace std;

/*class Rectangle {
    int width, height;
  public:
    void set_values (int,int);
    int area() {return width*height;}
};

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}*/

	class FileIO {
	public:
		std::string openFile( );


	};

	std::string openFile(std::string fileName)
	{
		std::ifstream file(fileName);
	}