/* Server Header File */

/* 
   Albert Owusu-Asare
   Zhi Chen

   created February 28, 2015
   last revised February 28, 2015
*/

#include <crypto_box.h>
#include "devurandom.h"

/* Methods for the client*/
//unsigned char* clientGenerateNonce();
void initialServerGenerateNonce();
void serverGenerateNonce();
void serverGenerateKeyPair();
void initialServerGenerateKeyPair();
void display_bytes(const unsigned char *byte_vector, long long int length);

/* Variables and Structures*/
unsigned char initial_server_nonce[crypto_box_NONCEBYTES];
unsigned char server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char initial_server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char initial_server_sk[crypto_box_SECRETKEYBYTES];

/*
typedef struct clientkeypairs{
  unsigned char sender_pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sender_sk[crypto_box_SECRETKEYBYTES];
}clientkeypairs;
*/
