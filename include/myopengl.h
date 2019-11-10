#undef OpenglAlg
//#include<glad/glad.h>
//#include<stdio.h>
//#include<OpenglAlg.h>
//#include<malloc.h>
#include<glfw_callback.h>
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include "Dense"
//#include<GLFW/glfw3.h>
#include<time.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
void set_callback(GLFWwindow* window)
{

glfwSetMouseButtonCallback(window,mouse_button_callback);
glfwSetCursorPosCallback(window,cursor_position_callback);
glfwSetKeyCallback(window,key_callback); 
glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
glfwGetFramebufferSize(window,&globalinfo.resolution[0],&globalinfo.resolution[1]);
glfwSetScrollCallback(window,scroll_callback);
}
void init_uniform(GLuint program)
{//vec3 iR=vec3(800,600,0);
//glUniform1i(glGetUniformLocation(program,"iResolution"),iR);
    //glm::
    Eigen::MatrixXf p=Projection(M_PI/3.0f,(float)globalinfo.resolution[0]/(float)globalinfo.resolution[1],0.2f,100.0f);

/*glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)globalinfo.resolution[0]/(float)globalinfo.resolution[1], 0.2f, 100.0f);
for(int i=0;i<4;i++)
{
for(int j=0)
}*/
glUniformMatrix4fv(glGetUniformLocation(program,"Proj"),1,GL_FALSE,p.data());
glUniformMatrix4fv(glGetUniformLocation(program,"Matrix"),1,GL_TRUE,arc.get_data(&arc));
Eigen::VectorXf a(2);
    a.coeffRef(0)=(float)globalinfo.resolution[0];
    a.coeffRef(1)=(float)globalinfo.resolution[1];
    glUniform2fv(glGetUniformLocation(program,"iResolution"),1,(float*)a.data());
//把像素着色器的纹理绑定纹理单元GL_TEXURE0
	glUniform1i(glGetUniformLocation(program,"ourTexture"),0);
}
void set_uniform(GLuint program)
{

glUniform2f(glGetUniformLocation(program,"iResolution"),(float)globalinfo.resolution[0],(float)globalinfo.resolution[1]);

    glUniform1f(glGetUniformLocation(program,"iTime"),globalinfo.run_time);
    glUniformMatrix4fv(glGetUniformLocation(program,"Matrix"),1,GL_TRUE,arc.get_data(&arc));
}
GLuint init_VAOs(GLuint* VAOs)
{
	/*GLfloat vertices[6][2]={
		{ -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
        {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2

	
	};*/
	GLfloat vertices[4][3]={{ -0.7f, -0.7f,-1.0f}, {  0.7f, -0.7f,-1.0f }, { -0.7f,  0.7f,-1.0f},{0.7f,0.7f,-1.0f}};
        //float texcoords[]={1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f};
	float texcoords[]={1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f};
	unsigned int indices[]={
	0,1,2,2,1,3
	};
	glGenVertexArrays(1,VAOs);
	glBindVertexArray(VAOs[0]);
	GLuint* Buffers=(GLuint*)malloc(sizeof(GLuint));
	glCreateBuffers(3,Buffers);
	glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	
        glBindBuffer(GL_ARRAY_BUFFER,Buffers[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(texcoords),texcoords,GL_STATIC_DRAW);
        ShaderInfo shaders[]={
	{ GL_VERTEX_SHADER, "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }	
	};

	_Shader_(shaders);
	GLuint program;
		program=_Program_(shaders);
        
glUseProgram(program);//开启这个词更合适
		glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
	glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
        glEnableVertexAttribArray( 0 );
         glBindBuffer(GL_ARRAY_BUFFER,Buffers[2]);
	 glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(2);
	 //glVertexAttribPointer(1,2,)
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
return program;

}
void init_texture()
{
	GLuint* textures=(GLuint*)malloc(sizeof(GLuint)*2);
glGenTextures(2,textures);
ImageInfo image;
image.data=stbi_load("linyueru.jpg",&image.width,&image.height,&image.n,0);
printf("%d",image.n);
/*if(image.data)
{
printf("width %d height %d\r\n",image.width,image.height);
}
*/
//printf("hello%dhello",(int)image.data[image.width*image.height*image.n+1]);
_Texture_(image,textures[0]);
stbi_image_free(image.data);
//先把纹理绑定一个纹理单元GL_TEXTURE0
glActiveTexture(GL_TEXTURE0);

glBindTexture(GL_TEXTURE_2D,textures[0]);
//glUniform1i(glGetUniformLocation())

}
void display(GLuint vao,GLuint program)
{//以下两个语句成对使用
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
static const float black[]={0.0f,0.0f,0.0f,0.0f};
glClearBufferfv(GL_COLOR,0,black);
glBindVertexArray(vao);
glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//glDrawArrays(GL_TRIANGLES,0,6);


}
void mydraw(void)
{
GLuint *VAOs=(GLuint*)malloc(sizeof(GLuint)); //*textures=(GLuint*)malloc(sizeof(GLuint)*2);
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
GLFWwindow* window=glfwCreateWindow(800,600,"learnopengl",NULL,NULL);
if(window==NULL)
{
printf("Failed to create GLFW window\r\n");
return;

}
//GlobalInfo_init(&globalinfo);
arc.ginfo=&globalinfo;
Arcroll_init(&arc);
//globalinfo.resolution[0]=800.0;
//globalinfo.resolution[1]=600.0;
   glfwMakeContextCurrent(window);


//glfwMakeContexCurrent(window);
if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{

return;
}

//glGenVertexArrays(1,VAOs);
init_texture();
GLuint program=init_VAOs(VAOs);
clock_t start,finish;
start=clock();
set_callback(window);
    init_uniform(program);

while(!glfwWindowShouldClose(window))
{

finish=clock();

globalinfo.run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
set_uniform(program);
        //glUniform1f(glGetUniforLocation())
display(VAOs[0],program);
glfwSwapBuffers(window);
glfwPollEvents();




}
glfwDestroyWindow(window);
glfwTerminate();


}

