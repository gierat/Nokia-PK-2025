#pragma once

#include "IEventsHandler.hpp"
#include <gmock/gmock.h>
#include <optional>

namespace ue
{

    class IEventsHandlerMock : public IEventsHandler
    {
    public:
        MOCK_METHOD(void, handleSib, (common::BtsId), (override));
        MOCK_METHOD(void, handleAttachAccept, (), (override));
        MOCK_METHOD(void, handleAttachReject, (), (override));
        MOCK_METHOD(void, handleDisconnected, (), (override));
        MOCK_METHOD(void, handleSmsReceived, (common::PhoneNumber from, std::string text), (override));
        MOCK_METHOD(void, handleSmsSentResult, (common::PhoneNumber to, bool success), (override));
        MOCK_METHOD(void, handleSmsComposeResult, (common::PhoneNumber recipient, const std::string &text), (override));
        MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber from), (override));
        MOCK_METHOD(void, handleCallDropped, (common::PhoneNumber peer), (override));
        MOCK_METHOD(void, handleCallAccept, (common::PhoneNumber), (override));
        MOCK_METHOD(void, handleCallReject, (common::PhoneNumber from), (override));
        MOCK_METHOD(void, handleUnknownRecipient, (common::PhoneNumber), (override));
        MOCK_METHOD(void, handleCallTalk, (common::PhoneNumber from, const std::string &text), (override));

        MOCK_METHOD(void, handleTimeout, (), (override));


        MOCK_METHOD(void, handleUiAction, (std::optional<std::size_t> selectedIndex), (override));
        MOCK_METHOD(void, handleUiBack, (), (override));
    };

}