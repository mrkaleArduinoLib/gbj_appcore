#include "gbj_appcore.h"
// Static members for sharing and saving memory across all instances of child
// classes.
char gbj_appcore::resultName_[30];
char gbj_appcore::reasonName_[30];
gbj_appcore::BootReasons gbj_appcore::reasonCode_ = BootReasons::BOOT_UNKNOWN;

void gbj_appcore::result()
{
  switch (lastResult_)
  {
    case ResultCodes::SUCCESS:
      strcpy_P(resultName_, PSTR("SUCCESS"));
      break;

    case ResultCodes::ERROR_NOINIT:
      strcpy_P(resultName_, PSTR("ERROR_NOINIT"));
      break;

    case ResultCodes::ERROR_NODEVICE:
      strcpy_P(resultName_, PSTR("ERROR_NODEVICE"));
      break;

    case ResultCodes::ERROR_PINS:
      strcpy_P(resultName_, PSTR("ERROR_PINS"));
      break;

    case ResultCodes::ERROR_ADDR:
      strcpy_P(resultName_, PSTR("ERROR_ADDR"));
      break;

    case ResultCodes::ERROR_DATA:
      strcpy_P(resultName_, PSTR("ERROR_DATA"));
      break;

    case ResultCodes::ERROR_ACK:
      strcpy_P(resultName_, PSTR("ERROR_ACK"));
      break;

    case ResultCodes::ERROR_CONNECT:
      strcpy_P(resultName_, PSTR("ERROR_CONNECT"));
      break;

    case ResultCodes::ERROR_PUBLISH:
      strcpy_P(resultName_, PSTR("ERROR_PUBLISH"));
      break;

    case ResultCodes::ERROR_SUBSCRIBE:
      strcpy_P(resultName_, PSTR("ERROR_SUBSCRIBE"));
      break;

    case ResultCodes::ERROR_AUTH:
      strcpy_P(resultName_, PSTR("ERROR_AUTH"));
      break;

    default:
      strcpy_P(resultName_, PSTR("ERROR_UNKNOWN"));
      break;
  }
}

void gbj_appcore::reason()
{
  if (strlen(reasonName_) > 0)
  {
    return;
  }
#if defined(ESP8266) || defined(ARDUINO_ARCH_ESP8266)
  rst_info *resetInfo;
  resetInfo = ESP.getResetInfoPtr();
  switch (resetInfo->reason)
  {
    case REASON_DEFAULT_RST:
      reasonCode_ = BootReasons::BOOT_DEFAULT_RST;
      strcpy_P(reasonName_, PSTR("BOOT_DEFAULT_RST"));
      break;

    case REASON_WDT_RST:
      reasonCode_ = BootReasons::BOOT_WDT_RST;
      strcpy_P(reasonName_, PSTR("BOOT_WDT_RST"));
      break;

    case REASON_EXCEPTION_RST:
      reasonCode_ = BootReasons::BOOT_EXCEPTION_RST;
      strcpy_P(reasonName_, PSTR("BOOT_EXCEPTION_RST"));
      break;

    case REASON_SOFT_WDT_RST:
      reasonCode_ = BootReasons::BOOT_SOFT_WDT_RST;
      strcpy_P(reasonName_, PSTR("BOOT_SOFT_WDT_RST"));
      break;

    case REASON_SOFT_RESTART:
      reasonCode_ = BootReasons::BOOT_SOFT_RESTART;
      strcpy_P(reasonName_, PSTR("BOOT_SOFT_RESTART"));
      break;

    case REASON_DEEP_SLEEP_AWAKE:
      reasonCode_ = BootReasons::BOOT_DEEP_SLEEP_AWAKE;
      strcpy_P(reasonName_, PSTR("BOOT_DEEP_SLEEP_AWAKE"));
      break;

    case REASON_EXT_SYS_RST:
      reasonCode_ = BootReasons::BOOT_EXT_SYS_RST;
      strcpy_P(reasonName_, PSTR("BOOT_EXT_SYS_RST"));
      break;

    default:
      reasonCode_ = BootReasons::BOOT_UNKNOWN;
      strcpy_P(reasonName_, PSTR("BOOT_UNKNOWN"));
      break;
  }
#elif defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
  esp_reset_reason_t reset_reason = esp_reset_reason();
  switch (reset_reason)
  {
    case ESP_RST_UNKNOWN:
      reasonCode_ = BootReasons::BOOT_UNKNOWN;
      strcpy_P(reasonName_, PSTR("ESP_RST_UNKNOWN"));
      break;

    case ESP_RST_POWERON:
      reasonCode_ = BootReasons::BOOT_DEFAULT_RST;
      strcpy_P(reasonName_, PSTR("ESP_RST_POWERON"));
      break;

    case ESP_RST_EXT:
      reasonCode_ = BootReasons::BOOT_EXT_SYS_RST;
      strcpy_P(reasonName_, PSTR("ESP_RST_EXT"));
      break;

    case ESP_RST_SW:
      reasonCode_ = BootReasons::BOOT_SOFT_RESTART;
      strcpy_P(reasonName_, PSTR("ESP_RST_SW"));
      break;

    case ESP_RST_PANIC:
      reasonCode_ = BootReasons::BOOT_EXCEPTION_RST;
      strcpy_P(reasonName_, PSTR("ESP_RST_PANIC"));
      break;

    case ESP_RST_INT_WDT:
      reasonCode_ = BootReasons::BOOT_INT_WDT_RST;
      strcpy_P(reasonName_, PSTR("ESP_RST_INT_WDT"));
      break;

    case ESP_RST_TASK_WDT:
      reasonCode_ = BootReasons::BOOT_TASK_WDT_RST;
      strcpy_P(reasonName_, PSTR("ESP_RST_TASK_WDT"));
      break;

    case ESP_RST_WDT:
      reasonCode_ = BootReasons::BOOT_WDT_RST;
      strcpy_P(reasonName_, PSTR("ESP_RST_WDT"));
      break;

    case ESP_RST_DEEPSLEEP:
      reasonCode_ = BootReasons::BOOT_WDT_RST;
      strcpy_P(reasonName_, PSTR("ESP_RST_DEEPSLEEP"));
      break;

    case ESP_RST_BROWNOUT:
      reasonCode_ = BootReasons::BOOT_BROWNOUT;
      strcpy_P(reasonName_, PSTR("ESP_RST_BROWNOUT"));
      break;

    case ESP_RST_SDIO:
      reasonCode_ = BootReasons::BOOT_SDIO;
      strcpy_P(reasonName_, PSTR("ESP_RST_SDIO"));
      break;

    default:
      reasonCode_ = BootReasons::BOOT_UNKNOWN;
      strcpy_P(reasonName_, PSTR("BOOT_UNKNOWN"));
      break;
  }
  if (reset_reason == ESP_RST_DEEPSLEEP)
  {
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
      case ESP_SLEEP_WAKEUP_UNDEFINED:
        reasonCode_ = BootReasons::BOOT_WAKEUP_UNDEFINED;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_UNDEFINED"));
        break;

      case ESP_SLEEP_WAKEUP_ALL:
        reasonCode_ = BootReasons::BOOT_WAKEUP_ALL;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_ALL"));
        break;

      case ESP_SLEEP_WAKEUP_EXT0:
        reasonCode_ = BootReasons::BOOT_WAKEUP_EXT0;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_EXT0"));
        break;

      case ESP_SLEEP_WAKEUP_EXT1:
        reasonCode_ = BootReasons::BOOT_WAKEUP_EXT1;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_EXT1"));
        break;

      case ESP_SLEEP_WAKEUP_TIMER:
        reasonCode_ = BootReasons::BOOT_WAKEUP_TIMER;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_TIMER"));
        break;

      case ESP_SLEEP_WAKEUP_TOUCHPAD:
        reasonCode_ = BootReasons::BOOT_WAKEUP_TOUCHPAD;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_TOUCHPAD"));
        break;

      case ESP_SLEEP_WAKEUP_ULP:
        reasonCode_ = BootReasons::BOOT_WAKEUP_ULP;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_ULP"));
        break;

      case ESP_SLEEP_WAKEUP_GPIO:
        reasonCode_ = BootReasons::BOOT_WAKEUP_GPIO;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_GPIO"));
        break;

      case ESP_SLEEP_WAKEUP_UART:
        reasonCode_ = BootReasons::BOOT_WAKEUP_UART;
        strcpy_P(reasonName_, PSTR("ESP_SLEEP_WAKEUP_UART"));
        break;

      default:
        reasonCode_ = BootReasons::BOOT_WAKEUP_UNDEFINED;
        strcpy_P(reasonName_, PSTR("BOOT_WAKEUP_UNDEFINED"));
        break;
    }
  }
#endif
}
