#include "power_config.h"

#ifdef ARDUINO

#include <Arduino.h>
#include <esp_sleep.h>

namespace MeshPowerManager
{
    static uint32_t last_activity_ms = 0;
    static bool initialized = false;

    void init()
    {
        last_activity_ms = millis();
        initialized = true;
    }

    void notify_activity()
    {
        last_activity_ms = millis();
    }

    void sleep_if_idle()
    {
#if ENABLE_MESH_POWER_SAVE
        if (!initialized)
        {
            return;
        }

        uint32_t now = millis();
        uint32_t elapsed = now - last_activity_ms;

        if (elapsed < MESH_MIN_SLEEP_MS)
        {
            return;
        }

        uint32_t sleep_ms = MESH_BEACON_INTERVAL_MS;

if (elapsed < MESH_BEACON_INTERVAL_MS)
{
    sleep_ms = MESH_BEACON_INTERVAL_MS - elapsed;
}

if (sleep_ms < MESH_MIN_SLEEP_MS)
{
    sleep_ms = MESH_MIN_SLEEP_MS;
}

        esp_sleep_enable_timer_wakeup(
            static_cast<uint64_t>(sleep_ms) * 1000ULL
        );

        esp_light_sleep_start();

        last_activity_ms = millis();
#endif
    }
}

#else

namespace MeshPowerManager
{
    void init()
    {
    }

    void notify_activity()
    {
    }

    void sleep_if_idle()
    {
    }
}

#endif
