#pragma once

#include "Screen.h"
#include "components/datetime/DateTimeController.h"
#include "components/ble/NotificationManager.h"
#include "components/ble/AlertNotificationService.h"
#include "../LittleVgl.h"

#include "FreeRTOS.h"
#include "portmacro_cmsis.h"

namespace Pinetime::Applications::Screens {
    class Temperature : public Screen {
    public:
        Temperature(DisplayApp* app,
                    Pinetime::Controllers::NotificationManager& notificationManager,
                    Pinetime::Controllers::AlertNotificationService& alertNotificationService);

        ~Temperature() override;
        bool Refresh() override;

    private:
        Pinetime::Controllers::NotificationManager& notificationManager;
        Pinetime::Controllers::AlertNotificationService& alertNotificationService;
        lv_obj_t *tempTitleRender;
        lv_obj_t *tempRender;
        const char *temperature;
    };
}