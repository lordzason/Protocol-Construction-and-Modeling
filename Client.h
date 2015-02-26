/* Client Header File */

/* 
   Albert Owusu-Asare
   Zhi Chen

   created February 25, 2015
   last revised February 25, 2015
*/

#include <crypto_box.h>
#include "devurandom.h"

/* Methods for the client*/
//unsigned char* clientGenerateNonce();
void clientGenerateNonce();

/* Variables and Structures*/

unsigned char client_shared_nonce[crypto_box_NONCEBYTES];
unsigned char sender_pk[crypto_box_PUBLICKEYBYTES];
/*
typedef struct clientkeypairs{
  unsigned char sender_pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sender_sk[crypto_box_SECRETKEYBYTES];
}clientkeypairs;
*/



