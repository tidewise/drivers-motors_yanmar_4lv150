#include "Yanmar4LV150Status.hpp"
#include <cmath>

using namespace motors_yanmar_4lv150;
using namespace j1939;

void Yanmar4LV150Status::update(pgns::ElectronicEngineController1 const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::ElectronicEngineController1::ID;

    engine_torque_mode = pgn.engine_torque_mode;
    drivers_demand_engine_torque = (pgn.drivers_demand_engine - 125) * PERCENTAGE_SCALE;
    actual_engine_torque = (pgn.actual_engine - 125) * PERCENTAGE_SCALE;
    engine_speed = base::JointState::Speed((pgn.engine_speed * 0.125) * RPM_TO_RADS);
    source_address = pgn.source_address;
    engine_starter_mode = pgn.engine_starter_mode;
    engine_demand_torque = (pgn.engine_demand - 125) * PERCENTAGE_SCALE;
}

void Yanmar4LV150Status::update(pgns::ElectronicEngineController2 const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::ElectronicEngineController2::ID;

    selected_gear = pgn.selected_gear - 125;
    actual_gear_ratio = pgn.actual_gear_ratio * 0.001;
    current_gear = pgn.current_gear - 125;
    transmission_requested_range = pgn.transmission_requested_range;
    transmission_current_range = pgn.transmission_current_range;
}

void Yanmar4LV150Status::update(pgns::FuelEconomy const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::FuelEconomy::ID;

    fuel_rate = (pgn.fuel_rate * 0.05) * LITERS_PER_HOUR_TO_SI;
    instantaneous_fuel_economy = pgn.instantaneous_fuel_economy * FUEL_ECONOMY_SCALE;
    average_fuel_economy = pgn.average_fuel_economy * FUEL_ECONOMY_SCALE;
    throttle_position = (pgn.throttle_position * 0.4) * PERCENTAGE_SCALE;
}

void Yanmar4LV150Status::update(pgns::EngineFluidLevelAndPressure1 const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::EngineFluidLevelAndPressure1::ID;

    fuel_delivery_pressure =
        base::Pressure::fromPascal((pgn.fuel_delivery_pressure * 4) * 1000.0);
    extended_crankcase_blow_by_pressure = base::Pressure::fromPascal(
        (pgn.extended_crankcase_blow_by_pressure * 0.05) * 1000.0);
    engine_oil_level = (pgn.engine_oil_level * 0.4) * PERCENTAGE_SCALE;
    engine_oil_pressure =
        base::Pressure::fromPascal((pgn.engine_oil_pressure * 4) * 1000.0);
    crankcase_pressure =
        base::Pressure::fromPascal((pgn.crankcase_pressure * 0.0078125 - 128) * 1000.0);
    coolant_pressure = base::Pressure::fromPascal((pgn.coolant_pressure * 2) * 1000.0);
    coolant_level = (pgn.coolant_level * 0.4) * PERCENTAGE_SCALE;
}

void Yanmar4LV150Status::update(pgns::EngineFluidLevelAndPressure2 const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::EngineFluidLevelAndPressure2::ID;

    injection_control_pressure = base::Pressure::fromPascal(
        pgn.injection_control_pressure * INJECTOR_PRESSURE_SCALE);
    injector_metering_rail_1_pressure = base::Pressure::fromPascal(
        pgn.injector_metering_rail_1_pressure * INJECTOR_PRESSURE_SCALE);
    injector_timing_rail_1_pressure = base::Pressure::fromPascal(
        pgn.injector_timing_rail_1_pressure * INJECTOR_PRESSURE_SCALE);
    injector_metering_rail_2_pressure = base::Pressure::fromPascal(
        pgn.injector_metering_rail_2_pressure * INJECTOR_PRESSURE_SCALE);
}

void Yanmar4LV150Status::update(pgns::InletConditions const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::InletConditions::ID;

    particulate_trap_inlet_pressure =
        base::Pressure::fromPascal((pgn.particulate_trap_inlet_pressure * 0.5) * 1000.0);
    boost_pressure = base::Pressure::fromPascal((pgn.boost_pressure * 2) * 1000.0);
    intake_manifold_1_temperature =
        base::Temperature::fromCelsius(pgn.intake_manifold_1_temperature - 40);
    air_inlet_pressure =
        base::Pressure::fromPascal((pgn.air_inlet_pressure * 2) * 1000.0);
    air_filter_1_differential_pressure = base::Pressure::fromPascal(
        (pgn.air_filter_1_differential_pressure * 0.05) * 1000.0);
    exhaust_gas_temperature =
        base::Temperature::fromCelsius(pgn.exhaust_gas_temperature * 0.03125 - 273);
    coolant_filter_differential_pressure = base::Pressure::fromPascal(
        (pgn.coolant_filter_differential_pressure * 0.5) * 1000.0);
}

void Yanmar4LV150Status::update(pgns::EngineHoursAndRevolutions const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::EngineHoursAndRevolutions::ID;

    total_engine_hours =
        base::Time::fromSeconds((pgn.total_engine_hours * 0.05) * 3600.0);
    total_engine_revolutions = pgn.total_engine_revolutions * 1000.0;
}

void Yanmar4LV150Status::update(pgns::VehicleElectricalPower const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::VehicleElectricalPower::ID;

    net_battery_current = pgn.net_battery_current - 125;
    alternator_current = pgn.alternator_current;
    alternator_potential = pgn.alternator_potential * 0.05;
    electrical_potential = pgn.electrical_potential * 0.05;
    battery_potential = pgn.battery_potential * 0.05;
}

void Yanmar4LV150Status::update(pgns::EngineTemperature1 const& pgn)
{
    time = pgn.time;
    last_received_pgn = pgns::EngineTemperature1::ID;

    engine_coolant_temperature =
        base::Temperature::fromCelsius(pgn.engine_coolant_temperature - 40);
    fuel_temperature = base::Temperature::fromCelsius(pgn.fuel_temperature - 40);
    engine_oil_temperature =
        base::Temperature::fromCelsius(pgn.engine_oil_temperature * 0.03125 - 273);
    turbo_oil_temperature =
        base::Temperature::fromCelsius(pgn.turbo_oil_temperature * 0.03125 - 273);
    engine_intercooler_temperature =
        base::Temperature::fromCelsius(pgn.engine_intercooler_temperature - 40);
    engine_intercooler_thermostat_opening =
        (pgn.engine_intercooler_thermostat_opening * 0.4) * PERCENTAGE_SCALE;
}

bool Yanmar4LV150Status::update(can_common::PGNMessage const& msg)
{
    switch (msg.pgn) {
        case pgns::ElectronicEngineController1::ID:
            update(pgns::ElectronicEngineController1::fromMessage(msg));
            return true;
        case pgns::ElectronicEngineController2::ID:
            update(pgns::ElectronicEngineController2::fromMessage(msg));
            return true;
        case pgns::FuelEconomy::ID:
            update(pgns::FuelEconomy::fromMessage(msg));
            return true;
        case pgns::EngineFluidLevelAndPressure1::ID:
            update(pgns::EngineFluidLevelAndPressure1::fromMessage(msg));
            return true;
        case pgns::EngineFluidLevelAndPressure2::ID:
            update(pgns::EngineFluidLevelAndPressure2::fromMessage(msg));
            return true;
        case pgns::InletConditions::ID:
            update(pgns::InletConditions::fromMessage(msg));
            return true;
        case pgns::EngineHoursAndRevolutions::ID:
            update(pgns::EngineHoursAndRevolutions::fromMessage(msg));
            return true;
        case pgns::VehicleElectricalPower::ID:
            update(pgns::VehicleElectricalPower::fromMessage(msg));
            return true;
        case pgns::EngineTemperature1::ID:
            update(pgns::EngineTemperature1::fromMessage(msg));
            return true;
        default:
            return false;
    }
}