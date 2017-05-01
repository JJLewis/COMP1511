import numpy as np
def extract(pixels, extractInfo):

    (startRow, startCol, copyWidth, copyHeight) = extractInfo
    #startRow = 5
    '''
    print extractInfo
    copy = [[2] * copyWidth] * copyHeight
    v = startRow
    while v < startRow + copyHeight:
        h = startCol
        while h < startCol + copyWidth:
            copy[v - startRow][h - startCol] = pixels[v][h]
            h += 1
        v += 1
    return copy
    '''
    p = np.array(pixels)
    c = p[startRow:startRow+copyHeight, startCol:startCol+copyWidth]
    #print c
    return c.tolist()