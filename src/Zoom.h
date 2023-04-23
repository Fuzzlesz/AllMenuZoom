#pragma once

namespace Model
{
	struct Data;
}

class ModelManager : public ISingleton<ModelManager>
{
public:
	void ProcessButtonDown(RE::INPUT_DEVICE a_device, std::uint32_t a_key);
};
