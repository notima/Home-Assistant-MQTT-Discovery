#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ha_discovery.hpp"

int main() {
    HADeviceTracker tracker;
    memset(&tracker, 0, sizeof(HADeviceTracker));
    tracker.name = "test tracker";
    tracker.availability_topic = "hello/world/foo/bar";
    tracker.state_topic = "hello/world/foo/bar";
    tracker.icon = "mdi:lan";
    HADevice device;
    memset(&device, 0, sizeof(HADevice));
    tracker.device = &device;
    tracker.device->configuration_url = "http://192.168.4.1";
    tracker.device->identifiers[0] = "1234";
    tracker.device->identifiers[1] = "5678";
    tracker.device->numIdentifiers = 2;
    tracker.device->name = "test device";
    char* json = (char*)malloc(255);
    haDeviceTrackerToJson(json, tracker);
    printf("[%ld] %s\n", strlen(json), json);

    return strcmp(json, "{\"avty_t\":\"hello/world/foo/bar\",\"dev\":{\"ids\":[\"1234\",\"5678\"],\"cu\":\"http://192.168.4.1\",\"name\":\"test device\"},\"ic\":\"mdi:lan\",\"name\":\"test tracker\",\"stat_t\":\"hello/world/foo/bar\"}");
}