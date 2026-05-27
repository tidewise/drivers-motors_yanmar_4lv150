#include <gtest/gtest.h>
#include "motors_yanmar_4lv150/Helpers.hpp"

using namespace motors_yanmar_4lv150;

struct HelpersTest : public ::testing::Test {};

TEST_F(HelpersTest, toDCSourceStatus_maps_fields_correctly)
{
    j1939::pgns::VehicleElectricalPower pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.alternator_potential = 240;
    pgn.alternator_current = 50;

    auto dc_status = toDCSourceStatus(pgn);

    ASSERT_EQ(dc_status.time, pgn.time);
    ASSERT_NEAR(dc_status.voltage, 12.0, 1e-3);
    ASSERT_NEAR(dc_status.current, 50.0, 1e-3);
    ASSERT_NEAR(dc_status.max_current, YANMAR_4LV150_MAX_CURRENT, 1e-3);
}