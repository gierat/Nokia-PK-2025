#include "ComposingSmsState.hpp"
#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "Messages/PhoneNumber.hpp"


namespace ue
{

    ComposingSmsState::ComposingSmsState(Context &context)
        : BaseState(context, "ComposingSmsState")
    {
        logger.logInfo("Entering SMS Composition");
        context.user.showSmsCompose();
    }

    void ComposingSmsState::handleUiAction(std::optional<std::size_t> selectedIndex)
    {
        logger.logInfo("Sending SMS initiated");

        auto recipient = context.user.getSmsRecipient();
        auto text = context.user.getSmsText();

        if (!recipient.isValid() || text.empty()) {
            logger.logInfo("Cannot send SMS: Invalid recipient or empty text");
            context.user.showAlert("Error", "Invalid recipient or empty text");
            return;
        }

        context.smsRepository.addSentSms(recipient, text, SmsMessage::Status::SENT);
        context.bts.sendSms(recipient, text);
        logger.logInfo("SMS sending to: ", recipient);

        context.setState<ConnectedState>();
    }

    void ComposingSmsState::handleUiBack()
    {
        logger.logInfo("SMS composition cancelled by user");
        context.setState<ConnectedState>();
    }

    void ComposingSmsState::handleDisconnected()
    {
        logger.logInfo("Disconnected while composing SMS");
        context.user.showAlert("Disconnected", "Connection lost during SMS composition.");
        context.setState<NotConnectedState>();
    }

    void ComposingSmsState::handleSmsReceived(common::PhoneNumber from, std::string text)
    {
        logger.logInfo("SMS received from ", from, " while composing - adding to inbox");
        context.smsRepository.addReceivedSms(from, text);
        context.user.showNewSms();
    }

    void ComposingSmsState::handleSmsSentResult(common::PhoneNumber to, bool success)
    {
        logger.logInfo("SMS send result for ", to, " received while composing - ignoring");
    }

}