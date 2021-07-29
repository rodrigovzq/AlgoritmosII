'''
Escribir en psudocodigo una funcion que reciba una cantidad de dados *n* y una suma *s*. La funcion debe imprimir todas las tiradas posibles con n dados cuya suma sea s. Por ejemplo con n=2 y s=7, debe imprimir [1,6],[2,5].[3,4],[4,3],[5,2],[6,1]
- Que tecnica algoritmica uso?
- de que orden es el algoritmo en tiempo y memoria?
'''

def dados(n,s,solucion_parcial):
	if n == 0:
		if sum(solucion_parcial) == s:
			return [solucion_parcial]
		else:
			return []
	restante = sum(solucion_parcial) - s
	if restante < n or restante > 6*n:
		return []
	soluciones = []
	
	for i in range(1,7):
		solucion_actual = copia(solucion_parcial)
		solucion_actual.append(i)
		soluciones.agregar_todas(dados(n-1),s,solucion_parcial)
	return soluciones
	

				
	