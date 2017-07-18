precision mediump float;

varying vec3 v_coord;

uniform samplerCube u_texture0;

void main()
{
		//gl_FragColor = vec4(v_color,1.0);
		//gl_FragColor = vec4(1.0, 0.0 ,0.0 ,1.0);
		vec4 color = textureCube(u_texture0, v_coord);
		//if( color.a < 0.5 )
		//	discard;
		
		gl_FragColor = vec4(color.rgb,1.0);
		//gl_FragColor = vec4(v_uv.x,v_uv.y,0.0,1.0);
		//gl_FragColor = vec4(v_pos.x,v_pos.y,v_pos.z,1.0);
		//gl_FragColor  = vec4(1.0,0.0,0.0,1.0);

}
