precision mediump float;

varying vec2 v_uv;
varying vec3 v_norm;

uniform vec3 u_fog;
uniform vec3 u_camera;
uniform float u_r;
uniform float u_R;

uniform sampler2D u_texture0;

varying vec3 v_position;

uniform float u_shininess;
uniform vec3 u_ambient;

struct directionalLight {
    vec3 direction;
  
    vec3 diffuse;
    vec3 specular;
	float specCoef;
};

uniform directionalLight u_dirLight;

void main()
{
	//gl_FragColor = vec4(v_color,1.0);
	//gl_FragColor = vec4(1.0, 0.0 ,0.0 ,1.0);
	vec4 color = texture2D(u_texture0, v_uv);
	//if( color.a < 0.5 )
	//	discard;
	float dist = (distance(u_camera, v_position)-u_r)/(u_R - u_r);
	float alpha = clamp(dist, 0.0, 1.0);

	vec4 c_final = color;

	//c_final.rgb = vec4(u_fog*alpha,1.0).rgb + ((1.0-alpha)*c_final).rgb;

	vec3 L = normalize(u_dirLight.direction);
	vec3 N = normalize(v_norm);
	vec3 R = normalize(reflect(L,N));
	vec3 E = normalize(v_position-u_camera);

	vec3 comp_amp = c_final.rgb * u_ambient;
	vec3 comp_diff = c_final.rgb * u_dirLight.diffuse * max(dot(N,-L),0.0);
	vec3 comp_spec = u_dirLight.specular * u_dirLight.specCoef * pow(max(dot(R,E),0.0), u_shininess);
	
	c_final.rgb = comp_amp + comp_diff + comp_spec;

	c_final.rgb = vec4(u_fog*alpha,1.0).rgb + ((1.0-alpha)*c_final).rgb;

	gl_FragColor = c_final;

	//gl_FragColor = vec4(v_uv.x,v_uv.y,0.0,1.0);
	//gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}
