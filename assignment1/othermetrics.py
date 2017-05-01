def sumBlacks(pixels):
    height = len(pixels)
    width = len(pixels[0])

    sum = 0
    for v in xrange(height):
        for h in xrange(width):
            if pixels[v][h] == 1:
                sum += 1
    return sum

def getDensity(pixels):
    height = len(pixels)
    width = len(pixels[0])

    return float(sumBlacks(pixels)) / float(width * height)

def getHoleFraction(pixels):
    import numHoles
    height = len(pixels)
    width = len(pixels[0])

    hole = numHoles.isolateHoles(pixels)
    sum = sumBlacks(hole)

    return float(sum) / float(width * height)