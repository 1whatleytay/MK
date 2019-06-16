#include <Methods.h>

const MethodInfo targetMethods[] = {
	{"kill", {}, "kill [target]"},
	{"give", {
		{"item", Params::Item},
		{"count", Params::Number},
		{"data", Params::Text, {}, true},
	}, "give [target] [item][data] [count]"},
	{"playSound", {
		{"sound", Params::Text},
		{"source", Params::Text, {"master", "music", "record", "weather", "block", "hostile", "neutral", "player", "ambient", "voice", }},
		{"coord", Params::Coordinate, {}, true},
		{"volume", Params::Text, {}, true},
		{"pitch", Params::Text, {}, true},
		{"minVolume", Params::Text, {}, true},
	}, "playsound [sound] [source] [target] [coord] [volume] [pitch] [minVolume]"},
	{"gamemode", {
		{"mode", Params::Text, {"survival", "creative", "adventure", "spectator", }},
	}, "gamemode [mode] [target]"},
	{"addTag", {
		{"name", Params::Text},
	}, "tag [target] add [name]"},
	{"removeTag", {
		{"name", Params::Text},
	}, "tag [target] remove [name]"},
	{"listTags", {}, "tag [target] list"},
};