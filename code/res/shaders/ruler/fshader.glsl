#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform vec3 backgroundColor;
varying vec2 coords;

void main()
{

    vec2 crds = gl_FragCoord.xy + vec2(0.5,0.5);
    // Border bottom
    if(crds.y == 1.0)
    {
        gl_FragColor = vec4(0.109, 0.109, 0.109, 1.0);
        return;
    }

    float rest = mod(crds.x,30.0);
    // Verical lines
    if(rest == 0.0 && coords.y < 0.5)
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

