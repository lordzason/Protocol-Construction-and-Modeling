/* Main */

/* 
   Albert Owusu-Asare
   Zhi Chen

   Code Referenced From:
   John David Stone
   Department of Computer Science
   Grinnell College
   stone@cs.grinnell.edu

   created February 25, 2015
   last revised February 25, 2015
*/

#include <stdio.h>
#include <assert.h>
#include "crypto_box.h"
#include "Client.h"
#include "Server.h"
#include "devurandom.h"

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0

/* Display the contents of an array of unsigned char values. */
void display_bytes(const unsigned char *byte_vector, long long int length) {
  long long int counter = 0;
  while (counter < length) {
    (void) printf("%02x", byte_vector[counter]);
    (void) putchar((++counter & 0xF) ? ' ' : '\n');
  }
  if (counter & 0xF)
    putchar('\n');
  putchar('\n');
}

int main()
{
  unsigned char* client_nonce_n1;
  clientkeypair ckeypair;

  client_nonce_n1 = clientGenerateNonce(); //Generates nonce for client
  //printf("Client Nonce N1\n");
  display_bytes(client_nonce_n1, crypto_box_NONCEBYTES); //Display client nonce

  ckeypair = clientGenerateKeyPair(); //Generate the client key pair

  //Concate nonce and public key pair

  //Encrypt with server's initial public key and send to the server

  return NO_ERROR;
}
