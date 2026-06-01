#ifndef MOTORS_YANMAR_4LV150_YANMAR_4LV150_STATUS_HPP
#define MOTORS_YANMAR_4LV150_YANMAR_4LV150_STATUS_HPP

#include <base/Float.hpp>
#include <base/JointState.hpp>
#include <base/Pressure.hpp>
#include <base/Temperature.hpp>
#include <base/Time.hpp>
#include <cmath>
#include <j1939/PGNs.hpp>

namespace motors_yanmar_4lv150 {
    /**
     * @brief Full status of the Yanmar 4LV150 engine feedback
     */
    struct Yanmar4LV150Status {
        static constexpr double PERCENTAGE_SCALE = 1.0 / 100.0;
        static constexpr double RPM_TO_RADS = 2.0 * M_PI / 60.0;
        static constexpr double LITERS_PER_HOUR_TO_SI = 1.0 / 3600000.0;
        static constexpr double FUEL_ECONOMY_SCALE = 1000.0 / 512.0;
        static constexpr double INJECTOR_PRESSURE_SCALE = 1000000.0 / 256.0;

        /** @brief Timestamp of the last received status update */
        base::Time time;

        /** @brief ID of the most recently received PGN */
        int last_received_pgn;

        /**
         * @brief State of engine torque control system.
         * @note PGN: 61444 | SPN: 899
         */
        j1939::pgns::EngineTorqueMode engine_torque_mode;

        /**
         * @brief Driver's requested torque.
         * @note Unit: Percentage | PGN: 61444 | SPN: 512
         */
        double drivers_demand_engine_torque = base::unknown<double>();

        /**
         * @brief Actual torque output.
         * @note Unit: Percentage | PGN: 61444 | SPN: 513
         */
        double actual_engine_torque = base::unknown<double>();

        /**
         * @brief Engine crankshaft speed.
         * @note Unit: rad/s | PGN: 61444 | SPN: 190
         */
        base::JointState engine_speed;

        /**
         * @brief Source address of the device controlling the engine.
         * @note PGN: 61444 | SPN: 1483
         */
        int source_address;

        /**
         * @brief Status of engine starter.
         * @note PGN: 61444 | SPN: 1675
         */
        j1939::pgns::EngineStarterMode engine_starter_mode;

        /**
         * @brief Engine torque demand.
         * @note Unit: Percentage | PGN: 61444 | SPN: 2432
         */
        double engine_demand_torque = base::unknown<double>();

        /**
         * @brief Selected gear during the current shift or the next pending shift
         * @note Unit: Gear | PGN: 61445 | SPN: 524
         */
        int selected_gear;

        /**
         * @brief Actual ratio of input shaft speed to output shaft speed.
         * @note Unit: Percentage | PGN: 61445 | SPN: 526
         */
        double actual_gear_ratio = base::unknown<double>();

        /**
         * @brief Currently engaged gear or last gear engaged.
         * @note PGN: 61445 | SPN: 523
         */
        int current_gear;

        /** TUDO: fix
         * @brief Requested transmission range.
         * @note PGN: 61445 | SPN: 162
         */
        int transmission_requested_range;

        /** TUDO: fix
         * @brief Current transmission range.
         * @note PGN: 61445 | SPN: 163
         */
        int transmission_current_range;

        /**
         * @brief Amount of fuel consumed by engine per unit of time.
         * @note Unit: m^3/s | PGN: 65266 | SPN: 183
         */
        double fuel_rate = base::unknown<double>();

        /**
         * @brief Current fuel economy at current speed.
         * @note Unit: m/kg | PGN: 65266 | SPN: 184
         */
        double instantaneous_fuel_economy = base::unknown<double>();

        /**
         * @brief Average of instantaneous fuel economy over trip/interval.
         * @note Unit: m/kg | PGN: 65266 | SPN: 185
         */
        double average_fuel_economy = base::unknown<double>();

        /**
         * @brief Position of the valve used to regulate the supply of a fluid
         * @note Unit: Percentage | PGN: 65266 | SPN: 51
         */
        double throttle_position = base::unknown<double>();

        /**
         * @brief Gage pressure of fuel as delivered from supply to the injection pump
         * @note PGN: 65263 | SPN: 94
         */
        base::Pressure fuel_delivery_pressure;

        /**
         * @brief Differential crankcase blow-by pressure.
         * @note PGN: 65263 | SPN: 22
         */
        base::Pressure extended_crankcase_blow_by_pressure;

        /**
         * @brief Ratio of sump oil volume to maximum required volume
         * @note Unit: Percentage | PGN: 65263 | SPN: 98
         */
        double engine_oil_level = base::unknown<double>();

        /**
         * @brief Gage pressure of oil in engine lubrification system
         * @note PGN: 65263 | SPN: 100
         */
        base::Pressure engine_oil_pressure;

        /**
         * @brief Cage pressure inside engine crankcase.
         * @note PGN: 65263 | SPN: 101
         */
        base::Pressure crankcase_pressure;

        /**
         * @brief Cage pressure of liquid found in engine colling system
         * @note PGN: 65263 | SPN: 109
         */
        base::Pressure coolant_pressure;

        /**
         * @brief Ratio of actual coolant liquid volume to total cooling system volume
         * @note Unit: Percentage | PGN: 65263 | SPN: 111
         */
        double coolant_level = base::unknown<double>();

        /**
         * @brief Gage pressure of the engine oil in fuel injection
         * @note PGN: 65243 | SPN: 164
         */
        base::Pressure injection_control_pressure;

        /**
         * @brief Gage ressure in fuel metering rail 1.
         * @note PGN: 65243 | SPN: 157
         */
        base::Pressure injector_metering_rail_1_pressure;

        /**
         * @brief Pressure in fuel timing rail 1.
         * @note PGN: 65243 | SPN: 156
         */
        base::Pressure injector_timing_rail_1_pressure;

        /**
         * @brief Pressure in fuel metering rail 2.
         * @note PGN: 65243 | SPN: 1349
         */
        base::Pressure injector_metering_rail_2_pressure;

        /**
         * @brief Exhaust back pressure as a result of particle accumulation on filter
         * media placed in the exhaust stream
         * @note PGN: 65270 | SPN: 81
         */
        base::Pressure particulate_trap_inlet_pressure;

        /**
         * @brief Air gage pressure measured downstream in the compressor discharge of
         * the turbocharger
         * @note PGN: 65270 | SPN: 102
         */
        base::Pressure boost_pressure;

        /**
         * @brief Pre-combustion intake manifold air temperature.
         * @note PGN: 65270 | SPN: 105
         */
        base::Temperature intake_manifold_1_temperature;

        /**
         * @brief Absolute air pressure at inlet to intake mainfold or air box
         * @note PGN: 65270 | SPN: 106
         */
        base::Pressure air_inlet_pressure;

        /**
         * @brief Delta pressure across air filter.
         * @note PGN: 65270 | SPN: 107
         */
        base::Pressure air_filter_1_differential_pressure;

        /**
         * @brief Temperature of exhaust gas.
         * @note PGN: 65270 | SPN: 173
         */
        base::Temperature exhaust_gas_temperature;

        /**
         * @brief Delta pressure across coolant filter.
         * @note PGN: 65270 | SPN: 112
         */
        base::Pressure coolant_filter_differential_pressure;

        /**
         * @brief Accumulated time of operation of engine.
         * @note PGN: 65253 | SPN: 247
         */
        base::Time total_engine_hours;

        /**
         * @brief Cumulative engine crankshaft revolutions during its operation.
         * @note Unit: Revolutions | PGN: 65253 | SPN: 249
         */
        double total_engine_revolutions = base::unknown<double>();

        /**
         * @brief Net flow of electrical into/out of the battery
         * @note Unit: A | PGN: 65271 | SPN: 114
         */
        double net_battery_current = base::unknown<double>();

        /**
         * @brief Current from alternator.
         * @note Unit: A | PGN: 65271 | SPN: 115
         */
        double alternator_current = base::unknown<double>();

        /**
         * @brief Electical potential at alternator.
         * @note Unit: V | PGN: 65271 | SPN: 167
         */
        double alternator_potential = base::unknown<double>();

        /**
         * @brief Electrical potential of the battery.
         * @note Unit: V | PGN: 65271 | SPN: 168
         */
        double electrical_potential = base::unknown<double>();

        /**
         * @brief Electrical potential measured at the input of the ECU.
         * @note Unit: V | PGN: 65271 | SPN: 158
         */
        double battery_potential = base::unknown<double>();

        /**
         * @brief Engine coolant liquid temperature.
         * @note PGN: 65262 | SPN: 110
         */
        base::Temperature engine_coolant_temperature;

        /**
         * @brief Temperature of fuel entering injectors.
         * @note PGN: 65262 | SPN: 174
         */
        base::Temperature fuel_temperature;

        /**
         * @brief Temperature of the engine lubrificant.
         * @note PGN: 65262 | SPN: 175
         */
        base::Temperature engine_oil_temperature;

        /**
         * @brief Turbocharger lubrificant temperature.
         * @note PGN: 65262 | SPN: 176
         */
        base::Temperature turbo_oil_temperature;

        /**
         * @brief Air temperature after intercooler.
         * @note PGN: 65262 | SPN: 52
         */
        base::Temperature engine_intercooler_temperature;

        /**
         * @brief Thermostat current position used to regulate the engine intercooler
         * temperature.
         * @note Unit: Percentage | PGN: 65262 | SPN: 1134
         */
        double engine_intercooler_thermostat_opening = base::unknown<double>();

        void update(j1939::pgns::ElectronicEngineController1 const& pgn);
        void update(j1939::pgns::ElectronicEngineController2 const& pgn);
        void update(j1939::pgns::FuelEconomy const& pgn);
        void update(j1939::pgns::EngineFluidLevelAndPressure1 const& pgn);
        void update(j1939::pgns::EngineFluidLevelAndPressure2 const& pgn);
        void update(j1939::pgns::InletConditions const& pgn);
        void update(j1939::pgns::EngineHoursAndRevolutions const& pgn);
        void update(j1939::pgns::VehicleElectricalPower const& pgn);
        void update(j1939::pgns::EngineTemperature1 const& pgn);

        /**
         * @brief Updates the status using a raw PGNMessage.
         * @return true if the PGN was recognized and handled, false otherwise.
         */
        bool update(can_common::PGNMessage const& msg);
    };
}

#endif