#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "ViewingSmsListState.hpp"
#include <vector>

namespace ue {
    ConnectedState::ConnectedState(Context &context)
        : BaseState(context, "ConnectedState") {
        context.user.showConnected();
    }

    void ConnectedState::showMainMenu() {
        logger.logInfo("Entering Main Menu");
        context.user.showConnected();
    }


    void ConnectedState::handleSmsReceived(common::PhoneNumber from, std::string text) {
        logger.logInfo("SMS received from: ", from);
        std::size_t smsIndex = context.smsRepository.addSms(from, text);
        logger.logDebug("SMS stored at index: ", smsIndex);
        context.user.showNewSms();
    }

    void ConnectedState::handleUiAction(std::optional<std::size_t> selectedIndex) {
        if (!selectedIndex.has_value()) {
            logger.logInfo("UI Action received with no index in Main Menu");
            return;
        }

        std::size_t index = selectedIndex.value();
        logger.logInfo("Main menu action selected: index ", index);


        if (index == 0) {
            logger.logInfo("Compose SMS action selected - (Not Implemented Yet)");
        } else if (index == 1) {
            logger.logInfo("View SMS action selected");
            context.setState<ViewingSmsListState>();
        } else {
            logger.logInfo("Unknown main menu index selected: ", index);
        }
    }

    void ConnectedState::handleUiBack() {
        logger.logInfo("Back action in main menu - ignored");
    }

    void ConnectedState::handleDisconnectedFromBts() {
        context.user.showNotConnected();
        context.setState<NotConnectedState>();
    }
}
