#include "commandcenter.h"



void CommandCenter::setWorkSchedule(const DeviceWorkSchedule* schedul){
    planes[schedul->deviceId] = schedul->schedule;
}

std::string CommandCenter::processingMeterage(const std::string meterage, uint64_t deviceID){

    uint8_t plans = 0;
    int64_t value = 0;

    std::istringstream stream(meterage);
    int type = 0;
    stream >> type;
    switch (type) {
        case 0:
        {

            MeterageMessage meterageStruct = MessageSerializator::deserializeMeterage(meterage);
            if(meterageStruct.timestamp == planes[deviceID][0].timeStamp)
            {
                plansValue[deviceID] = planes[deviceID][0].value;
                planes[deviceID].erase( planes[deviceID].begin());
            }
            value = static_cast<int64_t>(plansValue[deviceID]) - static_cast<int64_t>(meterageStruct.value);
        }
        case 1: {
            CommandMessage command;
            stream >> command.correction;
        }
        case 2: {
            ErrorMessage error;
            stream >> error.errorType;

        }
        // Вы можете выбрать, какой тип возвращать по умолчанию, в данном случае возвращаю MeterageMessage в std::variant
        default: {
            MeterageMessage defaultMeterage;

        }
    }

    const struct CommandMessage Commande{value};
    std::string get = MessageSerializator::serialize(Commande);

    //debug
    struct CommandMessage h = MessageSerializator::deserializeCommand(get);
    std::cout << static_cast<int>(h.correction) << std::endl;

    return get;
}
