#include "ViewingSingleSmsState.hpp"
#include "ViewingSmsListState.hpp"
#include "NotConnectedState.hpp"
#include <stdexcept>

namespace ue
{

    ViewingSingleSmsState::ViewingSingleSmsState(Context &context, std::size_t smsIndex)
        : BaseState(context, "ViewingSingleSmsState"),
          viewingSmsIndex(smsIndex)
    {
        const auto &allSms = context.smsRepository.getAllSms();
        if (viewingSmsIndex >= allSms.size())
        {
            logger.logError("Invalid SMS index provided: ", viewingSmsIndex);
            context.setState<ViewingSmsListState>();
            return;
        }

        const SmsMessage &message = allSms[viewingSmsIndex];
        logger.logInfo("Viewing SMS at index: ", viewingSmsIndex, ", From: ", message.from);

        if (!message.isRead)
        {
            logger.logDebug("Marking SMS as read: index ", viewingSmsIndex);
            context.smsRepository.markAsRead(viewingSmsIndex);
        }

        context.user.showSmsView(message);
    }

    void ViewingSingleSmsState::handleUiBack()
    {
        logger.logInfo("Back action from single SMS view.");
        context.setState<ViewingSmsListState>();
    }

    void ViewingSingleSmsState::handleDisconnectedFromBts()
    {
        logger.logInfo("Connection lost while viewing single SMS.");
        context.setState<NotConnectedState>();
    }

    void ViewingSingleSmsState::handleSmsReceived(common::PhoneNumber from, std::string text)
    {
        logger.logInfo("SMS received while viewing another SMS (from: ", from, ")");
        std::size_t smsIndex = context.smsRepository.addSms(from, text);
        logger.logDebug("SMS stored at index: ", smsIndex);
        context.user.showNewSms();
    }

}