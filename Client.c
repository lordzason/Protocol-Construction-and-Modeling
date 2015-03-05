/* Client */

/* 
   Albert Owusu-Asare
   Zhi Chen

   Code Referenced From:
   John David Stone
   Department of Computer Science
   Grinnell College
   stone@cs.grinnell.edu

   created February 10, 2015
   last revised February 24, 2015
*/

#include <stdio.h>
#include <assert.h>
#include <crypto_box.h>
#include "Client.h"
#include "devurandom.h"

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0
#define NONCE_PK_LENGTH          crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES


/*Fields and Variables*/
unsigned char client_sk[crypto_box_SECRETKEYBYTES];
unsigned char client_nonce[crypto_box_NONCEBYTES];

//unsigned char * ciphertext;
unsigned char* concatResult;

/* Generates a nonce composed of 0s or a random nonce */
void clientGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  //long long int counter;

  randombytes(client_nonce, crypto_box_NONCEBYTES);
  /*for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    client_shared_nonce[counter] = 0;*/
  printf("Client Shared Nonce:\n");
  display_bytes(client_nonce, crypto_box_NONCEBYTES);
  //return shared_nonce;

}//clientGenerateNonce()

/* Construct keypairs for sender and receiver. */
void clientGenerateKeyPair()
{
  int result;
  result = crypto_box_keypair(client_pk,client_sk);
  assert(result == 0);
}//clientGenerateKeyPair()

/* Client nonce and public key concatenation */
/*void client_nonce_pk_concatation()
{
  int counter;

  for (counter = 0; counter < crypto_box_ZEROBYTES; counter++)
    client_nonce_pk_concatation_result[counter] = 0;

  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    client_nonce_pk_concatation_result[crypto_box_ZEROBYTES + counter] = client_shared_nonce[counter];

  for (counter = 0; counter < crypto_box_PUBLICKEYBYTES; counter++)
    client_nonce_pk_concatation_result[crypto_box_ZEROBYTES + crypto_box_NONCEBYTES + counter] = client_pk[counter];

    }//client_nonce_pk_concatation()*/

/* Client encrypts concatenation using server's public key 
   (using nonce N0 from the server), signs it with server's
   first time signing key */
long long  client_encrypt_nonce_pk_send(unsigned char *serverNonce,long long nonce_length,unsigned char *server_pk,char * output_filename)
{
  //  long long ciphertext_length = nonce_length + crypto_box_PUBLICKEYBYTES + crypto_box_ZEROBYTES;
 long long ciphertext_length = nonce_length + crypto_box_ZEROBYTES;
 unsigned char ciphertext[ciphertext_length];
 unsigned char  concateResult[ciphertext_length];
 unsigned char  final_message [ciphertext_length + crypto_box_PUBLICKEYBYTES];
 int result;

  //concatenates the N1 with zero bytes
 clientZeroConcatenate (concateResult,client_nonce,nonce_length);
  //  clientConcatenate(client_shared_nonce,crypto_box_NONCEBYTES, client_pk, crypto_box_PUBLICKEYBYTES);

  // encrypts the results of the concatenation 
  // result = crypto_box(ciphertext, concatResult, crypto_box_ZEROBYTES+NONCE_PK_LENGTH, nonce, pk, sk);
  result = crypto_box(ciphertext,concateResult,ciphertext_length,serverNonce,server_pk,client_sk);
  assert(result == 0);
  //concatenate the results from encryption with client public key
  clientPairConcatenate (final_message,client_pk, crypto_box_PUBLICKEYBYTES, ciphertext, ciphertext_length);
 
  printf("CipherText :\n");
  display_bytes(final_message,ciphertext_length +crypto_box_PUBLICKEYBYTES );
  // send the results of the encryption to an output file
  client_send_encryption(output_filename,final_message,ciphertext_length+crypto_box_PUBLICKEYBYTES);
  return ciphertext_length +crypto_box_PUBLICKEYBYTES ;
}//client_encrypt_nonce_pk()

/* Client sends encrypted message to the server */
void client_send_encryption(char *encryptedFileLocation,unsigned char  ciphertext [], int ciphertext_length )
{
  FILE *clientEncryptedFile;
  //long long int counter = 0;
  clientEncryptedFile = fopen(encryptedFileLocation, "w");

  /*while (counter < crypto_box_ZEROBYTES+NONCE_PK_LENGTH) {
    (void) fprintf(clientEncryptedFile, "%02x", ciphertext[counter]);
    counter++;*/
  printf("Client writing to Encrypted File\n");
  display_bytes(ciphertext,crypto_box_ZEROBYTES+NONCE_PK_LENGTH);
 fwrite(ciphertext, sizeof(unsigned char), ciphertext_length * sizeof(unsigned char), clientEncryptedFile);

  fclose(clientEncryptedFile);
}//client_send_encryption
/* Concatenates two elements together */
void  clientPairConcatenate (unsigned char* result, unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length)
{
  int counter;

  for (counter = 0; counter < element1Length; counter++)
    result[counter] = element1[counter];

  for (counter = 0; counter < element2Length; counter++)
    result[element1Length + counter] = element2[counter];
}//clientConcatenate
/*
void clientConcatenate (unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length)
{
  int counter;
  unsigned char result[crypto_box_ZEROBYTES + element1Length + element2Length];

  for (counter = 0; counter < crypto_box_ZEROBYTES; counter++)
    result[counter] = 0;

  for (counter = 0; counter < element1Length; counter++)
    result[crypto_box_ZEROBYTES + counter] = element1[counter];

  for (counter = 0; counter < element2Length; counter++)
    result[crypto_box_ZEROBYTES + element1Length + counter] = element2[counter];

  concatResult = result;
}//clientConcatenate
*/
/* Add zero bytes to element */
void clientZeroConcatenate (unsigned char * result, unsigned char *element1, long long element1Length)
{
  int counter;

  for (counter = 0; counter < crypto_box_ZEROBYTES; counter++)
    result[counter] = 0;

  for (counter = 0; counter < element1Length; counter++)
    result[crypto_box_ZEROBYTES + counter] = element1[counter];
  printf("concatenate with zero\n");
 display_bytes(result,crypto_box_ZEROBYTES+element1Length );
}//clientConcatenate
