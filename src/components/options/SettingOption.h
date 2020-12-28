#pragma once
#include "../../GameObject.h"
#include "../../inputs/MouseInput.h"

namespace yothello
{
	class SettingOption
	{
	public:
		virtual ~SettingOption() {}
		virtual void update(MouseInput& mouseInput) = 0;
	};
}