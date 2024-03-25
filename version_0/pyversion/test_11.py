nthreads = 4
from multiprocessing import Pool
from ctypes import *
import time

def main():

    #need to import .c file
    imported = CDLL("./11_1_advanced.so")

    stuff = imported.main()

    #with Pool(nthreads) as p:
    #    p.map()

if __name__ == "__main__":
    main()
    exit()
