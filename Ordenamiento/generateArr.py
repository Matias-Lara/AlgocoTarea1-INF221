import random

def generate_random_list(N):
    random_list = [random.randint(1, 100) for _ in range(N)]
    return random_list

def generate_ordered_list(N):
    ordered_list = list(range(1, N + 1))
    return ordered_list

#Archivo en modo write
with open("inputSort.txt", "w") as file:
    #6 arreglos aleatorios creciendo en potencias de 10
    for i in range(1, 7):
        random_list = generate_random_list(10**i) 
        file.write(f"{random_list}\n")  
    
    #6 arreglos ordenados creciendo en potencias de 10
    for i in range(1, 7):
        ordered_list = generate_ordered_list(10**i)  
        file.write(f"{ordered_list}\n")  
    