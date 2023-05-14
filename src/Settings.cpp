#include "Settings.h"

	void	Settings::LoadSettings()
{
	constexpr auto path = L"Data/SKSE/Plugins/fz_zoom.ini";

	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(path);

	ini::get_value(
		ini,
		editor.altActionKey,
		"TransformEditorKeyBinds",
		"AltActionKey",
		";Default key : LeftShift");

	editor.assign_keybind(
		ini,
		KEY_BIND::kScaleUp,
		"TransformEditorKeyBinds",
		"ScaleUp",
		";Default key : ScrollWheel Up");
	editor.assign_keybind(
		ini,
		KEY_BIND::kScaleDown,
		"TransformEditorKeyBinds",
		"ScaleDown",
		";Default key : ScrollWheel Down");

	(void)ini.SaveFile(path);
}
