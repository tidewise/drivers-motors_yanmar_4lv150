#include "Helpers.hpp"

namespace motors_yanmar_4lv150 {

    power_base::DCSourceStatus toDCSourceStatus(
        j1939::pgns::VehicleElectricalPower const& pgn)
    {
        power_base::DCSourceStatus status;
        status.time = pgn.time;

        status.voltage = pgn.alternator_potential * 0.05;
        status.current = pgn.alternator_current;

        status.max_current = YANMAR_4LV150_MAX_CURRENT;

        return status;
    }
}
