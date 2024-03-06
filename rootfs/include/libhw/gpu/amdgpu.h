#ifndef AMDGPU_H
#define AMDGPU_H

#include <cstdint>
#include <cstdlib>
typedef uint32_t u32;
typedef int32_t s32;
typedef uint8_t u8;

#if defined(_WIN32)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
extern "C"{
#include "amdgpu/atom-types.h"

#include "amdgpu/atomfirmware.h"

#include "amdgpu/signal_types.h"
#include "amdgpu/dc_dp_types.h"
#include "amdgpu/dm_pp_interface.h"
#include "amdgpu/kgd_pp_interface.h"
#include "amdgpu/atombios.h"
}
/*
#include "amdgpu/pptable_v1_0.h"

to use pptable, include these header and use directly. PPTable_t redefine many times and different,so I cannot inhereit impl

#include "amdgpu/smu9_driver_if.h"
#include "amdgpu/vega10_pptable.h"

#include "amdgpu/pm/powerplay/inc/vega12/smu9_driver_if.h"
#include "amdgpu/vega12_pptable.h"

#include "amdgpu/smu11_driver_if.h"
#include "amdgpu/vega20_pptable.h"


#include "amdgpu/smu13_driver_if_v13_0_0.h"
#include "amdgpu/smu_v13_0_pptable.h"
#include "amdgpu/smu_v11_0_pptable.h"
#include "amdgpu/smu_v11_0_7_pptable.h"
#include "amdgpu/smu_v13_0_7_pptable.h"
*/
#define SMU_13_0_TABLE_FORMAT_REVISION 1
#endif // AMDGPU_H
