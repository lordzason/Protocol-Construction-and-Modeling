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
#include "crypto_box.h"
#include "Client.h"

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0

//unsigned char shared_nonce[crypto_box_NONCEBYTES];

/* Generates a nonce composed of 0s or a random nonce */
unsigned char* clientGenerateNonce()
{
  static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  long long int counter;

  /* randombytes(shared_nonce, crypto_box_NONCEBYTES); */
  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    shared_nonce[counter] = 0;

  return shared_nonce;
}
