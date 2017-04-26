def getAttrArr(pixels):
    import balance
    import othermetrics
    import getbounding
    import extractNumber
    import numHoles

    extracted = extractNumber.extract(pixels, getbounding.getBoundingBox(pixels))
    height = len(extracted)
    width = len(extracted[0])
    area = width * height
    hBalance = balance.horizontalBalance(extracted)
    vBalance = balance.verticalBalance(extracted)
    holeCount = numHoles.numberOfHoles(extracted)
    h1 = 1 if holeCount > 0 else 0
    h2 = 1 if holeCount == 2 else 0
    blackDensity = othermetrics.getDensity(extracted)
    holeDensity = othermetrics.getHoleFraction(extracted)

    #               0       1       2       3           4               5           6       7
    inputData = [height, width, hBalance, vBalance, blackDensity, holeDensity, holeCount, area]
    #inputData = [height, width, hBalance, vBalance, blackDensity, holeDensity, h1, h2, area]

    #nn
    #inputData = [hBalance, vBalance, blackDensity, holeDensity, holeCount]

    return inputData