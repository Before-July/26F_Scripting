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
//	uv.x += u_time;
//	vec4 finalColor = vec4( u_percentage, v_uv.x, 0.5, 1.0);
	vec4 color  = texture2D( u_texture, uv);
	vec4 color1  = texture2D( u_texture2, uv);

//	color1 = step(color1.z * sin(u_time),0.5);

	float a = sin(u_time);

	vec4 finalColor = ( 1- color);

	if (color1.x < u_percentage)
		
		discard;

	if (color1.x < u_percentage + 0.05)
		finalColor = vec4(1,1,1,1);
		

	gl_FragColor = finalColor;
}
