#ifndef SENSOR_AMDGPU_H
#define SENSOR_AMDGPU_H
#include <string>
#include <array>
using namespace std;
#include "libdrm.h"
#include "../status.h"


class IP_AMDGPU
{
public:
    IP_AMDGPU(LibDrm* drm,int idx,std::map<std::string,std::map<std::string, std::string>>& infos);
    void parse(HardwareStatus_per* status);
private:
    int idx_ = -1;
    LibDrm* drm_ = nullptr;
};

#endif // SENSOR_AMDGPU_H
