/*
 * server.h
 *
 *  Created on: Aug 19, 2022
 *      Author: yosra
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "../terminal/ternimal.h"

#define ACC_MAX 255

typedef int uint32_t;

typedef enum EN_transState_t
{
	APPROVED,
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
	Noerror,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE
}EN_serverError_t ;

typedef struct ST_transaction_t
{
ST_cardData_t cardHolderData;
ST_terminalData_t terminalData;
EN_transStat_t transState;
uint32_t transactionSequenceNumber;
}ST_transaction;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

EN_transStat_t recieveTransactionData(ST_transaction *transData);
EN_transStat_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction *transData);
void AccountDataReset(void);
void TransactionSetup(ST_transaction *Transaction, ST_cardData_t *cardHolderData, ST_terminalData_t *terminalData);

#endif /* SERVER_SERVER_H_ */
