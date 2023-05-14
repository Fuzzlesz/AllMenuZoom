#include "Hooks.h"

#include <Settings.h>
#include <Zoom.h>

namespace Hooks
{
	static bool isAltKeyHeld{ false };
	static std::uint32_t numTimesTogglePressed{ 0 };

	static std::once_flag loadConditions;

	// Init

	struct ProcessButton
	{
		static bool thunk(RE::MenuEventHandler* a_this, RE::ButtonEvent* a_event)
		{
			if (!func(a_this, a_event)) {
				const auto settings = Settings::GetSingleton();

				const auto key = a_event->GetIDCode();
				const auto device = a_event->GetDevice();

				if (a_event->IsHeld()) {
					if (key == settings->editor.altActionKey) {
						isAltKeyHeld = true;
					}
				}
				else if (a_event->IsDown()) {
					if (numTimesTogglePressed == 1) {
						ZoomManager::GetSingleton()->ProcessButtonDown(device, key, isAltKeyHeld);
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
	};
	void Install()
	{
	}
}
