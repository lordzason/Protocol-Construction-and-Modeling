
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
//server's secret key
unsigned char server_sk[crypto_box_SECRETKEYBYTES];
//current nonce to be used in decrytion
unsigned char current_nonce[crypto_box_NONCEBYTES]; 
//next nonce to be used in encryption
unsigned char next_nonce[crypto_box_NONCEBYTES]; 
//stores the public key of the client
unsigned char client_pk [crypto_box_PUBLICKEYBYTES];

/* Generates a server initial nonce composed of 0s or a random nonce */
void initialServerGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  long long int counter;

  /* randombytes(shared_nonce, crypto_box_NONCEBYTES); */
  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    initial_server_nonce[counter] = 0;
}//clientGenerateNonce()



/* Generates a nonce composed of 0s or a random nonce */
void serverGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  long long int counter;

  /* randombytes(shared_nonce, crypto_box_NONCEBYTES); */
  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    initial_server_nonce[counter] = 0; //REMEMBER TO CHANGE LOCATION OF NONCE
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


/*
 * Parameters : filename , string reprentation of the file to retrieve encrypted message from 
                cipher_text_length,  the length of the encrypted message            
 */
void server_decrypt_message (char * filename, long long cipher_text_length){

  //Variables
  int counter;
  FILE *encryptedFile;
  unsigned char ciphertext[cipher_text_length];
  unsigned char receive_encoded [cipher_text_length]; //length change???
  unsigned char message[cipher_text_length - crypto_box_PUBLICKEYBYTES]; //length change???

  //Read file into ciphertext
  encryptedFile = fopen(filename, "r");
  fread(ciphertext,sizeof(unsigned char), cipher_text_length * sizeof(unsigned char), 
        encryptedFile);
  fclose(encryptedFile);

  //Shed off the client's question from the nonces???
  for (counter = 0; counter <cipher_text_length ; counter++)
    receive_encoded[counter] = ciphertext[counter];

  //Separate the two nonces???

  //Use cryptobox open to decrpyt the ciphertext
  int result = crypto_box_open(message, receive_encoded, 
                               cipher_text_length-crypto_box_PUBLICKEYBYTES,initial_server_nonce,
                               client_pk,server_sk); //initial_server_nonce will change to other nonces
  assert(result == 0);
  printf("Server Decrypted Message:\n");
  display_bytes(message,cipher_text_length-crypto_box_PUBLICKEYBYTES);
}//server_decrypt_message(char *)

/*
 * Parameters : filename , string reprentation of the file to retrieve the encrypted message 
                cipher_text_length,  the length of the encrypted message             
*/
void initial_server_decrypt_message (char * filename, long long cipher_text_length){

  //Variables
  int counter;
  FILE *encryptedFile;
  unsigned char ciphertext[cipher_text_length];
  int actual_length = cipher_text_length -crypto_box_PUBLICKEYBYTES;
  //unsigned char receive_encoded [cipher_text_length -crypto_box_PUBLICKEYBYTES];
  unsigned char receive_encoded [actual_length];
  // unsigned char message[cipher_text_length - crypto_box_PUBLICKEYBYTES];
  unsigned char message[actual_length];
 // Read file into ciphertext
  
  encryptedFile = fopen(filename, "r");
  fread(ciphertext,sizeof(unsigned char), cipher_text_length * sizeof(unsigned char), 
        encryptedFile);
  fclose(encryptedFile);

  //Shed off the client public key if inital message
  for (counter = 0; counter <crypto_box_PUBLICKEYBYTES ; counter++)
    client_pk[counter] = ciphertext[counter];
  for (counter = 0; counter <cipher_text_length ; counter++)
    receive_encoded[counter] = ciphertext[counter+crypto_box_PUBLICKEYBYTES];

  //Use cryptobox open to decrpyt the ciphertext
  int result = crypto_box_open(message, receive_encoded, 
                               actual_length,initial_server_nonce,
                               client_pk,server_sk);
  assert(result == 0);

  //Shed of zero bytes from the decrypted message
    for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    current_nonce[counter] = message[counter+crypto_box_ZEROBYTES];

  printf("Server Decrypted Client Public Key:\n");
  display_bytes(client_pk,crypto_box_PUBLICKEYBYTES);
  printf("Server Decrypted Message:\n");
  display_bytes(message,cipher_text_length-crypto_box_PUBLICKEYBYTES);
  printf("Showing the current nonce after decryption:\n");
  display_bytes(current_nonce,crypto_box_NONCEBYTES);
}//server_decrypt_message(char *)
