import random
file = open("testing_data.txt", "w")
n = 1000
max_word_len = 10
string = ''
a_code = ord('a')
z_code = ord('z')

for i in range(n):
    word_len = random.random()*max_word_len + 1
    string = ""
    for j in range(int(word_len)):
        sym = random.random()*(z_code - a_code) + a_code
        string = string + chr(int(sym))
    file.write(string + " ")
file.close()
