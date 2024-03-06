#ifndef KMS_H
#define KMS_H
#include <vector>
#include <map>
#include <cstdint>
#include "libdrm/amdgpu_drm.h"
#include "libdrm/amdgpu.h"

class LibDrm
{
public:
    LibDrm(int idx);
    ~LibDrm();
    uint32_t read_reg(uint32_t offset);
    uint32_t  major_version_;
    uint32_t  minor_version_;

    drm_amdgpu_info_device device_info_;
    amdgpu_gpu_info gpu_info_; //amdgpu_gpu_info is wrapper of drm_amdgpu_info_device, but two has some different content


    amdgpu_device_handle device_handle_ = nullptr;
    int fd_ = -1;

private:
    int idx_ = -1;
};

#endif // KMS_H
