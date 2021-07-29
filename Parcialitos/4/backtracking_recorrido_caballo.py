'''
El problema del recorrido de un caballo de ajedrez consiste en indicar una serie de 64 movimientos para que un caballo
que se encuentra en una dada posicion del tablero pise todas las casillas sin repetir ninguna.
Escribir el psudocodigo de una funcion bool recorrido_del_caballo(a,x,y,i) que resuelva este problema usando backtracking sabiendo que:

- El parametro A es una matriz de enteros de 8x8.
- Los parametros x e y indican la posicion actual del caballo.
- i es el numero de paso actual.
- La funcion devuelve true o false si se encontro un recorrido o no.
- Se tiene una funcion obtener_movimientos(x,y) que dada la una posicon devuelve una lista con todos los movimientos posibles, descartando solo aquellos que se excedan del tablero.

Inicialmente la funcion se llama con A llena de ceros, algun par de puntes x e y (entre 0 y 8) e i igual a cero. Si la funcion devuelve treu debe completar la matriz con el orden en el cual se visita cada casilla.
'''
mov_final = 64
def recorrido_del_caballo(A,x,y,i):
	if i == mov_final:
		return True
	movimientos_posibles = obtener_movimientos(x,y)
	#Pruebo todos los movimientos posibles desde la posicion actual
	for pos in movimientos_posibles:
		x_pos, y_pos = pos
		# Si puedo moverme hacia esa posicion, lo hago
		if A[x,pos][y_pos] == 0:
			A[x,pos][y_pos] = i # Me muevo hacia la posicion
			i+=1 
			# Llamo recursivamente para la nueva posicion y pruebo todas las posibilidades. Hago backtrack si false
			if recorrido_del_caballo(A, x_pos, y_pos, i):
				return True
			else:
				#Backtrack
				i-=1
				A[x,pos][y_pos] = 0
	return True
				