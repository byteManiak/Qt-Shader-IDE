# Qt Shader IDE
This is a GLSL shader IDE that I'm writing in Qt (and thus, inherently, C++) and a bit of OpenGL, mostly for educational purposes.

While the IDE only supports OpenGL 3.3 core profile for now, I will try to add support for multiple versions, including OpenGL 4.5.

## To do
- [x] Add ability to manage .glsl files.
- [ ] Add ability to change fonts.
- [x] Syntax highlighting.
- [x] Basic error checking.
- [x] UI cleanup.
- [x] Implement ```time``` uniform.
- [x] Implement ```resolution``` uniform.
- [ ] Implement ```mouse``` uniform.
- [x] Textures in fragment shader.
- [ ] ```Help``` section.
- [ ] Text formatting features.

~~Doesn't work properly on Windows yet. GL context is blank on most test machines. Need to do more debugging.~~
With the new GL context code, the project works mostly fine on Windows.
