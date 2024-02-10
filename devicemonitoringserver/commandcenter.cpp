#include "commandcenter.h"



void CommandCenter::setWorkSchedule(const DeviceWorkSchedule* schedul){
    planes[schedul->deviceId] = schedul->schedule;
    if(planes[schedul->deviceId].size() == 0)
        bitError = true;

}

std::string CommandCenter::processingMeterage(const std::string meterage, uint64_t deviceID){


    if(bitError == true)
    {
        struct ErrorMessage tip{ErrorMessage::NoSchedule};
        return MessageSerializator::serialize(tip);
    }

    std::istringstream stream(meterage);
    MeterageMessage meterageStruct = MessageSerializator::deserializeMeterage(meterage);
    if(meterageStruct.timestamp == planes[deviceID][0].timeStamp)
    {
        plansValue[deviceID] = planes[deviceID][0].value;
        planes[deviceID].erase( planes[deviceID].begin());
    }else if(meterageStruct.timestamp < planes[deviceID][0].timeStamp)
    {
        struct ErrorMessage tip{ErrorMessage::NoTimestamp};
        return MessageSerializator::serialize(tip);
    }else if (meterageStruct.timestamp <= pastTime[deviceID])
    {
        struct ErrorMessage tip{ErrorMessage::Obsolete};
        return MessageSerializator::serialize(tip);
    }
    int64_t value = static_cast<int64_t>(plansValue[deviceID]) - static_cast<int64_t>(meterageStruct.value);

    const struct CommandMessage Commande{value};
    std::string get = MessageSerializator::serialize(Commande);

    //debug
    struct CommandMessage h = MessageSerializator::deserializeCommand(get);
    std::cout << static_cast<int>(h.correction) << std::endl;

    pastTime[deviceID] = meterageStruct.timestamp;
    return get;
}
