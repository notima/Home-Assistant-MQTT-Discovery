#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ha_discovery.hpp"

int main() {
    HASensor sensor = HASensor();
    sensor.name = "test sensor";
    sensor.state_topic = "hello/world/foo/bar";
    sensor.force_update = true;
    HADevice device = HADevice();
    sensor.device = &device;
    sensor.device->configuration_url = "http://192.168.4.1";
    sensor.device->identifiers[0] = "1234";
    sensor.device->identifiers[1] = "5678";
    sensor.device->numIdentifiers = 2;
    sensor.device->name = "test device";
    sensor.enabled_by_default = true;
    sensor.expire_after = 20;
    char* json = (char*)malloc(255);
    haSensorToJson(json, sensor);
    printf("[%ld] %s\n", strlen(json), json);

    return strcmp(json, "{\"dev\":{\"ids\":[\"1234\",\"5678\"],\"cu\":\"http://192.168.4.1\",\"name\":\"test device\"},\"name\":\"test sensor\",\"stat_t\":\"hello/world/foo/bar\",\"exp_aft\":20,\"frc_upd\":true}");
}