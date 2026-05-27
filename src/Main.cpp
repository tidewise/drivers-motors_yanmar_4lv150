#include "Yanmar4LV150Status.hpp"
#include <iodrivers_base/Driver.hpp>
#include <iostream>
#include <j1939/CAN.hpp>
#include <j1939/PGNs.hpp>
#include <j1939/Receiver.hpp>

using namespace std;
using namespace j1939;

void usage(ostream& stream)
{
    cerr << "usage: motors_yanmar_4lv150_bin URI\n";
    cerr << "\n";
    cerr << "URI is the can interface, eg.: can0\n";
    cerr << flush;
}

int main(int argc, char const* argv[])
{
    if (argc < 2) {
        usage(cout);
        return 0;
    }

    string uri = argv[1];

    j1939::CAN can_interface(uri, "socket");
    motors_yanmar_4lv150::Yanmar4LV150Status status;

    while (true) {
        try {
            auto msg = can_interface.readMessage();
            bool updated = status.update(msg);

            if (updated) {
                cout << "--- Yanmar 4LV150 Status ---\n";
                cout << "time: " << status.time << "\n";
                cout << "last_received_pgn: " << status.last_received_pgn << "\n";
                cout << "engine_torque_mode: "
                     << static_cast<int>(status.engine_torque_mode) << "\n";
                cout << "drivers_demand_engine_torque: "
                     << status.drivers_demand_engine_torque << "\n";
                cout << "actual_engine_torque: " << status.actual_engine_torque << "\n";
                cout << "engine_speed (rad/s): " << status.engine_speed.speed << "\n";
                cout << "source_address: " << status.source_address << "\n";
                cout << "engine_starter_mode: "
                     << static_cast<int>(status.engine_starter_mode) << "\n";
                cout << "engine_demand_torque: " << status.engine_demand_torque << "\n";
                cout << "selected_gear: " << status.selected_gear << "\n";
                cout << "actual_gear_ratio: " << status.actual_gear_ratio << "\n";
                cout << "current_gear: " << status.current_gear << "\n";
                cout << "transmission_requested_range: "
                     << status.transmission_requested_range << "\n";
                cout << "transmission_current_range: "
                     << status.transmission_current_range << "\n";
                cout << "fuel_rate: " << status.fuel_rate << "\n";
                cout << "instantaneous_fuel_economy: "
                     << status.instantaneous_fuel_economy << "\n";
                cout << "average_fuel_economy: " << status.average_fuel_economy << "\n";
                cout << "throttle_position: " << status.throttle_position << "\n";
                cout << "fuel_delivery_pressure (Pa): "
                     << status.fuel_delivery_pressure.toPa() << "\n";
                cout << "extended_crankcase_blow_by_pressure (Pa): "
                     << status.extended_crankcase_blow_by_pressure.toPa() << "\n";
                cout << "engine_oil_level: " << status.engine_oil_level << "\n";
                cout << "engine_oil_pressure (Pa): " << status.engine_oil_pressure.toPa()
                     << "\n";
                cout << "crankcase_pressure (Pa): " << status.crankcase_pressure.toPa()
                     << "\n";
                cout << "coolant_pressure (Pa): " << status.coolant_pressure.toPa()
                     << "\n";
                cout << "coolant_level: " << status.coolant_level << "\n";
                cout << "injection_control_pressure (Pa): "
                     << status.injection_control_pressure.toPa() << "\n";
                cout << "injector_metering_rail_1_pressure (Pa): "
                     << status.injector_metering_rail_1_pressure.toPa() << "\n";
                cout << "injector_timing_rail_1_pressure (Pa): "
                     << status.injector_timing_rail_1_pressure.toPa() << "\n";
                cout << "injector_metering_rail_2_pressure (Pa): "
                     << status.injector_metering_rail_2_pressure.toPa() << "\n";
                cout << "particulate_trap_inlet_pressure (Pa): "
                     << status.particulate_trap_inlet_pressure.toPa() << "\n";
                cout << "boost_pressure (Pa): " << status.boost_pressure.toPa() << "\n";
                cout << "intake_manifold_1_temperature (C): "
                     << status.intake_manifold_1_temperature.getCelsius() << "\n";
                cout << "air_inlet_pressure (Pa): " << status.air_inlet_pressure.toPa()
                     << "\n";
                cout << "air_filter_1_differential_pressure (Pa): "
                     << status.air_filter_1_differential_pressure.toPa() << "\n";
                cout << "exhaust_gas_temperature (C): "
                     << status.exhaust_gas_temperature.getCelsius() << "\n";
                cout << "coolant_filter_differential_pressure (Pa): "
                     << status.coolant_filter_differential_pressure.toPa() << "\n";
                cout << "total_engine_hours (s): "
                     << status.total_engine_hours.toSeconds() << "\n";
                cout << "total_engine_revolutions: " << status.total_engine_revolutions
                     << "\n";
                cout << "net_battery_current: " << status.net_battery_current << "\n";
                cout << "alternator_current: " << status.alternator_current << "\n";
                cout << "alternator_potential: " << status.alternator_potential << "\n";
                cout << "electrical_potential: " << status.electrical_potential << "\n";
                cout << "battery_potential: " << status.battery_potential << "\n";
                cout << "engine_coolant_temperature (C): "
                     << status.engine_coolant_temperature.getCelsius() << "\n";
                cout << "fuel_temperature (C): " << status.fuel_temperature.getCelsius()
                     << "\n";
                cout << "engine_oil_temperature (C): "
                     << status.engine_oil_temperature.getCelsius() << "\n";
                cout << "turbo_oil_temperature (C): "
                     << status.turbo_oil_temperature.getCelsius() << "\n";
                cout << "engine_intercooler_temperature (C): "
                     << status.engine_intercooler_temperature.getCelsius() << "\n";
                cout << "engine_intercooler_thermostat_opening: "
                     << status.engine_intercooler_thermostat_opening << "\n";
                cout << "----------------------------\n" << endl;
            }
        }
        catch (iodrivers_base::TimeoutError&) {
            cout << "TIMEOUT" << endl;
        }
    }
    return 0;
}