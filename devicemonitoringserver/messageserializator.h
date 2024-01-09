#ifndef DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
#define DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H

#include "common.h"
#include <string>

enum MessageType {
    Meterage,
    Command,
    Error
};

// Структура сообщения с измерением
struct MeterageMessage {
    uint8_t value;
    uint64_t timestamp;
};

// Структура сообщения с командой управления
struct CommandMessage {
    double correction;
};

// Структура сообщения со статусом ошибки
struct ErrorMessage {
    std::string errorType;
};

// Структуры сообщений
class MessageSerializator{
public:
    std::string serialize(MessageType type, const void* message);
    void deserialize(const std::string& data, MessageType& type, void* message);
private:
};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
