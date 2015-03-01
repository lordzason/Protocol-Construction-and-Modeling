/* Server */

/* 
   Albert Owusu-Asare
   Zhi Chen

   Code Referenced From:
   John David Stone
   Department of Computer Science
   Grinnell College
   stone@cs.grinnell.edu

   created February 28, 2015
   last revised February 28, 2015
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

/*Fields and Variables*/
unsigned char server_sk[crypto_box_SECRETKEYBYTES];

/* Generates a server initial nonce composed of 0s or a random nonce */
void initialServerGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  long long int counter;

  /* randombytes(shared_nonce, crypto_box_NONCEBYTES); */
  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    initial_server_nonce[counter] = 0;

  //return shared_nonce;

}//clientGenerateNonce()

/* Generates a nonce composed of 0s or a random nonce */
void serverGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  long long int counter;

  /* randombytes(shared_nonce, crypto_box_NONCEBYTES); */
  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    initial_server_nonce[counter] = 0; //REMEMBER TO CHANGE LOCATION OF NONCE

  //return shared_nonce;

}//clientGenerateNonce()

/* Construct keypairs for server's personal use. */
void  serverGenerateKeyPair()
{
  int result;
  result = crypto_box_keypair(server_pk,server_sk);
  assert(result == 0);
}//clientGenerateKeyPair()

/* Construct initial keypairs for server. */
void  initialServerGenerateKeyPair()
{
  int result;
  result = crypto_box_keypair(initial_server_pk,initial_server_sk);
  assert(result == 0);
}//clientGenerateKeyPair()

//Getters and setters for the message
