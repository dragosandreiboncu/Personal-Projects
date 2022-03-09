import base64

def _chunks(string, chunk_size):
    for i in range(0, len(string), chunk_size):
        yield string[i:i+chunk_size]
 
def hex_2_str(data):
    return ''.join(chr(int(x, 16)) for x in _chunks(data, 2))

def bitxor(a, b):
    return [x ^ y for (x, y) in zip(a, b)]
    
def string_to_bytes(string_data):
    return string_data.encode()
    
def bytes_to_string(string_data):
    return string_data.decode()
