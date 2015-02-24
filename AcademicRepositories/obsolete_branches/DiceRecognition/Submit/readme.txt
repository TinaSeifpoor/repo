This is homework #1 of Cihan SARI for CMPE 537 done by using OpenCV 2.4.2 and Qt 4.8.2

Includes:
	readme.txt
		-- This file

	CMPE537-HW1.pdf
		-- 	Report, contains all the steps and comments
		
	DiceRecognition.pro
		-- Project file, used for solution at Qt Creator 2.5.0

	contouranalysis.h
		-- Header of ContourAnalysis class
		
	contouranalysis.cpp
		-- Source of ContourAnalysis class
		
	dicerecognition.h
		-- Header of DiceRecognition class

	dicerecognition.cpp
		-- Source of DiceRecognition class
		
	myotsu.h
		-- Header of MyOtsu class

	myotsu.cpp
		-- Source of MyOtsu class
		
Notes:
	I have not used Otsu on my solution. Therefore, to see my Otsu implementation, please un-comment lines 19 - 24. They should provide a difference image between OpenCV's implementation and mine.
	
Another Note:
	I had to change PerformanceMeter's readLabels function (line 36) for it not to give me a compiler error.
	From:
	    ifstream dataFile(filePath, ios::in);
	To:
	    const char * c = filePath.c_str();
		ifstream dataFile(c, ios::in);