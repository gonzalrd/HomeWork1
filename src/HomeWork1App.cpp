/**
@author Raquel Gonzalez
@Date 08-31-2012
**/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class HomeWork1App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	
  private:
	Surface* mySurface_; //The Surface object whose pixel array we will modify
  
	//Track how many frames we have shown, for animatino purposes
	int frame_number_;
	boost::posix_time::ptime app_start_time_;

	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; //Must be the next power of 2 bigger or equal to app dimensions

	/** This satisfies the "rectangle" requirement, goal A.1
	 */
	void drawRectangles(uint8_t* pixels, int x1, int y1,  int rect_width, int rect_height, Color8u fill);
};

void HomeWork1App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void HomeWork1App::drawRectangles(uint8_t* pixels, int x1, int y1, int rect_width, int rect_height, Color8u fill){

	Color8u c = Color8u(192,123,0);
	c.r = fill.r;
	c.b = fill.b;
	c.g = fill.g;

	

	for(int x = x1; x<rect_height; x++){
		for(int y = y1; y<rect_width; y++){
	pixels[3*(x + y*kTextureSize)] = c.r;
	pixels[3*(x + y*kTextureSize)+1] = c.g;
	pixels[3*(x + y*kTextureSize)+2] = c.b;
		}

	}
}

void HomeWork1App::setup()
{
	frame_number_=0;
		
   //This is the setup that everyone needs to do
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	
}

void HomeWork1App::mouseDown( MouseEvent event )
{

	//Get our array of pixel information
	uint8_t* dataArray = (*mySurface_).getData();

	int red = (rand() % 200 + 50);
	int blue = (rand() % 200 + 50);
	int green = (rand() % 200 + 50);

	Color8u fill1 = Color8u(red,green,blue);

	int xValue = (rand() % 400 + 50);
	int yValue = (rand() % 400 + 50);
	int width = (rand() % 400 + 200);
	int height = (rand() % 400 + 200);
	
	drawRectangles(dataArray,xValue,yValue,width,height, fill1);
	
}

void HomeWork1App::update()
{


	

		//Only save the first frame of drawing as output
	if(frame_number_ == 0){
		writeImage("raquelImage.png",*mySurface_);
		//We do this here, instead of setup, because we don't want to count the writeImage time in our estimate
		app_start_time_ = boost::posix_time::microsec_clock::local_time();
	}

	//keeps track of how many frames we have shown.
	frame_number_++;
	
	//For debugging: Print the actual frames per second
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration msdiff = now - app_start_time_;
    console() << (1000.0*frame_number_) / msdiff.total_milliseconds() << std::endl;
	

}

void HomeWork1App::draw()
{
	// clear out the window with black
	//Draw our texture to the screen, using graphics library
	gl::draw(*mySurface_);
	//gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HomeWork1App, RendererGl )
