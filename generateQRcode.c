#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lib/encoding.h"

#define EXTRA_URI_CHARS 41

char * encodeSecret(char * secret);
char * generateHOTPURI(char * issuer, char * accountName, char * encodedHex);
char * generateTOTPURI(char * issuer, char * accountName, char * encodedHex);

int
main(int argc, char * argv[])
{
	if ( argc != 4 ) {
		printf("Usage: %s [issuer] [accountName] [secretHex]\n", argv[0]);
		return(-1);
	}

	char *	issuer = argv[1];
	char *	accountName = argv[2];
	char *	secret_hex = argv[3];


	assert (strlen(secret_hex) <= 20);

	printf("\nIssuer: %s\nAccount Name: %s\nSecret (Hex): %s\n\n",
		issuer, accountName, secret_hex);

	// Create an otpauth:// URI and display a QR code that's compatible
	// with Google Authenticator

	issuer = urlEncode(issuer);
	accountName = urlEncode(accountName);
	char * encodedSecret = encodeSecret(secret_hex);

	char * hotpURI = generateHOTPURI(issuer, accountName, encodedSecret);
	char * totpURI = generateTOTPURI(issuer, accountName, encodedSecret);

	displayQRcode(hotpURI);
	displayQRcode(totpURI);

	free(hotpURI);
	free(totpURI);

	return (0);
}

/*TODO: Implement HMAC encode */
char * encodeSecret(char * secret) {

	return "CI2FM6EQCI2FM6EQ";
}

char * generateHOTPURI(char * issuer, char * accountName, char * encodedHex) {
	char * retValue = malloc(strlen(issuer) + strlen(accountName) + strlen(encodedHex) + EXTRA_URI_CHARS + 1);
	strcpy(retValue, "otpauth://hotp/");
	strcat(retValue, issuer);
	strcat(retValue, "?issuer=");
	strcat(retValue, accountName);
	strcat(retValue, "&secret=");
	strcat(retValue, encodedHex);
	strcat(retValue, "&counter=1");
	
	return retValue;
}

char * generateTOTPURI(char * issuer, char * accountName, char * encodedHex) {
	char * retValue = malloc(strlen(issuer) + strlen(accountName) + strlen(encodedHex) + EXTRA_URI_CHARS + 1);
	strcpy(retValue, "otpauth://totp/");
	strcat(retValue, issuer);
	strcat(retValue, "?issuer=");
	strcat(retValue, accountName);
	strcat(retValue, "&secret=");
	strcat(retValue, encodedHex);
	strcat(retValue, "&period=30");

	return retValue;
}
