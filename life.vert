varying vec2 texCoord;
void main(){
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; //The order in which you times matrices and vertices is IMPORTANT.
	gl_Position = gl_Vertex; // faster... dont need the viewprojection anyway
    	texCoord = gl_MultiTexCoord0.xy;
}
