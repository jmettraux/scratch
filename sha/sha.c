
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
  char data[] = "lore ipsum\n";
  char hash[SHA512_DIGEST_LENGTH];
  SHA512((unsigned char *)data, strlen(data), (unsigned char *)hash);

  printf("%i\n", SHA512_DIGEST_LENGTH);
  puts(data);
  for (size_t i = 0; i < SHA512_DIGEST_LENGTH; ++i)
  {
    //printf("i%zu %02x, ", i, (unsigned char)hash[i]);
    printf("%02x", (unsigned char)hash[i]);
  }
  printf("\n");
}

