#version 330 core

out vec4 FragColor;

uniform sampler2D TextureSampler;
in vec4 Color;
in vec2 TextureCoordinates;

void main()
{
//   FragColor = texture(TextureSampler, TextureCoordinates) * Color;
   FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}