#pragma once

#include "Messages/PhoneNumber.hpp"
#include <string>
#include <vector>
#include <map>
#include <optional>


namespace ue
{
    struct SmsMessage
    {
        enum class Direction { INCOMING, OUTGOING };
        enum class Status { RECEIVED_READ, RECEIVED_UNREAD, SENT, FAILED };

        common::PhoneNumber from;
        std::string text;
        bool isRead;
        Direction direction;
        Status status;

        SmsMessage(common::PhoneNumber from, std::string text)
            : text(text), direction(Direction::INCOMING), status(Status::RECEIVED_UNREAD)
        {}

        SmsMessage(common::PhoneNumber to, std::string text, Status initialStatus)
            : text(text), direction(Direction::OUTGOING), status(initialStatus)
        {}
    };

    class SmsRepository
    {
    public:
        SmsRepository() = default;

        std::size_t addReceivedSms(common::PhoneNumber from, const std::string& text);
        std::size_t addSentSms(common::PhoneNumber to, const std::string& text, SmsMessage::Status initialStatus = SmsMessage::Status::SENT);
        std::size_t addSms(common::PhoneNumber from, const std::string& text);

        const std::vector<SmsMessage>& getAllSms() const;
        std::size_t getUnreadCount() const;


        bool markAsRead(std::size_t index);
        bool markLastOutgoingSmsAsFailed();


    private:
        std::vector<SmsMessage> messages;
        std::optional<std::size_t> lastSentSmsIndex;
    };

}
