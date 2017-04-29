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

def sealLeftWall(pixels):
    sealed = pixels
    for x in xrange(len(sealed)):
        sealed[x][0] = 1
    return sealed

def sealRightWall(pixels):
    sealed = pixels
    for x in xrange(len(sealed)):
        sealed[x][len(sealed[0]) - 1] = 1
    return sealed

def halves(pixels, side):
    height = len(pixels)
    width = len(pixels[0])

    half = extractArraySection(pixels, 0, width/2.0, height, width)
    half = sealLeftWall(half)
    if side == 0:
        half = extractArraySection(pixels, 0, 0, height, width/2.0)
        half = sealRightWall(half)

    import getattributeArray
    features = getattributeArray.getAttrArr(half)
    return [features[6], features[8], features[9], features[2], features[3]]

if __name__ == '__main__':
    import openpbm
    import getbounding
    import extractNumber

    fstruct = 'pbms/digit/*N_*F.pbm'
    for n in [1,2,3,5,7]:
        print "For number: " + str(n)
        allForNum = []
        for f in xrange(100):
            file = openpbm.fileNameFrom(fstruct, n, f)
            pixels = openpbm.read_pbm(file)
            extracted = extractNumber.extract(pixels, getbounding.getBoundingBox(pixels))
            features = halves(extracted, 0)
            allForNum.append(features)
        import getNumberData
        getNumberData.writeToFile('digit-feature-data/hr_' + str(n) + '.csv', allForNum)
