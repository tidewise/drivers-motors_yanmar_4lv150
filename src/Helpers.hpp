#ifndef MOTORS_YANMAR_4LV150_HELPERS_HPP
#define MOTORS_YANMAR_4LV150_HELPERS_HPP

#include "Yanmar4LV150Status.hpp"
#include <power_base/DCSourceStatus.hpp>

namespace motors_yanmar_4lv150 {
    constexpr float YANMAR_4LV150_MAX_CURRENT = 130.0f;

    power_base::DCSourceStatus toDCSourceStatus(
        j1939::pgns::VehicleElectricalPower const& pgn);
}

#endif