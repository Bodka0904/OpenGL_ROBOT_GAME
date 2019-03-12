#version 120

varying vec2 texCoord0;
varying vec3 normal0;


uniform sampler2D diffuse;
uniform vec3 uColor;

void main()
{
	if(texCoord0 == vec2(0,0))
	{
		gl_FragColor = vec4(uColor, 1.0);
	}
	else
	{
		gl_FragColor = texture2D(diffuse,texCoord0) 
			*clamp(dot(-vec3(0,0,1), normal0),0.0,1.0) * 4;
	}
}