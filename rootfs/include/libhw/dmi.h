#ifndef DMI_H
#define DMI_H
#include <vector>
#include <cstdint>
#pragma pack(1)
struct CoolingDevice{
    uint16_t tempProbe;
    uint8_t type:5;
    uint8_t status:3;
    uint8_t unitGroup;
    uint32_t oem;
    uint16_t normalSpeedRPM;
    uint8_t description;//only exist when size is 0xF or larger
};

class Dmi
{
public:
    Dmi();
    std::vector<CoolingDevice> coolingDevices;
private:
    void dmi_table_decode(const uint8_t *buf, uint32_t len);
};
enum DmiType{
    bios_info = 0, // Required
    system_info = 1, // Required
    baseboard_info = 2,
    module_info = 2,
    system_enclosure = 3, // Required
    system_chassis = 3, // Required
    processor_info = 4, // Required
    memory_controller_info = 5, // Obsolete
    memory_module_info = 6, // Obsolete
    cache_info = 7, // Required
    port_connector_info = 8,
    system_slots = 9, // Required
    onboard_device_info = 10, // Obsolete
    oem_strings = 11,
    system_config_options = 12,
    language_info = 13,
    group_associations = 14,
    system_event_log = 15,
    memory_array = 16, // Required
    memory_device = 17, // Required
    memory_error_info_32bit = 18,
    memory_array_mapped_addr = 19, // Required
    memory_device_mapped_addr = 20,
    builtin_pointing_device = 21,
    portable_battery = 22,
    system_reset = 23,
    hardware_security = 24,
    system_power_controls = 25,
    voltage_probe = 26,
    cooling_device = 27,
    temperature_probe = 28,
    electrical_current_probe = 29,
    out_of_band_remote_access = 30,
    bis_entry_point = 31, // Required
    system_boot_info = 32, // Required
    memory_error_info_64bit = 33,
    management_device = 34,
    management_device_component = 35,
    management_device_threshold = 36,
    memory_channel = 37,
    ipmi_device_info = 38,
    system_power_supply = 39,
    additional_info = 40,
    onboard_device_extinfo = 41,
    management_controller_host = 42,
    inactive = 126,
    end_of_table = 127, // Always last structure
};
#endif // DMI_H
