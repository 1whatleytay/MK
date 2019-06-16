#include <Methods.h>

const MethodInfo globalMethods[] = {
	{"help", {
		{"command", Params::Text, {}, true},
	}, "help [command]"},
	{"say", {
		{"text", Params::Text},
	}, "say [text]"},
	{"weather", {
		{"weather", Params::Text, {"clear", "rain", "thunder", }},
	}, "weather [weather]"},
	{"clone", {
		{"c1", Params::Coordinate},
		{"c2", Params::Coordinate},
		{"c3", Params::Coordinate},
		{"mask", Params::Text, {"filtered", "masked", "replace", }, true},
		{"mode", Params::Text, {"force", "move", "normal", }, true},
		{"block", Params::Item, {}, true},
	}, "clone [c1] [c2] [c3] [mask] [mode] [block]"},
	{"difficulty", {
		{"level", Params::Text, {"peaceful", "easy", "normal", "hard", "p", "e", "n", "h", }},
	}, "difficulty [level]"},
	{"summon", {
		{"entity", Params::Entity},
		{"coord", Params::Coordinate, {}, true},
		{"data", Params::Text, {}, true},
	}, "summon [entity] [coord] [data]"},
	{"setTime", {
		{"value", Params::Text},
	}, "time set [value]"},
	{"addTime", {
		{"value", Params::Text},
	}, "time add [value]"},
	{"queryTime", {
		{"type", Params::Text, {"daytime", "gametime", "day", }},
	}, "time query [type]"},
};