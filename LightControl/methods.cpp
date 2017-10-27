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

void membershipDegree(signed int p_err)
{


}
