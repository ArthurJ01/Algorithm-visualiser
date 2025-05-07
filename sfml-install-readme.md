# Linking new libraries or whatever STATICALLY
In tasks.json you have
```json
    "-lsfml-graphics-s",
    "-lsfml-window-s",
    "-lsfml-system-s",
    "-lopengl32",
    "-lwinm",
    "-lgdis32"
```
To add a library to link add the library with "-lsfml-graphics" + "-s" suffix for static linking, then check 
https://www.sfml-dev.org/tutorials/3.0/getting-started/code-blocks/#creating-and-configuring-an-sfml-project 
for the dependencies you need to add.

# Linking dynamically (do this)

```json
    "-lsfml-graphics",
    "-lsfml-window",
    "-lsfml-system",
```

Do that and just make sure you have the dll in the same folder as the .exe
