#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discovery.h"

int main() {
    MqttSensor sensor;
    memset(&sensor, 0, sizeof(MqttSensor));
    sensor.name = "test sensor";
    sensor.state_topic = "hello/world/foo/bar";
    sensor.force_update = true;
    MqttDevice device;
    memset(&device, 0, sizeof(MqttDevice));
    sensor.device = &device;
    sensor.device->configuration_url = "http://192.168.4.1";
    sensor.device->identifiers[0] = "1234";
    sensor.device->identifiers[1] = "5678";
    sensor.device->numIdentifiers = 2;
    sensor.device->name = "test device";
    sensor.enabled_by_default = true;
    sensor.expire_after = 20;
    char* json = malloc(255);
    mqttSensorToJson(json, sensor);
    printf("[%ld] %s\n", strlen(json), json);

    return strcmp(json, "{\"dev\":{\"ids\":[\"1234\",\"5678\"],\"cu\":\"http://192.168.4.1\",\"name\":\"test device\"},\"exp_aft\":20,\"frc_upd\":true,\"name\":\"test sensor\",\"stat_t\":\"hello/world/foo/bar\"}");
}