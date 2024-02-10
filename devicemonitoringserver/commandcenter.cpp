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
        plansValue[deviceID].value = planes[deviceID][0].value;
        plansValue[deviceID].timeStamp = planes[deviceID][0].timeStamp;
        planes[deviceID].erase( planes[deviceID].begin());
    }else if(!plansValue[deviceID].timeStamp)
    {
        struct ErrorMessage tip{ErrorMessage::NoTimestamp};
        return MessageSerializator::serialize(tip);
    }else if (meterageStruct.timestamp <= pastTime[deviceID])
    {
        struct ErrorMessage tip{ErrorMessage::Obsolete};
        return MessageSerializator::serialize(tip);
    }
    int64_t value = static_cast<int64_t>(plansValue[deviceID].value) - static_cast<int64_t>(meterageStruct.value);
    //Запись в storageSKO
    storageSKO[deviceID][plansValue[deviceID].value].push_back(value);

    const struct CommandMessage Commande{value};
    std::string get = MessageSerializator::serialize(Commande);

    pastTime[deviceID] = meterageStruct.timestamp;
    return get;
}
