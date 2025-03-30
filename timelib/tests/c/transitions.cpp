#include "CppUTest/TestHarness.h"
#include "timelib.h"
#include <string.h>

TEST_GROUP(transitions)
{
};

#define TEST_EXISTS(n,tz) \
	TEST(transitions, n) { \
		return; \
		int error; \
		timelib_tzinfo *tzi = timelib_parse_tzfile(tz, timelib_builtin_db(), &error); \
		CHECK(tzi != NULL); \
		CHECK(error == TIMELIB_ERROR_NO_ERROR || error == TIMELIB_ERROR_SLIM_FILE); \
		timelib_dump_tzinfo(tzi); \
		timelib_tzinfo_dtor(tzi); \
	}

#define TEST_TRANSITION(n,tz,ts,eab,eoff,edst) \
	TEST(transitions, n) { \
		int error; \
		timelib_time_offset *tto; \
		timelib_tzinfo *tzi = timelib_parse_tzfile(tz, timelib_builtin_db(), &error); \
		CHECK(tzi != NULL); \
		tto = timelib_get_time_zone_info((ts), tzi); \
		CHECK(tto != NULL); \
		LONGS_EQUAL((eoff), tto->offset); \
		STRCMP_EQUAL((eab), tto->abbr); \
		LONGS_EQUAL((edst), tto->is_dst); \
		timelib_time_offset_dtor(tto); \
		timelib_tzinfo_dtor(tzi); \
	}

TEST_EXISTS(utc_00, "UTC")
TEST_TRANSITION(utc_01, "UTC", INT64_MIN / 2, "UTC", 0, 0)
TEST_TRANSITION(utc_02, "UTC", 0,             "UTC", 0, 0)
TEST_TRANSITION(utc_03, "UTC", INT64_MAX / 2, "UTC", 0, 0)

TEST_EXISTS(tokyo_00, "Asia/Tokyo")
TEST_TRANSITION(tokyo_01, "Asia/Tokyo",   INT64_MIN, "LMT", 33539, 0)
TEST_TRANSITION(tokyo_02, "Asia/Tokyo", -2587712401, "LMT", 33539, 0)
TEST_TRANSITION(tokyo_03, "Asia/Tokyo", -2587712400, "JST", 32400, 0)
TEST_TRANSITION(tokyo_04, "Asia/Tokyo", -2587712399, "JST", 32400, 0)
TEST_TRANSITION(tokyo_05, "Asia/Tokyo",  -577962001, "JDT", 36000, 1)
TEST_TRANSITION(tokyo_06, "Asia/Tokyo",  -577962000, "JST", 32400, 0)
TEST_TRANSITION(tokyo_07, "Asia/Tokyo",  -577961999, "JST", 32400, 0)
TEST_TRANSITION(tokyo_08, "Asia/Tokyo",           0, "JST", 32400, 0)
TEST_TRANSITION(tokyo_09, "Asia/Tokyo",   INT64_MAX, "JST", 32400, 0)

TEST_EXISTS(ams_00, "Europe/Amsterdam")
TEST_TRANSITION(ams_01, "Europe/Amsterdam",   INT64_MIN, "LMT",   1172, 0)
TEST_TRANSITION(ams_02, "Europe/Amsterdam", -4260212372, "AMT",   1172, 0)
TEST_TRANSITION(ams_03, "Europe/Amsterdam", -1025745573, "NST",   4772, 1)
TEST_TRANSITION(ams_04, "Europe/Amsterdam", -1025745572, "+0120", 4800, 1)
TEST_TRANSITION(ams_05, "Europe/Amsterdam",   811904399, "CEST",  7200, 1)
TEST_TRANSITION(ams_06, "Europe/Amsterdam",   811904440, "CET",   3600, 0)
TEST_TRANSITION(ams_07, "Europe/Amsterdam",   828234000, "CEST",  7200, 1)

TEST_TRANSITION(ams_08, "Europe/Amsterdam",   846377999, "CEST",  7200, 1)
TEST_TRANSITION(ams_09, "Europe/Amsterdam",   846378000, "CET",   3600, 0)
TEST_TRANSITION(ams_10, "Europe/Amsterdam",   846378001, "CET",   3600, 0)

TEST_TRANSITION(ams_11, "Europe/Amsterdam",   859683599, "CET",   3600, 0)
TEST_TRANSITION(ams_12, "Europe/Amsterdam",   859683600, "CEST",  7200, 1)
TEST_TRANSITION(ams_13, "Europe/Amsterdam",   859683600, "CEST",  7200, 1)

TEST_EXISTS(can_00, "Australia/Canberra")
TEST_TRANSITION(can_01, "Australia/Canberra",   1193500799, "AEST", 36000, 0)
TEST_TRANSITION(can_02, "Australia/Canberra",   1193500800, "AEDT", 39600, 1)
TEST_TRANSITION(can_03, "Australia/Canberra",   1193500801, "AEDT", 39600, 1)

TEST_TRANSITION(can_04, "Australia/Canberra",   1207411199, "AEDT", 39600, 1)
TEST_TRANSITION(can_05, "Australia/Canberra",   1207411200, "AEST", 36000, 0)
TEST_TRANSITION(can_06, "Australia/Canberra",   1207411201, "AEST", 36000, 0)

TEST_TRANSITION(can_07, "Australia/Canberra",   1223135999, "AEST", 36000, 0)
TEST_TRANSITION(can_08, "Australia/Canberra",   1223136000, "AEDT", 39600, 1)
TEST_TRANSITION(can_09, "Australia/Canberra",   1223136001, "AEDT", 39600, 1)

TEST_TRANSITION(can_10, "Australia/Canberra",   1238860799, "AEDT", 39600, 1)
TEST_TRANSITION(can_11, "Australia/Canberra",   1238860800, "AEST", 36000, 0)
TEST_TRANSITION(can_12, "Australia/Canberra",   1238860801, "AEST", 36000, 0)


TEST_EXISTS(lh_00, "Australia/Lord_Howe")
TEST_TRANSITION(lh_01, "Australia/Lord_Howe", 1207407599, "+11",   39600, 1)
TEST_TRANSITION(lh_02, "Australia/Lord_Howe", 1207407600, "+1030", 37800, 0)
TEST_TRANSITION(lh_03, "Australia/Lord_Howe", 1207407601, "+1030", 37800, 0)

TEST_TRANSITION(lh_04, "Australia/Lord_Howe", 1317482999, "+1030", 37800, 0)
TEST_TRANSITION(lh_05, "Australia/Lord_Howe", 1317483000, "+11",   39600, 1)
TEST_TRANSITION(lh_06, "Australia/Lord_Howe", 1317483001, "+11",   39600, 1)

TEST_TRANSITION(lh_07, "Australia/Lord_Howe", 1365260399, "+11",   39600, 1)
TEST_TRANSITION(lh_08, "Australia/Lord_Howe", 1365260400, "+1030", 37800, 0)
TEST_TRANSITION(lh_09, "Australia/Lord_Howe", 1365260401, "+1030", 37800, 0)

// local new year 2011
TEST_TRANSITION(lh_10, "Australia/Lord_Howe", 1293800399, "+11",   39600, 1)
TEST_TRANSITION(lh_11, "Australia/Lord_Howe", 1293800400, "+11",   39600, 1)
TEST_TRANSITION(lh_12, "Australia/Lord_Howe", 1293800401, "+11",   39600, 1)

// UT new year 2011
TEST_TRANSITION(lh_13, "Australia/Lord_Howe", 1293839999, "+11",   39600, 1)
TEST_TRANSITION(lh_14, "Australia/Lord_Howe", 1293840000, "+11",   39600, 1)
TEST_TRANSITION(lh_15, "Australia/Lord_Howe", 1293840001, "+11",   39600, 1)


// Fiji has a large time-of-effect hour of 99
TEST_EXISTS(fiji_00, "Pacific/Fiji")
TEST_TRANSITION(fiji_01, "Pacific/Fiji", 1608386399, "+12", 43200, 0)
TEST_TRANSITION(fiji_02, "Pacific/Fiji", 1608386400, "+13", 46800, 1)
TEST_TRANSITION(fiji_03, "Pacific/Fiji", 1608386401, "+13", 46800, 1)


// Has a switch at a non-hour barrier
TEST_EXISTS(chat_00, "Pacific/Chatham")
TEST_TRANSITION(chat_01, "Pacific/Chatham", 1821880799, "+1245", 45900, 0)
TEST_TRANSITION(chat_02, "Pacific/Chatham", 1821880800, "+1345", 49500, 1)
TEST_TRANSITION(chat_03, "Pacific/Chatham", 1821880801, "+1345", 49500, 1)


// Ireland has negative DST
TEST_EXISTS(eire_00, "Europe/Dublin")
TEST_TRANSITION(eire_01, "Europe/Dublin", 859683599, "GMT",    0, 1)
TEST_TRANSITION(eire_02, "Europe/Dublin", 859683600, "IST", 3600, 0)
TEST_TRANSITION(eire_03, "Europe/Dublin", 859683601, "IST", 3600, 0)

#define TEST_TRANSITION_FROM_TEST_DIR(n,tz,ts,eab,eoff) \
	TEST(transitions, n) { \
		int error; \
		timelib_time_offset *tto; \
		timelib_tzdb *test_directory = timelib_zoneinfo("tests/c/files"); \
		CHECK(test_directory != NULL); \
		timelib_tzinfo *tzi = timelib_parse_tzfile(tz, test_directory, &error); \
		CHECK(tzi != NULL); \
		tto = timelib_get_time_zone_info((ts), tzi); \
		CHECK(tto != NULL); \
		LONGS_EQUAL((eoff), tto->offset); \
		STRCMP_EQUAL((eab), tto->abbr); \
		timelib_time_offset_dtor(tto); \
		timelib_tzinfo_dtor(tzi); \
		timelib_zoneinfo_dtor(test_directory); \
	}

// With a fake NY file, where I've modified the POSIX string to full year DST
TEST_TRANSITION_FROM_TEST_DIR(ny_01, "New_York_mod_Full_Year_DST", 1615483094, "EDT", -14400)
TEST_TRANSITION_FROM_TEST_DIR(ny_02, "New_York_mod_Full_Year_DST", 1609477199, "EDT", -14400)
TEST_TRANSITION_FROM_TEST_DIR(ny_03, "New_York_mod_Full_Year_DST", 1609477200, "EDT", -14400)
TEST_TRANSITION_FROM_TEST_DIR(ny_04, "New_York_mod_Full_Year_DST", 1609477201, "EDT", -14400)
