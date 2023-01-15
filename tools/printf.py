digits = "0123456789"

number = 576001

buff = list()
num_digits = 0
while number >= 10:
    num_digits += 1
    buff.append(digits[number % 10])
    number = number // 10
num_digits += 1
buff.append(digits[number % 10])
temp = 0
for n in range(num_digits):
    print(buff)
    temp = buff[n]
    buff[n] = buff[num_digits - n - 1]
    buff[num_digits - n - 1] = temp
    if((num_digits  -  1)// 2 == n):
        break
    # num_digits -= 1
print(buff)

