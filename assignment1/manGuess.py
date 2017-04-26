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

def noHoles(features):
    height = features[0]
    width = features[1]
    hBalance = features[2]
    vBalance = features[3]
    blackDensity = features[4]
    area = features[7]

    vals = [vBalance, hBalance, blackDensity, vBalance-hBalance]
    #           vB             hB          bD           vB-hB
    avg1s = [0.513545995, 0.525280464, 0.371528497, -0.011734469]
    avg2s = [0.50816045, 0.544074217, 0.379821942, -0.035913766]
    avg3s = [0.503079739, 0.572549886, 0.418143286, -0.069470147]
    avg5s = [0.506133777, 0.513417449, 0.418263036, -0.007283672]
    avg7s = [0.403378435, 0.530864138, 0.333130337, -0.127485704]
    allAvgs = [avg1s, avg2s, avg3s, avg5s, avg7s]

    max1s = [0.497575446, 0.698155444, 0.589670014, 0.114104116]
    max2s = [0.595729921, 0.627140656, 0.561155914, 0.112858112]
    max3s = [0.852272727, 0.683075463, 0.588235294, 0.008996669]
    max5s = [0.5642533, 0.617132867, 0.572450805, 0.080998947]
    max7s = [0.480858086, 0.699111111, 0.503267974, 0.008538673]
    allMaxes = [max1s, max2s, max3s, max5s, max7s]

    min1s = [0.442459505, 0.4232532, 0.171948052, -0.255695939]
    min2s = [0.440241902, 0.42096118, 0.264520202, -0.160065942]
    min3s = [0.433945922, 0.512787524, 0.216878403, -0.163414825]
    min5s = [0.435660316, 0.4346537, 0.264423077, -0.094255409]
    min7s = [0.305428249, 0.419571295, 0.203488372, -0.366472222]
    allMins = [min1s, min2s, min3s, min5s, min7s]


    ans = [1,2,3,5,7]

    if vBalance-hBalance < -0.0943:
        index = indexOf(ans, 5)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]

    if vBalance-hBalance > -0.0085:
        index = indexOf(ans, 7)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]


    if vBalance > 0.4809:
        index = indexOf(ans, 7)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if hBalance > 0.5135:
        index = indexOf(ans, 5)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if blackDensity > 0.50327:
        index = indexOf(ans, 7)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]

    if hBalance < 0.51279:
        index = indexOf(ans, 3)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
        index = indexOf(ans, 2)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if blackDensity < 0.265:
        index = indexOf(ans, 2)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
        index = indexOf(ans, 5)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]

    #return rangeMethod(allMaxes, allMins, vals, ans)
    return deviationMethod(allAvgs, vals, ans)

def hasHoles(features):
    height = features[0]
    width = features[1]
    hBalance = features[2]
    vBalance = features[3]
    blackDensity = features[4]
    holeDensity = features[5]
    holeCount = features[6]
    area = features[7]
    hHoleBalance = features[8]
    vHoleBalance = features[9]

    vals = [vBalance, hBalance, blackDensity, holeDensity, hHoleBalance, vHoleBalance]
    #           vB             hB          bD          hD       hHoleB       vHoleB
    avg0s = [0.50224126, 0.49946983, 0.51078787, 0.25400239, 0.500646788, 0.500470992]
    avg4s = [0.51961881, 0.54726439, 0.44558401, 0.06440427, 0.545390918, 0.497673672]
    avg6s = [0.51598543, 0.46690274, 0.51049573, 0.11210898, 0.520124085, 0.66581604]
    avg9s = [0.48285105, 0.52934610, 0.50199315, 0.12144133, 0.485020415, 0.332551043]
    allAvgs = [avg0s, avg4s, avg6s, avg9s]

    max0s = [0.54402028, 0.53911205, 0.69516509, 0.47796353, 0.557639752, 0.528851315]
    max4s = [0.58678802, 0.63155040, 0.59935897, 0.16258741, 0.671568627, 0.584854995]
    max6s = [0.60045118, 0.51220430, 0.65046296, 0.21785714, 0.667913832, 0.716302953]
    max9s = [0.54267401, 0.59926090, 0.68684896, 0.23958333, 0.604333868, 0.375364431]
    allMaxes = [max0s, max4s, max6s, max9s]

    min0s = [0.455238095, 0.428082192, 0.30862069, 0.117391304, 0.445364425, 0.462624113]
    min4s = [0.449059561, 0.44899676, 0.259800664, 0.02182285, 0.437693419, 0.359429066]
    min6s = [0.46015561, 0.401942067, 0.308943089, 0.052083333, 0.392874693, 0.620032116]
    min9s = [0.425593363, 0.469117435, 0.327489481, 0.051445578, 0.336236934, 0.293334824]
    allMins = [min0s, min4s, min6s, min9s]



    ans = [0,4,6,9]

    # Filter Smallest Maxes
    if vHoleBalance > 0.37537:
        index = indexOf(ans, 9)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if hHoleBalance > 0.55764:
        index = indexOf(ans, 0)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
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

    if vHoleBalance < 0.62004:
        index = indexOf(ans, 6)
        if index != -1:
            del allAvgs[index]
            del allMaxes[index]
            del allMins[index]
            del ans[index]
    if hHoleBalance < 0.44537:
        index = indexOf(ans, 0)
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
        if len(ans) == 0:
            return -1
        if vHoleBalance > 0.620032:
            return 6
        if vHoleBalance < 0.375365:
            return 9
        return rangeMethod(allMaxes, allMins, vals, ans)
        #return deviationMethod(allAvgs, vals, ans)

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
    sumWrong = 0
    toTest = [1,2,3,5,7]
    #toTest = [1]
    #toTest = [0,4,6,8,9]
    #toTest = [0,1,2,3,4,5,6,7,8,9]
    numOfGuesses = (len(toTest) * 100.0)
    for i in toTest:
        sumWrong += autoTest(i)
    print "Accuracy of: " + str(((len(toTest) * 100.0) - sumWrong) / len(toTest)) + "%"