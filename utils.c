/*****************************************************************
 *   Authors: Albert Owusu-Asare
 *            Zhi Chen
 *
 *   Last revised:  Tue Mar 17 16:14:20 CDT 2015
 *
 *   This file contains the source for  basic utilities for the 
 *   Protocol Construction.
 *
 *   The file contians the following methods:
 *   
 *******************************************************************/
#include <stdio.h>
#include <utils.h>
#include <stdlib.h>
#include <crypto_box.h>
#include "devurandom.h" //used for testing with random bytes


/* Display the contents of an array of unsigned char values. 
   This method  was copied verbatim ,with permission, from
   John Stone, Grinnell College.
*/
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


/* Adds "crypto_box_ZEROBYTES" number of zero bytes to the front of the 
   contents of "element". Note that " crypto_box_ZEROBYTES" is part 
   of the crypto_box libraries.
*/
void concat_zero_bytes(unsigned char * result, unsigned char *element, 
long long elementLength)
{
  int counter;
  for (counter = 0; counter < crypto_box_ZEROBYTES; counter++)
    result[counter] = 0;

  for (counter = 0; counter < elementLength; counter++)
    result[crypto_box_ZEROBYTES + counter] = element[counter];

}//serverZeroConcatenate(unsigned char *, unsigned char *, long long)

/* Concatenates two buffers together.
   Parameters : buffer1, the first buffer
                buf1_len, the length of the first buffer
                buffer2, the second buffer
                buf2_len, the length of the second buffer
   Post condition : contents of buffer1 appears before contents of buffer 2
*/
void  concat_buffers (unsigned char* result_buffer, unsigned char *buffer1, 
                      long long buf1_len, unsigned char *buffer2, 
                      long long buf2_len){

  int counter;

  for (counter = 0; counter < buf1_len; counter++)
    result_buffer[counter] = buffer1[counter];

  for (counter = 0; counter < buf2_len; counter++)
    result_buffer[buf1_len + counter] = buffer2[counter];

}//concat_buffers(unsigned char *,long long,  unsigned char *, long long)

/* Concatenates 3 buffers : current nonce ,next nonce, message and adds
 * zero bytes in front of the resultant buffer.
 * 

/* Writes the contents of the buffer "text" to the fileLocation "fileLocation"
*/
void write_message_to_file(char *fileLocation,unsigned char text [],
                           int text_length){
  FILE *output_stream;
  output_stream = fopen(fileLocation, "w");

  fwrite(text, sizeof(unsigned char), text_length * sizeof(unsigned char),
         output_stream);

 
  fclose(output_stream);

}//write_message_to_file(char *, unsigned char [])

/* Generates a random nonce see documentation of devurandom.c */
unsigned char *  generate_nonce(){
  unsigned char * nonce =  (unsigned char *) malloc(sizeof(unsigned char) 
                                                    *crypto_box_NONCEBYTES);
  randombytes(nonce, crypto_box_NONCEBYTES); 
  return nonce;
}//generate_nonce
/*
int main (){
 
 //  Variables for testing
  char out_file [45] ="output_filename.txt";
 unsigned char sample_nonce[crypto_box_NONCEBYTES];
 unsigned char another_nonce[crypto_box_NONCEBYTES];
 unsigned char resultant[crypto_box_NONCEBYTES + crypto_box_ZEROBYTES]; 


 //add random bytes to all sample buffers
 randombytes(sample_nonce, crypto_box_NONCEBYTES);
 randombytes(another_nonce, crypto_box_NONCEBYTES);

  printf("Testing sample Nonce:\n");
  display_bytes(sample_nonce, crypto_box_NONCEBYTES);
  printf("Testing sample Nonce: +zero Bytes\n");
  concat_zero_bytes(resultant,sample_nonce,crypto_box_NONCEBYTES);

  // TEST 02 : testing file send; PASS
  write_message_to_file(out_file,resultant,crypto_box_NONCEBYTES + 
                        crypto_box_ZEROBYTES);


  //TEST 03 : testing contenation of two buffers : PASS
  unsigned char resultant_00[crypto_box_NONCEBYTES+crypto_box_NONCEBYTES];
  concat_buffers (resultant_00,sample_nonce, crypto_box_NONCEBYTES,
                  another_nonce, crypto_box_NONCEBYTES);
 printf("Testing another nonce:s\n");
 display_bytes(another_nonce,crypto_box_NONCEBYTES);
 printf("Testing concatenation of two bytes:s\n");
  display_bytes(resultant_00, crypto_box_NONCEBYTES+crypto_box_NONCEBYTES);


  //TEST 04 : Generate nonce test :PASS
  unsigned char * nonce = generate_nonce();
 printf("Testing generate_nonce():\n");
  display_bytes(nonce,crypto_box_NONCEBYTES);
  return 0;
}//main for testing

*/
