#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "deviceworkschedule.h"
#include <messageserializator.h>
#include <map>

class CommandCenter {
public:
    // Задать план работы
    void setWorkSchedule(const DeviceWorkSchedule* schedul);

    // Сравнение измерений
    std::string processingMeterage(std::string meterage, uint64_t deviceID);

private:
    std::map<uint64_t, std::vector<Phase>> planes;
};

#endif // COMMANDCENTER_H
