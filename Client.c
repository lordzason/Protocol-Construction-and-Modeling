
/*****************************************************************
 *   Authors:      Albert Owusu-Asare
 *                 Zhi Chen
 *
 *   Created:      February 10, 2015
 *   Last revised: Tue Mar 17 16:14:20 CDT 2015
 *
 *   This file contains the source for the methods of the client.
 *
 *   Special thanks to John David Stone for both his insight and 
 *   help with supplying  preliminary code(tryout.c) from which 
 *   this code base was inspired.
 *  
 *   John David Stone
 *   Department of Computer Science
 *   Grinnell College
 *   stone@cs.grinnell.edu

 *******************************************************************/



#include <stdio.h>
#include <assert.h>
#include <crypto_box.h>
#include <time.h>
#include "Client.h"
#include "utils.h"
#include "devurandom.h"

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0
#define NONCE_PK_LENGTH          crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES
#define COMBINED_NONCE_LENGTH    (crypto_box_ZEROBYTES + crypto_box_NONCEBYTES 
+ crypto_box_NONCEBYTES)

/*Fields and Variables*/
unsigned char client_sk[crypto_box_SECRETKEYBYTES];
//unsigned char client_nonce[crypto_box_NONCEBYTES];
unsigned char * current_nonce;
unsigned char * next_nonce;
//unsigned char * ciphertext;
unsigned char* concatResult;


/* Construct keypairs for sender and receiver. */
void clientGenerateKeyPair()
{
  int result;
  result = crypto_box_keypair(client_pk,client_sk);
  assert(result == 0);
  printf("\nClient.c Client Secret Key Generate:\n"); //remember to take out this line
  display_bytes(client_sk,crypto_box_SECRETKEYBYTES); //remember to take out this line
}//clientGenerateKeyPair()


/* Client encrypts concatenation using server's public key 
   (using nonce N0 from the server), signs it with server's
   first time signing key */
long long  client_encrypt_nonce_pk_send(unsigned char *serverNonce,long long nonce_length,
                                        unsigned char *server_pk,char * output_filename)
{
  current_nonce = serverNonce;
  next_nonce = generate_nonce();
  long long ciphertext_length = nonce_length + crypto_box_ZEROBYTES;
  unsigned char ciphertext[ciphertext_length];
  unsigned char concateResult[ciphertext_length];
  unsigned char final_message [ciphertext_length + crypto_box_PUBLICKEYBYTES];
  int result;

  // Concatenate nonce N1 with zero bytes
  concat_zero_bytes(concateResult,next_nonce,nonce_length);

  // Encrypts the results of the concatenation 
  result = crypto_box(ciphertext,concateResult,ciphertext_length,serverNonce,server_pk,client_sk);
  assert(result == 0);

  // Concatenate the results from encryption with client public key
  concat_buffers(final_message,client_pk, crypto_box_PUBLICKEYBYTES, ciphertext, ciphertext_length);
 
  printf("\nClient.c Initial cypher text of  N1 + client public key:\n");
  display_bytes(final_message,ciphertext_length + crypto_box_PUBLICKEYBYTES);

  // Send the results of the encryption to an output file
  write_message_to_file(output_filename,final_message,ciphertext_length+crypto_box_PUBLICKEYBYTES);
  
  // Prepare nonce for next transmission
  current_nonce = next_nonce;
  next_nonce =  generate_nonce();
  return ciphertext_length + crypto_box_PUBLICKEYBYTES ;
}//client_encrypt_nonce_pk()


/*
 * trying to hide a lot of details and encapsulate information
 *
 */

unsinged char * client_encrypt_message(unsigned char * message, long long message_length,
                                  unsigned char * receiver_pk){

  // Every message to be decrypted will be of the form:
  // zero bytes + current Nonce + Next Nonce + message;
  unsigned char unencrypted_message[COMBINED_NONCE_LENGTH + message_length];
  
  //concate current and next nonce
  next_nonce = generate_nonce();
  concat_buffers


}//client_encrypt_message()

/* Client sends encrypted message to the server 
void client_send_encryption(char *encryptedFileLocation,unsigned char  ciphertext [], int ciphertext_length )
{
  FILE *clientEncryptedFile;
  clientEncryptedFile = fopen(encryptedFileLocation, "w");

  printf("Client Wrote to the Encrypted File the Following:\n");
  display_bytes(ciphertext,crypto_box_ZEROBYTES+NONCE_PK_LENGTH);
  fwrite(ciphertext, sizeof(unsigned char), ciphertext_length * sizeof(unsigned char), clientEncryptedFile);
  fclose(clientEncryptedFile);
}//client_send_encryption
*/

/* Concatenates two elements together 
void  clientPairConcatenate (unsigned char* result, unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length)
{
  int counter;

  for (counter = 0; counter < element1Length; counter++)
    result[counter] = element1[counter];

  for (counter = 0; counter < element2Length; counter++)
    result[element1Length + counter] = element2[counter];
}//clientConcatenate

*/

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

/* Generates a nonce composed of 0s or a random nonce 
void clientGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  //long long int counter;

  randombytes(client_nonce, crypto_box_NONCEBYTES);
  //for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    //client_shared_nonce[counter] = 0;
  printf("Client Shared Nonce:\n");
  display_bytes(client_nonce, crypto_box_NONCEBYTES);
  //return shared_nonce;

  }//clientGenerateNonce() */

/* Add zero bytes to element 
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
*/
