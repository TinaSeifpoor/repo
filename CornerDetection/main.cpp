#include "visionmanager.h"
using namespace std;

int main()
{
    VisionManager vm;

//    const string& image1 = "./data/img1.png";
//    const string& image2 = "./data/img6.png";
//    vector<string> homographyFilepath;
//    homographyFilepath.push_back("./data/H1to2p");
//    homographyFilepath.push_back("./data/H1to3p");
//    homographyFilepath.push_back("./data/H1to4p");
//    homographyFilepath.push_back("./data/H1to5p");
//    homographyFilepath.push_back("./data/H1to6p");
//    homographyFilepath.push_back("./data/H1to6p");


//    vm.inspectImagesWithHomography(image1, image2,
//                                  homographyFilepath[4]);
    const string& image1 = "./data/kuzey.jpg";
    const string& image2 = "./data/kuzey45.jpg";
    vm.inspectImagesWithHomography(image1, image2, "");
    cout << "\n";
    return 0;
}

