#include "Hooks.h"
#include "PresetManager.h"
#include "Settings.h"

namespace Hooks
{
	static bool isAltKeyHeld{ false };
	static std::uint32_t numTimesTogglePressed{ 0 };

	static std::once_flag loadConditions;

	
	struct ProcessButton
	{
		static bool thunk(RE::ConstructibleObjectMenu* a_this, RE::ButtonEvent* a_event)
		{
			if (!func(a_this, a_event)) {
				const auto settings = Settings::GetSingleton();

				const auto key = a_event->GetIDCode();
				const auto device = a_event->GetDevice();

				if (a_event->IsHeld()) {
					if (key == settings->editor.altActionKey) {
						isAltKeyHeld = true;
					}
					if (numTimesTogglePressed == 1) {
						ModelManager::GetSingleton()->ProcessButtonHeld(device, key, isAltKeyHeld);
					}
				}
				else if (a_event->IsUp()) {
					if (key == settings->editor.altActionKey) {
						isAltKeyHeld = false;
					}
				}
				return false;
			}
			return true;
		}
		static inline REL::Relocation<decltype(thunk)> func;

		static inline constexpr std::size_t index{ 1 };
		static inline constexpr std::size_t size{ 0x1 };

	
	void Install()
	{
		logger::info("Installed ZOOM ZOOM ZOOM menu hooks");

		stl::write_vfunc<RE::ConstructibleObjectMenu, ProcessButton>();

	}
}
