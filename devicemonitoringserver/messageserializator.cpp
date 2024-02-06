
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
    stream << MessageType::Error << ' ' << message.errorType;
    return stream.str();
}


struct MeterageMessage MessageSerializator::deserializeMeterage(const std::string& data){
    std::istringstream stream(data);
    MeterageMessage meterage;
    stream >> meterage.value >> meterage.timestamp;
    return meterage;

}

struct CommandMessage MessageSerializator::deserializeCommand(const std::string& data){
    std::istringstream stream(data);
    CommandMessage command;
    stream >> command.correction;
    return command;

}



