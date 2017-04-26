import getattributeArray

def getGuess(n, f):
    import openpbm

    fstruct = 'pbms/digit/*N_*F.pbm'

    file = openpbm.fileNameFrom(fstruct, n, f)
    pixels = openpbm.read_pbm(file)
    return crack(pixels)

def userTest():
    while True:
        n = input("Number: ")
        f = input("File Numer: ")
        print "Guessing: " + str(getGuess(n, f))

def autoTest(number):
    numWrong = 0
    for f in xrange(100):
        guess = getGuess(number, f)
        if guess != number:
            print "Got " + str(number) + " file " + str(f) + " wrong, guessed " + str(guess)
            numWrong += 1
    print "For " + str(number) + ", got " + str(numWrong) + " wrong."
    return numWrong

def noHoles(features):
    height = features[0]
    width = features[1]
    hBalance = features[2]
    vBalance = features[3]
    blackDensity = features[4]
    holeDensity = features[5]
    area = features[7]

def subtractArrs(arr1, arr2):
    diff = []
    for i in xrange(len(arr1)):
        diff.append(arr1[i] - arr2[i])
    return diff

def sumArray(arr):
    sum = 0
    for i in xrange(len(arr)):
        sum += arr[i]
    return sum

def minElement(arr):
    smallest = arr[0]
    for i in xrange(len(arr)):
        if arr[i] < smallest:
            smallest = arr[i]
    return smallest

def indexOf(arr, element):
    index = -1
    for i in xrange(len(arr)):
        if arr[i] == element:
            index = i
            break
    return index

def hasHoles(features):
    height = features[0]
    width = features[1]
    hBalance = features[2]
    vBalance = features[3]
    blackDensity = features[4]
    holeDensity = features[5]
    holeCount = features[6]
    area = features[7]

    vals = [vBalance, hBalance, blackDensity, holeDensity]
    #           vB             hB          bD          hD
    avg0s = [0.50224126, 0.49946983, 0.51078787, 0.25400239]
    avg4s = [0.51961881, 0.54726439, 0.44558401, 0.06440427]
    avg6s = [0.51598543, 0.46690274, 0.51049573, 0.11210898]
    avg9s = [0.48285105, 0.52934610, 0.50199315, 0.12144133]
    allAvgs = [avg0s, avg4s, avg6s, avg9s]

    max0s = [0.54402028, 0.53911205, 0.69516509, 0.47796353]
    max4s = [0.58678802, 0.63155040, 0.59935897, 0.16258741]
    max6s = [0.60045118, 0.51220430, 0.65046296, 0.21785714]
    max9s = [0.54267401, 0.59926090, 0.68684896, 0.23958333]
    allMaxes = [max0s, max4s, max6s, max9s]

    min0s = [0.455238095, 0.428082192, 0.30862069, 0.117391304]
    min4s = [0.449059561, 0.44899676, 0.259800664, 0.02182285]
    min6s = [0.46015561, 0.401942067, 0.308943089, 0.052083333]
    min9s = [0.425593363, 0.469117435, 0.327489481, 0.051445578]
    allMins = [min0s, min4s, min6s, min9s]

    ans = [0,4,6,9]

    if vBalance > 0.5427:
        index = indexOf(ans, 9)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if hBalance > 0.5123:
        index = indexOf(ans, 6)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if holeDensity > 0.1626:
        index = indexOf(ans, 4)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if blackDensity > 0.5994:
        index = indexOf(ans, 4)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]

    if hBalance < 0.4692:
        index = indexOf(ans, 9)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if vBalance < 0.4602:
        index = indexOf(ans, 6)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if blackDensity < 0.3275:
        index = indexOf(ans, 9)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if holeDensity < 0.1174:
        index = indexOf(ans, 0)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]

    if holeCount == 2:
        return 8
    else:
        #return rangeMethod(allMaxes, allMins, vals, ans)
        return deviationMethod(allAvgs, vals, ans)

def rangeMethod(allMaxs, allMins, vals, ans):
    allDiffs = []
    for n in xrange(len(allMaxs)):
        diff = []
        for f in xrange(len(vals)):
            max = allMaxs[n][f]
            min = allMins[n][f]
            mid = (max + min) / 2.0
            factor = 1.0 / (max - mid)

            val = vals[f]
            diff.append((val - mid) * factor)
        allDiffs.append(sumArray(diff))
    index = indexOf(allDiffs, minElement(allDiffs))
    return ans[index]

def deviationMethod(allAvgs, vals, ans):
    deviations = []
    for i in xrange(len(allAvgs)):
        diff = subtractArrs(allAvgs[i], vals)
        deviations.append(sumArray(diff))
    index = indexOf(deviations, minElement(deviations))
    return ans[index]

def crack(pixels):
    features = getattributeArray.getAttrArr(pixels)
    numHoles = features[6]
    if numHoles == 0:
        return noHoles(features)
    else:
        return hasHoles(features)


if __name__ == '__main__':
    autoTest(0)