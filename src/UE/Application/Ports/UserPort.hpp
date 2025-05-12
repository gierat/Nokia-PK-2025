#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include <vector>
#include "SmsRepository.hpp"
#include "IEventsHandler.hpp"
#include <optional>

namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showNewSms() override;

    void showSmsList(const std::vector<SmsMessage>& messages);
    void showSmsView(const SmsMessage& message);
    void showAlert(const std::string& title, const std::string& message);

private:
    void acceptCallback();
    void rejectCallback();

    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IEventsHandler* handler = nullptr;
    details::GuiViewMode currentViewMode = details::VIEW_MODE_UNKNOWN;

};

}
