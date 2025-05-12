#include "SmsRepository.hpp"

namespace ue
{

    std::size_t SmsRepository::addSms(common::PhoneNumber from, const std::string& text)
    {
        messages.emplace_back(from, text, false);
        return messages.size() - 1;
    }

    const std::vector<SmsMessage>& SmsRepository::getAllSms() const
    {
        return messages;
    }

    std::size_t SmsRepository::getUnreadCount() const
    {
        std::size_t count = 0;
        for (const auto& message : messages)
        {
            if (!message.isRead)
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

        messages[index].isRead = true;
        return true;
    }

}
