from cs50 import get_float

while True:
    amount = get_float("Change owed : ")
    if amount >= 0:
        break
sum = 0
x = round(amount * 100)
dom = [25, 10, 5, 1]

for i in range(len(dom)):
    sum += x // dom[i]
    x -= (x // dom[i]) * dom[i]
print(sum)
