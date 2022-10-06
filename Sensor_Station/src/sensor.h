/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <zephyr/drivers/sensor.h>

/* Measurements ranges for Bosch BME688 sensor */
#define SENSOR_TEMP_CELSIUS_MIN (-40)
#define SENSOR_TEMP_CELSIUS_MAX (85)
#define SENSOR_TEMP_CELSIUS_TOLERANCE (1)
#define SENSOR_PRESSURE_KPA_MIN (30)
#define SENSOR_PRESSURE_KPA_MAX (110)
#define SENSOR_PRESSURE_KPA_TOLERANCE (0)
#define SENSOR_HUMIDITY_PERCENT_MIN (10)
#define SENSOR_HUMIDITY_PERCENT_MAX (90)
#define SENSOR_HUMIDITY_PERCENT_TOLERANCE (3)

// ADC Registers

//#define ADS1115_SERIAL_DEBUG

#define ADS1115_ADDRESS_ADDR_GND    0x48 // address pin low (GND)
#define ADS1115_ADDRESS_ADDR_VDD    0x49 // address pin high (VCC)
#define ADS1115_ADDRESS_ADDR_SDA    0x4A // address pin tied to SDA pin
#define ADS1115_ADDRESS_ADDR_SCL    0x4B // address pin tied to SCL pin
#define ADS1115_DEFAULT_ADDRESS     ADS1115_ADDRESS_ADDR_GND

#define ADS1115_RA_CONVERSION       0x00
#define ADS1115_RA_CONFIG           0x01
#define ADS1115_RA_LO_THRESH        0x02
#define ADS1115_RA_HI_THRESH        0x03

#define ADS1115_CFG_OS_BIT          15
#define ADS1115_CFG_MUX_BIT         14
#define ADS1115_CFG_MUX_LENGTH      3
#define ADS1115_CFG_PGA_BIT         11
#define ADS1115_CFG_PGA_LENGTH      3
#define ADS1115_CFG_MODE_BIT        8
#define ADS1115_CFG_DR_BIT          7
#define ADS1115_CFG_DR_LENGTH       3
#define ADS1115_CFG_COMP_MODE_BIT   4
#define ADS1115_CFG_COMP_POL_BIT    3
#define ADS1115_CFG_COMP_LAT_BIT    2
#define ADS1115_CFG_COMP_QUE_BIT    1
#define ADS1115_CFG_COMP_QUE_LENGTH 2


#define ADS1115_MUX_P0_N1           0x00 // default
#define ADS1115_MUX_P0_N3           0x01
#define ADS1115_MUX_P1_N3           0x02
#define ADS1115_MUX_P2_N3           0x03
#define ADS1115_MUX_P0_NG           0x04
#define ADS1115_MUX_P1_NG           0x05
#define ADS1115_MUX_P2_NG           0x06
#define ADS1115_MUX_P3_NG           0x07

#define ADS1115_PGA_6P144           0x00
#define ADS1115_PGA_4P096           0x01
#define ADS1115_PGA_2P048           0x02 // default
#define ADS1115_PGA_1P024           0x03
#define ADS1115_PGA_0P512           0x04
#define ADS1115_PGA_0P256           0x05
#define ADS1115_PGA_0P256B          0x06
#define ADS1115_PGA_0P256C          0x07

#define ADS1115_MV_6P144            0.187500
#define ADS1115_MV_4P096            0.125000
#define ADS1115_MV_2P048            0.062500 // default
#define ADS1115_MV_1P024            0.031250
#define ADS1115_MV_0P512            0.015625
#define ADS1115_MV_0P256            0.007813
#define ADS1115_MV_0P256B           0.007813 
#define ADS1115_MV_0P256C           0.007813

#define ADS1115_MODE_CONTINUOUS     0x00
#define ADS1115_MODE_SINGLESHOT     0x01 // default

#define ADS1115_RATE_8              0x00
#define ADS1115_RATE_16             0x01
#define ADS1115_RATE_32             0x02
#define ADS1115_RATE_64             0x03
#define ADS1115_RATE_128            0x04 // default
#define ADS1115_RATE_250            0x05
#define ADS1115_RATE_475            0x06
#define ADS1115_RATE_860            0x07

#define ADS1115_COMP_MODE_HYSTERESIS    0x00 // default
#define ADS1115_COMP_MODE_WINDOW        0x01

#define ADS1115_COMP_POL_ACTIVE_LOW     0x00 // default
#define ADS1115_COMP_POL_ACTIVE_HIGH    0x01

#define ADS1115_COMP_LAT_NON_LATCHING   0x00 // default
#define ADS1115_COMP_LAT_LATCHING       0x01

#define ADS1115_COMP_QUE_ASSERT1    0x00
#define ADS1115_COMP_QUE_ASSERT2    0x01
#define ADS1115_COMP_QUE_ASSERT4    0x02
#define ADS1115_COMP_QUE_DISABLE    0x03 // default

/**
 * @brief Initializes Bosch BME688 sensor.
 *
 * @note Has to be called before other functions are used.
 *
 * @return 0 if success, error code if failure.
 */
int sensor_init(void);

/**
 * @brief Updates and stores internally data measured by sensor.
 *
 * @note A single call updates temperature, pressure and humidity values at once.
 *
 * @return 0 if success, error code if failure.
 */
int sensor_update_measurements(void);

/**
 * @brief Provides last measured value of temperature.
 *
 * @note Call sensor_update_measurements() to update the value.
 *
 * @param temperature [out] temperature value in Celsiuss degrees.
 *
 * @return 0 if success, error code if failure.
 */
int sensor_get_temperature(float *temperature);

/**
 * @brief Provides last measured value of pressure.
 *
 * @note Call sensor_update_measurements() to update the value.
 *
 * @param pressure [out] pressure value in kPa.
 *
 * @return 0 if success, error code if failure.
 */
int sensor_get_pressure(float *pressure);

/**
 * @brief Provides last measured value of relative humidity.
 *
 * @note Call sensor_update_measurements() to update the value.
 *
 * @param humidity [out] relative humidity value in %.
 *
 * @return 0 if success, error code if failure.
 */
int sensor_get_humidity(float *humidity);

#endif /* SENSOR_H */
