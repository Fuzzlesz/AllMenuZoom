#pragma once

class ZoomManager : public ISingleton<ZoomManager>
{
public:
	void ProcessButtonDown(RE::INPUT_DEVICE a_device, std::uint32_t a_key, bool a_altKeyHeld);

};
