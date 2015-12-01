uniform sampler2D texture;
varying vec3 normals;

void main( void ) {
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    if( pixel.r + pixel.g + pixel.b <= 2.0)
        gl_FragColor = vec4(1.0,1.0,1.0,0.0);
    else
        gl_FragColor = vec4(normals.x ,normals.y ,normals.z ,1.0);
}