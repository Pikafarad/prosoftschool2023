#include <iostream>
#include <sstream>
#include <messageserializator.h>
// Типы сообщений



std::string MessageSerializator::serialize(MessageType type, const void *message) {
    std::ostringstream stream;
    stream << static_cast<int>(type) << ' ';

    switch (type) {
        case Meterage:
            serializeMeterage(stream, *static_cast<const MeterageMessage*>(message));
            break;
        case Command:
            serializeCommand(stream, *static_cast<const CommandMessage*>(message));
            break;
        case Error:
            serializeError(stream, *static_cast<const ErrorMessage*>(message));
            break;
    }

    return stream.str();
}