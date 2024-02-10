#include "test_runner.h"
#include "tests.h"
#include <servermock/taskqueue.h>
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "deviceworkschedule.h"
#include "messageserializator.h"
#include <variant>
#include <chrono>

int main()
{
//    TestRunner tr;
//    RUN_TEST(tr, taskQueueTest);
//    RUN_TEST(tr, safeObjectPointerTest);
//    RUN_TEST(tr, connectionChannelTest);
//    RUN_TEST(tr, clientServerTest);
//
// TODO: собственные тесты
//    RUN_TEST(tr, monitoringServerTest1);
//    return 0;
TaskQueue taskQueue;
// Создаем клиента и сервер
AbstractClientConnection* client = new ClientConnectionMock(taskQueue);
AbstractConnectionServer* server = new ConnectionServerMock(taskQueue);
DeviceMock device(client);
DeviceMonitoringServer servers(server);

// Даем индентификатор клиенту и просулшиваемый индентификатор серверу
device.bind(13);
servers.listen(5);

// Запрашиваем подключение к серверу
bool conn = 0;
conn = device.connectToServer(5);
//std::cout << conn << std::endl;

//struct Phase phas;


struct DeviceWorkSchedule sched;

sched.deviceId = 13;
//sched.schedule.push_back(phas);
//sched.schedule.push_back(phas1);

// Создаем вектор для тестового сообщений
std::vector<uint8_t> testMeterages = {3, 5, 6, 7, 9};

// Отправляем тестовый список измерений

servers.setDeviceWorkSchedule(sched);
device.setMeterages(testMeterages);
while (taskQueue.processTask())
    device.startMeterageSending();



return 0;
}
