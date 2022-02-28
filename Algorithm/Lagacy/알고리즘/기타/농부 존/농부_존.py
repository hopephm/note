T_i = []

work = int(input())

for i in range(work):
    temp1, temp2 = map(int, input().split())
    T_i.append([temp2,temp1])

T_i.sort()

temp = T_i[work-1][0]
for i in reversed(range(1,work)):
    if (temp - T_i[i][1]) < T_i[i-1][0]:
        temp = (temp - T_i[i][1])
    else:
        temp = T_i[i-1][0]

if(temp - T_i[0][1] < 0) : print(-1)
else : print(temp - T_i[0][1])