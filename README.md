# duo2HardwareTest
Testing HALs using C++

This is intended to be used inside the DUO-DE AOSP build tree.

In order to use this:

Install an AOSP line:
```
source build/envsetup.sh
source build/core/build_id.mk

lunch treble_arm64_bgN-bp2a-userdebug
make display_topology_test
make touch_pen_test
```

Copy to device 
```
adb push <ROOT LOCATION>/touch_pen_test /data/local/tmp
```

Run Shell (needs root!)
```
adb shell

// Use Magisk to get su
su

//navigate to binary location
cd ./data/local/tmp
./touch_pen_test <args>
./display_topology_test <args>
```

Read the script for possible arg combos.
