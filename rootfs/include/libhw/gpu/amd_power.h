#ifndef AMD_POWER_H
#define AMD_POWER_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include "amdgpu.h"
#include "libdrm.h"
#include "../status.h"

struct Power_AMDGPU_voltage_clock_table{
    Power_AMDGPU_voltage_clock_table(std::string dev_path):dev_path_(dev_path){}
    void parse();
    void flush();
    void print();

    struct VC{
        uint32_t voltage = 0;
        uint32_t freq = 0;
    };
    std::vector<VC> od_sclk;
    uint32_t od_sclk_min = std::numeric_limits<uint32_t>::min();
    uint32_t od_sclk_max = std::numeric_limits<uint32_t>::max();
    std::vector<VC> od_mclk;
    uint32_t od_mclk_min = std::numeric_limits<uint32_t>::min();
    uint32_t od_mclk_max = std::numeric_limits<uint32_t>::max();
    uint32_t vddc_min = std::numeric_limits<uint32_t>::min();
    uint32_t vddc_max = std::numeric_limits<uint32_t>::max();
    bool needFlush = false;

private:
    std::string dev_path_;
};

struct Power_AMDGPU_pptable{
    Power_AMDGPU_pptable(std::string dev_path):dev_path_(dev_path){sync(false);}
    bool sync(bool flush);
    bool needFlush = false;
    std::vector<char> buf;
protected:
    std::string dev_path_;
};

struct Power_AMDGPU{
    Power_AMDGPU(LibDrm* drm, std::string dev_path);
    Power_AMDGPU_voltage_clock_table vctable;  //may not use this,use pptable and drm api instead
    Power_AMDGPU_pptable pptable;
    void parse(HardwareStatus_per* status);
    int flush_voltage_clock_table();
    void setPerfromanceLevel(amd_dpm_forced_level level);
private:
    std::string dev_path_;
    //TODO: change to online normal values
    Power_AMDGPU_voltage_clock_table vctable_o;
    LibDrm* drm_ = nullptr;
};


#endif // AMD_POWER_H
