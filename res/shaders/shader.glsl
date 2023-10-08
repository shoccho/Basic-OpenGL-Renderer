#shader vertex
#version 330 core

uniform float u_dt;

layout(location = 0) in vec4 position;
out float dt;

void main(){
    gl_Position = vec4(position.x, position.y,0,1);
    dt = u_dt;
};

#shader fragment
#version 330 core

out vec4 color;
in float dt;

void main(){
    color = vec4(abs(cos(dt)),abs(tan(dt)),abs(sin(dt)), 1);
};
