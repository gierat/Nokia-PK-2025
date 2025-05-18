#pragma once

#include "BaseState.hpp"

namespace ue
{

    class ViewingSingleSmsState : public BaseState
    {
    public:

        ViewingSingleSmsState(Context &context, std::size_t smsIndex);

        void handleUiBack() override;
        void handleUiAction(std::optional<std::size_t> selectedIndex) override;

        void handleDisconnected() override;
        void handleSmsReceived(common::PhoneNumber from, std::string text) override;

    private:
        std::size_t viewingSmsIndex;
    };

}