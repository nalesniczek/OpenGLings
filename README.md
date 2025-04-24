
## bartek 
dla windows
```bash
clang++ -Iinclude src/glad.c src/main.cpp -Llib -lglfw3dll -lopengl32 -lgdi32 -o bin/program
0```

## od krzyś

bartek dodaj instrukcje jak to uruchomic na linux?

dobra chuj sam to zrobiłem. 

```bash
clang++ -Iinclude src/glad.c src/main.cpp -Llib -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o bin/program
```
1. **`-lglfw3dll`**: Na Linuxie używa się `-lglfw`, ponieważ biblioteka GLFW jest dostępna w tej formie.
2. **`-lopengl32`**: Na Linuxie używa się `-lGL` dla OpenGL.
3. **`-lgdi32`**: Na Linuxie nie jest potrzebne, ale trzeba dodać inne biblioteki, takie jak `-lX11`, `-lpthread`, `-lXrandr`, `-lXi`, i `-ldl`, które są wymagane przez GLFW.

Ubuntu trzeba zainstalowac dodatkowe pakiety/biblioteki:

```bash
sudo apt-get install libglfw3-dev libgl1-mesa-dev
```

