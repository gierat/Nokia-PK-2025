#include "SmsRepository.hpp"

namespace ue
{

    std::size_t SmsRepository::addReceivedSms(common::PhoneNumber from, const std::string &text)
    {
        messages.emplace_back(from, text);
        return messages.size() - 1;
    }

    std::size_t SmsRepository::addSentSms(common::PhoneNumber to, const std::string &text, SmsMessage::Status initialStatus)
    {
        messages.emplace_back(to, text, initialStatus);
        lastSentSmsIndex = messages.size() - 1;       
        return messages.size() - 1;
    }

    const std::vector<SmsMessage> &SmsRepository::getAllSms() const
    {
        return messages;
    }

    std::size_t SmsRepository::getUnreadCount() const
    {
        std::size_t count = 0;
        for (const auto &message : messages)
        {
            if (message.direction == SmsMessage::Direction::INCOMING && message.status == SmsMessage::Status::RECEIVED_UNREAD)
            {
                count++;
            }
        }
        return count;
    }

    bool SmsRepository::markAsRead(std::size_t index)
    {
        if (index >= messages.size())
        {
            return false;
        }

        if (messages[index].direction == SmsMessage::Direction::INCOMING && messages[index].status == SmsMessage::Status::RECEIVED_UNREAD)
        {
            messages[index].status = SmsMessage::Status::RECEIVED_READ;
            return true;
        }
        return false;
    }

    bool SmsRepository::markLastOutgoingSmsAsFailed()
    {
        if (lastSentSmsIndex.has_value() && lastSentSmsIndex.value() < messages.size())
        {
            auto &msg = messages[lastSentSmsIndex.value()];
            if (msg.direction == SmsMessage::Direction::OUTGOING)
            {
                msg.status = SmsMessage::Status::FAILED;
                lastSentSmsIndex.reset();
                return true;
            }
        }
        for (int i = messages.size() - 1; i >= 0; --i)
        {
            if (messages[i].direction == SmsMessage::Direction::OUTGOING && messages[i].status == SmsMessage::Status::SENT)
            {
                messages[i].status = SmsMessage::Status::FAILED;
                return true;
            }
        }
        return false;
    }


}
