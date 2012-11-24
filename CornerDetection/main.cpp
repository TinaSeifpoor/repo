#include "visionmanager.h"
using namespace std;

int main()
{
    cout << "Hello World!";
    const string& imageFilepath = "./data/img1.png";
    vector<string> homographyFilepath;
    homographyFilepath.push_back("./data/H1to2p");
    homographyFilepath.push_back("./data/H1to2p");
    homographyFilepath.push_back("./data/H1to3p");
    homographyFilepath.push_back("./data/H1to4p");
    homographyFilepath.push_back("./data/H1to5p");
    homographyFilepath.push_back("./data/H1to6p");

    VisionManager vm;
    vm.inspectImageWithHomography(imageFilepath,
                                  homographyFilepath[0]);
    return 0;
}

