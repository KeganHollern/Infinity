#pragma once


class Infinity {
public:
	Infinity();
	~Infinity();

	void Init();
	void LoadPlugins();
private:
	std::thread startup;
};