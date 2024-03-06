#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <fstream>
extern std::ofstream ofs;
extern std::ofstream ofs_warning;
extern std::ofstream ofs_test;

#include "pci.h"
#include "scsi.h"
#include <limits>
#include "dmi.h"
#include "hwmon.h"
#include "status.h"

struct HardwareInfo_per{
	PCI_Info* pci_info = nullptr;
    SCSI_config* scsi_cfg = nullptr;
    Hwmon* hwmon = nullptr;
    std::string name;
    bool enable = true;
    const std::string dev_path;
    HardwareInfo_per(std::string _dev_path);
    ~HardwareInfo_per();
    virtual std::shared_ptr<HardwareStatus_per> status_get_per() = 0;
    virtual std::map<std::string, std::string> get_infos(){return infos_;};
    virtual void test(){};
    std::map<std::string,std::map<std::string, std::string>> infos;
protected:
    std::map<std::string, std::string> infos_;
    static Dmi dmi;
    friend class CPUInfo;
};


class HardwareInfo{
public:
    HardwareInfo();
    virtual ~HardwareInfo(){};
    std::vector<HardwareInfo_per*> hwinfos;
    std::shared_ptr<HardwareStatus> status_cal();
    virtual void test();
protected:
    virtual std::shared_ptr<HardwareStatus> status_cal_(std::shared_ptr<HardwareStatus> now);
    virtual std::shared_ptr<HardwareStatus> status_get() = 0;
    std::shared_ptr<HardwareStatus> last_status_ = nullptr;
    std::shared_ptr<HardwareStatus> last_status_cal_ = nullptr;
};
