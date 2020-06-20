#version 330 core

layout(origin_upper_left) in vec4 gl_FragCoord;

out vec4 FragColor;

uniform vec2 WindowSize;

const float sunRadius = 40.0;
const float solarRadius = 700.0;
const float orbitLineThickness = 1;

// To Improve by UBO (probably)
uniform vec4 PlanetsColor[9];
uniform float PlanetsRadius[9];
uniform float PlanetsDistance[9];
uniform float PlanetsAngle[9];
uniform int hoveredPlanet;

in vec4 Color;

void main()
{
   float distanceFromCenter = length(gl_FragCoord);
   float angle = degrees(asin(gl_FragCoord.y / distanceFromCenter));
   float lightFactor = 1.0 - distanceFromCenter / solarRadius;
   
   if (distanceFromCenter <= sunRadius)
      FragColor = vec4(0.8, 0.6, 0.0, 1.0);
   else
   {
      if (distanceFromCenter <= solarRadius)
         FragColor = Color + vec4(0.3 * lightFactor, 0.0, 0.6 * lightFactor, 1.0);
      else
         FragColor = Color;
      
      for (int i = 0; i < 9; ++i)
      {
         float distance = length(vec4((PlanetsDistance[i] * cos(radians(PlanetsAngle[i]))) - gl_FragCoord.x,
                                      (PlanetsDistance[i] * sin(radians(PlanetsAngle[i]))) - gl_FragCoord.y, 0.0, 1.0));
         if (distance <= PlanetsRadius[i])
            FragColor = PlanetsColor[i];
         else if (i == hoveredPlanet && distance <= PlanetsRadius[i] + 2)
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
         else if (distanceFromCenter >= PlanetsDistance[i] - (orbitLineThickness / 2)
               && distanceFromCenter <= PlanetsDistance[i] + (orbitLineThickness / 2)
               && mod(angle, 10) < 8
               && mod(angle, 10) > 2)
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
      }
   }
}