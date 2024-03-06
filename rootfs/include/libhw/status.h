#ifndef STATUS_H
#define STATUS_H
#include <string>
#include <limits>
#include <map>
#include <vector>
#include <memory>
struct StatusValue{
    std::string longname;
    std::string unit = "%";
    float value = 0;
    float value_target = 0;
    int precision = 1;
    float value_max = 0;
    float value_crit = 0;
    float value_crit_hist = 0;
    float value_min = 0;
    bool enable = true;
    bool counter =false;
};

struct HardwareStatus_per{
    std::map<std::string, std::map<std::string, StatusValue>> status;//group,status
    virtual void print(){};
};

struct HardwareStatus{
    HardwareStatus();
    std::vector<std::shared_ptr<HardwareStatus_per>> hws;
    uint64_t tsMs;
    std::map<std::string, StatusValue> status;
    virtual void print(){};
};
#endif // STATUS_H
