#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>
#include <cstdint>

class Monitor
{
public:
    Monitor(std::string dev_path);
    void sync(bool flush);
    std::string dpms;
    std::vector<char> edid;
    bool enabled;
    bool connected;
    uint32_t connector_id;
    std::vector<std::string> modes;
private:
    std::string dev_path_;
};

#endif // MONITOR_H
