#include "Zoom.h"
#include "Settings.h"

void ZoomManager::ProcessButtonDown(RE::INPUT_DEVICE a_device, std::uint32_t a_key, bool a_altKeyHeld)
{
	static auto settings = Settings::GetSingleton();
	static auto zoom = RE::UserEvents::GetSingleton();

	switch (a_device) {
	case RE::INPUT_DEVICE::kMouse:
		a_key += SKSE::InputMap::kMacro_MouseButtonOffset;
		break;
	case RE::INPUT_DEVICE::kGamepad:
		a_key = SKSE::InputMap::GamepadMaskToKeycode(a_key);
		break;
	default:
		break;
	}

	if (const auto key_bind = settings->editor.keyBinds.key(a_key)) {
		switch (*key_bind) {
		case Settings::KEY_BIND::kScaleUp:
			zoom->itemZoom;
			break;
		default:
			break;
		}
	}
}
