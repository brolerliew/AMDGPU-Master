# AMDGPU Master
## Overview
1. Show detailed AMDGPU information like Voltage, Frequency, IP, Power, Firmware, VRAM, Core, PCI-E and other Chip informations.
2. Monitor GPU running status, including IP specific usage and all available status information reading from registers

## Screenshots 
infos:

![图片](https://github.com/brolerliew/AMDGPU-Master/assets/2776196/9af937aa-3d0d-4b05-a693-2d34250de56a)
![图片](https://github.com/brolerliew/AMDGPU-Master/assets/2776196/b5c13582-3c80-47e0-b2b1-c150d3eda43e)
![图片](https://github.com/brolerliew/AMDGPU-Master/assets/2776196/0c5b12be-9cd2-4443-b5f3-dd3f6e9ca6fb)
![图片](https://github.com/brolerliew/AMDGPU-Master/assets/2776196/be1a1c1c-b8d8-4969-855b-b9b0c2bf6263)
![图片](https://github.com/brolerliew/AMDGPU-Master/assets/2776196/c3681dfc-73bb-4e61-9f41-a0d8cdcb6d8c)

status:
![图片](https://github.com/brolerliew/AMDGPU-Master/assets/2776196/e4a254f0-ee28-4e64-9bfa-ca500c1ee78a)

# Build
rootfs directory is libraries and headers this repo used, including libdrm precompiled binary. This repo is developed on latest Ubuntu with KDE. You can always use libdrm-dev package on latest Ubuntu instead of the precompile one.

To build, use QtCreator(with Qt6 installed) open AMDGPU-Master/amdgpu_master/CMakeLists.txt project file, click run.

# TODO
