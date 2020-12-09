#ifndef ENCRYPT_H
#define ENCRYPT_H

void Arbiter_Des_encipher(char* plaintext,char* ciphertext,const unsigned char* key);

void Arbiter_Des_decipher(char* ciphertext, char* plaintext, const unsigned char* key);

#endif