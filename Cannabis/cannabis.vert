uniform float TWIST;

void main()
{
	float ANGLE = gl_Vertex.x * TWIST;

	float radius = (1.f + sin(ANGLE))
					* (1.f + 0.9f * cos(8.f * ANGLE))
					* (1.f + 0.1f * cos(24.f * ANGLE));
	 /*
      Rotate vertex around Y axis:
      x' = x * cos(angle) - z * sin(angle)
      y' = y;
      z' = x * sin(angle) + z * cos(angle);
      w' = w;
    */
    vec4 twistedCoord = vec4(
		gl_Vertex.x + radius * cos(ANGLE),
        gl_Vertex.y + radius * sin(ANGLE),
        gl_Vertex.z,
        gl_Vertex.w
    );
    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
