# version 330 core

layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

void main(){
	vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(512,384); 
	vertexPosition_homoneneousspace /= vec2(512,384);
	gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);
	
	UV = vertexUV * vec2(1.0, -1.0);
}
