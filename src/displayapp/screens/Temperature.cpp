#include <string.h>
#include "Temperature.h"
#include "Screen.h"
#include "Symbols.h"
#include "lvgl/lvgl.h"
#include "projdefs.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include <tuple>

using namespace Pinetime::Applications::Screens;

Temperature::Temperature(DisplayApp* app,
                         Pinetime::Controllers::NotificationManager& notificationManager,
                         Pinetime::Controllers::AlertNotificationService& alertNotificationService)
    : Screen(app),
      notificationManager {notificationManager},
      alertNotificationService {alertNotificationService} {

        auto notification = notificationManager.GetLastNotification();

        if (notification.valid) {
            temperature = notification.Message();
        }
        else
        {
            temperature = "--";
        }

        tempTitleRender = lv_label_create(lv_scr_act(), nullptr);
        lv_obj_set_style_local_text_color(tempTitleRender, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x008080));
        lv_label_set_text(tempTitleRender, "Temperature");
        lv_obj_align(tempTitleRender, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 0);

        tempRender = lv_label_create(lv_scr_act(), nullptr);
        lv_obj_set_style_local_text_font(tempRender, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
        lv_obj_set_style_local_text_color(tempRender, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x008080));
        lv_label_set_text(tempRender, temperature);
        lv_obj_align(tempRender, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
    }

Temperature::~Temperature() {
    lv_obj_clean(lv_scr_act());
}

bool Temperature::Refresh() {

    if (notificationManager.AreNewNotificationsAvailable()) {

        notificationManager.ClearNewNotificationFlag();
        auto notification = notificationManager.GetLastNotification();

        if (notification.valid) {
            temperature = notification.Message();
            lv_label_set_text(tempRender, temperature);
        }
    }

    return true;
}
