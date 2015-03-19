/*****************************************************************
 *   Authors:     Albert Owusu-Asare  <owusuasa@grinnell.edu>
 *                Zhi Chen
 *   Last edited: Wed Mar 18 17:33:35 CDT 2015

 *
 *   This file contains function prototypes for  basic utilities for the 
 *   Protocol Construction.
 *   
 *******************************************************************/
#ifndef _UTILS_  //include guards to prevent double declaration
#define _UTILS_

#ifndef _CRYPTO_BOX_
#define _CRYPTO_BOX_
#include <crypto_box.h>  //crypto box libraries
#endif
#ifndef _RANDOM_
#define _RANDOM_
#include "devurandom.h"
#endif

/* Display the contents of an array of unsigned char values. 
   This method  was copied verbatim ,with permission, from
   John Stone, Grinnell College.
*/
 void display_bytes(const unsigned char *byte_vector, long long int length);

/* Adds "crypto_box_ZEROBYTES" number of zero bytes to the front of the 
   contents of "element". Note that " crypto_box_ZEROBYTES" is part 
   of the crypto_box libraries.
*/
void concat_zero_bytes(unsigned char * result_buffer, unsigned char *element, 
                     long long elementLength);

/* Concatenates two buffers together.
   Parameters : buffer1, the first buffer
                buf1_len, the length of the first buffer
                buffer2, the second buffer
                buf2_len, the length of the second buffer
   Post condition : contents of buffer1 appears before contents of buffer 2
*/
void  concat_buffers (unsigned char* result_buffer, unsigned char *buffer1, 
                      long long buf1_len, unsigned char *buffer2, 
                      long long buf2_len);

/* Concatenates 3 buffers : current nonce ,next nonce, message and adds
 * zero bytes in front of the resultant buffer.
 *
 */
unsigned char * concat_zero_nonce_message (unsigned char  * n0, unsigned char * n1,
                                           unsigned char * message, 
                                           long long message_length);

/* Writes the contents of the buffer "text" to the fileLocation "fileLocation"
*/
void write_message_to_file(char *fileLocation,unsigned char text [],
                           int text_length);

/* Generates a random nonce see documentation of devurandom.c
*/
unsigned char *  generate_nonce();



#endif
