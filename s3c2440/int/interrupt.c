#include "s3c24xx.h"
// isr
void EINT_Handle()
{
    unsigned long oft = INTOFFSET;
    unsigned long val;

	
    switch( oft )
    {   
    	 // K1 button    
        case 1:   // EINT1
        {   
            GPBDAT |= (0xF<<5);   
            GPBDAT &= ~(1<<5);      
            break;
        }
        
        // K2 button
        case 4:	  // EINT4_7
        {   
            GPBDAT |= (0xF<<5);   
            GPBDAT &= ~(1<<6);     
            break;
        }

         // K3 button    
        case 2: 	// EINT2
        {   
            GPBDAT |= (0xF<<5);  
            GPBDAT &= ~(1<<7);      
            break;
        }

         // K4 button    
        case 0:		// EINT0
        {   
            GPBDAT |= (0xF<<5);   
            GPBDAT &= ~(1<<8);     
            break;
        }

        default:
            break;
    }

   	// clear int
    if( oft == 4 ) 
        EINTPEND = (1<<4);   // EINT4_7ºÏÓÃIRQ4
    SRCPND = 1<<oft;
    INTPND = 1<<oft;
}
