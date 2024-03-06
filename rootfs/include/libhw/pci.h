#pragma once
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

struct PciSubDevice{
    std::string vendor_id;
    std::string device_id;
    std::string name;
};
struct PciDevice{
    std::string id;
    std::string name;
    std::unordered_map<std::string, PciSubDevice> subdevs;
};
struct PciVendor{
    std::string id;
    std::string name;
    std::unordered_map<std::string, PciDevice> devs;
};
struct PciResource{
    uint64_t start_addr;
    uint64_t end_addr;
    uint64_t flags;
};
struct PCI_Info{
	PCI_Info(std::string dev_path);
    uint8_t cfg64[64];
	std::map<std::string, uint32_t> aer_dev_correctable;
	std::map<std::string, uint32_t> aer_dev_fatal;
	std::map<std::string, uint32_t> aer_dev_nonfatal;
    std::vector<PciResource> resources;
    //mmio(resource),iommu parse
    std::string name;
    //rom file is handled in gpu
    static std::unordered_map<std::string, PciVendor> pciinfo;
};

