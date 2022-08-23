/*
 * Application.c
 *
 *  Created on: Aug 19, 2022
 *      Author: yosra
 */
#include "Application.h"

void appStart(void)
{
	ST_cardData_t C_info;
	ST_terminalData_t T_Info;
	ST_transaction S_info;

	/*
	 * Reset
	 */
	AccountDataReset();
/*
 * card section
 */
	 if (getCardHolderName(&C_info) == WRONG_NAME)
	    {
	        printf("Declined.\nWrong Name!\n");
	        return;
	    }
	 if (getCardExpiryDate(&C_info) == WRONG_EXP_DATE)
	    {
	        printf("Declined.\nWrong expiry date!\n");
	        return;
	    }
	 if (getCardPAN(&C_info) == WRONG_PAN)
	    {
	        printf("Declined.\nWrong Primary Account Number!\n");
	        return;
	    }

/*
 * terminal section
 */

	     if (getTransactionDate(&T_Info) == WRONG_DATE)
	     {
	         printf("Declined.\nWrong Date!\n");
	         return;
	     }

	     if (isCardExpired(&C_info, &T_Info) == EXPIRED_CARD)
	     {
	         printf("Declined.\nExpired card!\n");
	         return;
	     }

	     if (getTransactionAmount(&T_Info) == INVALID_AMOUNT )
	     {
	    	 printf("Declined.\nINVALID_AMOUNT!\n");
	    	 return;
	     }

	     setMaxAmount(&T_Info);

	     if(isBelowMaxAmount(&T_Info)== EXCEED_MAX_AMOUNT)
	     {
	    	 printf("Declined.\nEXCEED_MAX_AMOUNT!\n");
	    	 return;
	     }
/*
 * server section
 */
	     TransactionSetup(&S_info, &C_info, &T_Info);

	     EN_transStat_t ret;

	     ret = recieveTransactionData(&S_info);
	     switch(ret)
	     {
	     case DECLINED_INSUFFECIENT_FUND:
	    	 printf("Declined.\nDECLINED_INSUFFECIENT_FUND\n");
	    	 return;
	     case DECLINED_STOLEN_CARD:
	    	 printf("Declined.\nDECLINED_STOLEN_CARD!\nCalling Police...\n");
	    	 return;
	     case INTERNAL_SERVER_ERROR:
	    	 printf("Declined.\nINTERNAL_SERVER_ERROR\n");
	    	 return;
	     default:
	    	 printf("Approved\n");
	    	 return;
	     }
}





