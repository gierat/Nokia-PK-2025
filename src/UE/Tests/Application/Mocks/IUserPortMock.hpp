#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"
#include "Application/SmsRepository.hpp"
#include <vector>
#include <string>
namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showNewSms, (), (override));

    MOCK_METHOD(void, showSmsList, (const std::vector<SmsMessage>& messages), (override));
    MOCK_METHOD(void, showSmsView, (const SmsMessage& message), (override));
    MOCK_METHOD(void, showAlert, (const std::string& title, const std::string& message), (override));

};

}
