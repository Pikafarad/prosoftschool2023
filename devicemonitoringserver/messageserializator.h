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
    // Перегрузка для модуля сериализации
    std::string serialize(const MeterageMessage& message);
    std::string serialize(const CommandMessage& message);
    std::string serialize(const ErrorMessage& message);

    // Перегрузка для модуля сериализации
    void deserialize(const std::string& data, MessageType& type, MeterageMessage& message);
    void deserialize(const std::string& data, MessageType& type, CommandMessage& message);
    void deserialize(const std::string& data, MessageType& type, ErrorMessage& message);
};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
