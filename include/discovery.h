#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MqttDevice {
    char* configuration_url;
    char* identifiers[4];
    uint8_t numIdentifiers;
    char* manufacturer;
    char* model;
    char* name;
    char* suggested_area;
    char* sw_version;
    char* via_device;
} MqttDevice;

typedef struct MqttEntity {
    char* availability_topic;
    MqttDevice* device;
    char* encoding;
    char* entity_category;
    char* icon;
    char* name;
    char* object_id;
    char* payload_available;
    char* payload_not_available;
    uint8_t qos;
    char* state_topic;
    char* unique_id;
} MqttEntity;

typedef struct MqttSensor {
    struct MqttEntity;
    char* device_class;
    bool enabled_by_default;
    int expire_after;
    bool force_update;
    char* last_reset;
    char* state_class;
    char* unit_of_measurement;
} MqttSensor;

typedef struct MqttDeviceTracker {
    struct MqttEntity;
} MqttDeviceTracker;

void mqttSensorToJson(char* json, MqttSensor sensor);
void mqttDeviceTrackerToJson(char* json, MqttDeviceTracker tracker);

#ifdef __cplusplus
}
#endif