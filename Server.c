
/*****************************************************************
 *   Authors:      Albert Owusu-Asare
 *                 Zhi Chen
 *
 *   Created:      February 28, 2015
 *   Last revised: Tue Mar 17 16:14:20 CDT 2015
 *
 *   This file contains the source for the methods of the server.
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
#include <stdlib.h>
#include <assert.h>
#include <crypto_box.h>
#include <time.h>
#include "Server.h"
#include "utils.h"
#include "devurandom.h"

//Check if all of the defines are needed

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0
#define SIZE_TIME_t              8
#define COMBINED_NONCE_LENGTH    (crypto_box_ZEROBYTES + crypto_box_NONCEBYTES 
+ crypto_box_NONCEBYTES)

/*Fields and Variables*/
//Server's secret key
unsigned char server_sk[crypto_box_SECRETKEYBYTES];
//Current nonce to be used in decrytion
unsigned char *current_nonce;
//Next nonce to be used in encryption
unsigned char * next_nonce;
//Stores the public key of the client
unsigned char client_pk [crypto_box_PUBLICKEYBYTES];

/* Activates server by generating initial server nonce and initial server
   key pair*/
void server_start_first_time_init(){
  // Generates a server initial nonce composed of  a random nonce
   randombytes(initial_server_nonce, crypto_box_NONCEBYTES);

  //set current nonce to initial nonce;
  current_nonce = initial_server_nonce;

  // Generate initial keypairs for the server 
  int result;
  result = crypto_box_keypair(initial_server_pk,initial_server_sk);
  assert(result == 0);

  // Generate personal Key pair 
  result = crypto_box_keypair(server_pk,server_sk);
  assert(result == 0);
  //Generate next_nonce
  unsigned char * temp_nonce = (unsigned char *) malloc(crypto_box_NONCEBYTES * 
                                                        sizeof(unsigned char));
  randombytes(temp_nonce, crypto_box_NONCEBYTES); 
  next_nonce = temp_nonce;
  assert(next_nonce != NULL);
}//initialise_server()

/*
 * Parameters : filename , string reprentation of the file to retrieve encrypted message from 
                cipher_text_length,  the length of the encrypted message            
 */

/*void server_decrypt_message (char * filename, long long cipher_text_length){

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
  printf("\nServer.c Server Decrypted Message:\n");
  display_bytes(message,cipher_text_length-crypto_box_PUBLICKEYBYTES);
}//server_decrypt_message(char *)

*/
/* 
 * i think what we are doing is to establish a protocol where we always use two
 * nonces
 */
void server_decrypt_message (char * filename, long long cipher_text_length){

  //Variables
  int counter;
  FILE *encryptedFile;
  unsigned char cipher_text[cipher_text_length];
  unsigned char nonce_portion[COMBINED_NONCE_LENGTH]; // stores zero bytes + 2 nonces
  unsigned char message[cipher_text_length]; //stores decrypted message
  unsigned char remaining_info[cipher_text_length -COMBINED_NONCE_LENGTH];
  unsigned char * nonce = (unsigned char) malloc(crypto_box_NONCEBYTES * sizeof(unsigned char));

  //Read file into ciphertext
  encryptedFile = fopen(filename, "r");
  fread(cipher_text,sizeof(unsigned char), cipher_text_length * sizeof(unsigned char), 
        encryptedFile);
  fclose(encryptedFile);
 

  //Use cryptobox open to decrpyt the ciphertext
  int result = crypto_box_open(message,cipher_text,cipher_text_length,current_nonce,
                               client_pk,server_sk); //initial_server_nonce will change to other nonces
  assert(result == 0);

  printf("\nServer.c Server Decrypted Message:\n");
  display_bytes(message,cipher_text_length);

  // Split message into respective components
  // Get the next nonce;
  for(counter= 0 ; counter <crypto_box_NONCEBYTES; counter ++){
    nonce[counter] = message[crypto_box_NONCEBYTES + crypto_box_ZEROBYTES + counter];

    next_nonce  = nonce;
    // Get the remaining information
    for(counter= 0; counter < cipher_text_length - COMBINED_NONCE_LENGTH ; counter ++){
      remaining_info[counter] = message[COMBINED_NONCE_LENGTH +counter];
    }//for

    // We will decide what to do with this next

  }//for
}//server_decrypt_message(char *)

/*
 * Parameters : filename , string reprentation of the file to retrieve the encrypted message 
                cipher_text_length,  the length of the encrypted message             


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

  printf("\nServer.c Server Decrypted Client Public Key:\n");
  display_bytes(client_pk,crypto_box_PUBLICKEYBYTES);
  printf("\nServer.c Server Decrypted Message:\n");
  display_bytes(message,cipher_text_length-crypto_box_PUBLICKEYBYTES);
  printf("\nServer.c Showing the current nonce after decryption:\n");
  display_bytes(current_nonce,crypto_box_NONCEBYTES);
}//server_decrypt_message(char *)
*/
/*
 * Performs encryption on the time stamp, current and next nonces
 */
void server_encrypt_time_message(char *encryptedFileLocation){
  char * newEncryptedFileLocation = encryptedFileLocation;
  // nonce current + nonce next + zero bytes + time stamp
  int length = crypto_box_ZEROBYTES + crypto_box_NONCEBYTES + crypto_box_NONCEBYTES + 1;
  unsigned char  message [length];
  unsigned char  cipher_text [length];
  union Data timestamp;
  timestamp.time = time(NULL);

  //concatenates current_nonce and next_nonce
  unsigned char combined_nonce[crypto_box_NONCEBYTES +  crypto_box_NONCEBYTES];
  // serverPairConcatenate(combined_nonce,current_nonce,crypto_box_NONCEBYTES, 
  //                    next_nonce,crypto_box_NONCEBYTES); OLD :Use utils.h instead

  concat_buffers(combined_nonce,current_nonce,crypto_box_NONCEBYTES, 
                      next_nonce,crypto_box_NONCEBYTES);

  //Concatenate the zero bytes to the combined nonces
  int combined_zero_nonce_length =  crypto_box_NONCEBYTES +  crypto_box_NONCEBYTES + crypto_box_ZEROBYTES;
  //  serverZeroConcatenate(combined_zero_nonce,combined_nonce,combined_zero_nonce_length);
  //  serverZeroConcatenate(message,combined_nonce,combined_zero_nonce_length);
  concat_zero_bytes(message,combined_nonce,combined_zero_nonce_length);
  message[length - 1] = timestamp.time_bytes;

  //Concatenate the zero bytes with the combined nonces to the time stamp
  // serverPairConcatenate(message,combined_zero_nonce,combined_zero_nonce_length, 
  //  timestamp.time_bytes, 1);

  //Encrypt the result of all concatenation
  int result = crypto_box(cipher_text,message,length,current_nonce,client_pk,server_sk);
  assert(result == 0);
  printf("\nServer.c Server Encrypt Time Message:\n");
  display_bytes(cipher_text,length);

  //Server sends encrypted time stamp to the client via a file
  //  server_send_encryption(newEncryptedFileLocation,cipher_text,length); new uses utils
  write_message_to_file(newEncryptedFileLocation,cipher_text,length); //new uses utils

}//server_encrypt_message()







/*
WE MIGHT NOT NEED THIS. SWITCHED TO UTILS.C
void  serverPairConcatenate (unsigned char* result, unsigned char *element1, long long element1Length, unsigned char *element2, long long element2Length)
{
  int counter;

  for (counter = 0; counter < element1Length; counter++)
    result[counter] = element1[counter];

  for (counter = 0; counter < element2Length; counter++)
    result[element1Length + counter] = element2[counter];
}//serverPairConcatenate




*/



/*
WE MIGHT NOT NEED THIS SWITCHED TO utils.c
void serverZeroConcatenate (unsigned char * result, unsigned char *element1, long long element1Length)
{
  int counter;

  for (counter = 0; counter < crypto_box_ZEROBYTES; counter++)
    result[counter] = 0;

  for (counter = 0; counter < element1Length; counter++)
    result[crypto_box_ZEROBYTES + counter] = element1[counter];
  printf("Server concatenate with zero\n");
  display_bytes(result,crypto_box_ZEROBYTES+element1Length );
}//serverZeroConcatenate

*/
/* Server sends encrypted message to the client */
 /*
USES MUCH GENERAL VERSION IN UTILS.H
void server_send_encryption(char *encryptedFileLocation,unsigned char ciphertext [], int ciphertext_length )
{
  FILE *serverEncryptedFile;
  serverEncryptedFile = fopen(encryptedFileLocation, "w");

  fwrite(ciphertext, sizeof(unsigned char), ciphertext_length * sizeof(unsigned char), serverEncryptedFile);
  printf("Server Wrote to File the Following:\n");
  display_bytes(ciphertext,crypto_box_ZEROBYTES+ciphertext_length);
  fclose(serverEncryptedFile);
}//client_send_encryption

 */
  /*void initialServerGenerateNonce()
{
  // static unsigned char shared_nonce[crypto_box_NONCEBYTES];
  long long int counter;

  for (counter = 0; counter < crypto_box_NONCEBYTES; counter++)
    initial_server_nonce[counter] = 0;
}//clientGenerateNonce()*/

/* Construct initial keypairs for server. 
void  initialServerGenerateKeyPair()
{
  int result;
  result = crypto_box_keypair(initial_server_pk,initial_server_sk);
  assert(result == 0);
  }//clientGenerateKeyPair()*/

/* Generates a random nonce
void serverGenerateNonce()
{
  randombytes(next_nonce, crypto_box_NONCEBYTES); 
  printf("The server's next nonce is :\n");
  display_bytes(next_nonce,crypto_box_NONCEBYTES);
}//clientGenerateNonce()

*/

/* Construct keypairs for server's personal use. 
void  serverGenerateKeyPair()
{
  int result;
  result = crypto_box_keypair(server_pk,server_sk);
  assert(result == 0);
}//clientGenerateKeyPair()

*/
