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
void serverGenerateKeyPair();
void initialServerGenerateKeyPair();
void serverGenerateNonce();
void client_send_encryption(char *encryptedFileLocation,unsigned char  ciphertext [], int ciphertext_length );
void display_bytes(const unsigned char *byte_vector, long long int length);
long long  client_encrypt_nonce_pk_send(unsigned char *nonce,long long nonce_length,unsigned char *pk, unsigned char *sk,char * output_filename);
void clientConcatenate (unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length);

/* Variables and Structures*/
unsigned char client_pk[crypto_box_PUBLICKEYBYTES];




