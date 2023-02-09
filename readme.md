# PluginLoader
*A simple way to integrate Plugin support*</br>

---
## What is this?
The host-side implemented PluginLoader for my [PluginLoader_Example](https://github.com/sam-k0/PluginLoader_DefaultPlugin). <br>



---
## Prerequisites
- GNU GCC Compiler
- GameMaker Studio 1.4+ (not really needed)

## Setup
Easiest is to download this repo. <br>

The Loader is one simple DLL with exposed functions in main.cpp<br>
If you are using GameMaker Studio to integrate this, it's easiest to download the prebuilt **Extension Package**.<br>

The whole thing is currently using some GameMakerStudio specific callbacks to return values, but it can also be changed to just return plain values with little effort.<br>

---
**In-IDE-Setup**<br>
The DLL has to be built the same architecture as the host application.<br>

You should also **statically link the standard library**<br>
*This can be done by using these linker flags*:<br>
`-static-libgcc -static-libstdc++`

