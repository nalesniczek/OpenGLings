# OpenGling
Notes from lerning OpenGl
(The name of project inspired from Krzysztof's Ziglings, oh I basically copied it but don't tell him)

# Workspace
Configurating workspace in vscode is a nightmare 
I know that I could use Cmkae but like who cares if running my project via terminal works
```bash
clang++ -Iinclude src/glad.c src/main.cpp -Llib -lglfw3dll -lopengl32 -lgdi32 -o bin/program
```
Yup it's on windows
And ehhh on the branch master you can find cmake and how to run it via terminal on Linux made by Krzysztof


# Generating window
Oh it's some random functions like whole this project

# VAO, VBO, EBO
VBO - Vertex Buffer Object
It's role is to store information for object and send it directly to GPU, so it can access it easily 

Generating the VBO:
```c++
unsigned int VBO;//why int? oh becasue we are creating ID for VBO
glGenBuffer(1, &VBO);//we are generating 1 buffer and assign it to VBO's adress
glBindBuffer(GL_ARRAY_BUFFER, VBO);//now we are telling opengl what's the VBO
glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);//and now giving opengl data for VBO for us it's array of vertcies, it's like points to draw and we tell, how we want to draw it, now for GL_STATIC_DRAW, if we want to change data a lot GL_DYNAMIC_DRAW
```

VAO - Vertex Array Object
So VAO is telling GPU how to interpret our VBO data we gave it 
Generatig VAO:
```c++
unsigned int VAO;
glGenBuffer(1, &VAO);//remember to generate VAO before the VBO
/*glVertexAttribPointer(locationOfShader, sizeOfAtributte, typeOfAtributes, ifNormalised, sizeOfDatatype, (void*)offset); this is how it looks to tell 
GPU how it should interpret data, meh*/
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);/*example 0 -loaction we set in shader's code, 3 - size of one attribute 
here it's position (I mean I haven't even satged earlier in notes what is in my verticies but like it's for me, another thing is that I write it also 
for me but I pretend like someone reads it lol) GL_FLOAT - what type are this attributes, GL_FALSE - means I don't want to normalise my atributes, 
3*sizeof(float) - just means how much space should it prepare to interpret (void*)0 - offset in VBO, for now it's 0 but if I put more information in 
verticies and need to extract them then I have to set offset (no Idea what (void*) means, I read something on the interent still nothing)
*/
glEnableVertexAttribArray(0);
```