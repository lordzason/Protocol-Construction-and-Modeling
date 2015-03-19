/*****************************************************************
 *   Authors:      Albert Owusu-Asare <owusuasa@grinnell.edu>
 *                 Zhi Chen           
 *
 *   Created:      created February 25, 2015
 *   Last revised: Tue Mar 17 16:15:47 CDT 2015
 *
 *   This file contains the main method that simulates the Protocol
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
#include "Server.h"
#include "devurandom.h"
#include "utils.h"

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0


/* Main models the protocols for the client and the server*/
int main()
{
  /* Output fileNames*/
  char initial_client_encryption_location [] ="clientEncryptedFile.txt"; 
  char server_encrypted_timestamp_location [] = "serverEncryptedTimeStamp.txt"; 

  /* PROTOCOL STEP 0 :Sever Initialisation: */

  printf("\nSTEP 0 : Beginning server initialisation process...\n");
  server_start_first_time_init();

  //display progress to stdout
  printf("\nServer's Initial Public Key:\n");
  display_bytes(initial_server_pk,crypto_box_PUBLICKEYBYTES);
  printf("\nServer's Initial Secret Key:\n");
  display_bytes(initial_server_sk,crypto_box_SECRETKEYBYTES);
  printf("\nServer's Initial Nonce:\n");
  display_bytes(initial_server_nonce, crypto_box_NONCEBYTES);
  printf("\nServer's Personal Public Key:\n");
  display_bytes(server_pk,crypto_box_PUBLICKEYBYTES);
  printf("\nGenerated server's next nonce.. Not shown here for safety\n");

  /* PROTOCOL STEP 1: Client send initial message  */
     printf("\nSTEP 1 : Client to send initial message...\n");
  
     // Generate client public keyPair 
  clientGenerateKeyPair();
  printf("\nClient Public Key:\n");
  display_bytes(client_pk,crypto_box_PUBLICKEYBYTES);

  // Client concatenates the nonce and its own public key 
  client_send_initial_message(initial_client_encryption_location,server_pk);
  // long long cipher_text_length = client_encrypt_nonce_pk_send(initial_server_nonce,
  //    crypto_box_NONCEBYTES,
  //   server_pk,
  //    initial_client_encryption_location);
  printf("\nClient Encrypted and Sent Initial Nonce to file\n");


  /* PROTOCOL STEP 2: Server Decrypts Client's Message and Encrypts New Message */
  /* Server decrypts initial message*/
  //printf("Server Decrypt\n");
  // server_decrypt_message (initial_client_encryption_location,cipher_text_length);

  /* PROTOCOL STEP 3*/
  //time_t name = time(NULL);
  //server_encrypt_time_message(server_encrypted_timestamp_location);

  return NO_ERROR;
}
  /* Generate server's personal keyPair 
  serverGenerateKeyPair();
  printf("Server's Personal Public Key:\n");
  display_bytes(server_pk,crypto_box_PUBLICKEYBYTES);
  */

  /* Generate server nonce 
    initialServerGenerateNonce();
  printf("Server's Initial Nonce:\n");
  display_bytes(initial_server_nonce, crypto_box_NONCEBYTES);*/



/* Generate client nonce */
  //printf("Client's Nonce:\n");
  //clientGenerateNonce();
