uniform sampler2D texture;
varying vec2 texCoord;

void main(){
	int neighbors;
	neighbors  = texture2D(texture, texCoord + vec2(0.00125, 0.00166666666)).r;
	neighbors += texture2D(texture, texCoord + vec2(0.00125, 0.0)		).r;
	neighbors += texture2D(texture, texCoord + vec2(0.00125,-0.00166666666)).r;
	neighbors += texture2D(texture, texCoord + vec2(0.0, 	  0.00166666666)).r;
	neighbors += texture2D(texture, texCoord + vec2(0.0, 	 -0.00166666666)).r;
	neighbors += texture2D(texture, texCoord + vec2(-0.00125,0.00166666666)).r;
	neighbors += texture2D(texture, texCoord + vec2(-0.00125,0.0)		).r;
	neighbors += texture2D(texture, texCoord + vec2(-0.00125,-0.00166666666)).r;

	gl_FragColor.r = texture2D(texture, texCoord);
	gl_FragColor.r += step(3, neighbors);
	gl_FragColor.r *= step(2, neighbors);
//	gl_FragColor.r *= 1-step(4, neighbors);
	gl_FragColor.r *= step(neighbors, 3);
//	gl_FragColor.r += step(6, neighbors);
//	gl_FragColor.r *= step(neighbors, 6);

}
