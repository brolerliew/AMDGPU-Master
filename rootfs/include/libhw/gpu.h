#pragma once
#include <vector>
#include <string>
#include "hardwareinfo.h"
#include "gpu/amd_power.h"
#include "gpu/amd_bios.h"
#include "gpu/amd_ip.h"
#include "gpu/amd_mem.h"
#include "gpu/amd_encoderdecoder.h"
#include "gpu/monitor.h"
#include "gpu/libdrm.h"

struct GPUInfo_per: public HardwareInfo_per{
    GPUInfo_per(int idx);
    void test();
    std::shared_ptr<HardwareStatus_per> status_get_per();
private: //constructor sequence should be drm first
    LibDrm drm;
public:
    Power_AMDGPU power;
    BIOS_AMDGPU vbios;
    IP_AMDGPU ip;
    Mem_AMDGPU mem;
    EncoderDecoder_AMDGPU decoderEncoder;
    std::vector<Monitor> monitors;
};


struct GPUStatus_per: public HardwareStatus_per{

};

class GPUInfo: public HardwareInfo{
public:
    GPUInfo();
private:
    std::shared_ptr<HardwareStatus> status_get();
};
