#version 330 core

out vec4 FragColor;

uniform sampler2D samplerTexture;
in vec4 Color;
in vec2 TextureCoordinates;

void main()
{
   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(samplerTexture, TextureCoordinates).r);
   FragColor = Color * sampled;
}