#include "commandcenter.h"

void CommandCenter::setWorkSchedule(const DeviceWorkSchedule* schedul){
    planes[schedul->deviceId] = schedul->schedule;
}

std::string CommandCenter::processingMeterage(std::string meterage, uint64_t deviceID){

    uint8_t plans = 0;
    uint8_t value = 0;

    struct MeterageMessage a;
    std::istringstream stream(meterage);
    int type = 0;
    stream >> type;
    switch (type) {
        case 0: {
            MeterageMessage meterage;
            stream >> meterage.value >> meterage.timestamp;
            for(size_t i = 0; i < planes[deviceID].size(); i++ )
            {
                if(meterage.timestamp >= planes[deviceID][i].timeStamp)
                {
                    plans = planes[deviceID][i].value;
                    value = plans - meterage.value;
                }

            }
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
    for (char c : get) {
        std::cout << static_cast<int>(c) << " ";
}
    return get;
}
