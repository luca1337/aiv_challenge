#define SDL_MAIN_HANDLED

#include <aiv_unit_test.h>
#include <aiv_clock.h>
#include <aiv_context.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

extern aiv_context_t* context;
static aiv_clock_t* aiv_clock;

#define INIT_CLOCK(px, py)\
	context = aiv_context_new("aiv_test_clock", 800, 600, NULL);\
	aiv_clock = aiv_clock_new("clock_hand.png", px, py, 0)


TEST(clock_new_green)
{
	INIT_CLOCK(0, 0);

	ASSERT_THAT(aiv_clock != NULL);
}

TEST(clock_position_set)
{
	INIT_CLOCK(10, 25);

	ASSERT_THAT(aiv_clock->pos_x == 10);
	ASSERT_THAT(aiv_clock->pos_y == 25);
}

TEST(clock_position_changed_green)
{
	INIT_CLOCK(10, 25);

	ASSERT_THAT(aiv_clock->pos_x == 10);
	ASSERT_THAT(aiv_clock->pos_y == 25);

	aiv_clock->pos_x += 7;
	aiv_clock->pos_y += 12;

	ASSERT_THAT(aiv_clock->pos_x == 17);
	ASSERT_THAT(aiv_clock->pos_y == 37);
}

TEST(clock_position_changed_red)
{
	INIT_CLOCK(10, 25);

	ASSERT_THAT(aiv_clock->pos_x == 10);
	ASSERT_THAT(aiv_clock->pos_y == 25);

	aiv_clock->pos_x += 7;
	aiv_clock->pos_y += 12;

	ASSERT_THAT(aiv_clock->pos_x == 17);
	ASSERT_THAT(aiv_clock->pos_y == 37);
}

TEST(clock_not_paused)
{
	INIT_CLOCK(10, 25);
	
	aiv_clock->is_paused = 0;

	ASSERT_THAT(aiv_clock->is_paused == 0);
}

TEST(clock_ticking_custom_start)
{
	INIT_CLOCK(10, 25);

	// to get the rotation:
	// calculate how long is a lap (360) and divide it by 60 (number of seconds once a minute)
	// then take the value and multiply it by how many second you want to tick and this will give
	// the rotation in degrees within 360 deg => (max_degrees / seconds_once_minute) * tick_seconds
	aiv_clock->aiv_clock_set_frame(aiv_clock, 25);

	ASSERT_THAT(aiv_clock->rotation == 150);
}

TEST(clock_ticking_custom_start_increased_by_one_tick)
{
	INIT_CLOCK(10, 25);

	aiv_clock->aiv_clock_set_frame(aiv_clock, 25);

	ASSERT_THAT(aiv_clock->rotation == 150);
}

int main(int argc, char** argv)
{
	RUN_TEST(clock_new_green);
	RUN_TEST(clock_position_set);
	RUN_TEST(clock_position_changed_green);
	RUN_TEST(clock_not_paused);
	RUN_TEST(clock_ticking_custom_start);
	PRINT_TEST_RESULTS();
	return 0;
}
