#include "include.h"



void Arbiter_Des_encipher(char* plaintext,char* ciphertext,const unsigned char* key)
{
	int i =0;
	int j =0;
	int k =0;
	

	int buf_len =0;
	int enc_len =0;


	for(i=0; i<5; i++)
	{
		for(j=0; j<8; j++)
		{
		
			des_encipher((const unsigned char*)(plaintext+ ((j+i)+(7*i))),(unsigned char*)(ciphertext+((j+i)+(7*i))),key);
		}
		
		
	}
}


void Arbiter_Des_decipher(char* ciphertext, char* plaintext2, const unsigned char* key)
{
	int i =0;
	int j =0;

	int dec_len =0;

	for(i=0; i<5; i++)
	{
		for(j=0; j<8; j++)
		{
			
			des_decipher((const unsigned char*)(ciphertext+((j+i)+(7*i))),(unsigned char*)(plaintext2+ ((j+i)+(7*i))),key);
		}
		
		
	}
	dec_len = strlen(ciphertext);
	printf("%s\t%d\n",ciphertext,dec_len);
	
	dec_len = strlen(plaintext2);
	printf("복호화된 문자열\n");
	printf("%s\t%d\n",plaintext2,dec_len);
}