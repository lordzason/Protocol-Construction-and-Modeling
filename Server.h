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
unsigned char server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char initial_server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char initial_server_sk[crypto_box_SECRETKEYBYTES];
unsigned char server_sk[crypto_box_SECRETKEYBYTES]; //REMEMBER TO REMOVE

/* Methods for the client*/
void initialServerGenerateNonce();
void serverGenerateNonce();
void serverGenerateKeyPair();
void initialServerGenerateKeyPair();
void display_bytes(const unsigned char *byte_vector, long long int length);
void initial_server_decrypt_message (char * filename, long long cipher_text_length);
void server_decrypt_message (char * filename, long long cipher_text_length);




