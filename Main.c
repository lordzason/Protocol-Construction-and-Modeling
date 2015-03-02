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
#include <crypto_box.h>
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

/* Main models the protocols for the client and the server*/
int main()
{
  /* Output fileNames*/
  char initial_client_encryption_location [] ="clientEncryptedFile.txt"; 

  /* Generate server's initial keyPair */
  initialServerGenerateKeyPair();
  printf("Server's Initial Public Key:\n");
  display_bytes(initial_server_pk,crypto_box_PUBLICKEYBYTES);

  /* Generate server's personal keyPair */
  serverGenerateKeyPair();
  printf("Server's Personal Public Key:\n");
  display_bytes(server_pk,crypto_box_PUBLICKEYBYTES);

  /* Generate server nonce */
  initialServerGenerateNonce();
  printf("Server's Initial Nonce:\n");
  display_bytes(initial_server_nonce, crypto_box_NONCEBYTES);

  /* Generate client nonce */
  clientGenerateNonce();
  
  /* Generate client public keyPair */
  clientGenerateKeyPair();
  printf("Client Public Key:\n");
  display_bytes(client_pk,crypto_box_PUBLICKEYBYTES);

  /* Client concatenates the nonce and its own public key */
  long long cipher_text_length = client_encrypt_nonce_pk_send(initial_server_nonce,crypto_box_NONCEBYTES,initial_server_pk, initial_server_sk,initial_client_encryption_location);
  
  /* Client encrypts concatenation using server's public key 
     (using nonce N0 from the server), signs it with server's
     first time signing key */
  // client_encrypt_nonce_pk();
  //  display_bytes(ciphertext,crypto_box_ZEROBYTES+NONCE_PK_LENGTH);

  /* Client sends encrypted message to the server */
  //  client_send_encryption("clientEncryptedFile.txt");
 
 /* Server decrypts initial message*/

  return NO_ERROR;
}
