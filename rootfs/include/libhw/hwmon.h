#ifndef HWMON_H
#define HWMON_H
#include <string>
#include <map>
#include <list>
#include "status.h"
class StatusValue;

class Hwmon
{
public:
    Hwmon(std::string path):hwmon_path(path){}
    void parse(HardwareStatus_per* status);
    static void parse_name(std::string hwmon_name, HardwareStatus_per* status);
    void tempFanTest(int fan_idx);

    bool parseTemp(HardwareStatus_per* status);
#define MAX_HWMON 10

private:
    std::string hwmon_path;
};

#endif // HWMON_H
