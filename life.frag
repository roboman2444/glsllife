uniform sampler2D texture;
varying vec2 texCoord;
varying vec2 offsetCoord;

void main(){
	int neighbors;
	neighbors  = textureOffset(texture, texCoord, ivec2(1, -1)).r;
//	neighbors += textureOffset(texture, texCoord, ivec2(1,  0)).r; // grabbed by textureGather
//	neighbors += textureOffset(texture, texCoord, ivec2(1,  1)).r; // grabbed by textureGather
//	neighbors += textureOffset(texture, texCoord, ivec2(0, -1)).r; // grabbed by textureGatherOffset
//	neighbors += textureOffset(texture, texCoord, ivec2(0,  1)).r; // grabbed by textureGather
//	neighbors += textureOffset(texture, texCoord, ivec2(-1,-1)).r; // grabbed by textureGatherOffset
//	neighbors += textureOffset(texture, texCoord, ivec2(-1, 0)).r; // grabbed by textureGatherOffset
	neighbors += textureOffset(texture, texCoord, ivec2(-1, 1)).r;


	vec4 tempvec;
	tempvec = textureGather(texture, texCoord);
	neighbors += tempvec.x;
	neighbors += tempvec.y;
	neighbors += tempvec.z;
//	neighbors += tempvec.w;
	gl_FragColor.r = tempvec.w; // carried life


//WIP
	tempvec = textureGather(texture, offsetCoord);
	neighbors += tempvec.x;
//	neighbors += tempvec.y;
	neighbors += tempvec.z;
	neighbors += tempvec.w;




/*//needs ogl 4, todo checks and todo do
	tempvec = textureGatherOffset(texture, texCoord, ivec2(-1.-1));
	neighbors += tempvec.x;
//	neighbors += tempvec.y;
	neighbors += tempvec.z;
	neighbors += tempvec.w;
*/


//	gl_FragColor.r = texture2D(texture, texCoord); // carried life grabbed by textureGather

	gl_FragColor.r += step(3, neighbors); //added life if under 3

	gl_FragColor.r *= step(2, neighbors); //death if under 2
	gl_FragColor.r *= step(neighbors, 3); // death if over 3

}
