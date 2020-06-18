#version 330 core

out vec4 FragColor;

uniform sampler2D TextureSampler;

uniform vec4 TargetColor;
uniform vec4 ReplaceColor;

in vec4 Color;
in vec2 TextureCoordinates;

void main()
{
   vec4 sampled = texture(TextureSampler, TextureCoordinates);
   if (sampled.rgb == TargetColor.rgb)
      FragColor = vec4(ReplaceColor.rgb, sampled.a) * Color;
   else
      FragColor = sampled * Color;
}