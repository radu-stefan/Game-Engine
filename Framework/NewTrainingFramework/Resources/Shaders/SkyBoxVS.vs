attribute vec3 a_posL;

varying vec3 v_pos;
varying vec3 v_coord;

uniform mat4 MVP;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = MVP * posL;

	v_coord = a_posL;
}
   