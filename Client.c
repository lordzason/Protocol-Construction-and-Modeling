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
unsigned char client_shared_nonce[crypto_box_NONCEBYTES];
//unsigned char * ciphertext;
unsigned char* concatResult;

/* Generates a nonce composed of 0s or a random nonce */
void clientGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  //long long int counter;

  randombytes(client_shared_nonce, crypto_box_NONCEBYTES);
  /*for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    client_shared_nonce[counter] = 0;*/
  printf("Client Shared Nonce:\n");
  display_bytes(client_shared_nonce, crypto_box_NONCEBYTES);
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
long long  client_encrypt_nonce_pk_send(unsigned char *nonce,long long nonce_length,unsigned char *pk, unsigned char *sk,char * output_filename)
{
  long long ciphertext_length = nonce_length + crypto_box_PUBLICKEYBYTES + crypto_box_ZEROBYTES;
  unsigned char ciphertext[ciphertext_length];
  int result;

  //concatenates the N0 and the public key of the client
  clientConcatenate(client_shared_nonce,crypto_box_NONCEBYTES, client_pk, crypto_box_PUBLICKEYBYTES);

  // encrypts the results of the concatenation 
  result = crypto_box(ciphertext, concatResult, crypto_box_ZEROBYTES+NONCE_PK_LENGTH, nonce, pk, sk);
  assert(result == 0);

  printf("CipherText :\n");
  display_bytes(ciphertext,ciphertext_length);
  // send the results of the encryption to an output file
  client_send_encryption(output_filename,ciphertext,ciphertext_length);
  return ciphertext_length;
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
  display_bytes(ciphertext,crypto_box_ZEROBYTES+NONCE_PK_LENGTH);
 fwrite(ciphertext, sizeof(unsigned char), ciphertext_length * sizeof(unsigned char), clientEncryptedFile);

  fclose(clientEncryptedFile);
}//client_send_encryption

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

