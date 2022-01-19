#include "include/loadCommand.h"

/*список команд для keyboardEmulator*/
const std::map<std::string,std::string> loadCommand (){
    return  std:: map<std::string, std::string>  {
        {"VolUp", "XF86AudioRaiseVolume"},
        {"VolDown", "XF86AudioLowerVolume"},
        {"FullScreen", "f"},
        {"RL", "Left"},
        {"RR", "Right"},
        {"Play", "XF86AudioPlay"},
        {"Next", "Shift_L+n"},
        {"Mute", "XF86AudioMute"}
       
};


}