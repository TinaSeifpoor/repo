#include "visionmanager.h"
using namespace std;

int main()
{
    const string& imageFilepath = "./data/kuzey.jpg";
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

