# Introduction à OpenGL: Matériel pour la formation
![alt text](screen.png "kom c bo")

## Slides

Disponibles au format ODT dans ce repo

## Traces RenderDoc

Trop lourdes pour aller sur github, elles sont dispo sur
http://xol.io/random/traces

## Exemples de code

### Compilation sous Linux (Debian & dérivés)

Dépendances: 

 * Sur une debian fraiche: `apt install build-essential libglfw-dev libglew-dev libglew-dbg`

Pour chaque exemple, se placer dans son répertoire ( `cd 0Xmachintruc` ), et taper `make`.
`./demo` lance l'application
	
### Compilation des exemples sous Windows

Dépendances: 

 * mingw-64 (fourni gcc, make)
 * glfw3, glew, headers opengl à copier dans le dossier d'installation de mingw-64
	
TODO: tester sur une machine et tout installer from scratch

Pour chaque exemple, se placer dans son répertoire ( `cd 0Xmachintruc` ), et taper `mingw32-make`.
`./demo.exe` lance l'application
