#include "PerformanceMeter.h"
#include "RandomDiceRecognizer.h"

#include "dicerecognizer.h"



int main()
{
    // you are only allowed to change the line below!
    IDiceRecognizer *recognizer = new DiceRecognizer();
    
    // read image
    PerformanceMeter(recognizer).evaluate();

    delete recognizer;

    return 0;
}
