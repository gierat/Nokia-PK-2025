#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include <memory>

namespace ue
{
using namespace ::testing;

class ApplicationTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsPortMock> btsPortMock;
    StrictMock<IUserPortMock> userPortMock;
    StrictMock<ITimerPortMock> timerPortMock;

    std::unique_ptr<Application> applicationPtr;

    void SetUp() override {
        EXPECT_CALL(userPortMock, showNotConnected());
    }

    void createApplication() {
        applicationPtr = std::make_unique<Application>(PHONE_NUMBER,
                                      loggerMock,
                                      btsPortMock,
                                      userPortMock,
                                      timerPortMock);
    }


    void verifyShowNotConnectedOnStart() {
        Mock::VerifyAndClearExpectations(&userPortMock);
    }
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{};

TEST_F(ApplicationTestSuite, UeShallAttachToBtsAfterReceivingSib)
{
    createApplication();
    verifyShowNotConnectedOnStart();

    common::BtsId btsId{42};

    EXPECT_CALL(btsPortMock, sendAttachRequest(btsId));
    EXPECT_CALL(timerPortMock, startTimer(std::chrono::milliseconds{500}));
    applicationPtr->handleSib(btsId);

    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showConnected());
    applicationPtr->handleAttachAccept();
}

TEST_F(ApplicationTestSuite, UeShallHandleAttachmentRejection)
{
    createApplication();
    verifyShowNotConnectedOnStart();

    common::BtsId btsId{42};

    EXPECT_CALL(btsPortMock, sendAttachRequest(btsId));
    EXPECT_CALL(timerPortMock, startTimer(std::chrono::milliseconds{500}));
    applicationPtr->handleSib(btsId);

    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showNotConnected());
    applicationPtr->handleAttachReject();
}

TEST_F(ApplicationTestSuite, UeShallHandleAttachmentTimeout)
{
    createApplication();
    verifyShowNotConnectedOnStart();

    common::BtsId btsId{42};

    EXPECT_CALL(btsPortMock, sendAttachRequest(btsId));
    EXPECT_CALL(timerPortMock, startTimer(std::chrono::milliseconds{500}));
    applicationPtr->handleSib(btsId);

    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showNotConnected());
    applicationPtr->handleTimeout();
}

TEST_F(ApplicationTestSuite, UeShallHandleDisconnection)
{
    createApplication();
    verifyShowNotConnectedOnStart();

    common::BtsId btsId{42};
    EXPECT_CALL(btsPortMock, sendAttachRequest(btsId));
    EXPECT_CALL(timerPortMock, startTimer(std::chrono::milliseconds{500}));
    applicationPtr->handleSib(btsId);

    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showConnected());
    applicationPtr->handleAttachAccept();

    EXPECT_CALL(userPortMock, showNotConnected());
    applicationPtr->handleDisconnected();
}

};
