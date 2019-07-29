#pragma once
class Trigger
{
public:
	std::vector<std::function<void(Event*)>> actions;

private:
};