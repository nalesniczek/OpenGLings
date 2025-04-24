
## bartek 
dla windows
```bash
clang++ -Iinclude src/glad.c src/main.cpp -Llib -lglfw3dll -lopengl32 -lgdi32 -o bin/program
```

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


# Co to jest `CMAKE`
CMAKE jest to oprogramowanie potrzebne do budowania projektów napisanych w `C/C++` generalnie nie ogarniam co się tam dzieje ale: 

1. Zrobiłem folder [build](/build)
- w nim są pliki konfiguracyjne do budowy projektu, w nim uruchamiamy komendy:
```bash 
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..  
```
te '..' oznaczają że plik `CMakeLists.txt` jest w folderze wyżej czyli w folderze głównym projektu.

- gdy już wszystko działa i się powiedzie powinieneś zobaczyć coś takiego: 
```bash
    ~/OpenGLings/build  on   master ?3  cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..                                                 

-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: ~/github/OpenGLings/build
```

- następnie zmuszasz CMAKE do zbudowania projektu:
```bash
#komenda
make

# output
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/kitajussus/github/OpenGLings/build
[ 25%] Building C object CMakeFiles/glad.dir/src/glad.c.o
[ 50%] Linking C static library libglad.a
[ 50%] Built target glad
[ 75%] Building CXX object CMakeFiles/Main.dir/src/main.cpp.o
[100%] Linking CXX executable Main

```

**Dzięki tym wszystkim procedurom i komendom ClangD powinien nauczyć się wykrywać biblioteki bo już zna dependencje i wie co z czym się je.** 
