#include <iostream>
#include <sstream>
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

void MessageSerializator::deserialize(const std::string& data) {
    switch (data.) {

}
    std::istringstream stream(data);
    stream >> message.value >> message.timestamp;
}

}



