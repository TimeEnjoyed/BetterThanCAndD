/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <QWidget>
#include <plugin-support.h>

#include "test.hpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

/*
static void OBSEvent(enum obs_frontend_event event, void *) {
    obs_log(LOG_INFO, "OBSEvent function called");
    if (event == OBS_FRONTEND_EVENT_FINISHED_LOADING) {
        set_browser_source_url("Browser", "https:/leetcode.com");
    }
}
*/

bool obs_module_load(void) {
    QWidget *main_window = (QWidget *) obs_frontend_get_main_window();
    TwitchClient tc = TwitchClient(
        "",
        ""
    );

    TwitchClipFetcher tcf = TwitchClipFetcher(tc);
    tcf.setBroadcasterIdFromStreamerHandle("supertf");

    BrowserDialog *browserDialog = new BrowserDialog(main_window);

    const char *browser_source = browserDialog->getText();

    std::pair<std::string, double> clipPair = tcf.fetchRandomClip();

    obs_log(LOG_INFO, "After fetching clip");

    set_browser_source_url(browser_source, clipPair.first.c_str());

    obs_log(LOG_INFO, "After setting browser source url");

    obs_frontend_add_dock(browserDialog);

    /*
    obs_log(LOG_INFO, "sanity check");

    obs_frontend_add_event_callback(OBSEvent, nullptr);
    */

    obs_log(LOG_INFO, "plugin loaded successfully (version %s)", PLUGIN_VERSION);

    return true;
}

void obs_module_unload(void)
{
    obs_log(LOG_INFO, "plugin unloaded");
}
