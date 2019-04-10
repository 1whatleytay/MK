# MK - A minecraft datapack tool.

## Building
MK depends on CMake to build. Be sure to download it [here](https://cmake.org/).
Clone the repository with `git clone https://github.com/1whatleytay/MK.git`.

- Open the directory with `cd MK`.
- Creating the project depends on your OS:
  - On Windows, you can generate a Visual Studio project with `cmake -G "Visual Studio 12 2013 Win64" .`.
  - On macOS, you can generate an XCode project with `cmake -G XCode .`.
  - On a platform with make, CMake will usually default to it. Just try `cmake .`.
- You can now build MK with the project that was generated (something like  `make`).

## Creating a DataPack
To create a datapack, pass an .mk source file as the first parameter to MK.
It should look something like `mk main.mk`.
It will generate the DataPack in the current directory.


## Source
You can create DataPacks with .mk files (which I realize now are an alias for MakeFiles but whatever they don't need to be named .mk).
The MK language is made of many different components, here are a few important ones.

### Tags
Tags are like flavour information for your datapack. They look like this `#tagName tagValue`. It's best to put them at the top of your .mk file.
Tags can hold a number of values and can define data for your project.

Tag Name | Tag Value | Default
-------- | --------- | -------
name | The DataPack name. | MK
description | The DataPack description. | 
format | The DataPack format. | 1
init | The name of the internal init funtion. | __init

### Functions
These are DataPack functions, not exactly the programming type.
They take no parameters and return nothing.
They can be called in game using `/function datapack-name:function-name`.
You can declare one in MK using the `func` keyword.
A function declaration looks like this:

    func function_name {
        // Function contents here.
    }

The `func` keyword can also be prefixed with a few options to subscribe it to in-game events.
Most functions contain commands or code to describe what they do.

`load func name { }` declares a function that will be run once the DataPack is loaded.

`tick func name { }` declares a function that will be run every in-game tick.

### Commands
Raw Minecraft commands will be prefixed with the `/` symbol.
These can be put into functions and will be run just as typed.
One of MK's goals is to avoid using raw commands as much as possible, however they may be necessary for complex expressions.

### Global Methods
Global methods provide a functional way of interfacing with Minecraft.
They can be called with `method_name(param1, param2)`.
The following methods currently exist:

Method Name | Method Function
----------- | ---------------
say(text) | Says `text` in chat. No quotes.

### Targets
A target can be a player name or a group (in the future, they can also be a type of entity).
Groups are:

Group | Function
----- | -------
everyone | Targets every player.
everything | Targets every entity.
random | Targets a random player.
self | Targets the entity that is executing the function.
nearest | Targets the closest entity to the player.

These groups evaluate to Minecraft's `@a`, `@e`, `@r`, `@s` and `@p`, so feel free to use whichever combination you'd like.

Targets have the following methods that can affect its state, which can be called with `target.method_name(param1, param2)`.

Method Name | Method Function
----------- | ---------------
kill() | Kills the target.
give(item, count, data?) | Gives the target `count` `item`s with NBT data `data` if it exists.

### Scores
A score can be declared in our out of a function with the `score` keyword.
Each entity can have a different value for the score.
A score is declared like so:

    // Dummy Score
    score score_name;
    // Typed Score
    score score_health : health;

Putting a colon after a score declaration can give it a type.
Score types can be any [statistic value](https://minecraft.gamepedia.com/Scoreboard#Criteria) defined in Minecraft.

Scores have the following methods that can modify its value, which can be called with `score_name.method_name(param1, param2)`.

Method Name | Method Function
----------- | ---------------
set(target, value) | Sets the value of the score to `value` for `target`.
add(target, value) | Increments the value of the score by `value` for `target`.
sub(target, value) | Decrements the value of the score by `value` for `target`.
setDisplay(location) | Sets the display location for this score. Can be `sidebar`, `aboveName` or `list`.

### Executes
You can have a series of operations affect a target with executes.
An execute is defined like so:

    as target {
        // Code Here.
    }

These can be put in functions.
Anything within the braces will be executed by the target.
