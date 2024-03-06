#ifndef AMD_MEM_H
#define AMD_MEM_H
#include <string>
using namespace std;
#include "libdrm.h"
#include "../status.h"

class Mem_AMDGPU
{
public:
    Mem_AMDGPU(LibDrm* drm, std::string dev_path, std::map<std::string,std::map<std::string, std::string>>& infos);
    void parse(HardwareStatus_per* status);

private:
    std::string dev_path_;
    LibDrm* drm_ = nullptr;
    //get firmware version and feature from /sys/kernel/debug/dri/0/amdgpu_firmware_info, this has a ip list than ioctl
};
#endif // AMD_MEM_H
