
/*****************************************************************
 *   Authors:      Albert Owusu-Asare
 *                 Zhi Chen
 *
 *   Created:      February 10, 2015
 *   Last revised: Tue Mar 17 16:14:20 CDT 2015
 *
 *   This file contains the source for the methods of the client.
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
#include "Client.h"
#include "utils.h"
#include "devurandom.h"

#define INTERNAL_MESSAGE_LENGTH  45
#define MESSAGE_LENGTH           (crypto_box_ZEROBYTES + INTERNAL_MESSAGE_LENGTH)
#define NO_ERROR                 0
#define NONCE_PK_LENGTH          crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES
#define COMBINED_NONCE_LENGTH    (crypto_box_ZEROBYTES + crypto_box_NONCEBYTES + crypto_box_NONCEBYTES)
//#define MESSAGE_1_LENGTH         crypto_box_PUBLICKEYBYTES



/*Fields and Variables*/
unsigned char client_sk[crypto_box_SECRETKEYBYTES];
unsigned char * current_nonce;
unsigned char * next_nonce;
unsigned char* concatResult;
unsigned  char *message1;


/* Construct keypairs for sender and receiver. */
void clientGenerateKeyPair(){
  int result;
  result = crypto_box_keypair(client_pk,client_sk);
  assert(result == 0);
  printf("\nClient.c Client Secret Key Generate:\n"); //remember to take out this line
  display_bytes(client_sk,crypto_box_SECRETKEYBYTES); //remember to take out this line
}//clientGenerateKeyPair()


/* Client encrypts concatenation using server's public key 
   (using nonce N0 from the server), signs it with server's
   first time signing key */
/*
long long  client_encrypt_nonce_pk_send(unsigned char *serverNonce,long long nonce_length,
                                        unsigned char *server_pk,char * output_filename)
{
  current_nonce = serverNonce;
  next_nonce = generate_nonce();
  long long ciphertext_length = nonce_length + crypto_box_ZEROBYTES;
  unsigned char ciphertext[ciphertext_length];
  unsigned char concateResult[ciphertext_length];
  unsigned char final_message [ciphertext_length + crypto_box_PUBLICKEYBYTES];
  int result;

  // Concatenate nonce N1 with zero bytes
  concat_zero_bytes(concateResult,next_nonce,nonce_length);

  // Encrypts the results of the concatenation 
  result = crypto_box(ciphertext,concateResult,ciphertext_length,serverNonce,server_pk,client_sk);
  assert(result == 0);

  // Concatenate the results from encryption with client public key
  concat_buffers(final_message,client_pk, crypto_box_PUBLICKEYBYTES, ciphertext, ciphertext_length);
 
  printf("\nClient.c Initial cypher text of  N1 + client public key:\n");
  display_bytes(final_message,ciphertext_length + crypto_box_PUBLICKEYBYTES);

  // Send the results of the encryption to an output file
  write_message_to_file(output_filename,final_message,ciphertext_length+crypto_box_PUBLICKEYBYTES);
  
  // Prepare nonce for next transmission
  current_nonce = next_nonce;
  next_nonce =  generate_nonce();
  return ciphertext_length + crypto_box_PUBLICKEYBYTES ;
}//client_encrypt_nonce_pk()

*/

/*
 * Encrypts Client messages
 *
 */

unsigned char * client_encrypt_message(unsigned char * message, long long message_length,
                              unsigned char * receiver_pk){
  

  unsigned char *unencrypted_message;
  unsigned long long mlen = COMBINED_NONCE_LENGTH + message_length ;
  unsigned char *encrypted_message = (unsigned char *) malloc((COMBINED_NONCE_LENGTH + message_length) 
                                                              * sizeof(unsigned char));  
  int results;

  //generate next nonce each time a new message is to be sent
  next_nonce = generate_nonce();

  // Every message to be encrypted will be of the form:
  // zero bytes + current Nonce + Next Nonce + message;
  unencrypted_message = concat_zero_nonce_message (current_nonce,next_nonce,
                                                   message, message_length);
  //use crypto box to encrypt the message     
  results =  crypto_box(encrypted_message,unencrypted_message,mlen,current_nonce,receiver_pk,client_sk);
  assert(results == 0);
  return encrypted_message;
}//client_encrypt_message()


/*
 *  Client sends initial message
 */
void client_send_initial_message(char * output_filename,unsigned char * receiver_pk){
  //  message1 = client_pk;
  unsigned char * encrypted_message = client_encrypt_message(message1,MESSAGE_1_LENGTH,receiver_pk); 
  write_message_to_file(output_filename,encrypted_message,MESSAGE_1_LENGTH);
}//


/*
 * Rolls through the array of messages and selects the next message to send.
 */

unsigned char * next_message(){
  assert(message_counter < NUM_MESSAGES);
  unsigned char * message = messages[message_counter];
  message_counter ++;
  return message;
}
