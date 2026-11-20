// glsl
varying vec4 v_color; // input
varying vec2 v_uv;

uniform sampler2D u_texture;
uniform sampler2D u_texture2;
uniform vec3 u_color;
uniform float u_time;
uniform float u_percentage;

void main()
{
	vec2 uv = v_uv;

	//vec4 finalColor = vec4( u_percentage, 0.0, 0.0, 1.0 );

	vec4 color1 = texture2D( u_texture, uv );
	vec4 color2 = texture2D( u_texture2, uv );

//	vec4 finalColor = color1 * (1 - u_percentage) +
//	                  color2 * (u_percentage);

	vec4 finalColor = color1;
	if( color2.r < u_percentage )
		discard;

	if( color2.r < u_percentage + 0.05 )
		finalColor = vec4( 1, 0, 0, 1 );

	gl_FragColor = finalColor;
}
