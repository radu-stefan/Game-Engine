attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv_blend;
attribute vec3 a_norm;

varying vec3 v_norm;
varying vec2 v_uv;
varying vec2 v_uv_blend;

uniform sampler2D u_texture0;
uniform vec3 u_height;
uniform mat4 MVP;
uniform vec2 u_uv_offset;

uniform mat4 u_model;
varying vec3 v_position;

void main()
{
	v_position = (u_model * vec4(a_posL,1.0)).xyz;
	
	vec4 c_blend = texture2D(u_texture0, a_uv_blend + u_uv_offset);

	vec4 posL = vec4(a_posL, 1.0);
	posL.y += c_blend.r * u_height.r + c_blend.g * u_height.g + c_blend.b * u_height.b;

	gl_Position = MVP * posL;

	v_norm = a_norm;
	v_uv = a_uv;
	v_uv_blend = a_uv_blend + u_uv_offset;
}
   