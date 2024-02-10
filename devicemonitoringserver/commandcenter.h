#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "deviceworkschedule.h"
#include <messageserializator.h>
#include <map>

/*!
 * \brief Класс командного центра.
 */
class CommandCenter {
public:
    /*!
     * \brief Задать план работы.
     * \param schedul - План работы устройства
     */
    void setWorkSchedule(const DeviceWorkSchedule* schedul);
    /*!
     * \brief Обработка измерения командным центром.
     * \param meterage - Сообщение с измерением
     * \param deviceID - Идентификатор устройства
     */
    std::string processingMeterage(std::string meterage, uint64_t deviceID);
private:
    std::map<uint64_t, std::vector<Phase>> planes; ///< Этапы плана
    std::map<uint64_t, Phase> plansValue; ///< Этап плана для данной метки времени
    std::map<uint64_t, uint64_t> pastTime; ///< Метка времени на прошлом измерении
    std::map<uint64_t, std::map<uint64_t, std::vector<int64_t>>> storageSKO; ///< Хранение СКО для данной ID
    bool bitError = false; ///< Бит ошибки, если не задан план
};

#endif // COMMANDCENTER_H
