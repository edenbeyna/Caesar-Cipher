#include "cipher.h"
#include <ctype.h>
#include <stdio.h>

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.
int const lower_ascii = 97;
int const upper_ascii = 65;
int const alphabet = 26;

// See full documentation in header file
void encode (char s[], int k)
{
  int i;
  int cypher_value;
  while(k < 0){
      k = k + alphabet;
  }
  for (i=0; s[i] != '\0'; i++){
      if (!isalpha(s[i])){
          continue;
      }
      else if(isupper(s[i])){
          cypher_value =
                  ((int) s[i] - upper_ascii + k) % alphabet + upper_ascii;
          s[i] = (char) cypher_value;


      }
      else{
          cypher_value = ((int) s[i] - lower_ascii + k) % alphabet + lower_ascii;
          s[i] = (char) cypher_value;
      }
  }
}

// See full documentation in header file
void decode (char s[], int k)
{
    k = -k;
    encode(s, k);
}

