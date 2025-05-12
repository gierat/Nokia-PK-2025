#include "ViewingSmsListState.hpp"
#include "ViewingSingleSmsState.hpp"
#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{
    ViewingSmsListState::ViewingSmsListState(Context &context)
        : BaseState(context, "ViewingSmsListState")
    {
        showList();
    }

    void ViewingSmsListState::showList()
    {
        currentSmsList = context.smsRepository.getAllSms();
        if (currentSmsList.empty())
        {
            logger.logInfo("SMS list is empty.");
            context.user.showAlert("SMS Inbox", "No messages.");
            context.setState<ConnectedState>();
        }
        else
        {
            context.user.showSmsList(currentSmsList);
        }
    }

    void ViewingSmsListState::handleUiAction(std::optional<std::size_t> selectedIndex)
    {
        if (!selectedIndex.has_value())
        {
            logger.logInfo("UI Action received with no index in SMS List");
            return;
        }

        std::size_t index = selectedIndex.value();
        if (index < currentSmsList.size())
        {
            logger.logInfo("SMS selected at index: ", index);
            context.setState<ViewingSingleSmsState>(index);
        }
        else
        {
            logger.logError("Selected index out of bounds: ", index, " (List size: ", currentSmsList.size(), ")");
        }
    }

    void ViewingSmsListState::handleUiBack()
    {
        logger.logInfo("Back action from SMS List view.");
        context.setState<ConnectedState>();
    }

    void ViewingSmsListState::handleDisconnectedFromBts()
    {
        logger.logInfo("Connection lost while viewing SMS list.");
        context.setState<NotConnectedState>();
    }

    void ViewingSmsListState::handleSmsReceived(common::PhoneNumber from, std::string text)
    {
        logger.logInfo("SMS received while viewing list (from: ", from, ")");
        std::size_t smsIndex = context.smsRepository.addSms(from, text);
        logger.logDebug("SMS stored at index: ", smsIndex);
        context.user.showNewSms();
        showList();
    }
}