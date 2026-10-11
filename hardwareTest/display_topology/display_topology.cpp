#include <iostream>
#include <string>
#include <vendor/surface/displaytopology/1.2/IDisplayTopology.h> 

using vendor::surface::displaytopology::V1_2::IDisplayTopology;
using android::sp;
using android::hardware::Return;

void setComposition(sp<IDisplayTopology> service, int mode) {
    // Cast the integer to your HIDL strongly-typed enum
    IDisplayTopology::DisplayComposition testMode = static_cast<IDisplayTopology::DisplayComposition>(mode);

    std::cout << "[+] Transmitting composition mode: " << mode << std::endl;
    Return<int32_t> set_result = service->setComposition(testMode);
    
    if (!set_result.isOk()) {
        std::cerr << "[-] IPC transaction failed: " << set_result.description() << std::endl;
        return;
    }
    
    std::cout << "[+] setComposition returned code: " << static_cast<int32_t>(set_result) << std::endl;
}

void getComposition(sp<IDisplayTopology> service) {
    std::cout << "[+] Requesting current composition mode..." << std::endl;
    
    // getComposition generates the enum synchronously 
    Return<IDisplayTopology::DisplayComposition> get_result = service->getComposition();
    
    if (!get_result.isOk()) {
        std::cerr << "[-] IPC transaction failed: " << get_result.description() << std::endl;
        return;
    }
    
    IDisplayTopology::DisplayComposition currentMode = get_result;
    std::cout << "[+] Current device composition mode: " << static_cast<int32_t>(currentMode) << std::endl;
}

void getBezelSize(sp<IDisplayTopology> service){
    std::cout << "[+] Getting Bezel Size..." << std::endl;
    Return<int32_t> bezelSize = service->getBezelSize();
    std::cout << "[+] getBezelSize returned: " << static_cast<int32_t>(bezelSize) << std::endl;
}

void getBezelDefaultSize(sp<IDisplayTopology> service){
    std::cout << "[+] Getting Default Bezel Size..." << std::endl;
    Return<int32_t> defaultBezelSize = service->getBezelDefaultSize();
    std::cout << "[+] getBezelDefaultSize returned: " << static_cast<int32_t>(defaultBezelSize) << std::endl;
}

void setBezelSize(sp<IDisplayTopology> service, int32_t size) {
    std::cout << "[+] Triggering setBezelSize with value: " << size << std::endl;
    
    // Because there is no generates clause, the return type is Return<void>
    Return<int32_t> result = service->setBezelSize(size);
    
    // Always check if the transport transaction succeeded
    if (!result.isOk()) {
        std::cerr << "[-] HwBinder IPC Transaction failed: " << result.description() << std::endl;
        return;
    }
    
    std::cout << "[+] setBezelSize returned: " << static_cast<int32_t>(result) << std::endl;
}

void getLayoutState(sp<IDisplayTopology> service){
    std::cout << "[+] Getting current layout state..." << std::endl;
    Return<IDisplayTopology::LayoutState> layoutState = service->getLayoutState();

    IDisplayTopology::LayoutState returnState = layoutState;
    std::cout << "[+] getLayoutState returned: " << static_cast<int32_t>(returnState) << std::endl;
}

void setLayoutState(sp<IDisplayTopology> service, int state) {
    std::cout << "[+] Setting Layout state with value: " << state << std::endl;

    IDisplayTopology::LayoutState testState = static_cast<IDisplayTopology::LayoutState>(state);

    service->setLayoutState(testState);
    
    std::cout << "[+] setLayoutState triggered" << std::endl;
}

void onRotation(sp<IDisplayTopology> service, int rotVal){
    // Cast the integer to your HIDL strongly-typed enum
    IDisplayTopology::RotationAngle rotAngle = static_cast<IDisplayTopology::RotationAngle>(rotVal);

    std::cout << "[+] setting Rot?: " << rotVal << std::endl;
    Return<void> rot = service->onRotation(rotAngle);
    
    std::cout << "[+] onRotation triggered" << std::endl;
}

void setExternalModeHint(sp<IDisplayTopology> service, int mode){
    std::cout << "[+] Setting External Mode Hint with value: " << mode << std::endl;

    IDisplayTopology::ExternalModeHint modeSet = static_cast<IDisplayTopology::ExternalModeHint>(mode);

    service->setExternalModeHint(modeSet);
    
    std::cout << "[+] setExternalModeHint triggered" << std::endl;
}

void getExternalModeHint(sp<IDisplayTopology> service){
    std::cout << "[+] Getting current External mode hint..." << std::endl;
    Return<IDisplayTopology::ExternalModeHint> returnVal = service->getExternalModeHint();

    IDisplayTopology::ExternalModeHint returnState = returnVal;
    std::cout << "[+] getExternalModeHint returned: " << static_cast<int32_t>(returnState) << std::endl;
}

int main(int argc, char** argv) {

    // We need at least argv[1] (the function string/int). 
    // If they want to write/set, they also need argv[2].
    if (argc < 2) {
        std::cout << "[-] Usage: ./display_topology <func_id> [int_val]" << std::endl;
        std::cout << "    func_id: 1 = setComposition, 2 = getComposition, 3 = getBezelSize";
        std::cout << "    4 = getBezelDefaultSize, 5 = setBezelSize, 6 = onRotation";
        std::cout << "    7 = setLayoutState, 8 = getLayoutState, 9 = setExternalModeHint" ;
        std::cout << "    10 = getExternalModeHint" << std::endl;
        return -1;
    }

    int funcInt = std::stoi(argv[1]);
    int intVal = 0;

    if (funcInt == 1 || funcInt == 5 || funcInt == 6 || funcInt == 7 || funcInt == 9) {
        if (argc < 3) {
            std::cerr << "[-] Error: setComposition requires a value argument (0-3).\n";
            return -1;
        }
        intVal = std::stoi(argv[2]);
    }
    
    std::cout << "[+] Connecting to DisplayTopology Service..." << std::endl;

    // 1. Fetch the default instance of the target HAL service
    // If the service has a specific instance name, pass it as an argument (e.g., "default")
    sp<IDisplayTopology> service = IDisplayTopology::getService();

    if (service == nullptr) {
        std::cerr << "[-] Failed to fetch the DisplayTopology service proxy." << std::endl;
        return -1;
    }
    std::cout << "[+] Successfully connected to the DisplayTopology service!" << std::endl;

    switch (funcInt) {
        case 1:
            setComposition(service, intVal);
            break;
        case 2:
            getComposition(service);
            break;
        case 3:
            getBezelSize(service);
            break;
        case 4: 
            getBezelDefaultSize(service);  
            break;
        case 5:
            setBezelSize(service, intVal);
            break;
        case 6:
            onRotation(service, intVal);
            break;
        case 7: 
            setLayoutState(service, intVal);
            break;
        case 8: 
            getLayoutState(service);
            break;
        case 9:
            setExternalModeHint(service, intVal);
            break;
        case 10:
            getExternalModeHint(service);
            break;
        default:
            std::cerr << "[-] Unknown function ID. Current range 1-10" << std::endl;
            break;
    }
    return 0;
}