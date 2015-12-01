varying vec3 normals;

void main(void)
{
gl_TexCoord[0] = gl_MultiTexCoord0;
normals = normalize(gl_Normal);
gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

} 