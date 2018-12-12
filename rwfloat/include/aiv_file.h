#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUF_SZ 10

typedef struct aiv_file{
    FILE* stream;
    char* buffer;
}aiv_file_t;

int aiv_file_init(aiv_file_t* aiv_file)
{
    memset(aiv_file, 0, sizeof(aiv_file_t));
    aiv_file->buffer = malloc(sizeof(float) * MAX_BUF_SZ);
    if(!aiv_file->buffer){
        fprintf(stderr, "could not allocate memory buffer for file\n");
        return -1;
    }
    memset(aiv_file->buffer, 0, sizeof(float) * MAX_BUF_SZ);
    return 0;
}

int aiv_file_writefloat_bin(aiv_file_t* aiv_file, const char* file)
{
    fopen_s(&aiv_file->stream, file, "wb");
    if(!aiv_file->stream){
        fprintf(stderr, "could not open file\n");
        return -1;
    }

    int i = 0;
    float value = 10.0f;
    for(; i < MAX_BUF_SZ; i++)
    {
        aiv_file->buffer[i] = ((float)rand() / (float)(RAND_MAX)) * value;
        printf("writing: [%f] at [%d]\n", (float)aiv_file->buffer[i], i);
    }
    printf("size of file [%llu] bytes.\n", sizeof(float) * MAX_BUF_SZ);
    printf("--------------------------\n");

    fwrite(aiv_file->buffer, sizeof(float), MAX_BUF_SZ, aiv_file->stream);

    fclose(aiv_file->stream);
    free(aiv_file->buffer);

    return 0;
}

int aiv_file_readfloat_bin(aiv_file_t* aiv_file, const char* file)
{
    fopen_s(&aiv_file->stream, file, "rb");
    if(!aiv_file->stream){
        fprintf(stderr, "could not open file\n");
        return -1;
    }

    fseek(aiv_file->stream, 0, SEEK_END);
    int file_length = ftell(aiv_file->stream);
    fseek(aiv_file->stream, 0, SEEK_SET);

    if(file_length != (sizeof(float) * MAX_BUF_SZ)){
        fprintf(stderr, "incorrect file size [%d] bytes, the file size must be exactly [%llu] bytes.\n", file_length, sizeof(float) * MAX_BUF_SZ);
        return -1;
    }

    char* data = malloc(file_length);
    if(!data){
        fprintf(stderr, "could not allocate memory buffer for reading file\n");
        return -1;
    }

    // pointer math, here i wil read char * char but for the sizeof(float)
    size_t result = fread(data, sizeof(char), file_length, aiv_file->stream);
    if(result != file_length){
        fprintf(stderr, "there was an error while reading file\n");
        return -1;
    }

    int i = 0;
    for(; i < (file_length / sizeof(float)); i++)
    {
        printf("reading: [%f] at [%d]\n", (float)data[i], i);
    }

    fclose(aiv_file->stream);
    free(data);

    return 0;
}