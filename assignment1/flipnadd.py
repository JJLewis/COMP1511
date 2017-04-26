def sumMatrixes(m1, m2):
    m3 = []
    for v in xrange(len(m1)):
        row = []
        for h in xrange(len(m1[0])):
            row.append(m1[v][h] + m2[v][h])
        m3.append(row)
    return m3

def flipnadd(pixels):
    import numHoles
    flipped = numHoles.horFlipArr(pixels)
    summed = sumMatrixes(pixels, flipped)
    numHoles.replaceAll(summed, 2, 1)
    #numHoles.printarr(summed)
    import getattributeArray
    print getattributeArray.getAttrArr(summed)

if __name__ == '__main__':
    import openpbm
    import getbounding
    import extractNumber

    fstruct = 'pbms/digit/*N_*F.pbm'
    for n in xrange(1):
        print "For number: " + str(n)
        for f in xrange(100):
            file = openpbm.fileNameFrom(fstruct, 2, f)
            pixels = openpbm.read_pbm(file)
            extracted = extractNumber.extract(pixels, getbounding.getBoundingBox(pixels))
            flipnadd(extracted)