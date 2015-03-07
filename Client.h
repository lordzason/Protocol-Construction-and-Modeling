/*****************************************************************
 *   Authors:     Albert Owusu-Asare  <owusuasa@grinnell.edu>
 *                Zhi Chen
 *
 *   Created:     February 25, 2015
 *   Last edited: Fri Mar  6 16:07:08 CST 2015
 *
 *   This file contains function prototypes for the client side of the
 *   Protocol Construction.
 *   
 *******************************************************************/


#include <crypto_box.h>
#include "devurandom.h"

/* Variables and Structures*/
unsigned char client_pk[crypto_box_PUBLICKEYBYTES];
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

