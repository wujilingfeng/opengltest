#version 450 core
out vec4 fColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
uniform int Vsize;
uniform vec2 iResolution;
uniform float iTime;
in vec4 id_in;
uniform vec2 mousecoord;
uniform int action;
uniform int key_action;
uniform int key;
uniform int button;
//uniform int F[140000];
in float depth;
vec3 faceid; 
//vec3 pos;
//0是release 0是left,
//69 key_E
//86 key_v
vec3 getcoord(vec2 a,vec2 b,vec2 c)
{
     vec2 te1=id_in.xy-c;
    vec2 te2=a-c;
    vec2 te3=b-c;
    float de=te2.x*te3.y-te2.y*te3.x;
    vec3 re=vec3(0.0,0.0,0.0);
    re.x=(te3.y*te1.x-te3.x*te1.y)/de;
    re.y=(-te2.y*te1.x+te2.x*te1.y)/de;
    re.z=1-re.x-re.y;
    return re;


}

vec3 getfaceid()
{
    vec3 faceid=vec3(0,0,0);

    vec2 a,b,c;
    vec3 coord;
    for(int i=2;i<Vsize;i++)
    {
        for(int j=1;j<i;j++)
        {
            for(int k=0;k<j;k++)
            {
                a.x=abs(sin(k));a.y=abs(cos(k));
                b.x=abs(sin(j));b.y=abs(cos(j));
                c.x=abs(sin(i));c.y=abs(cos(i));
                coord=getcoord(a,b,c);
                if(coord.x>=0&&coord.y>=0&&coord.z>=0)
                {
                 
                    if(abs(dot(vec3(k,j,i),coord)-id_in.z)<=0.000001)
                    {   
                     
                        faceid.x=k;
                        faceid.y=j;
                        faceid.z=i;
                     break; 
                    }
                }
            
            }
        
        }
    
    }


    return faceid;

}

vec3 trans_code(float a)
{
    //a=a*10000;
    vec3 re;
    re.z=mod(a,255);
    re.y=mod(floor(a/255),255);
    re.x=mod(floor(a/(255*255)),255);
    
    return re;



}
void main()
{
    vec2 uv=gl_FragCoord.xy/iResolution.xy;
//0到1范围
    vec2 coord_uv=mousecoord.xy/iResolution.xy;
    coord_uv.y=1-coord_uv.y;
   // vec3 pos_color;
 //faceid=getfaceid();  
    float code;
    float code1;
    
    vec2 a,b,c;
    a.x=abs(sin(id_in.z*3+0));a.y=abs(cos(id_in.z*3+0));
    b.x=abs(sin(id_in.z*3+1));b.y=abs(cos(id_in.z*3+1));
    c.x=abs(sin(id_in.z*3+2));c.y=abs(cos(id_in.z*3+2));
    vec3 coord=getcoord(a,b,c);
     
    
    code=id_in.z;
    if(coord.x>=coord.y&&coord.y>=coord.z)
    {
        code1=3; 
    
    }
    else if(coord.y>=coord.x&&coord.x>=coord.z)
    {
        code1=1;
    
    
    }
    else if(coord.y>=coord.z&&coord.z>=coord.x)
    {
        code1=7;
    
    }
    else if(coord.x>=coord.z&&coord.z>=coord.y)
    {
        code1=6;
    
    }
    else if(coord.z>=coord.x&&coord.x>=coord.y)
    {
        code1=2;
    }
    else
    {
        code1=5;
    }
    
    fColor=vec4(ourColor,0.2);

    
    if(abs(uv.x-coord_uv.x)<=2/iResolution.x&&abs(uv.y-coord_uv.y)<=2/iResolution.y)
    {
        if(abs(uv.x-coord_uv.x)<=1/iResolution.x&&abs(uv.y-coord_uv.y)<=1/iResolution.y)
        {
         fColor=vec4(trans_code(code)/255.0,code1/255);

        }
        else
        {
            fColor=vec4(trans_code(code)/255.0,code1/255);
        }
    
    }
   
  
    //i_color();
   //fColor=texture(ourTexture,TexCoord);
    //fColor=vec4(0.0,0.5,0.4,1.0);
}
