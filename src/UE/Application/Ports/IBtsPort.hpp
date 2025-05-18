#pragma once

#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"


namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleDisconnected() = 0;
    virtual void handleSmsReceived(common::PhoneNumber, std::string) = 0;
    virtual void handleSmsSentResult(common::PhoneNumber to, bool success) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendSms(common::PhoneNumber to, const std::string& text) = 0;
};

}
