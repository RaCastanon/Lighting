#include "methods.h"

unsigned int middlePoints[5][2];

/* Function name: setProcess()
 * Developer:     Raul Castañon
 * Details:       All process in one button
 */
void setProcess(void)
{
    qDebug("uno");

}

/* Function name: setMiddlePoints(uint, uint)
 * Developer:     Raul Castañon
 * Details:       Get middle points from the data of the image
 */
void setMiddlePoints(unsigned int cols, unsigned int rows)
{
    middlePoints[0][0] = (int)(cols/2.0);
    middlePoints[0][1] = (int)(rows/2.0);

    middlePoints[1][0] = (int)(cols/4.0);
    middlePoints[1][1] = (int)(rows/4.0);

    middlePoints[2][0] = (int)(3*(cols/4.0));
    middlePoints[2][1] = (int)(rows/4.0);

    middlePoints[3][0] = (int)(cols/4.0);
    middlePoints[3][1] = (int)(3*(rows/4.0));

    middlePoints[4][0] = (int)(3*(cols/4.0));
    middlePoints[4][1] = (int)(3*(rows/4.0));

}

/* Function name: fuzzyController(signed int)
 * Developer:     Raul Castañon
 * Details:       Get the control signal due a fuzzy controller logic
 */
void fuzzyController(signed int p_err)
{
    //Get membership degree of the error
    membershipDegree(p_err);

}

/* Function name: membershipDegree(signed int)
 * Developer:     Raul Castañon
 * Details:       Get the membership degree of the error
 */
void membershipDegree(signed int err)
{
    //We have five membership areas for the error, this process is known as fuzzification
    //First area -> mu_e_TN
    if ((err >= TOO_NEGATIVE) && (err < LOW_NEGATIVE))
    {
        mu_e_TN = ((LOW_NEGATIVE - err)/(LOW_NEGATIVE-TOO_NEGATIVE));
    }
    else
    {
        mu_e_TN = 0.0;
    }
    //Second area -> mu_e_N
    if ((err >= TOO_NEGATIVE) && (err < LOW_NEGATIVE))
    {
        mu_e_N = ((err - TOO_NEGATIVE)/(LOW_NEGATIVE-TOO_NEGATIVE));
    }
    else if ((err >= LOW_NEGATIVE) && (err < ZERO))
    {
        mu_e_N = ((ZERO - err)/(ZERO - LOW_NEGATIVE));
    }
    else
    {
        mu_e_N = 0.0;
    }
    //Third area -> mu_e_Z
    if((err >= LOW_NEGATIVE) && (err < ZERO))
    {
        mu_e_Z = ((err - LOW_NEGATIVE)/(ZERO - LOW_NEGATIVE));
    }
    else if ((err >= ZERO) && (err < LOW_POSITIVE))
    {
        mu_e_Z = ((ZERO - err)/(LOW_POSITIVE - ZERO));
    }
    else
    {
        mu_e_Z = 0.0;
    }
    //Fourth area -> mu_e_P
    if((err >= ZERO) && (err < LOW_POSITIVE))
    {
        mu_e_P = ((err - ZERO)/(LOW_POSITIVE - ZERO));
    }
    else if((err >= LOW_POSITIVE) && (err < TOO_POSITIVE))
    {
        mu_e_P = ((TOO_POSITIVE - err)/(TOO_POSITIVE - LOW_POSITIVE));
    }
    else
    {
        mu_e_P = 0.0;
    }
    //Fifth area -> mu_e_TP
    if((err >= LOW_POSITIVE) && (err <= TOO_POSITIVE))
    {
        mu_e_TP = ((err - LOW_POSITIVE)/(TOO_POSITIVE - LOW_POSITIVE));
    }
    else
    {
        mu_e_TP = 0.0;
    }
}
