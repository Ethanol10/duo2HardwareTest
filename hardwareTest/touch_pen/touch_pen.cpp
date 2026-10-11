#include <iostream>
#include <string>
#include <vendor/surface/touchpen/1.3/ITouchPen.h> 

using vendor::surface::touchpen::V1_3::ITouchPen;
using android::sp;
using android::hardware::Return;

void setDisplayState(sp<ITouchPen> service, int mode) {
    // Cast the integer to your HIDL strongly-typed enum
    ITouchPen::DisplayState testMode = static_cast<ITouchPen::DisplayState>(mode);

    std::cout << "[+] Transmitting DisplayState mode: " << mode << std::endl;
    service->setDisplayState(testMode);
    std::cout << "[+] setDisplayState Triggered"<< std::endl;
}

void setDexterity(sp<ITouchPen> service, int mode){
    ITouchPen::Dexterity testMode = static_cast<ITouchPen::Dexterity>(mode);

    std::cout << "[+] Transmitting Dexterity mode: " << mode << std::endl;
    service->setDexterity(testMode);
    std::cout << "[+] setDexterity Triggered"<< std::endl;
}

void setTapToWakeEnable(sp<ITouchPen> service, bool mode){
    std::cout << "[+] Transmitting Dexterity mode: " << mode << std::endl;
    service->setTapToWakeEnable(mode);
    std::cout << "[+] setTapToWakeEnable Triggered"<< std::endl;
}

void setInteractive(sp<ITouchPen> service, bool mode){
    std::cout << "[+] Transmitting Interactivity mode: " << mode << std::endl;
    service->setInteractive(mode);
    std::cout << "[+] setInteractive Triggered"<< std::endl;
}

void hingeAngle(sp<ITouchPen> service, int angle){
    std::cout << "[+] Transmitting DisplayState mode: " << angle << std::endl;
    service->hingeAngle(angle);
    std::cout << "[+] hingeAngle Triggered"<< std::endl;
}

int main(int argc, char** argv) {

    // We need at least argv[1] (the function string/int). 
    // If they want to write/set, they also need argv[2].
    if (argc < 2) {
        std::cout << "[-] Usage: ./touch_pen <func_id> [int_val]" << std::endl;
        std::cout << "    func_id: 1 = setDisplayState, 2 = setDexterity, 3 = setTapToWakeEnable";
        std::cout << "             4 = setInteractive, 5 = hingeAngle" << std::endl;
        return -1;
    }

    int funcInt = std::stoi(argv[1]);
    int intVal = 0;
    bool boolVal = false;

    if (funcInt == 1 || funcInt == 5) {
        if (argc < 3) {
            std::cerr << "[-] Error: selected func requires a value argument.\n";
            return -1;
        }
        intVal = std::stoi(argv[2]);
    }

    if(funcInt == 3 || funcInt == 4){
        if(argc < 4){
            std::cerr << "[-] Error: selected func requires a bool val" << std::endl;
            return -1;
        }

        boolVal = std::string(argv[3]) == "true";
    }

    std::cout << "[+] Connecting to TouchPen Service..." << std::endl;

    // 1. Fetch the default instance of the target HAL service
    // If the service has a specific instance name, pass it as an argument (e.g., "default")
    sp<ITouchPen> service = ITouchPen::getService();

    if (service == nullptr) {
        std::cerr << "[-] Failed to fetch the TouchPen service proxy." << std::endl;
        return -1;
    }
    std::cout << "[+] Successfully connected to the TouchPen service!" << std::endl;

    switch (funcInt) {
        case 1:
            if(intVal == -1){
                std::cout << "[-] setComposition requires a value to test" << std::endl;
                return -1;
            }
            setDisplayState(service, intVal);
            break;
        case 2:
            setDexterity(service, intVal);
            break;
        case 3:
            setTapToWakeEnable(service, boolVal);
            break;
        case 4:
            setInteractive(service, boolVal);
            break;
        case 5: 
            hingeAngle(service, intVal);
            break;
        default:
            std::cerr << "[-] Unknown function ID. Current range 1-2" << std::endl;
            break;
    }
    return 0;
}