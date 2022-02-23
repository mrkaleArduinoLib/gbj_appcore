#include "gbj_appcore.h"
// Static members for sharing and saving memory across all instances of child
// classes.
char gbj_appcore::reasonName_[22];
gbj_appcore::BootReasons gbj_appcore::reasonCode_ = BootReasons::BOOT_UNKNOWN;

void gbj_appcore::reason()
{
  if (strlen(reasonName_))
  {
    return;
  }
  strcpy_P(reasonName_, PSTR("BOOT_UNKNOWN"));
#if defined(ESP8266) || defined(ESP32)
  switch (ESP.getResetInfoPtr()->reason)
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
  }
#endif
}
