/*****************************************************************
 *   Authors:     Albert Owusu-Asare  <owusuasa@grinnell.edu>
 *                Zhi Chen
 *   Created:     February 28, 2015
 *   Last edited: Thu Mar  5 21:43:09 CST 2015
 *
 *   This file contains function prototypes for  basic utilities 
 *   for the  server
 *   
 *******************************************************************/

#ifndef _SERVER_  //include guards to prevent double declaration
#define _SERVER_

#ifndef _CRYPTO_BOX_ //include  guards to prevent double declaration
#define _CRYPTO_BOX_
#include <crypto_box.h>  //crypto box libraries
#endif

#ifndef _RANDOM_ //include  guards to prevent double declaration
#define _RANDOM_
#include "devurandom.h"
#endif

/* Variables and Structures*/

//server initialisation variables
unsigned char initial_server_nonce[crypto_box_NONCEBYTES];
unsigned char initial_server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char initial_server_sk[crypto_box_SECRETKEYBYTES];

unsigned char server_pk[crypto_box_PUBLICKEYBYTES];
unsigned char client_pk [crypto_box_PUBLICKEYBYTES];
 

union Data
{
  time_t time;
  unsigned char time_bytes;
};

/* Methods for the client*/

/* Activates server by generating initial server nonce and initial server
   key pair*/
void server_start_first_time_init();
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

#endif
