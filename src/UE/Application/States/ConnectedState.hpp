#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleDisconnectedFromBts() override;
    void handleSmsReceived(common::PhoneNumber from, std::string text) override;


    void handleUiAction(std::optional<std::size_t> selectedIndex) override;
    void handleUiBack() override;

private:
    void showMainMenu();
};

}
