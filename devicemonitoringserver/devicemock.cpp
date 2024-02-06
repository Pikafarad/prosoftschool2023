#include "devicemock.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <server/abstractclientconnection.h>

DeviceMock::DeviceMock(AbstractClientConnection* clientConnection) :
    m_clientConnection(clientConnection)
{
    struct ConnectedHandler : public AbstractAction
    {
    public:
        ConnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onConnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setConnectedHandler(new ConnectedHandler(this));

    struct DisconnectedHandler : public AbstractAction
    {
    public:
        DisconnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onDisconnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setDisconnectedHandler(new DisconnectedHandler(this));

    struct MessageHandler : public AbstractMessageHandler
    {
        MessageHandler(DeviceMock* client) :
            m_client(client) {}

    private:
        void operator()(const std::string& message) final
        {
            m_client->onMessageReceived(message);
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setMessageHandler(new MessageHandler(this));
}

DeviceMock::~DeviceMock()
{
    delete m_clientConnection;
}

bool DeviceMock::bind(uint64_t deviceId)
{
    return m_clientConnection->bind(deviceId);
}

bool DeviceMock::connectToServer(uint64_t serverId)
{
    return m_clientConnection->connectToHost(serverId);
}

void DeviceMock::sendMessage(const std::string& message) const
{
    m_clientConnection->sendMessage(message);
}

void DeviceMock::onMessageReceived(const std::string& messeg)
{
    // TODO: Разобрать std::string, прочитать команду,
    // записать ее в список полученных комманд
    struct MeterageMessage a;
    struct CommandMessage b;
    std::istringstream stream(messeg);
    int type = 0;
    stream >> type;
    switch (type) {
        case 0: {
                a = MessageSerializator::deserializeMeterage(messeg);
        }
        case 1: {
            CommandMessage command;
            b = MessageSerializator::deserializeCommand(messeg);



        }
        case 2: {
            ErrorMessage error;
            stream >> error.errorType;

        }
        // Вы можете выбрать, какой тип возвращать по умолчанию, в данном случае возвращаю MeterageMessage в std::variant
        default: {
            MeterageMessage defaultMeterage;

        }
    }
    sendNextMeterage(); // Отправляем следующее измерение
}

void DeviceMock::onConnected()
{
    // TODO, если нужно
}

void DeviceMock::onDisconnected()
{
    // TODO, если нужно
}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
}

void DeviceMock::startMeterageSending()
{
    sendNextMeterage();
}

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size())
        return;
    const auto meterage = m_meterages.at(m_timeStamp);
    (void)meterage;
    ++m_timeStamp;
    // TODO: Сформировать std::string и передать в sendMessage
    const struct MeterageMessage Meterage{meterage, m_timeStamp};
    const std::string message = MessageSerializator::serialize(Meterage);
    sendMessage(message);
}
