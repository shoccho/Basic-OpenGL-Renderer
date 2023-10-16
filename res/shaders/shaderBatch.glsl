#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;

out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * vec4(position, 1.0f);
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
}

#shader fragment
#version 410 core

out vec4 color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform float u_dt;
uniform sampler2D u_Textures[2];

void main(){
    int indx = int(v_TexIndex);
    vec4 texColor = texture(u_Textures[indx], v_TexCoord);
    vec4 randColor = vec4(abs(cos(u_dt)),abs(tan(u_dt)),abs(sin(u_dt)),1);
    color = texColor*randColor;
}
