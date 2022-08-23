/*
 * card.c
 *
 *  Created on: Aug 19, 2022
 *      Author: yosra
 */
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	printf("Enter Card Holder Name PlZ\n");
	scanf("%s",cardData->cardHolderName);
	if(cardData->cardHolderName[0] == '\0' || strlen(cardData->cardHolderName)<20 || strlen(cardData->cardHolderName)>24)
		return WRONG_NAME;
	else return OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	printf("Card Expiration Date is needed \nPlZ Use the following format MM/YY\n");
	scanf("%s",cardData->cardExpirationDate);
	if(cardData->cardExpirationDate[0] == '\0' || strlen(cardData->cardExpirationDate)!= 5)
			return WRONG_EXP_DATE;
	else return OK;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	printf("PlZ Enter card's Primary Account Number\n");
	scanf("%s",cardData->primaryAccountNumber);
	if(cardData->primaryAccountNumber[0] == '\0' || strlen(cardData->primaryAccountNumber)<16 || strlen(cardData->primaryAccountNumber)>19)
		return WRONG_PAN;
	else return OK;
}









