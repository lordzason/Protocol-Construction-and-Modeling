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
void serverGenerateKeyPair();
void initialServerGenerateKeyPair();
void serverGenerateNonce();
void client_send_encryption(char *encryptedFileLocation);
void display_bytes(const unsigned char *byte_vector, long long int length);
void client_encrypt_nonce_pk(unsigned char *nonce, unsigned char *pk, unsigned char *sk);
void clientConcatenate (unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length);

/* Variables and Structures*/
unsigned char client_pk[crypto_box_PUBLICKEYBYTES];
/*
typedef struct clientkeypairs{
  unsigned char sender_pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sender_sk[crypto_box_SECRETKEYBYTES];
}clientkeypairs;
*/



