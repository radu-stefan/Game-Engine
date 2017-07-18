attribute vec3 a_posL;
attribute vec2 a_uv;

varying vec2 v_uv;

uniform mat4 MVP;

//fog
uniform mat4 u_model;
varying vec3 v_position;

void main()
{
//fog
	v_position = (u_model * vec4(a_posL,1.0)).xyz;
	
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = MVP * posL;
	v_uv = a_uv;
}
   