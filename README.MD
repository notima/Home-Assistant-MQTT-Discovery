# Home Assistant MQTT Discovery Library

This library provides data structures and serialization functions for Home Assistant MQTT Discovery configurations.

## Example usage

```c
HASensor sensor = HASensor();
HADevice device = HADevice();
sensor.name = "test sensor";
sensor.state_topic = "hello/world/foo/bar";
sensor.force_update = true;
sensor.device = &device;
sensor.device->configuration_url = "http://192.168.4.1";
sensor.device->identifiers[0] = "1234";
sensor.device->identifiers[1] = "5678";
sensor.device->numIdentifiers = 2;
sensor.device->name = "test device";
sensor.enabled_by_default = true;
sensor.expire_after = 20;
// make sure to allocate enough memory
char* json = (char*)malloc(255);
haSensorToJson(json, sensor); // result is written to json
```

After running the above code, the json buffer will contain the following:

```json
// new lines and spaces added for readability

{
    "avty_t": "hello/world/foo/bar",
    "dev": {
        "ids": [
            "1234",
            "5678"
        ],
        "cu": "http://192.168.4.1" ,
        "name": "test device"
    },
    "ic": "mdi:lan",
    "name": "test tracker",
    "stat_t": "hello/world/foo/bar"
}
```

## Testing

```bash
cmake . -B build
cmake --build build
cd build
ctest
```