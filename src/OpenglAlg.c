#undef OpenglAlg
#include<Mesh_view/OpenglAlg.h>


GLchar* _ReadFile_ (char* filename)
{
#ifdef WIN32
	FILE* infile;
	fopen_s(&infile,filename,"rb");
#else
	FILE* infile=fopen(filename,"rb");
#endif
  if(!infile)
  {
  	printf("can't open this file\r\n");
  	return NULL;
  }
    fseek(infile,0,SEEK_END);//定位到离文末0字节处
    int len=ftell(infile);//当前处离文首多少字节
    fseek(infile,0,SEEK_SET);//定位到文首
    GLchar* source=(char*)malloc(len+1);
    fread(source,1,len,infile);
    fclose(infile);
    source[len]=0;
    return (source);


}


void _Shader_(ShaderInfo* shaders)
{

ShaderInfo* entry=shaders;	
while(entry->type!=GL_NONE)
{
	
    	if(entry->filename==NULL)
    	{

        	printf("finename is NULL\n");
		continue;
    	}
	GLuint shader=glCreateShader(entry->type);
	const GLchar* source= _ReadFile_(entry->filename);
	if(source==NULL)
	{
		printf("this file is blank\r\n");
	
	return;
	}
	glShaderSource(shader,1,&source,NULL);
	free((GLchar *)source);
	glCompileShader(shader);
	GLint compiled;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
	if(!compiled)
	{
#ifdef _DEBUG
	GLsizei len;
	glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&len);
	GLchar* log=(GLchar*)malloc(len+1);
	glGetShaderInfoLog(shader,len,&len,log);
	printf("shader compiled error,%s\r\n",log);
	free(log);
#endif
    	printf("failed to compiled\n");
	return;

}

entry->shader=shader;
entry++;
}

}
GLuint _Program_ (ShaderInfo* shaderinfos)
{
	

if(shaderinfos==NULL)
{printf("shaderinfos is null\r\n");
	return 0;
}
GLuint program=glCreateProgram();

for(ShaderInfo* entry=shaderinfos;entry->type!=GL_NONE;entry++)
{
glAttachShader(program,entry->shader);
glDeleteShader(entry->shader);
//entry++;
}
glLinkProgram(program);
GLint linked;
glGetProgramiv(program,GL_LINK_STATUS,&linked);
if(!linked)
{
#ifdef _DEBUG

              GLint infoLen;
glGetProgrmiv(program,GL_INFO_LOG_LENGTH,&infolen)
char* strinfo=(char*)malloc(infolen+1);
glGetProgramInfoLog(program,infolen,NULL,strinfo);
printf("can't linked ,&s\r\n",strinfo);
free(strinfo);
#endif
printf("can't linked \r\n");
glDeleteProgram(program);
return 0;

}

/*for(auto entry=shaderinfos;entry->type!=GL_NONE;entry++)
{
//glDeleteShader(entry->shader);
//vector_destroy(pvec_v1);
glDetachShader(program,entry->shader);
}*/

return program;

//return program;
}

void _Texture_ (ImageInfo *image,GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D,texture);
	//glTexStorage2D(GL_TEXTURE_2D,1,GL_RGB8,image.width,image.height);
	//glTexSubImage2D(GL_TEXTURE_2D,0,0,0,image.width,image.height,GL_RGB,GL_UNSIGNED_BYTE,image.data);
       //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width,image->height,0,GL_RGB,GL_UNSIGNED_BYTE,(unsigned char*)(image->data));
	
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);

}
void _Texture_Array_GL_FLOAT1(ImageInfo* image,GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, image->width, image->height, 0,GL_RED,GL_FLOAT, (GLfloat*)(image->data));
    glBindTexture(GL_TEXTURE_2D, 0);

}
void _Texture_Array_GL_FLOAT(ImageInfo* image,GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, image->width, image->height, 0,GL_RGB,GL_FLOAT, (GLfloat*)(image->data));
    glBindTexture(GL_TEXTURE_2D, 0);

}
void _Texture_Array_GL_R32UI(ImageInfo* image,GLuint texture)
{
	
glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, image->width, image->height, 0,GL_RED,GL_FLOAT, (GLfloat*)(image->data));
    glBindTexture(GL_TEXTURE_2D, 0);


}




