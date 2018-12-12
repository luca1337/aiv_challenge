#include <aiv_unit_test.h>
#include <aiv_file.h>

TEST(aiv_file_init)
{
    aiv_file_t aiv_file;
    int result = aiv_file_init(&aiv_file);

    ASSERT_THAT(result == 0);
}

TEST(aiv_file_written)
{
    aiv_file_t aiv_file;
    aiv_file_init(&aiv_file);

    int result = aiv_file_writefloat_bin(&aiv_file, "test.bin");

    ASSERT_THAT(result == 0);
}

TEST(aiv_file_read_size_green)
{
    aiv_file_t aiv_file;
    aiv_file_init(&aiv_file);

    int result = aiv_file_readfloat_bin(&aiv_file, "correct_size.bin");

    ASSERT_THAT(result == 0);
}

TEST(aiv_file_read_size_red)
{
    aiv_file_t aiv_file;
    aiv_file_init(&aiv_file);

    int result = aiv_file_readfloat_bin(&aiv_file, "incorrect_size.bin");

    ASSERT_THAT(result == -1);
}

int main(int argc, char** argv)
{
    RUN_TEST(aiv_file_init);
    RUN_TEST(aiv_file_written);
    RUN_TEST(aiv_file_read_size_green);
    RUN_TEST(aiv_file_read_size_red);
    PRINT_TEST_RESULTS();
    return 0;
}