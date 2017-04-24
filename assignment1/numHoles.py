def findFirst(pixels, num):
    for row in xrange(len(pixels)):
        for col in xrange(len(pixels[0])):
            if pixels[row][col] == num:
                return (row, col)
    return (-1,-1)

def isOnRightWall(pixels, location):
    (row, col) = location
    return col + 1 == len(pixels[0])

def isOnLeftWall(location):
    (row, col) = location
    return col == 0

def isOnTopWall(pixels, location):
    (row, col) = location
    return row + 1 == len(pixels)

def isOnBottomWall(location):
    (row, col) = location
    return row == 0

def isOnWall(pixels, location):
    return isOnBottomWall(location) or isOnTopWall(pixels, location) or isOnRightWall(pixels, location) or isOnLeftWall(location)

def findNextNum(pixels, current, num):
    (crow, ccol) = current
    # look right, up, left, then down

    if not isOnRightWall(pixels, current):
        if pixels[crow][ccol + 1] == num: # check right
            return (crow, ccol + 1)
        if not isOnTopWall(pixels, current): # top right
            if pixels[crow + 1][ccol + 1] == num:
                return (crow + 1, ccol + 1)

    if not isOnTopWall(pixels, current):
        if pixels[crow + 1][ccol] == num: # top
            return (crow + 1, ccol)
        if not isOnLeftWall(current):
            if pixels[crow + 1][ccol - 1] == num: # top left
                return (crow + 1, ccol - 1)

    if not isOnLeftWall(current):
        if pixels[crow][ccol - 1] == num: # left
            return (crow, ccol - 1)
        if not isOnBottomWall(current): # bottom left
            if pixels[crow - 1][ccol - 1] == num:
                return (crow - 1, ccol - 1)

    if not isOnBottomWall(current):
        if pixels[crow - 1][ccol] == num: # bottom
            return (crow - 1, ccol)
        if not isOnRightWall(pixels, current): # bottom right
            if pixels[crow - 1][ccol + 1] == num:
                return (crow - 1, ccol + 1)

    return (-1, -1)

def floodFill(pixels, start, fromnum, tonum):
    (frow, fcol) = start
    pixels[frow][fcol] = tonum
    (nrow, ncol) = findNextNum(pixels, (frow, fcol), fromnum)
    while nrow != -1:
        pixels[nrow][ncol] = tonum
        (nrow, ncol) = findNextNum(pixels, (nrow, ncol), fromnum)
    return pixels

def printarr(pixels):
    for i in pixels:
        print i
    print "--------------------"

def replaceAll(pixels, num, withNum):
    for row in xrange(len(pixels)):
        for col in xrange(len(pixels[0])):
            if pixels[row][col] == num:
                pixels[row][col] = withNum
    return pixels

def numberOfHoles(pixels):
    (frow, fcol) = findFirst(pixels, 0)
    numTimesFilled = 0
    # make all 0s to 2s
    while frow != -1:
        pixels = floodFill(pixels, (frow, fcol), 0, 2)
        numTimesFilled += 1
        (frow, fcol) = findFirst(pixels, 0)
    #0printarr(pixels)
    # for every 0 that is on a wall, flood fill from it
    for _ in xrange(numTimesFilled + 1):
        location = findFirst(pixels, 2)
        if isOnWall(pixels, location):
            pixels = floodFill(pixels, location, 2, 1)
            numTimesFilled -= 1
    printarr(replaceAll(pixels, 2, 0))
    return numTimesFilled

if __name__ == '__main__':
    import openpbm
    import getbounding
    import extractNumber

    fstruct = 'pbms/digit/*N_*F.pbm'
    for n in xrange(1):
        sum = 0
        print "For number: " + str(n)
        for f in xrange(1):
            file = openpbm.fileNameFrom(fstruct, n, f)
            pixels = openpbm.read_pbm(file)
            extracted = extractNumber.extract(pixels, getbounding.getBoundingBox(pixels))
            #printarr(extracted)
            numh = numberOfHoles(extracted)
            print numh
            sum += numh

        print sum / 100.0