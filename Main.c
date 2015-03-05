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
#include <time.h>
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
  char server_encrypted_timestamp_location [] = "serverEncryptedTimeStamp.txt"; 

  /* Generate server's initial keyPair */
  initialServerGenerateKeyPair();
  printf("Server's Initial Public Key:\n");
  display_bytes(initial_server_pk,crypto_box_PUBLICKEYBYTES);
  printf("Server's Initial Secret Key:\n");
  display_bytes(initial_server_sk,crypto_box_SECRETKEYBYTES);

  /* Generate server's personal keyPair */
  serverGenerateKeyPair();
  printf("Server's Personal Public Key:\n");
  display_bytes(server_pk,crypto_box_PUBLICKEYBYTES);
  printf("Server's Personal Secret Key:\n");
  display_bytes(server_sk,crypto_box_SECRETKEYBYTES);

  /* Generate server nonce */
  initialServerGenerateNonce();
  printf("Server's Initial Nonce:\n");
  display_bytes(initial_server_nonce, crypto_box_NONCEBYTES);

  /* Generate client nonce */
  printf("Client's Nonce:\n");
  clientGenerateNonce();
  
  /* Generate client public keyPair */
  clientGenerateKeyPair();
  printf("Client Public Key:\n");
  display_bytes(client_pk,crypto_box_PUBLICKEYBYTES);
  printf("Client Secret Key:\n");
  display_bytes(client_sk,crypto_box_SECRETKEYBYTES);

  /* Client concatenates the nonce and its own public key */
  printf("Client Encrypt and Send\n");
  long long cipher_text_length = client_encrypt_nonce_pk_send(initial_server_nonce,crypto_box_NONCEBYTES,server_pk,initial_client_encryption_location);
  printf("Client Encrypt and Send End\n");
  
  /* Server decrypts initial message*/
  printf("Server Decrypt\n");
  //server_decrypt_message (initial_client_encryption_location,cipher_text_length);
  initial_server_decrypt_message (initial_client_encryption_location,cipher_text_length);

  /* PROTOCOL 3*/
  serverGenerateNonce(); 
  time_t name = time(NULL);
  server_encrypt_time_message(server_encrypted_timestamp_location);

  return NO_ERROR;
}
