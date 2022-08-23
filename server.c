/*
 * server.c
 *
 *  Created on: Aug 21, 2022
 *      Author: yosra
 */
#include "server.h"

ST_accountsDB_t account[ACC_MAX];
ST_transaction Tdata[ACC_MAX];
uint32_t iTdata = 0; // Transaction data index.
static float currentBalance=0.0;

void AccountDataReset(void)
{
	memset(account, 0, sizeof(account));

	account[0].balance = 4800;
	strcpy(account[0].primaryAccountNumber, "12345678998765432");
	account[1].balance = 890024.36;
	strcpy(account[1].primaryAccountNumber, "23456789987654321");
	account[2].balance = 200.0;
	strcpy(account[2].primaryAccountNumber, "11111111111111111");
	account[3].balance = 5000.0;
	strcpy(account[3].primaryAccountNumber, "44444444444444444");
	account[4].balance = 90000.0;
	strcpy(account[4].primaryAccountNumber, "14785236996325874");
}

void TransactionSetup(ST_transaction *Transaction, ST_cardData_t *cardHolderData, ST_terminalData_t *terminalData)
{
	memcpy(&Transaction->cardHolderData, cardHolderData, sizeof(ST_cardData_t));
	memcpy(&Transaction->terminalData, terminalData, sizeof(ST_terminalData_t));
}

EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
	transData->transState = APPROVED;
	    if (isValidAccount(&transData->cardHolderData) == DECLINED_STOLEN_CARD)
	    {
	        transData->transState = DECLINED_STOLEN_CARD;
	    }
	    else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	    {
	        transData->transState = DECLINED_INSUFFECIENT_FUND;
	    }
	    else if (saveTransaction(transData) == SAVING_FAILED)
	    {
	        transData->transState = INTERNAL_SERVER_ERROR;
	    }
	    else if (transData->transState == APPROVED)
	    {
	        // Update balance
	        uint8_t index = 0;
	        while(account[index].primaryAccountNumber[0])
	        {
	            if (strcmp(transData->cardHolderData.primaryAccountNumber, account[index].primaryAccountNumber) == 0)
	            {
	                printf("Your old balance was: %f\n", account[index].balance);
	                account[index].balance -= transData->terminalData.transAmount;
	                printf("Your new balance is: %f\n", account[index].balance);
	                break;
	            }
	            index++;
	        }
	    }
	    return transData->transState;
}

EN_transStat_t isValidAccount(ST_cardData_t *cardData)
{
	uint32_t i ;
	    for(i=0; i<255;i++)
	    {
	        if(!strcmp(cardData->primaryAccountNumber, account[i].primaryAccountNumber))
	        {
	            // Saved the balance in a buffer so that I can use it in isAmountAvailable
	            currentBalance = account[i].balance;
	            printf("Account index is %d \n", i);
	            return APPROVED;
	        }
	    }
	    return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
	if (termData->transAmount < currentBalance)
	    {
	        return OK;
	    }
	    return LOW_BALANCE;
}


EN_serverError_t saveTransaction(ST_transaction *transData)
{
	if(iTdata >= ACC_MAX)
	{
	    return SAVING_FAILED;
	}
	memcpy(&Tdata[iTdata], transData, sizeof(ST_transaction));
	Tdata[iTdata].transactionSequenceNumber = iTdata + 1;
	printf("Transaction sequence number: %d\n", Tdata[iTdata].transactionSequenceNumber);
	iTdata++;
	return OK;
}



