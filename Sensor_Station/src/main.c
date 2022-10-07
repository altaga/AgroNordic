/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 * Copyright (c) 2019 Marcio Montenegro <mtuxpe@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include "sensor.h"

#define COUNTER_NODE DT_ALIAS(counter)
#define ENABLE_NODE DT_ALIAS(enable)

LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);

static const struct gpio_dt_spec counters = GPIO_DT_SPEC_GET_OR(COUNTER_NODE, gpios, {0});

static const struct gpio_dt_spec enabler = GPIO_DT_SPEC_GET_OR(ENABLE_NODE, gpios, {0});

/* Button value. */
static uint16_t temp;
static uint16_t hum;
static uint16_t moi;

/* Prototype */
static ssize_t recv(struct bt_conn *conn,
					const struct bt_gatt_attr *attr, const void *buf,
					uint16_t len, uint16_t offset, uint8_t flags);

/* ST Custom Service  */
static struct bt_uuid_128 st_service_uuid_temp = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe40, 0xcc7a, 0x482a, 0x984a, 0x7f2ed5b3e58f));
static struct bt_uuid_128 st_service_uuid_hum = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe41, 0xcc7a, 0x482a, 0x984a, 0x7f2ed5b3e58f));
static struct bt_uuid_128 st_service_uuid_moi = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe42, 0xcc7a, 0x482a, 0x984a, 0x7f2ed5b3e58f));

/* ST Notify Sensors services */
static struct bt_uuid_128 temp_notif_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe43, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed19));
static struct bt_uuid_128 hum_notif_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe44, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed19));
static struct bt_uuid_128 moi_notif_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x0000fe45, 0x8e22, 0x4541, 0x9d4c, 0x21edae82ed19));

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
#define ADV_LEN 12

/* Advertising data */
static uint8_t manuf_data[ADV_LEN] = {
	0x01 /*SKD version */,
	0x83 /* STM32WB - P2P Server 1 */,
	0x00 /* GROUP A Feature  */,
	0x00 /* GROUP A Feature */,
	0x00 /* GROUP B Feature */,
	0x00 /* GROUP B Feature */,
	0x00, /* BLE MAC start -MSB */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, /* BLE MAC stop */
};

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
	BT_DATA(BT_DATA_MANUFACTURER_DATA, manuf_data, ADV_LEN)};

/* BLE connection */
struct bt_conn *conn;
/* Notification state */
volatile bool notify_enable_temp;
volatile bool notify_enable_hum;
volatile bool notify_enable_moi;

static void mpu_ccc_cfg_changed_temp(const struct bt_gatt_attr *attr, uint16_t value)
{
	ARG_UNUSED(attr);
	notify_enable_temp = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("Notification %s", notify_enable_temp ? "enabled" : "disabled");
}

static void mpu_ccc_cfg_changed_hum(const struct bt_gatt_attr *attr, uint16_t value)
{
	ARG_UNUSED(attr);
	notify_enable_hum = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("Notification %s", notify_enable_hum ? "enabled" : "disabled");
}

static void mpu_ccc_cfg_changed_moi(const struct bt_gatt_attr *attr, uint16_t value)
{
	ARG_UNUSED(attr);
	notify_enable_moi = (value == BT_GATT_CCC_NOTIFY);
	LOG_INF("Notification %s", notify_enable_moi ? "enabled" : "disabled");
}

/* The embedded board is acting as GATT server.
 * The ST BLE Android app is the BLE GATT client.
 */

/* ST BLE Sensor GATT services and characteristic */

BT_GATT_SERVICE_DEFINE(stsensor_svc,
					   BT_GATT_PRIMARY_SERVICE(&st_service_uuid_temp),
					   BT_GATT_CHARACTERISTIC(&temp_notif_uuid.uuid, BT_GATT_CHRC_NOTIFY,
											  BT_GATT_PERM_READ, NULL, NULL, &temp),
					   BT_GATT_CCC(mpu_ccc_cfg_changed_temp, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
					   BT_GATT_PRIMARY_SERVICE(&st_service_uuid_hum),
					   BT_GATT_CHARACTERISTIC(&hum_notif_uuid.uuid, BT_GATT_CHRC_NOTIFY,
											  BT_GATT_PERM_READ, NULL, NULL, &hum),
					   BT_GATT_CCC(mpu_ccc_cfg_changed_hum, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
					   BT_GATT_PRIMARY_SERVICE(&st_service_uuid_moi),
					   BT_GATT_CHARACTERISTIC(&moi_notif_uuid.uuid, BT_GATT_CHRC_NOTIFY,
											  BT_GATT_PERM_READ, NULL, NULL, &moi),
					   BT_GATT_CCC(mpu_ccc_cfg_changed_moi, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE), );

static void bt_ready(int err)
{
	if (err)
	{
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return;
	}
	LOG_INF("Bluetooth initialized");
	/* Start advertising */
	err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err)
	{
		LOG_ERR("Advertising failed to start (err %d)", err);
		return;
	}

	LOG_INF("Configuration mode: waiting connections...");
}

static void connected(struct bt_conn *connected, uint8_t err)
{
	if (err)
	{
		LOG_ERR("Connection failed (err %u)", err);
	}
	else
	{
		LOG_INF("Connected");
		if (!conn)
		{
			conn = bt_conn_ref(connected);
		}
	}
}

static void disconnected(struct bt_conn *disconn, uint8_t reason)
{
	if (conn)
	{
		bt_conn_unref(conn);
		conn = NULL;
	}

	LOG_INF("Disconnected (reason %u)", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

void main(void)
{
	// Initialize the Sensor Subsystem
	int err = sensor_init();
	if (err)
	{
		LOG_ERR("Failed to initialize sensor: %d", err);
	}

	// Initialize the Bluetooth Subsystem
	err = bt_enable(bt_ready);
	if (err)
	{
		LOG_ERR("Bluetooth init failed (err %d)", err);
	}

	gpio_pin_configure_dt(&counters, GPIO_INPUT);
	gpio_pin_configure_dt(&enabler, GPIO_INPUT);
	uint16_t counter = 0;
	uint16_t counterMemory = 0;
	int flagSave = 0;
	int flagIN = 0;
	int flagOUT = 0;

	while (1)
	{
		if (!gpio_pin_get_dt(&enabler))
		{
			flagSave = 1;
			if (!gpio_pin_get_dt(&counters))
			{
				flagIN = true;
				flagOUT = false;
			}
			if (gpio_pin_get_dt(&counters))
			{
				flagOUT = true;
			}
			if (flagOUT && flagIN)
			{
				flagIN = false;
				flagOUT = false;
				counter++;
			}
		}
		else
		{
			float temps = 0;
			float hums = 0;

			if (flagSave)
			{
				counterMemory = counter;
				flagSave = 0;
				counter = 0;
			}

			int err = sensor_update_measurements();
			if (err)
			{
				LOG_ERR("Failed to update sensor");
			}

			// Get Sensor Data
			sensor_get_temperature(&temps);
			sensor_get_humidity(&hums);

			// Set Temperature
			temp = (uint16_t)(temps * 100);
			LOG_INF("%d", temp / 100);
			k_msleep(1);

			// Set Humidity
			hum = (uint16_t)hums;
			LOG_INF("%d", hum);
			k_msleep(1);

			// Set Moisture
			moi = (uint16_t)counterMemory;
			LOG_INF("%d", moi);
			k_msleep(1);

			// Notify Temperature
			err = bt_gatt_notify(NULL, &stsensor_svc.attrs[2],
								 &temp, sizeof(temp));
			if (err)
			{
				LOG_ERR("Notify error: %d", err);
			}
			else
			{
				LOG_INF("Send notify ok");
				temp = (temp == 0) ? 0x100 : 0;
			}
			k_msleep(1000);
			// Notify Humidity
			err = bt_gatt_notify(NULL, &stsensor_svc.attrs[5],
								 &hum, sizeof(hum));
			if (err)
			{
				LOG_ERR("Notify error: %d", err);
			}
			else
			{
				LOG_INF("Send notify ok");
				hum = (hum == 0) ? 0x100 : 0;
			}
			k_msleep(1000);
			// Notify Moisture
			err = bt_gatt_notify(NULL, &stsensor_svc.attrs[8],
								 &moi, sizeof(moi));
			if (err)
			{
				LOG_ERR("Notify error: %d", err);
			}
			else
			{
				LOG_INF("Send notify ok");
				moi = (moi == 0) ? 0x100 : 0;
			}
			k_msleep(1000);
		}
		k_msleep(1);
	}
}
