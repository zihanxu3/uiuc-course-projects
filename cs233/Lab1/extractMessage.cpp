/**
 * @file
 * Contains an implementation of the extractMessage function.
 */

#include <iostream> // might be useful for debugging
#include <assert.h>
#include "extractMessage.h"

using namespace std;

char *extractMessage(const char *message_in, int length) {
   // Length must be a multiple of 8
   assert((length % 8) == 0);

   // allocates an array for the output
   char *message_out = new char[length];
   for (int i=0; i<length; i++) {
   		message_out[i] = 0;    // Initialize all elements to zero.
	}

	// TODO: write your code here
    for (int i = 0; i < length / 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                message_out[i*8 + j] = ((message_in[i*8 + k] >> j) & 1) << k | message_out[i*8 + j];
            }
        }
    }
	return message_out;
}
