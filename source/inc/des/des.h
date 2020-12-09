#ifndef __DES_H_
#define __DES_H_


typedef enum DesEorD_ {encipher, decipher} DesEorD;

static void permute(unsigned char* bits, const int* mapping, int n);

static int des_main(const unsigned char* source, unsigned char* target, const unsigned char* key, DesEorD direction);

void des_encipher(const unsigned char* plaintext, unsigned char* ciphertext, const unsigned char* key);

void des_decipher(const unsigned char* ciphertext, unsigned char* plaintext, const unsigned char* key);

#endif