#version 400

out vec4 frag_color;
vec4 pos;

void main () {
  pos = gl_FragCoord;
  frag_color = vec4(mod(pos.x,100)/100.0, 0.0, 0.0, 1.0);
}

