#pragma once

#include "BaseState.hpp"

namespace ue
{

    class ViewingSmsListState : public BaseState
    {
    public:
        ViewingSmsListState(Context& context);

        void handleUiAction(std::optional<std::size_t> selectedIndex) override;
        void handleUiBack() override;

        void handleDisconnectedFromBts() override;
        void handleSmsReceived(common::PhoneNumber from, std::string text) override;


    private:
        void showList();
        std::vector<SmsMessage> currentSmsList;
    };

}