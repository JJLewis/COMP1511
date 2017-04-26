def extractArraySection(array, sV, sH, eV, eH):
    newArr = []
    v = int(sV)
    while v < eV:
        h = int(sH)
        row = []
        while h < eH:
            row.append(array[v][h])
            h += 1
        newArr.append(row)
        v += 1
    return newArr

def doesBlackExist(pixels, threshold):
    sum = 0
    for v in xrange(len(pixels)):
        for h in xrange(len(pixels[0])):
            if pixels[v][h] == 1:
                sum += 1
    return sum > threshold

def quadrants(pixels):
    height = len(pixels)
    width = len(pixels[0])
    q1 = extractArraySection(pixels, 0,             0,          height/2.0, width/2.0)
    q2 = extractArraySection(pixels, 0,             width/2.0,  height/2.0, width)
    q3 = extractArraySection(pixels, height/2.0,    0,          height,     width/2.0)
    q4 = extractArraySection(pixels, height/2.0,    width/2.0,  height,     width)
    quads = [q1,q2,q3,q4]

    areaOfQuad = (height * width) / 4.0

    numQuads = 0
    for quad in quads:
        if doesBlackExist(quad, areaOfQuad/4.0):
            numQuads += 1
    #print numQuads

    return numQuads

if __name__ == '__main__':
    import openpbm
    import getbounding
    import extractNumber

    fstruct = 'pbms/digit/*N_*F.pbm'
    for n in [1,2,3,5,7]:
        print "For number: " + str(n)
        num4s = 0
        for f in xrange(100):
            file = openpbm.fileNameFrom(fstruct, n, f)
            pixels = openpbm.read_pbm(file)
            extracted = extractNumber.extract(pixels, getbounding.getBoundingBox(pixels))
            if quadrants(extracted) == 4:
                num4s += 1
        print str(n) + " total num 4s: " + str(num4s)