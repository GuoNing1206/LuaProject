function printx(x)
  print(string.format("0x%X", x))
end

function Init()
	for k, v in pairs(gl) do
		print(k, v)
	end
  printx(bit32.band(0xDF, 0xFD))
  print(type(math))
end

function Rend()
	gl.glDisable(gl.GL_LIGHTING);
	gl.glClear(gl.GL_COLOR_BUFFER_BIT);

	for i = -1, 1, 0.2 do
		for j = -1, 1, 0.2 do
			gl.glColor3f(i/2+0.5, j/2+0.5, a);
			gl.glPushMatrix();
			gl.glTranslatef(i, j, 0);
			gl.glRotatef(45, 0, 1, 0);
			gl.auxWireSphere((i/2+0.5 + j/2+0.5)/20);
			gl.glPopMatrix();
		end
	end
	
	gl.glPushMatrix();
	gl.glRotatef(45, 0, 0, 1);
	gl.glPointSize(3);
	gl.glBegin(gl.GL_POINTS);
	for i = -1, 1, 0.2 do
		for j = -1, 1, 0.2 do
			gl.glColor3f(i/2+0.5, j/2+0.5, 0);
			gl.glVertex3f(i, j, 0);
		end
	end
	gl.glEnd();
	gl.glPopMatrix();
	
	gl.glPushMatrix();
	gl.glColor3f(0, .5, 1)
	gl.glRotatef(45, 0, 1, 0);
	gl.auxWireSphere(1);
	gl.glPopMatrix();
end
