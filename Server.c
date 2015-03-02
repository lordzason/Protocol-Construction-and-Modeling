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

/* Decrypt initial message */
/*void server_decrypt_message (char * filename, long long cipher_text_length){
  //variables cryptobox_open
  unsigned char message[cipher_text_length];
  unsigned char ciphertext[cipher_text_length];
  // read file into ciphertext
  FILE *encryptedFile;
  encryptedFile = fopen(filename, "r");
  fread(ciphertext,sizeof(unsigned char), cipher_text_length * sizeof(unsigned char), encryptedFile);
  fclose(encryptedFile);
  //use cryptobox open to decrpyt the ciphertext
  //crypto_box_open(m,c,clen,n,pk,sk);
  printf("Display server_sk before client decryption:\n");
  display_bytes(server_sk,crypto_box_SECRETKEYBYTES);
  int result = crypto_box_open(message, ciphertext, cipher_text_length,initial_server_nonce,initial_server_pk,server_sk);
  //int result = crypto_box_open(message, ciphertext, cipher_text_length,initial_server_nonce,client_pk,initial_server_sk);
  assert(result == 0);
  printf("Server Decrypted Message: \n");
  display_bytes(message,cipher_text_length);
}//server_decrypt_message(char *)
*/



void server_decrypt_message (char * filename, long long cipher_text_length){

  //variables cryptobox_open
  unsigned char ciphertext[cipher_text_length];
  // read file into ciphertext
  FILE *encryptedFile;
  encryptedFile = fopen(filename, "r");
  fread(ciphertext,sizeof(unsigned char), cipher_text_length * sizeof(unsigned char), encryptedFile);
  fclose(encryptedFile);

  //shed of the client public key
  unsigned char receive_client_pk [crypto_box_PUBLICKEYBYTES];
    unsigned char receive_encoded [cipher_text_length -crypto_box_PUBLICKEYBYTES];
  int counter;
  for (counter = 0; counter <crypto_box_PUBLICKEYBYTES ; counter++)
    receive_client_pk[counter] = ciphertext[counter];
  for (counter = 0; counter <cipher_text_length ; counter++)
    receive_encoded[counter] = ciphertext[counter+crypto_box_PUBLICKEYBYTES ];


  //variables cryptobox_open
  unsigned char message[cipher_text_length - crypto_box_PUBLICKEYBYTES];
 
  //use cryptobox open to decrpyt the ciphertext
  //crypto_box_open(m,c,clen,n,pk,sk);
  printf("Display server_sk before client decryption:\n");
  int result = crypto_box_open(message, receive_encoded, cipher_text_length-crypto_box_PUBLICKEYBYTES,initial_server_nonce,receive_client_pk,server_sk);
  //int result = crypto_box_open(message, ciphertext, cipher_text_length,initial_server_nonce,client_pk,initial_server_sk);
  assert(result == 0);
  printf("Server Decrypted Message: \n");
  display_bytes(message,cipher_text_length-crypto_box_PUBLICKEYBYTES);
}//server_decrypt_message(char *)

