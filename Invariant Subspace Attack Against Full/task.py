# implementation of Midori64
import os
import random
from utils import *
import time

BLOCK_SIZE = 64
CELLS_SIZE = 4
KEY_SIZE = 128
ROUNDS = 16
S_Box0 = [
            b'\x00\x00\x00\x63', b'\x00\x00\x00\x61', b'\x00\x00\x00\x64', b'\x00\x00\x00\x33', b'\x00\x00\x00\x65', b'\x00\x00\x00\x62', 
            b'\x00\x00\x00\x66', b'\x00\x00\x00\x37', b'\x00\x00\x00\x38', b'\x00\x00\x00\x39', b'\x00\x00\x00\x31', 
            b'\x00\x00\x00\x35', b'\x00\x00\x00\x30', b'\x00\x00\x00\x32', b'\x00\x00\x00\x34', b'\x00\x00\x00\x36'
        ]

RKs = [ #a0
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31',
        #a1
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30',
        #a2
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31',
        #a3
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31',
        #a4
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31',
        #a5
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' +
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30',
        #a6
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30',
        #a7
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30',
        #a8
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31',
        #a9
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30',
        #a10
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31',
        #a11
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30',
        #a12
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' +
        b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30',
        #a13
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30',
        #a14
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x31' +
        b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x31' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30' + b'\x00\x00\x00\x30',
    ]
K_class = [b'\x00\x00\x00\x30' , b'\x00\x00\x00\x31']
S_class = [b'\x00\x00\x00\x38' , b'\x00\x00\x00\x39']

def key_add(s, key):
    next_s = [[] for _ in range(CELLS_SIZE)]
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            index = (j * CELLS_SIZE + i) * 4
            next_s[i].append(bytes(bitxor(s[i][j], key[index:index + 4])))
    return next_s


def sub_cell(s):
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            s[i][j] = S_Box0[j * CELLS_SIZE + i]
    return s

def sub_cell_attack(s):
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            if j * CELLS_SIZE + i == 8 or j * CELLS_SIZE + i == 9:
                s[i][j] = S_Box0[j * CELLS_SIZE + i]
    return s

def shuffle_cell(s):
    next_s = [[] for _ in range(CELLS_SIZE)]
    next_s[0] += [s[0][0], s[2][3], s[1][2], s[3][1]]
    next_s[1] += [s[2][2], s[0][1], s[3][0], s[1][3]]
    next_s[2] += [s[1][1], s[3][2], s[0][3], s[2][0]]
    next_s[3] += [s[3][3], s[1][0], s[2][1], s[0][2]]
    return next_s


def mix_column(s):
    next_s = [[[] for _ in range(CELLS_SIZE)] for _ in range(CELLS_SIZE)]
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            add_counter = 0
            for k in range(CELLS_SIZE):
                if i != k:
                    if add_counter == 0:
                        next_s[i][j] = s[k][j]
                    else:
                        next_s[i][j] = bytes(bitxor(next_s[i][j], s[k][j]))
                    add_counter += 1
    return next_s


def round_key(k0, k1, r):
    if r % 2 == 0:
        k = k0
    else:
        k = k1
    ai = RKs[r]
    RK = bytes(bitxor(k, ai))
    return RK


def midori64_encryption(plaintext, key):
    k0 = key[0:int(KEY_SIZE/2)]
    k1 = key[int(KEY_SIZE/2):int(KEY_SIZE)]
    WK = bytes(bitxor(k0, k1))

    # S <- P
    S = [[] for _ in range(CELLS_SIZE)]
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            index = (j * CELLS_SIZE + i) * 4
            S[i].append(plaintext[index:index + 4])

    S = key_add(S, WK)
    for r in range(ROUNDS-1):
        S = sub_cell(S)
        S = shuffle_cell(S)
        S = mix_column(S)
        S = key_add(S, round_key(k0, k1, r))
    S = sub_cell(S)
    S = key_add(S, WK)

    # C <- S
    ciphertext = [b'' for _ in range(BLOCK_SIZE)]
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            index = (j * CELLS_SIZE + i) * 4
            ciphertext[index:index + 4] = S[i][j]

    return bytes(ciphertext)



def midori64_invariant_attack(plaintext, key):
    k0 = key[0:int(KEY_SIZE/2)]
    k1 = key[int(KEY_SIZE/2):int(KEY_SIZE)]
    WK = bytes(bitxor(k0, k1))

    # S <- P
    S = [[] for _ in range(CELLS_SIZE)]
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            index = (j * CELLS_SIZE + i) * 4
            S[i].append(plaintext[index:index + 4])

    S = key_add(S, WK)
    for r in range(ROUNDS-1):
        S = sub_cell_attack(S)
        S = shuffle_cell(S)
        S = mix_column(S)
        S = key_add(S, round_key(k0, k1, r))
    S = sub_cell_attack(S)
    S = key_add(S, WK)

    # C <- S
    ciphertext = [b'' for _ in range(BLOCK_SIZE)]
    for i in range(CELLS_SIZE):
        for j in range(CELLS_SIZE):
            index = (j * CELLS_SIZE + i) * 4
            ciphertext[index:index + 4] = S[i][j]
    return bytes(ciphertext)


def find_key(plaintext, ciphertext, key, counter):
    if counter > int(KEY_SIZE/CELLS_SIZE):
        return b''
    ciphertext_found = midori64_invariant_attack(plaintext, key)
    if ciphertext == ciphertext_found:
        return key
    for i in range(int(KEY_SIZE/CELLS_SIZE)):
        continue_for = False
        new_key = b''
        for j in range(int(KEY_SIZE/CELLS_SIZE)):
            if i == j:
                byte = key[j * CELLS_SIZE: j * CELLS_SIZE + 4]
                if byte == K_class[1]:
                    continue_for = True
                new_key += K_class[1]
            else:
                new_key += key[j * CELLS_SIZE: j * CELLS_SIZE + 4]
        if continue_for is False:
            returned_key = find_key(plaintext, ciphertext, new_key, counter+1)
            if returned_key != b'':
                return returned_key
        else:
            return b''
    return b''


def main():
    print("Test algorithm:")
    key = os.urandom(KEY_SIZE)
    print("Key:")
    print(key)
    print("")
    plaintext = os.urandom(BLOCK_SIZE)
    print("Plaintext:")
    print(plaintext)
    print("")
    ciphertext = midori64_encryption(plaintext, key)
    print("Ciphertext:")
    print(ciphertext)
    print("")

    print("Test algorithm having small subspaces:")
    key = b''
    for _ in range(int(KEY_SIZE/CELLS_SIZE)):
        key += random.choice(K_class)
    print("Key0:")
    print(bytes_to_string(key[0:int(KEY_SIZE/2)]))
    print("Key1:")
    print(bytes_to_string(key[int(KEY_SIZE/2):int(KEY_SIZE)]))
    print("")
    plaintext = b''
    for _ in range(int(BLOCK_SIZE/CELLS_SIZE)):
        plaintext += random.choice(S_class)
    print("Plaintext:")
    print(bytes_to_string(plaintext))
    print("")
    ciphertext = midori64_invariant_attack(plaintext, key)
    print("Ciphertext:")
    print(bytes_to_string(ciphertext))
    print("")

    print("Find key having small subspaces:")
    key = b''
    indices = []
    number_of_1 = 2 #numarul de biti de 1 in cheie(conteaza la durata gasirii cheii corecte)
    for i in range(int(KEY_SIZE/CELLS_SIZE)):
        k = random.randint(0, 1)
        if k == 1:
            number_of_1-= 1
        if number_of_1 < 0:
            k = 0
        indices.append(k)
    for i in range(int(KEY_SIZE/CELLS_SIZE)):
        if indices[i] == 0:
            key += K_class[0]
        else:
            key += K_class[1]
    plaintext = b''
    for _ in range(int(BLOCK_SIZE/CELLS_SIZE)):
        plaintext += random.choice(S_class)
    ciphertext = midori64_invariant_attack(plaintext, key)
    print("Plaintext:")
    print(bytes_to_string(plaintext))
    print("")
    print("Ciphertext:")
    print(bytes_to_string(ciphertext))
    print("")
    print("Key given:")
    print(bytes_to_string(key))
    print("")
    key_found = b''
    start_time = time.time()
    for _ in range(int(KEY_SIZE/CELLS_SIZE)):
        key_found += K_class[0]
    ciphertext_found = midori64_invariant_attack(plaintext, key_found)
    if ciphertext != ciphertext_found:
        key_found = find_key(plaintext, ciphertext, key_found, 1)

    print("Key found:")
    print(bytes_to_string(key_found))
    print("")
    print("Key found in " + str(time.time() - start_time) + " seconds")

if __name__ == "__main__":
    main()
