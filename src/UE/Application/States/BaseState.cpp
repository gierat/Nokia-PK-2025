#include "BaseState.hpp"

namespace ue {
    BaseState::BaseState(Context &context, const std::string &name)
        : context(context),
          logger(context.logger, "[" + name + "]") {
        logger.logDebug("entry");
    }

    BaseState::~BaseState() {
        logger.logDebug("exit");
    }

    void BaseState::handleTimeout() {
        logger.logError("Uexpected: handleTimeout");
    }

    void BaseState::handleSib(common::BtsId btsId) {
        logger.logError("Uexpected: handleSib: ", btsId);
    }

    void BaseState::handleAttachAccept() {
        logger.logError("Uexpected: handleAttachAccept");
    }

    void BaseState::handleAttachReject() {
        logger.logError("Uexpected: handleAttachReject");
    }

    void BaseState::handleDisconnected() {
        logger.logError("Unexpected: handleDisconnectedFromBts");
    }

    void BaseState::handleSmsReceived(common::PhoneNumber from, std::string text) {
        logger.logError("Uexpected: handleSmsReceived from: ", from, " text: ", text);
    }

    void BaseState::handleSmsSentResult(common::PhoneNumber to, bool success)
    {
        logger.logError("Unexpected: handleSmsSentResult for: ", to, ", Success: ", success);
    }

    void BaseState::handleSmsComposeResult(common::PhoneNumber recipient, const std::string &text)
    {
        logger.logError("Unexpected: handleSmsComposeResult for: ", recipient, ", text: ", text);
    }

    void BaseState::handleUiAction(std::optional<std::size_t> selectedIndex) {
        std::string indexStr = selectedIndex.has_value() ? std::to_string(selectedIndex.value()) : "none";
        logger.logError("Unexpected: handleUiAction, index: ", indexStr);
    }

    void BaseState::handleUiBack() {
        logger.logError("Unexpected: handleUiBack");
    }
}
