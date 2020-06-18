#version 330 core

layout(location = 0) in vec2 VertexPos;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 VertexTextureCoordinates;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec4 Color;
out vec2 TextureCoordinates;

void main()
{
   gl_Position = Projection * View * Model * vec4(VertexPos, 0.0, 1.0);
   Color = VertexColor;
   TextureCoordinates = VertexTextureCoordinates;
}