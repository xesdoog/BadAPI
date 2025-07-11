/**
 * @file view_menubar.cpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of TupoyeMenu.
 * TupoyeMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * TupoyeMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with TupoyeMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#include "gta/script/fiber_pool.hpp"
#include "gta/script/natives.hpp"
#include "gui/components/components.hpp"
#include "lua/lua_manager.hpp"
#include "views/view.hpp"

#include <imgui.h>

namespace big
{
	void view::menu_bar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Unload Menu"))
				{
					g_lua_manager->trigger_event<"MenuUnloaded">();
					g_running = false;
				}

				if (ImGui::MenuItem("Rage Quit (hard crash)"))
				{
					g_running = false;
					exit(0);
					TerminateProcess(GetCurrentProcess(), 0);
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Extra"))
			{
				components::menu_item("Skip Cutscene", [] {
					CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
				});
				components::menu_item("Clear Tasks", [] {
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
				});

				ImGui::Separator();

				components::menu_item("Stop Player Switch", [] {
					STREAMING::STOP_PLAYER_SWITCH();
				});
				components::menu_item("Stop Loading", [] {
					if (CAM::IS_SCREEN_FADED_OUT())
						CAM::DO_SCREEN_FADE_IN(0);
					SCRIPT::SHUTDOWN_LOADING_SCREEN();
				});
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Main", nullptr, &g.window.main);
				ImGui::MenuItem("Demo", nullptr, &g.window.demo);

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}