//#version 130
//#extension GL_ARB_texture_gather : enable
uniform sampler2D texture;
varying vec2 texCoord;
varying vec2 offsetCoord;

void main(){
	float neighbors;
	neighbors  = textureOffset(texture, texCoord, ivec2(1, -1)).r;
//	neighbors += textureOffset(texture, texCoord, ivec2(1,  0)).r; // grabbed by textureGather
//	neighbors += textureOffset(texture, texCoord, ivec2(1,  1)).r; // grabbed by textureGather
//	neighbors += textureOffset(texture, texCoord, ivec2(0, -1)).r; // grabbed by textureGatherOffset
//	neighbors += textureOffset(texture, texCoord, ivec2(0,  1)).r; // grabbed by textureGather
//	neighbors += textureOffset(texture, texCoord, ivec2(-1,-1)).r; // grabbed by textureGatherOffset
//	neighbors += textureOffset(texture, texCoord, ivec2(-1, 0)).r; // grabbed by textureGatherOffset
	neighbors += textureOffset(texture, texCoord, ivec2(-1, 1)).r;


	vec4 tempvec;
	tempvec = textureGather(texture, offsetCoord);
	neighbors += tempvec.x;
//	neighbors += tempvec.y;
	neighbors += tempvec.z;
	neighbors += tempvec.w;


	tempvec = textureGather(texture, texCoord);
	neighbors += tempvec.x;
	neighbors += tempvec.y;
	neighbors += tempvec.z;
//	neighbors += tempvec.w;
//	gl_FragColor.r = tempvec.w; // carried life


//WIP






//	gl_FragColor.r = tempvec.w; // carried life
//	gl_FragColor.r += step(3.0, neighbors); //added life if under 3
//	gl_FragColor.r *= step(2.0, neighbors); //death if under 2
//	gl_FragColor.r *= step(neighbors, 3.0); // death if over 3

	if(neighbors == 2.0) gl_FragColor.r = tempvec.w; //carry if two
	else if(neighbors == 3.0) gl_FragColor.r = 1.0; //add life if one



}
