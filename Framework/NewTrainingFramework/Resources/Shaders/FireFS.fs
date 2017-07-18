precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

uniform float u_Time;
uniform float u_dispMax;

varying vec3 v_position;
uniform vec3 u_fog;
uniform vec3 u_camera;
uniform float u_r;
uniform float u_R;

void main()
{
	vec2 disp = texture2D(u_texture0, vec2(v_uv.x, v_uv.y + u_Time)).rg;

	vec2 offset = (disp*2.0-1.0)*u_dispMax;
	vec2 v_uv_displaced = v_uv + offset;
	vec4 c_fire = texture2D(u_texture1, v_uv_displaced);

	float c_alpha = texture2D(u_texture2, v_uv).r;
	
	vec4 c_final = vec4(c_fire.rgb,c_fire.a*c_alpha);

	float dist = (distance(u_camera, v_position)-u_r)/(u_R - u_r);
	float alpha = clamp(dist, 0.0, 1.0);

	/*if(c_final.a < 0.1)
	{
		discard;
	}*/
	c_final.rgb = vec4(u_fog*alpha,1.0).rgb + (1.0-alpha)*c_final.rgb;
	//c_final.a = c_fire.a;
	gl_FragColor = c_final;
	
}
