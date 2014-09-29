#include <QCoreApplication>
#include "cvconvnet.h"
#include "opencv/highgui.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
        if (argc <=2 )
        {
                cerr << "Usage: " << endl << "\ttestimg <network.xml> <imagefile(s)>" << endl;
                return 1;
        }

        // Create empty net object
        CvConvNet net;

        // Source featuremap size
        CvSize inputsz = cvSize(32,32);

        // Load mnist.xml file into a std::string called xml
        ifstream ifs(argv[1]);
        string xml ( (istreambuf_iterator<char> (ifs)) , istreambuf_iterator<char>() );

        // Create network from XML string
        if ( !net.fromString(xml) )
        {
                cerr << "*** ERROR: Can't load net from XML" << endl << "Check file "<< argv[1] << endl;
                return 1;
        }

        // create some GUI
        cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
        cvMoveWindow("Image", inputsz.height, inputsz.width);
        CvFont font;
        cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0);

        // Grayscale img pointer
        IplImage* img;

        // Also create a color image (for display)
        IplImage *colorimg = cvCreateImage( inputsz, IPL_DEPTH_8U, 3 );

        // Cycle over input images
        for (int i=2; i<argc; i++)
        {
                // Load the image
                if ((img = cvLoadImage( argv[i], CV_LOAD_IMAGE_GRAYSCALE )) == NULL)
                {
                        cerr << "ERROR: Bad image file: " << argv[i] << endl;
                        break;
                }

                // Forward propagate the grayscale (8 bit) image and get the value
                ostringstream val;
                val << (int) net.fprop(img);

                // Make image colorful
                cvCvtColor(img,colorimg,CV_GRAY2RGB);

                // Draw green text for the recognized number on top of the image
                cvPutText(colorimg, val.str().c_str(), cvPoint(0,inputsz.height/2), &font, CV_RGB(0,255,0));

                // show the image
                cvShowImage("Image", colorimg );
                cvWaitKey(1000);

                cvReleaseImage(&img);
        }
        // Free buffers
        cvReleaseImage(&colorimg);

        return 0;
}
