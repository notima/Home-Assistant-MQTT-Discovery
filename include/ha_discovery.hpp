#include "stdint.h"
#include "stdbool.h"

typedef struct HADevice {
    char* configuration_url;
    char* identifiers[4];
    uint8_t numIdentifiers;
    char* manufacturer;
    char* model;
    char* name;
    char* suggested_area;
    char* sw_version;
    char* via_device;
} HADevice;

typedef struct HAEntity {
    char* availability_topic;
    HADevice* device;
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
} HAEntity;

typedef struct HASensor : HAEntity {
    char* device_class;
    bool enabled_by_default;
    int expire_after;
    bool force_update;
    char* last_reset;
    char* state_class;
    char* unit_of_measurement;
} HASensor;

typedef struct HADeviceTracker : HAEntity {
    
} HADeviceTracker;

void haSensorToJson(char* json, HASensor sensor);
void haDeviceTrackerToJson(char* json, HADeviceTracker tracker);