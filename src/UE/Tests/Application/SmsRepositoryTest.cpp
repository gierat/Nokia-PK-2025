#include <gtest/gtest.h>
#include "Messages/PhoneNumber.hpp"
#include "Application/SmsRepository.hpp"

namespace ue
{

    class SmsRepositoryTest : public ::testing::Test
    {
    protected:
        SmsRepository smsRepository;
        common::PhoneNumber testSender{100};
        std::string testMessage1 = "Hello, this is a test SMS";
        std::string testMessage2 = "Another test message";
    };

    TEST_F(SmsRepositoryTest, shouldStoreNewSms)
    {
        std::size_t index = smsRepository.addReceivedSms(testSender, testMessage1);
        ASSERT_EQ(0u, index);
        ASSERT_EQ(1u, smsRepository.getAllSms().size());
        ASSERT_EQ(testSender, smsRepository.getAllSms()[0].peer);
        ASSERT_EQ(testMessage1, smsRepository.getAllSms()[0].text);
        ASSERT_EQ(SmsMessage::Status::RECEIVED_UNREAD, smsRepository.getAllSms()[0].status);
    }

    TEST_F(SmsRepositoryTest, shouldCountUnreadSms)
    {
        smsRepository.addReceivedSms(testSender, testMessage1);
        ASSERT_EQ(1u, smsRepository.getUnreadCount());

        smsRepository.addReceivedSms(testSender, testMessage2);
        ASSERT_EQ(2u, smsRepository.getUnreadCount());

        smsRepository.markAsRead(0);
        ASSERT_EQ(1u, smsRepository.getUnreadCount());

        smsRepository.markAsRead(1);
        ASSERT_EQ(0u, smsRepository.getUnreadCount());
    }

    TEST_F(SmsRepositoryTest, shouldMarkSmsAsRead)
    {
        smsRepository.addReceivedSms(testSender, testMessage1);
        ASSERT_EQ(SmsMessage::Status::RECEIVED_UNREAD, smsRepository.getAllSms()[0].status);

        bool result = smsRepository.markAsRead(0);
        ASSERT_TRUE(result);
        ASSERT_EQ(SmsMessage::Status::RECEIVED_READ, smsRepository.getAllSms()[0].status);

        result = smsRepository.markAsRead(1);
        ASSERT_FALSE(result);
    }

}