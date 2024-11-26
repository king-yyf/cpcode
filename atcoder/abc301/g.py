n = int(input())
points = []
for i in range(n):
    x, y, z = map(int, input().split())
    points.append((x, y, z))

visible = [0] * n  # keeps track of how many people are visible for each x value
for i in range(1, n):  # iterate over all people and find visible points for each x
    for x in range(-points[i][0], points[i][0]):  # iterate over all possible x values
        obstructed = False  # assume current x is not obstructed by default
        for j in range(i):  # check all points to the left of current point
            if points[j][0] >= x or (points[j][1] - points[i][1]) * (points[j][2] - points[i][2]) < 0:
                # point j is already to the right of x or blocks line of sight
                continue
            if obstructed or (points[j][1] - points[i][1]) / (points[j][0] - points[i][0]) == (points[i][2] - points[j][2]) / (points[i][0] - points[j][0]):
                # point j blocks line of sight or is on same line as previous point
                obstructed = True
                break
        if not obstructed:
            visible[x + points[i][0]] += 1  # mark point as visible

print(min(visible))  # choose x with minimum visible points


You will choose a point p=(x,y,z) such that x<0, and take a photo in the positive x-direction. If the point p and the positions 
A,B of two people are on the same line in the order  p,A,B, then the person at B will not be in the photo. Find the number of people in the photo when 
p is chosen to minimize this number.