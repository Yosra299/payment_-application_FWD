/*
 * terminal.c
 *
 *  Created on: Aug 19, 2022
 *      Author: yosra
 */
#include "ternimal.h"

void My_DateConv(uint8_t *_DateStr, P_My_Date _MyDate)
{
	uint8_t *p;

	p = _DateStr;

	if(strlen(_DateStr) > 5) // Full blown date..
	{
		p += 3;
		_MyDate->month = atoi(p);
		p += 5;
		_MyDate->year = atoi(p);
		return;
	}

	// Short date..
	_MyDate->month = atoi(p);
	p += 3;
	_MyDate->year = atoi(p);
}

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	printf("Enter Transaction Date PlZ\nNeeded format DD/MM/YYYY\n");
	scanf("%s",termData->transactionDate);
	if(termData->transactionDate[0] == '\0' || strlen(termData->transactionDate)>10)
			return WRONG_DATE;
	return OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	My_Date CardD, TermD;

	My_DateConv(cardData->cardExpirationDate, &CardD);
	My_DateConv(termData->transactionDate, &TermD);
	if(CardD.year<TermD.year)
		return EXPIRED_CARD;
	if(CardD.year==TermD.year){
		if(CardD.month<TermD.month)
			return EXPIRED_CARD;
	}
	return OK;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	printf("PlZ Enter Transaction Amount\n");
	scanf("%f",&termData->transAmount);
	if(termData->transAmount <= 0)
		return INVALID_AMOUNT;
	return OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if(termData->transAmount > termData->maxTransAmount )
		return EXCEED_MAX_AMOUNT;
	return OK;
}
void setMaxAmount(ST_terminalData_t *termData)
{
	termData->maxTransAmount = 5000.00;
}












