/**
 * @file self_globals.cpp
 * @brief Updates `self::*` globals.
 */

#include "backend/looped/looped.hpp"
#include "gta/joaat.hpp"
#include "gta/script/natives.hpp"
#include "gta/pointers.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	void looped::system_self_globals()
	{
		self::id = PLAYER::PLAYER_ID();

		self::ped = PLAYER::PLAYER_PED_ID();

		STATS::STAT_GET_INT("MPPLY_LAST_MP_CHAR"_J, &self::char_index, true);

		self::pos = ENTITY::GET_ENTITY_COORDS(self::ped, false /*Unused*/);

		self::rot = ENTITY::GET_ENTITY_ROTATION(self::ped, 2);

		if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, 0))
		{
			self::veh = PED::GET_VEHICLE_PED_IS_IN(self::ped, false);
		}
		else
		{
			self::veh = 0;
		}
	}
}
