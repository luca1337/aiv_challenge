#include <aiv_file.h>

int main(int argc, char** argv)
{
    srand((unsigned)time(NULL));

    aiv_file_t aiv_file;
    aiv_file_init(&aiv_file);

    if(argc > 1)
        aiv_file_readfloat_bin(&aiv_file, argv[1]);
    else
        aiv_file_writefloat_bin(&aiv_file, "correct_size.bin");

    return 0;
}