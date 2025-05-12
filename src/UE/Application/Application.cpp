#include "Application.hpp"
#include "States/NotConnectedState.hpp"
#include "States/ConnectedState.hpp"


namespace ue {
    Application::Application(common::PhoneNumber phoneNumber,
                             common::ILogger &iLogger,
                             IBtsPort &bts,
                             IUserPort &user,
                             ITimerPort &timer)
        : context{iLogger, bts, user, timer},
          logger(iLogger, "[APP] ") {
        logger.logInfo("Started");
        context.setState<NotConnectedState>();
    }

    Application::~Application() {
        logger.logInfo("Stopped");
    }

    void Application::handleTimeout() {
        context.state->handleTimeout();
    }

    void Application::handleSib(common::BtsId btsId) {
        context.state->handleSib(btsId);
    }

    void Application::handleAttachAccept() {
        context.state->handleAttachAccept();
    }

    void Application::handleAttachReject() {
        context.state->handleAttachReject();
    }

    void Application::handleDisconnectedFromBts() {
        context.state->handleDisconnectedFromBts();
    }

    void Application::handleUiAction(std::optional<std::size_t> selectedIndex) {
        context.state->handleUiAction(selectedIndex);
    }

    void Application::handleUiBack() {
        context.state->handleUiBack();
    }

    void Application::handleSmsReceived(common::PhoneNumber from, std::string text)
    {
        logger.logInfo("SMS received from: ", from);
        context.state->handleSmsReceived(from, text);
    }
}
