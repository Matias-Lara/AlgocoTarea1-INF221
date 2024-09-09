import random

def generate_random_list(N):
    random_list = [random.randint(1, N + 1) for _ in range(N)]
    return random_list

def generate_ordered_list(N):
    ordered_list = list(range(1, N + 1))
    return ordered_list

def generate_peak_list(N):
    peak = N // 2
    return list(range(1, peak + 1)) + list(range(peak, 0, -1))

def generate_repeated_value_list(N, percentage):
    repeated_value = random.randint(1, N + 1)
    repeated_count = int(N * percentage)
    other_count = N - repeated_count
    repeated_list = [repeated_value] * repeated_count + [random.randint(1, N + 1) for _ in range(other_count)]
    random.shuffle(repeated_list)
    return repeated_list


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

    #6 arreglos con numeros ordenados en forma de pico creciendo en potencias de 10
    #(crecen hasta el elemento central y decrecen hasta el ultimo elemento)
    for i in range(1, 7):
        peak_list = generate_peak_list(10**i)
        file.write(f"{peak_list}\n")  
    
    
    #6 arreglos con el 50% de los valores repetidos (valor 40) creciendo en potencias de 10
    for i in range(1, 7):
        repeated_list = generate_repeated_value_list(10**i, 0.15) 
        file.write(f"{repeated_list}\n")  
