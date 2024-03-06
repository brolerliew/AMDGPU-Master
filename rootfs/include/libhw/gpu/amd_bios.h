#ifndef AMD_BIOS_H
#define AMD_BIOS_H

#endif // AMD_BIOS_H

#include "amdgpu.h"
#include <string>
#include "libdrm.h"
struct BIOS_AMDGPU{
    BIOS_AMDGPU(LibDrm* drm, std::string dev_path);
    ~BIOS_AMDGPU();
    bool sync(bool flush);

    drm_amdgpu_info_vbios info;
    std::vector<uint8_t> data;

    ATOM_ROM_HEADER *hdr =nullptr;
    ATOM_MASTER_LIST_OF_DATA_TABLES *DataTblList = nullptr; //DataTblList->PowerPlayInfo is pptable in rom
private:
    std::string dev_path_;
    char* vbios = nullptr;

    LibDrm* drm_ = nullptr;
};
