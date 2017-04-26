def horizontalBalance(pixels):
    height = len(pixels)
    width = len(pixels[0])

    column_sum = 0
    n_black_pixels = 0

    v = 0
    while v < height:
        h = 0
        while h < width:
            if pixels[v][h] == 1:
                n_black_pixels += 1
                column_sum += h
            h += 1
        v += 1

    return (float(column_sum) / float(n_black_pixels) + 0.5) / float(width)

def verticalBalance(pixels):
    height = len(pixels)
    width = len(pixels[0])

    row_sum = 0
    n_black_pixels = 0

    v = 0
    while v < height:
        h = 0
        while h < width:
            if pixels[v][h] == 1:
                n_black_pixels += 1
                row_sum += v
            h += 1
        v += 1

    return (float(row_sum) / float(n_black_pixels) + 0.5) / float(height)

def verticalHoleBalance(pixels):
    import numHoles
    isolated = numHoles.isolateHoles(pixels)
    if numHoles.countHoles(isolated) == 0:
        return 0.5
    return verticalBalance(isolated)

def horizontalHoleBalance(pixels):
    import numHoles
    isolated = numHoles.isolateHoles(pixels)
    if numHoles.countHoles(isolated) == 0:
        return 0.5
    return horizontalBalance(isolated)

if __name__ == '__main__':
    import openpbm
    import getbounding
    import extractNumber

    fstruct = 'pbms/digit/*N_*F.pbm'
    for n in xrange(1):
        print "For number: " + str(n)
        for f in xrange(1):
            file = openpbm.fileNameFrom(fstruct, 6, f)
            pixels = openpbm.read_pbm(file)
            extracted = extractNumber.extract(pixels, getbounding.getBoundingBox(pixels))

            h = horizontalBalance(extracted)
            v = verticalBalance(extracted)
            hv = verticalHoleBalance(extracted)
            hh = horizontalHoleBalance(extracted)
            print "Horizontal: " + str(h) + " Vertical: " + str(v) + " V Hole: " + str(hv) + " H Hole: " + str(hh)