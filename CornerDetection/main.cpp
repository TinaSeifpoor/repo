#include "visionmanager.h"
using namespace std;

int main()
{
    const string& image1 = "./data/img1.png";
    const string& image2 = "./data/img2.png";
    vector<string> homographyFilepath;
    homographyFilepath.push_back("./data/H1to2p");
    homographyFilepath.push_back("./data/H1to2p");
    homographyFilepath.push_back("./data/H1to3p");
    homographyFilepath.push_back("./data/H1to4p");
    homographyFilepath.push_back("./data/H1to5p");
    homographyFilepath.push_back("./data/H1to6p");

    VisionManager vm;
    vm.inspectImagesWithHomography(image1, image2,
                                  homographyFilepath[0]);
    cout << "\n";
    return 0;
}

