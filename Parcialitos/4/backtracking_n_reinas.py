'''
Implemente en pseudocodigo de un algoritmo de backtracking que resuelva el problema de las 8 reinas (colocar 8 reinas en un tablero de 8x8 de manera que no se amenacen entre ellas). Puede considerar que ya se posee la funcion es_valida() que recibe una solucion parcial e indica si la misma es valida.

Ayuda: puede representarse la solucion con un arrelo. Ejemplo: [4,6,8,2,7,1,3,5]
indica que las reinas fueron colocadas en las posiciones [(1,4),(2,6),(3,8),...]
'''

def n_reinas(tablero, fila,n):
	#Caso base es donde las reinas ya fueron ubicadas
	if fila == n:
		return es_valida(tablero,n)
	# Chequeo si la opcion elegida es valida o no
	# Puedo meter esa condicion antes de realizar el paso tablero[fila][col]=1
	if not es_valida(tablero,n):
		return False
	
	for col in range(n):
		tablero[fila][col]=1
		# Llamo recursivamente para mirar todas las opciones disponibles a partir de la nueva reina posicionada
		if n_reinas(tablero, fila+1,n):
			return True
		else:
			# Bakctrack
			tablero[fila][col]=0
	return False