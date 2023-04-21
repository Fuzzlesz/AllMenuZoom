#pragma once

class Settings : public ISingleton<Settings>
{
public:
	enum class KEY_BIND
	{
		kScaleUp,      // WheelUp
		kScaleDown,    // WheelDown
	};

	void LoadSettings();

	// members

	struct
	{
		void assign_keybind(CSimpleIniA& a_ini, KEY_BIND a_keyBind, const char* a_section, const char* a_key, const char* a_comment)
		{
			const auto value = string::to_num<std::uint32_t>(a_ini.GetValue(a_section, a_key, std::to_string(keyBinds.value(a_keyBind)).c_str()));
			a_ini.SetValue(a_section, a_key, std::to_string(value).c_str(), a_comment);

			keyBinds.assign(a_keyBind, value);
		}

		BiMap<KEY_BIND, std::uint32_t> keyBinds{
			{ KEY_BIND::kScaleUp, RE::BSWin32MouseDevice::Key::kWheelUp + 256 },
			{ KEY_BIND::kScaleDown, RE::BSWin32MouseDevice::Key::kWheelDown + 256 },
		};

	} editor;
};
