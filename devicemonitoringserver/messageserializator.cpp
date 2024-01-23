
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

std::variant<struct MeterageMessage, struct CommandMessage,struct ErrorMessage> MessageSerializator::deserialize(const std::string& data) {
    std::istringstream stream(data);
    int type = 0;
    stream >> type;
    switch (type)
    {
    case 0:
        struct MeterageMessage Meterage;
        stream  >>  Meterage.value >> Meterage.timestamp;
        return Meterage;
        break;
    case 1:
        struct CommandMessage Command;
        stream  >>  Command.correction;
        return Command;
        break;
    case 2:
        struct ErrorMessage Error;
        stream  >>  Error.errorType;
        return Error;
        break;


    }


}



