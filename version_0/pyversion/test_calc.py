nthreads = 4
from multiprocessing import Pool
import ctypes as ct
import time
import sys

def main():

    start = time.time()

    # ensure there is a correct number of args
    if(len(sys.argv) != 3):
        print("Too many or too little arguments.")
        return 1

    # import associated .c files
    calculator = ct.CDLL("../calculate.so")
    array_generator = ct.CDLL("../array_generator.so")
    free = ct.CDLL("free_me.so")
    printer = ct.CDLL("print_me.so")

    # get size from param2
    size = int(sys.argv[2])


    # specify types ---------------------------------------------------------
    # calculator
    # calculate -> void | int **, int, long[5], int, int
    calculator.calculate.restype = None
    calculator.calculate.argtypes = [ct.POINTER(ct.POINTER(ct.c_int)), ct.c_int, ct.POINTER(ct.c_long), ct.c_int, ct.c_int]

    # array_generator
    # allocate_grid -> int ** | char *, int
    array_generator.allocate_grid.restype = ct.POINTER(ct.POINTER(ct.c_int * size * size))
    array_generator.allocate_grid.argtypes = [ct.c_wchar_p, ct.c_int]
    # allocate_array_3d -> long *** | int
    array_generator.allocate_array_3d.restype = ct.POINTER(ct.POINTER(ct.POINTER(ct.c_long * size * size * 5)))
    array_generator.allocate_array_3d.argtypes = [ct.c_int]

    #free
    #free_me_2d -> void | int **
    free.free_me_2d.restype = None
    free.free_me_2d.argtypes = [ct.POINTER(ct.POINTER(ct.c_int))]
    #free_me_3d -> void | long ***
    free.free_me_3d.restype = None
    free.free_me_3d.argtypes = [ct.POINTER(ct.POINTER(ct.POINTER(ct.c_long)))]
    # -----------------------------------------------------------------------


    # create useful arrays
    # int **
    numbers = (ct.POINTER(ct.POINTER(ct.c_int * size * size)))()
    #numbers = array_generator.allocate_grid(ct.c_wchar_p(sys.argv[1]), size)
    numbersArray = [[8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8],
    [49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56, 62, 0],
    [81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13, 36, 65],
    [52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36, 91],
    [22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80],
    [24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50],
    [32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70],
    [67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21],
    [24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72],
    [21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95],
    [78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92],
    [16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57],
    [86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58],
    [19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40],
    [4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66],
    [88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69],
    [4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36],
    [20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16],
    [20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54],
    [1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48]]

    print(numbers)
    print(numbers[0])
    print(numbers[0][0])
    for i in range(size):
        for j in range(size):
            numbers[i][j] = numbersArray[i][j]

    print("2D - 1")
    for i in range(size):
        print("ROW " + str(i) + ": [", end="")
        for j in range(size - 1):
            print(str(numbers[i][j]) + ", ", end="")
        print(str(numbers[i][size - 1]) + "]")

    # long ***
    #answer = (ct.c_long * size * size * 5)()
    answer = array_generator.allocate_array_3d(size)

    #for i in range(size)

    print("starting")
    print(numbers)
    print(numbers[0])
    print(numbers[0][0])
    print(ct.cast(numbers, ct.POINTER(ct.POINTER(ct.c_int))))
    print(ct.cast(numbers, ct.POINTER(ct.POINTER(ct.c_int)))[0])
    print(ct.cast(numbers, ct.POINTER(ct.POINTER(ct.c_int)))[0].contents)
    # check array
    for i in range(size):
        for j in range(size):
            calculator.calculate(ct.cast(numbers, ct.POINTER(ct.POINTER(ct.c_int))), size, ct.cast(answer[i][j], ct.POINTER(ct.c_long)), i, j)

    print("2D - 1")
    for i in range(size):
        print("ROW " + str(i) + ": [", end="")
        for j in range(size - 1):
            print(str(ct.cast(numbers, ct.POINTER(ct.c_int))[i * size + j]) + ", ", end="")
        print(str(ct.cast(numbers, ct.POINTER(ct.c_int))[i * size + (size - 1)]) + "]")

    #print("3D")
    #for i in range(size):
    #    print("ROW " + str(i) + ": [", end="")
    #    for j in range(size):
    #        print("COL " + str(j) + ": [", end="")
    #        for k in range(4):
    #            print(str(answer[i][j][k]) + ", ", end="")
    #        print(str(answer[i][j][4]) + "], ", end="")
    #    print("[" + str(answer[i][j][0]) + str(answer[i][j][1]) + str(answer[i][j][2]) + str(answer[i][j][3]) + str(answer[i][j][4]) + "]]")

    # determine and print biggest value
    printer.print_me(answer, size)

    end = time.time()

    # print time to run program
    print("Time it took this process to run:\n    " + str((end - start)))

    # free the malloc'ed memory
    free.free_me_2d(ct.cast(numbers, ct.POINTER(ct.POINTER(ct.c_int))))
    free.free_me_3d(ct.cast(answer, ct.POINTER(ct.POINTER(ct.POINTER(ct.c_long)))))

if __name__ == "__main__":
    main()
    exit()
