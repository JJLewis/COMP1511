def getBoundingBox(pixels):
    height = len(pixels)
    width = len(pixels[0])

    firstTop = -1
    leastH = width
    lastTop = -1
    highestH = -1
    lastRowWithPixel = -1

    v = height - 1
    while v >= 0:
        h = 0
        while h < width:
            pixel = pixels[v][h]
            if pixel == 1:
                if firstTop == -1:
                    firstTop = v
                if h < leastH:
                    leastH = h
                if h > highestH:
                    highestH = h
                if lastRowWithPixel - v > 1:
                    lastTop = lastRowWithPixel
                lastRowWithPixel = v
            h += 1
        v -= 1

    if lastTop == -1:
        lastTop = lastRowWithPixel

    startRow = lastTop
    startCol = leastH
    boxHeight = firstTop - lastTop + 1
    boxWidth = highestH - leastH + 1

    return (startRow, startCol, boxWidth, boxHeight)