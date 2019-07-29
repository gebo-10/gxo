#pragma once
class Action {
	int delay;
	std::function<void(Event*)> fun;
};