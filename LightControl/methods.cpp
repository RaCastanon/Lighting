#include "methods.h"

/*
 *Global variables declarations
 */
unsigned int middlePoints[5][2];

//Proportional error variables
double mu_e_TN  = 0.0;
double mu_e_N   = 0.0;
double mu_e_Z   = 0.0;
double mu_e_P   = 0.0;
double mu_e_TP  = 0.0;
//Integral error variables
double mu_ei_TN  = 0.0;
double mu_ei_N   = 0.0;
double mu_ei_Z   = 0.0;
double mu_ei_P   = 0.0;
double mu_ei_TP  = 0.0;
//Rules outputs
double u_TO[5]   = {0.0, 0.0, 0.0, 0.0, 0.0};
double u_O[5]    = {0.0, 0.0, 0.0, 0.0, 0.0};
double u_Z[5]    = {0.0, 0.0, 0.0, 0.0, 0.0};
double u_On[5]   = {0.0, 0.0, 0.0, 0.0, 0.0};
double u_TOn[5]  = {0.0, 0.0, 0.0, 0.0, 0.0};

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
void fuzzyController(signed int p_err, signed int i_err)
{
    //Get membership degree of the error
    membershipDegree(p_err, i_err);
    //Set rules
    setFuzzyRules();
    //Defuzzification

}

/* Function name: membershipDegree(signed int)
 * Developer:     Raul Castañon
 * Details:       Get the membership degree of the error
 */
void membershipDegree(signed int p_err, signed int i_err)
{
    //We have five membership areas for the error, this process is known as fuzzification
    //Proportional error membership degree
    //First area -> mu_e_TN
    if ((p_err >= TOO_NEGATIVE) && (p_err < LOW_NEGATIVE))
    {
        mu_e_TN = ((LOW_NEGATIVE - p_err)/(LOW_NEGATIVE-TOO_NEGATIVE));
    }
    else
    {
        mu_e_TN = 0.0;
    }
    //Second area -> mu_e_N
    if ((p_err >= TOO_NEGATIVE) && (p_err < LOW_NEGATIVE))
    {
        mu_e_N = ((p_err - TOO_NEGATIVE)/(LOW_NEGATIVE-TOO_NEGATIVE));
    }
    else if ((p_err >= LOW_NEGATIVE) && (p_err < ZERO))
    {
        mu_e_N = ((ZERO - p_err)/(ZERO - LOW_NEGATIVE));
    }
    else
    {
        mu_e_N = 0.0;
    }
    //Third area -> mu_e_Z
    if((p_err >= LOW_NEGATIVE) && (p_err < ZERO))
    {
        mu_e_Z = ((p_err - LOW_NEGATIVE)/(ZERO - LOW_NEGATIVE));
    }
    else if ((p_err >= ZERO) && (p_err < LOW_POSITIVE))
    {
        mu_e_Z = ((ZERO - p_err)/(LOW_POSITIVE - ZERO));
    }
    else
    {
        mu_e_Z = 0.0;
    }
    //Fourth area -> mu_e_P
    if((p_err >= ZERO) && (p_err < LOW_POSITIVE))
    {
        mu_e_P = ((p_err - ZERO)/(LOW_POSITIVE - ZERO));
    }
    else if((p_err >= LOW_POSITIVE) && (p_err < TOO_POSITIVE))
    {
        mu_e_P = ((TOO_POSITIVE - p_err)/(TOO_POSITIVE - LOW_POSITIVE));
    }
    else
    {
        mu_e_P = 0.0;
    }
    //Fifth area -> mu_e_TP
    if((p_err >= LOW_POSITIVE) && (p_err <= TOO_POSITIVE))
    {
        mu_e_TP = ((p_err - LOW_POSITIVE)/(TOO_POSITIVE - LOW_POSITIVE));
    }
    else
    {
        mu_e_TP = 0.0;
    }
    //Integral error membership degree
    //First area -> mu_e_TN
    if ((i_err >= TOO_NEGATIVE) && (i_err < LOW_NEGATIVE))
    {
        mu_ei_TN = ((LOW_NEGATIVE - i_err)/(LOW_NEGATIVE-TOO_NEGATIVE));
    }
    else
    {
        mu_ei_TN = 0.0;
    }
    //Second area -> mu_e_N
    if ((i_err >= TOO_NEGATIVE) && (i_err < LOW_NEGATIVE))
    {
        mu_ei_N = ((i_err - TOO_NEGATIVE)/(LOW_NEGATIVE-TOO_NEGATIVE));
    }
    else if ((i_err >= LOW_NEGATIVE) && (i_err < ZERO))
    {
        mu_ei_N = ((ZERO - i_err)/(ZERO - LOW_NEGATIVE));
    }
    else
    {
        mu_ei_N = 0.0;
    }
    //Third area -> mu_e_Z
    if((i_err >= LOW_NEGATIVE) && (i_err < ZERO))
    {
        mu_ei_Z = ((i_err - LOW_NEGATIVE)/(ZERO - LOW_NEGATIVE));
    }
    else if ((i_err >= ZERO) && (i_err < LOW_POSITIVE))
    {
        mu_ei_Z = ((ZERO - i_err)/(LOW_POSITIVE - ZERO));
    }
    else
    {
        mu_ei_Z = 0.0;
    }
    //Fourth area -> mu_e_P
    if((i_err >= ZERO) && (i_err < LOW_POSITIVE))
    {
        mu_ei_P = ((i_err - ZERO)/(LOW_POSITIVE - ZERO));
    }
    else if((i_err >= LOW_POSITIVE) && (i_err < TOO_POSITIVE))
    {
        mu_ei_P = ((TOO_POSITIVE - i_err)/(TOO_POSITIVE - LOW_POSITIVE));
    }
    else
    {
        mu_ei_P = 0.0;
    }
    //Fifth area -> mu_e_TP
    if((i_err >= LOW_POSITIVE) && (i_err <= TOO_POSITIVE))
    {
        mu_ei_TP = ((i_err - LOW_POSITIVE)/(TOO_POSITIVE - LOW_POSITIVE));
    }
    else
    {
        mu_ei_TP = 0.0;
    }
}

/* Function name: setFuzzyRules(void)
 * Developer:     Raul Castañon
 * Details:       Set the fuzzy rules
 */
void setFuzzyRules(void)
{
    //First rule
    u_TO[0] = std::min((signed int)mu_e_TN, (signed int)mu_ei_TN);
    //Second rule
    u_TO[1] = std::min((int)mu_e_TN, (int)mu_ei_N);
    //Third rule
    u_TO[2] = std::min(mu_e_TN, mu_ei_Z);
    //Fourth rule
    u_TO[3] = std::min(mu_e_TN, mu_ei_P);
    //Fifth rule
    u_TO[4] = std::min(mu_e_TN, mu_ei_TP);
    //Sixth rule
    u_O[0] = std::min(mu_e_N, mu_ei_TN);
    //Seventh rule
    u_O[1] = std::min(mu_e_N, mu_ei_N);
    //Eight rule
    u_O[2] = std::min(mu_e_N, mu_ei_Z);
    //Nineth rule
    u_O[3] = std::min(mu_e_N, mu_ei_P);
    //Tenth rule
    u_O[4] = std::min(mu_e_N, mu_ei_TP);
    //Eleventh rule
    u_Z[0] = std::min(mu_e_Z, mu_ei_TN);
    //Twelve rule
    u_Z[1] = std::min(mu_e_Z, mu_ei_N);
    //Thirteenth rule
    u_Z[2] = std::min(mu_e_Z, mu_ei_Z);
    //Fourteenth rule
    u_Z[3] = std::min(mu_e_Z, mu_ei_P);
    //Fiveteenth rule
    u_Z[4] = std::min(mu_e_Z, mu_ei_TP);
    //Sixteenth rule
    u_On[0] = std::min(mu_e_P, mu_ei_TN);
    //Seventeenth rule
    u_On[1] = std::min(mu_e_P, mu_ei_N);
    //Eighteenth rule
    u_On[2] = std::min(mu_e_P, mu_ei_Z);
    //Nineteenth rule
    u_On[3] = std::min(mu_e_P, mu_ei_P);
    //Twenthieth rule
    u_On[4] = std::min(mu_e_P, mu_ei_TP);
    //Twenty oneth rule
    u_TOn[0] = std::min(mu_e_TP, mu_ei_TN);
    //Twenty twoth rule
    u_TOn[1] = std::min(mu_e_TP, mu_ei_N);
    //Twenty threeth rule
    u_TOn[2] = std::min(mu_e_TP, mu_ei_Z);
    //Twenty fourth rule
    u_TOn[3] = std::min(mu_e_TP, mu_ei_P);
    //Twenty fiveth rule
    u_TOn[4] = std::min(mu_e_TP, mu_ei_TP);
}
