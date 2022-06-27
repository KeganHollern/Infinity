#pragma once


class GInfinity {
public:
	GInfinity();
	~GInfinity();

	void Init();
	void LoadPlugins();
private:
	std::thread startup;
};