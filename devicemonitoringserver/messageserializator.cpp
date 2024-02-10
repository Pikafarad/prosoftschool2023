
#include <messageserializator.h>

// Типы сообщений




std::string MessageSerializator::serialize(const MeterageMessage& message) {
    std::ostringstream stream;
    stream << MessageType::Meterage << ' ' << message.value << ' ' << message.timestamp;
    return stream.str();
}

std::string MessageSerializator::serialize(const CommandMessage& message) {
    std::ostringstream stream;
    stream << MessageType::Command << ' ' << message.correction;
    return stream.str();
}

std::string MessageSerializator::serialize(const ErrorMessage& message) {
    std::ostringstream stream;
    stream << MessageType::Error << ' ';

    switch (message.type) {
        case ErrorMessage::NoSchedule:
            stream << 0;
            break;
        case ErrorMessage::NoTimestamp:
            stream << 1;
            break;
        case ErrorMessage::Obsolete:
            stream << 2;
            break;
        default:
            // Обработка неизвестного типа ошибки
            break;
    }

    return stream.str();
}


struct MeterageMessage MessageSerializator::deserializeMeterage(const std::string& data){
    std::istringstream stream(data);
    MeterageMessage meterage;
    int type = 0;
    stream >> type >> meterage.value >> meterage.timestamp;
    return meterage;

}

struct CommandMessage MessageSerializator::deserializeCommand(const std::string& data){
    std::istringstream stream(data);
    CommandMessage command;
    int type = 0;
    stream >> type >> command.correction;
    return command;

}

struct ErrorMessage MessageSerializator::deserializeError(const std::string &data){
    std::istringstream stream(data);
    ErrorMessage err;
    int type = 0;
    int typeError = 0;
    stream >> type >> typeError;
    err.type = static_cast<ErrorMessage::errorType>(typeError);
    return err;

}



