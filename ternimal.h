/*
 * ternimal.h
 *
 *  Created on: Aug 19, 2022
 *      Author: yosra
 */

#ifndef TERMINAL_TERNIMAL_H_
#define TERMINAL_TERNIMAL_H_

#include "../card/card.h"
#include "time.h"
#include <stdlib.h>

typedef char uint8_t;
typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
 ok,
 WRONG_DATE,
 EXPIRED_CARD,
 INVALID_CARD,
 INVALID_AMOUNT,
 EXCEED_MAX_AMOUNT,
 INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
void setMaxAmount(ST_terminalData_t *termData);

/*
 * My data types..
 */
typedef struct My_Date
{
	int month;
	int year;
}My_Date, *P_My_Date;

/*
 * My prototypes..
 */
void My_DateConv(uint8_t *_DateStr, P_My_Date _MyDate);

#endif /* TERMINAL_TERNIMAL_H_ */
