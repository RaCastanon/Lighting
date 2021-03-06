#ifndef METHODS
#define METHODS

//Included libraries
#include <QDebug>
#include <stdlib.h>

//Defined params
#define TOO_NEGATIVE -255
#define LOW_NEGATIVE -128
#define ZERO         0
#define LOW_POSITIVE 128
#define TOO_POSITIVE 256


//Function declaration
void setProcess(void);
void setMiddlePoints(unsigned int, unsigned int);
void fuzzyController(signed int, signed int);
void membershipDegree(signed int, signed int);
void setFuzzyRules(void);

//Exported variables
extern unsigned int middlePoints[5][2];

#endif // METHODS

