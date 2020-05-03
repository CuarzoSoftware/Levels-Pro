#ifdef GL_ES
// Set default precision to medium
precision lowp int;
precision mediump float;
#endif

uniform vec3 backgroundColor;
uniform float barSize;
uniform float beats;
uniform float xScroll;
varying vec2 coords;


bool inRange(float rest, float range)
{
    if(rest <= range)
        return true;

    return false;
}
void main()
{

    vec2 crds = gl_FragCoord.xy - 0.5 + vec2(xScroll,0.0);
    // Border bottom
    if(crds.y == 0.0)
    {
        gl_FragColor = vec4(0.109, 0.109, 0.109, 1.0);
        return;
    }


    // Bar line
    float rest = mod(crds.x,barSize);
    if(!inRange(mod(crds.x-1.0,barSize),1.0) && inRange(rest,1.0))
    {
        gl_FragColor = vec4(0.396, 0.392, 0.396, 1.0);
        return;
    }


    // Beat line
    rest = mod(crds.x,barSize/beats);
    if(!inRange(mod(crds.x-1.0,barSize),4.0) && !inRange(mod(crds.x - 1.0,barSize/beats),1.0) && inRange(rest,1.0) && coords.y <= 0.5)
    {
        gl_FragColor = vec4(0.396, 0.392, 0.396, 1.0);
        return;
    }


    // Background
    else
    {
       gl_FragColor = vec4(backgroundColor, 1.0);
    }



}

