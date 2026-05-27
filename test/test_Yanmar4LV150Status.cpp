#include "j1939/PGNs.hpp"
#include "motors_yanmar_4lv150/Yanmar4LV150Status.hpp"
#include <base/Pressure.hpp>
#include <base/Temperature.hpp>
#include <gtest/gtest.h>

using namespace j1939;
using namespace motors_yanmar_4lv150;

struct Yanmar4LV150StatusTest : public ::testing::Test {};

TEST_F(Yanmar4LV150StatusTest, it_updates_from_eec1)
{
    Yanmar4LV150Status status;
    pgns::ElectronicEngineController1 pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.engine_torque_mode = pgns::ACCELERATOR_PEDAL;
    pgn.drivers_demand_engine = 125 + 50;
    pgn.actual_engine = 125 + 25;
    pgn.engine_speed = 8000;
    pgn.source_address = 15;
    pgn.engine_starter_mode = pgns::START_FINISHED;
    pgn.engine_demand = 125 + 10;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::ElectronicEngineController1::ID);
    ASSERT_EQ(status.engine_torque_mode, pgns::ACCELERATOR_PEDAL);
    ASSERT_NEAR(status.drivers_demand_engine_torque, 0.50, 1e-5);
    ASSERT_NEAR(status.actual_engine_torque, 0.25, 1e-5);
    ASSERT_TRUE(status.engine_speed.isSpeed());
    ASSERT_NEAR(status.engine_speed.speed, 104.7197551197, 1e-5);
    ASSERT_EQ(status.source_address, 15);
    ASSERT_EQ(status.engine_starter_mode, pgns::START_FINISHED);
    ASSERT_NEAR(status.engine_demand_torque, 0.10, 1e-5);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_eec2)
{
    Yanmar4LV150Status status;
    pgns::ElectronicEngineController2 pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.selected_gear = 125 + 2;
    pgn.actual_gear_ratio = 5382;
    pgn.current_gear = 125 + 3;
    pgn.transmission_requested_range = 296;
    pgn.transmission_current_range = 612;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::ElectronicEngineController2::ID);
    ASSERT_EQ(status.selected_gear, 2);
    ASSERT_NEAR(status.actual_gear_ratio, 5.382, 1e-5);
    ASSERT_EQ(status.current_gear, 3);
    ASSERT_EQ(status.transmission_requested_range, 296);
    ASSERT_EQ(status.transmission_current_range, 612);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_fuel_economy)
{
    Yanmar4LV150Status status;
    pgns::FuelEconomy pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.fuel_rate = 1000;
    pgn.instantaneous_fuel_economy = 4096;
    pgn.average_fuel_economy = 8192;
    pgn.throttle_position = 100;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::FuelEconomy::ID);
    ASSERT_NEAR(status.fuel_rate, 1.38888889e-5, 1e-9);
    ASSERT_NEAR(status.instantaneous_fuel_economy, 8000.0, 1e-5);
    ASSERT_NEAR(status.average_fuel_economy, 16000.0, 1e-5);
    ASSERT_NEAR(status.throttle_position, 0.4, 1e-5);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_fluid_level_and_pressure_1)
{
    Yanmar4LV150Status status;
    pgns::EngineFluidLevelAndPressure1 pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.fuel_delivery_pressure = 150;
    pgn.extended_crankcase_blow_by_pressure = 20;
    pgn.engine_oil_level = 128;
    pgn.engine_oil_pressure = 200;
    pgn.crankcase_pressure = 80;
    pgn.coolant_pressure = 100;
    pgn.coolant_level = 180;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::EngineFluidLevelAndPressure1::ID);
    ASSERT_NEAR(status.fuel_delivery_pressure.toPa(), 600000.0, 1e-5);
    ASSERT_NEAR(status.extended_crankcase_blow_by_pressure.toPa(), 1000.0, 1e-5);
    ASSERT_NEAR(status.engine_oil_level, 0.512, 1e-5);
    ASSERT_NEAR(status.engine_oil_pressure.toPa(), 800000.0, 1e-5);
    ASSERT_NEAR(status.crankcase_pressure.toPa(), -127375.0, 1e-5);
    ASSERT_NEAR(status.coolant_pressure.toPa(), 200000.0, 1e-5);
    ASSERT_NEAR(status.coolant_level, 0.72, 1e-5);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_fluid_level_and_pressure_2)
{
    Yanmar4LV150Status status;
    pgns::EngineFluidLevelAndPressure2 pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.injection_control_pressure = 100;
    pgn.injector_metering_rail_1_pressure = 200;
    pgn.injector_timing_rail_1_pressure = 300;
    pgn.injector_metering_rail_2_pressure = 400;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::EngineFluidLevelAndPressure2::ID);
    ASSERT_NEAR(status.injection_control_pressure.toPa(), 390625.0, 1e-5);
    ASSERT_NEAR(status.injector_metering_rail_1_pressure.toPa(), 781250.0, 1e-5);
    ASSERT_NEAR(status.injector_timing_rail_1_pressure.toPa(), 1171875.0, 1e-5);
    ASSERT_NEAR(status.injector_metering_rail_2_pressure.toPa(), 1562500.0, 1e-5);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_inlet_conditions)
{
    Yanmar4LV150Status status;
    pgns::InletConditions pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.particulate_trap_inlet_pressure = 10;
    pgn.boost_pressure = 20;
    pgn.intake_manifold_1_temperature = 60;
    pgn.air_inlet_pressure = 30;
    pgn.air_filter_1_differential_pressure = 40;
    pgn.exhaust_gas_temperature = 10000;
    pgn.coolant_filter_differential_pressure = 50;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::InletConditions::ID);
    ASSERT_NEAR(status.particulate_trap_inlet_pressure.toPa(), 5000.0, 1e-5);
    ASSERT_NEAR(status.boost_pressure.toPa(), 40000.0, 1e-5);
    ASSERT_NEAR(status.intake_manifold_1_temperature.getCelsius(), 20.0, 1e-5);
    ASSERT_NEAR(status.air_inlet_pressure.toPa(), 60000.0, 1e-5);
    ASSERT_NEAR(status.air_filter_1_differential_pressure.toPa(), 2000.0, 1e-5);
    ASSERT_NEAR(status.exhaust_gas_temperature.getCelsius(), 39.5, 1e-5);
    ASSERT_NEAR(status.coolant_filter_differential_pressure.toPa(), 25000.0, 1e-5);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_engine_hours_and_revolutions)
{
    Yanmar4LV150Status status;
    pgns::EngineHoursAndRevolutions pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.total_engine_hours = 10000;
    pgn.total_engine_revolutions = 20000;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::EngineHoursAndRevolutions::ID);
    ASSERT_NEAR(status.total_engine_hours.toSeconds(), 1800000.0, 1e-5);
    ASSERT_NEAR(status.total_engine_revolutions, 20000000.0, 1e-5);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_vehicle_electrical_power)
{
    Yanmar4LV150Status status;
    pgns::VehicleElectricalPower pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.net_battery_current = 135;
    pgn.alternator_current = 10;
    pgn.alternator_potential = 200;
    pgn.electrical_potential = 250;
    pgn.battery_potential = 300;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::VehicleElectricalPower::ID);
    ASSERT_NEAR(status.net_battery_current, 10.0, 1e-5);
    ASSERT_NEAR(status.alternator_current, 10.0, 1e-5);
    ASSERT_NEAR(status.alternator_potential, 10.0, 1e-5);
    ASSERT_NEAR(status.electrical_potential, 12.5, 1e-5);
    ASSERT_NEAR(status.battery_potential, 15.0, 1e-5);
}

TEST_F(Yanmar4LV150StatusTest, it_updates_from_engine_temperature_1)
{
    Yanmar4LV150Status status;
    pgns::EngineTemperature1 pgn;
    pgn.time = base::Time::fromMilliseconds(1234);
    pgn.engine_coolant_temperature = 100;
    pgn.fuel_temperature = 120;
    pgn.engine_oil_temperature = 10000;
    pgn.turbo_oil_temperature = 11000;
    pgn.engine_intercooler_temperature = 80;
    pgn.engine_intercooler_thermostat_opening = 100;

    status.update(pgn);

    ASSERT_EQ(status.time, pgn.time);
    ASSERT_EQ(status.last_received_pgn, pgns::EngineTemperature1::ID);
    ASSERT_NEAR(status.engine_coolant_temperature.getCelsius(), 60.0, 1e-5);
    ASSERT_NEAR(status.fuel_temperature.getCelsius(), 80.0, 1e-5);
    ASSERT_NEAR(status.engine_oil_temperature.getCelsius(), 39.5, 1e-5);
    ASSERT_NEAR(status.turbo_oil_temperature.getCelsius(), 70.75, 1e-5);
    ASSERT_NEAR(status.engine_intercooler_temperature.getCelsius(), 40.0, 1e-5);
    ASSERT_NEAR(status.engine_intercooler_thermostat_opening, 0.4, 1e-5);
}
