attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec2 a_uv;
attribute vec3 a_norm;

varying vec3 v_color;
varying vec2 v_uv;
varying vec3 v_norm;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 P;

uniform mat4 u_model;
varying vec3 v_position;

void main()
{
	v_position = (u_model * vec4(a_posL,1.0)).xyz;

	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = MVP * posL;
	v_color = a_color;
	v_uv = a_uv;

	v_norm = a_norm;
}
   