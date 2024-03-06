#ifndef ENCODERDECODER_AMDGPU_H
#define ENCODERDECODER_AMDGPU_H

#include "libdrm.h"
#include <string>
class EncoderDecoder_AMDGPU
{
public:
    EncoderDecoder_AMDGPU(LibDrm* drm,int idx,std::map<std::string,std::map<std::string, std::string>>& infos);

};

#endif // ENCODERDECODER_AMDGPU_H
