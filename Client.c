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
#include "Server.h"
#include "devurandom.h"

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0
#define NONCE_PK_LENGTH crypto_box_NONCEBYTES+crypto_box_PUBLICKEYBYTES

/*Fields and Variables*/
unsigned char client_sk[crypto_box_SECRETKEYBYTES];
unsigned char client_nonce_pk_concatation_result[crypto_box_ZEROBYTES+NONCE_PK_LENGTH];
unsigned char ciphertext[crypto_box_ZEROBYTES+NONCE_PK_LENGTH];

/* Generates a nonce composed of 0s or a random nonce */
void clientGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  long long int counter;

  /* randombytes(shared_nonce, crypto_box_NONCEBYTES); */
  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    client_shared_nonce[counter] = 0;

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
void client_nonce_pk_concatation()
{
  int counter;

  for (counter = 0; counter < crypto_box_ZEROBYTES; counter++)
    client_nonce_pk_concatation_result[counter] = 0;

  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    client_nonce_pk_concatation_result[crypto_box_ZEROBYTES + counter] = client_shared_nonce[counter];

  for (counter = 0; counter < crypto_box_PUBLICKEYBYTES; counter++)
    client_nonce_pk_concatation_result[crypto_box_ZEROBYTES + crypto_box_NONCEBYTES + counter] = client_pk[counter];

}//client_nonce_pk_concatation()

/* Client encrypts concatenation using server's public key 
   (using nonce N0 from the server), signs it with server's
   first time signing key */
void client_encrypt_nonce_pk()
{
  int result;

  result = crypto_box(ciphertext, client_nonce_pk_concatation_result, crypto_box_ZEROBYTES+NONCE_PK_LENGTH, initial_server_nonce, initial_server_pk, initial_server_sk);

  assert(result == 0);

}//client_encrypt_nonce_pk()

/* Client sends encrypted message to the server */
void client_send_encryption()
{

}


