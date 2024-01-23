#ifndef DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
#define DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H

#include "common.h"
#include <string>
#include <variant>
#include <iostream>
#include <sstream>

enum MessageType {
    Meterage,
    Command,
    Error
};

// Структура сообщения с измерением
struct MeterageMessage {
    int64_t value;
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
    static std::string serialize(const MeterageMessage& message);
    static std::string serialize(const CommandMessage& message);
    static std::string serialize(const ErrorMessage& message);

    // Перегрузка для модуля десериализации
    static std::variant<struct MeterageMessage, struct CommandMessage,struct ErrorMessage> deserialize(const std::string& data);

};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
