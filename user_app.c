/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    /* LED Initialization */
    LATA = 0x80;
    
    /* Timer0 control register initialization to turn timer on, asynch mode, 16 bit
     * Fosc/4, 1:16 prescaler, 1:1 postscaler */
    T0CON0 = 0x90; /* in binary: 1001 0000 */
    T0CON1 = 0x54; /* in binary: 0101 0100 */
    
} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    while(1)
    {
    /* Read LATA to a temporary variable */
    u32 u32Temporary = LATA; 
    
    /* initializing and incrementing static u16 variable */
    static u16 u16Static = u16Static + 0x0001;
    if(u16Static==500){
        u16Static = 0x0000;
    }
    
    u8 au8Pattern[0x01, 0x02, 0x04, 0x08, 0x10, 0x20];

    
    /* Use a bitmask and bitwise operation to clear the 6 LSBs */
    u32Temporary = u32Temporary & 0x000000c0; 
    
    /* Use a bitwise operation to update the 6 LSBs to the new value you want */
    u32Temporary = u32Temporary + 0x00000001;
    
    /* Write the temporary variable back to LATA */
    LATA = u32Temporary;
    
    if(LATA==0xBF){
        LATA=0x80;
        break;
 
    }
    
    }
} /* end UserAppRun */



/*--------------------------------------------------------------------
void TimeXus(INPUT_PARAMETER_)
Sets Timer0 to count u16Microseconds_
Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
*/
void TimeXus(INPUT_PARAMETER_)
{
    /* Disable the timer during config */
    T0CON0 = T0CON0 ^ 0x80;
    
    /* Preload TMR0H and TMR0L based on u16TimeXus */
    TMR0H = (2^16 - INPUT_PARAMETER_) & 0xf0;
    TMR0L = (2^16 - INPUT_PARAMETER_) & 0x0f;
    
    /* Clear TMR0IF and enable Timer 0 */
    PIR3 = PIR3 ^ 0x80;
    T0CON0 = T0CON0 ^ 0x80;
    
} /* end TimeXus () */

/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
