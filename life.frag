uniform sampler2D texture;
varying vec2 texCoord;
//varying vec2 neighborCoord[8];

void main(){
	int neighbors;
/*
	neighbors  = texture2D(texture, neighborCoord[0]).r;
	neighbors += texture2D(texture, neighborCoord[1]).r;
	neighbors += texture2D(texture, neighborCoord[2]).r;
	neighbors += texture2D(texture, neighborCoord[3]).r;
	neighbors += texture2D(texture, neighborCoord[4]).r;
	neighbors += texture2D(texture, neighborCoord[5]).r;
	neighbors += texture2D(texture, neighborCoord[6]).r;
	neighbors += texture2D(texture, neighborCoord[7]).r;

*/
	neighbors  = textureOffset(texture, texCoord, ivec2(1, -1)).r;
	neighbors += textureOffset(texture, texCoord, ivec2(1,  0)).r;
	neighbors += textureOffset(texture, texCoord, ivec2(1,  1)).r;
	neighbors += textureOffset(texture, texCoord, ivec2(0, -1)).r;
	neighbors += textureOffset(texture, texCoord, ivec2(0,  1)).r;
	neighbors += textureOffset(texture, texCoord, ivec2(-1,-1)).r;
	neighbors += textureOffset(texture, texCoord, ivec2(-1, 0)).r;
	neighbors += textureOffset(texture, texCoord, ivec2(-1, 1)).r;

	gl_FragColor.r = texture2D(texture, texCoord); // carried life

	gl_FragColor.r += step(3, neighbors); //added life if under 3

	gl_FragColor.r *= step(2, neighbors); //death if under 2
	gl_FragColor.r *= step(neighbors, 3); // death if over 3

}
