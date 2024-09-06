# rockchip EGL/GLES media player running on Wayland/Weston
This is an video player rendering by EGL/GLES, which running on the rockchip(tested on rk3288).
At the moment, this player doesn't support audio and I want to just showcase how we can use EGL/GLES renfererer on rockchip SoC.

## Prerequisite
Before building this player, 
you need your sys rootfs for rockchip having dependancies.
- FFmpeg
- weston/wayland (tested on rockchip rk3288 board)
- EGL/GLES library for your target board. (tested on rockchip rk3288 board)
- DRM library

I made buildroot as an example sys rootfs just to build this player
You can get form
[Github](https://github.com/Jin4everHome/buildroot.git)

## Build
Build sysfs
$git clone https://github.com/Jin4everHome/buildroot.git
$cd buildroot
$make rockchip_defconfig
$make
Build wayland_mpp_video_player
$cd ../
$git clone https://github.com/Jin4everHome/wayland_mpp_video_player.git
$cd wayland_mpp_video_player
$mkdir build
$cd build
$cmake ../
$make
## RUN
You need to install output executable file(rkplayer) to your target board.
The rootfs of your target board must have the dependancies when you are build rkplayer
```bash
1. Install binary rkplayer
2. run player on your target board
  [local]
     rkplay file://<path_to_your_local_media_file>
  [URL]
     rkplay https://<path_to_file>
     rkplay http://<path_to_file>
     rkplay udp://<path_to_file>
// code example
## License
This project is licensed under the MIT License - see the LICENSE file for details.




    

