/* Client Header File */

/* 
   Albert Owusu-Asare
   Zhi Chen

   created February 25, 2015
   last revised March 05, 2015
*/

#include <crypto_box.h>
#include "devurandom.h"

/* Variables and Structures*/
unsigned char client_pk[crypto_box_PUBLICKEYBYTES];
unsigned char client_sk[crypto_box_SECRETKEYBYTES]; //REMEMBER TO REMOVE
unsigned char* concatResult;

/* Methods for the client*/
void clientGenerateNonce();

void clientGenerateKeyPair();

void initialServerGenerateKeyPair();

long long  client_encrypt_nonce_pk_send(unsigned char *serverNonce,long long nonce_length,unsigned char *server_pk,char * output_filename);

void client_send_encryption(char *encryptedFileLocation,unsigned char  ciphertext [], int ciphertext_length );

void  clientPairConcatenate (unsigned char* result, unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length);

//void clientConcatenate (unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length);
void clientZeroConcatenate (unsigned char * result, unsigned char *element1, long long element1Length);

//void display_bytes(const unsigned char *byte_vector, long long int length);

