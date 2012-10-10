#include "PerformanceMeter.h"
#include "RandomDiceRecognizer.h"

#include "dicerecognizer.h"


#include <QDir>

int main()
{
    // you are only allowed to change the line below!
    IDiceRecognizer *recognizer = new DiceRecognizer();
    
    // read image
//    QString path("data/59.jpg");
//    cv::Mat im = cv::imread(path.toAscii().constData());
//    recognizer->readNumbers(im);
    PerformanceMeter(recognizer).evaluate();

        cv::waitKey();

    delete recognizer;

    return 0;
}
