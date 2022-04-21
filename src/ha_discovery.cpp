#include "ha_discovery.hpp"
#include "string.h"
#include "stdio.h"

void jsonOpen(char* json) {
    json[0] = '\0';
    strcat(json, "{");
}

void jsonClose(char* json) {
    strcat(json, "}");
}

void jsonAddSeparatorIfNeeded(char* json) {
    if(json[1] != '\0') {
        strcat(json, ",");
    }
}

void jsonAddStringProperty(char* json, char* name, char* value) {
    jsonAddSeparatorIfNeeded(json);
    int len = strlen(name) + strlen(value) + 6;
    char property[len];
    property[0] = '\0';
    sprintf(property, "\"%s\":\"%s\"", name, value);
    strcat(json, property);
}

void jsonAddBooleanProperty(char* json, char* name, bool value) {
    jsonAddSeparatorIfNeeded(json);
    int len = strlen(name) + 9;
    char property[len];
    property[0] = '\0';
    sprintf(property, "\"%s\":%s", name, value? "true" : "false");
    strcat(json, property);
}

void jsonAddIntegerProperty(char* json, char* name, int value) {
    jsonAddSeparatorIfNeeded(json);
    int len = strlen(name) + 9;
    char property[len];
    property[0] = '\0';
    sprintf(property, "\"%s\":%d", name, value);
    strcat(json, property);
}

void jsonAddObjProperty(char* json, char* name, char* objJson) {
    jsonAddSeparatorIfNeeded(json);
    int len = strlen(name) + strlen(objJson) + 2;
    char property[len];
    property[0] = '\0';
    sprintf(property, "\"%s\":%s", name, objJson);
    strcat(json, property);
}

void jsonAddStringList(char* json, char* name, char* entries[], int size) {
    jsonAddSeparatorIfNeeded(json);
    strcat(json, "\"");
    strcat(json, name);
    strcat(json, "\":");
    char list[255];
    list[0] = '\0';
    strcat(list, "[");
    for(int i = 0; i < size; i++) {
        jsonAddSeparatorIfNeeded(list);
        strcat(list, "\"");
        strcat(list, entries[i]);
        strcat(list, "\"");
    }
    strcat(list, "]");
    strcat(json, list);
}

void haDeviceToJson(char* json, HADevice device) {
    jsonOpen(json);
    if(device.numIdentifiers)
        jsonAddStringList(json, "ids", device.identifiers, device.numIdentifiers);
    if(device.configuration_url)
        jsonAddStringProperty(json, "cu", device.configuration_url);
    if(device.manufacturer)
        jsonAddStringProperty(json, "mf", device.manufacturer);
    if(device.model)
        jsonAddStringProperty(json, "mdl", device.model);
    if(device.name)
        jsonAddStringProperty(json, "name", device.name);
    if(device.suggested_area)
        jsonAddStringProperty(json, "sa", device.suggested_area);
    if(device.sw_version)
        jsonAddStringProperty(json, "sw", device.sw_version);
    if(device.via_device)
        jsonAddStringProperty(json, "via_device", device.via_device);
    jsonClose(json);
}

void addEntityPropertiesToJson(char* json, HAEntity entity) {
    if(entity.availability_topic)
        jsonAddStringProperty(json, "avty_t", entity.availability_topic);
    if(entity.device) {
        char device[255];
        haDeviceToJson(device, *entity.device);
        jsonAddObjProperty(json, "dev", device);
    }
    if(entity.entity_category)
        jsonAddStringProperty(json, "ent_cat", entity.entity_category);
    if(entity.icon)
        jsonAddStringProperty(json, "ic", entity.icon);
    if(entity.name)
        jsonAddStringProperty(json, "name", entity.name);
    if(entity.object_id)
        jsonAddStringProperty(json, "obj_id", entity.object_id);
    if(entity.payload_available)
        jsonAddStringProperty(json, "pl_avail", entity.payload_available);
    if(entity.payload_not_available)
        jsonAddStringProperty(json, "pl_not_avail", entity.payload_not_available);
    if(entity.qos)
        jsonAddIntegerProperty(json, "qos", entity.qos);
    if(entity.state_topic)
        jsonAddStringProperty(json, "stat_t", entity.state_topic);
    if(entity.unique_id)
        jsonAddStringProperty(json, "uniq_id", entity.unique_id);
}

void haSensorToJson(char* json, HASensor sensor) {
    jsonOpen(json);
    addEntityPropertiesToJson(json, sensor);
    if(sensor.device_class) 
        jsonAddStringProperty(json, "dev_cla", sensor.device_class);
    if(!sensor.enabled_by_default)
        jsonAddBooleanProperty(json, "enabled_by_default", sensor.entity_category);
    if(sensor.expire_after)
        jsonAddIntegerProperty(json, "exp_aft", sensor.expire_after);
    if(sensor.force_update)
        jsonAddBooleanProperty(json, "frc_upd", sensor.force_update);
    if(sensor.last_reset)
        jsonAddStringProperty(json, "last_reset", sensor.last_reset);
    if(sensor.state_class)
        jsonAddStringProperty(json, "stat_cla", sensor.state_class);
    jsonClose(json);
}

void haDeviceTrackerToJson(char* json, HADeviceTracker tracker){
    jsonOpen(json);
    addEntityPropertiesToJson(json, tracker);
    jsonClose(json);
}

bool mgos_Home_Assistant_MQTT_Discovery_C_lib_init(void) {
  return true;
}
