#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

out vec4 color;
in vec2 v_TexCoord;

uniform float u_dt;
uniform sampler2D u_Texture;

void main(){
    vec4 texColor = texture(u_Texture, v_TexCoord);
    vec4 randColor = vec4(abs(cos(u_dt)),abs(tan(u_dt)),abs(sin(u_dt)),1);
    color = texColor*randColor;
}
