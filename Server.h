/* Server Header File */

/* 
   Albert Owusu-Asare
   Zhi Chen

   created February 28, 2015
   last revised March 05, 2015
*/

#include <crypto_box.h>
#include "devurandom.h"
#include "Client.h" //REMEMBER TO REMOVE

/* Variables and Structures*/
unsigned char initial_server_nonce[crypto_box_NONCEBYTES];
unsigned char initial_server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char initial_server_sk[crypto_box_SECRETKEYBYTES];
unsigned char server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char server_sk[crypto_box_SECRETKEYBYTES]; //REMEMBER TO REMOVE
unsigned char client_pk [crypto_box_PUBLICKEYBYTES];
unsigned char current_nonce[crypto_box_NONCEBYTES]; 
unsigned char next_nonce[crypto_box_NONCEBYTES]; 
union Data
{
  time_t time;
  unsigned char time_bytes;
};

/* Methods for the client*/
void initialServerGenerateNonce();
void serverGenerateNonce();
void serverGenerateKeyPair();
void initialServerGenerateKeyPair();
void display_bytes(const unsigned char *byte_vector, long long int length);
void initial_server_decrypt_message (char * filename, long long cipher_text_length);
void server_decrypt_message (char * filename, long long cipher_text_length);
void server_encrypt_time_message(char *encryptedFileLocation);
void  serverPairConcatenate (unsigned char* result, unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length);
void serverZeroConcatenate (unsigned char * result, unsigned char *element1, long long element1Length);
void server_send_encryption(char *encryptedFileLocation,unsigned char ciphertext [], int ciphertext_length );

