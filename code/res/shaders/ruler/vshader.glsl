#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec2 vertexPos;
varying vec2 coords;

void main()
{
    gl_Position = vec4(vertexPos,0.0,1.0);

    if(vertexPos.x < 0.0) coords.x = 0.0;
    else coords.x = 1.0;
    if(vertexPos.y < 0.0) coords.y = 0.0;
    else coords.y = 1.0;

}

