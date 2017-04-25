import openpbm
import getattributeArray

def getData(number):
    fstruct = 'pbms/digit/*N_*F.pbm'
    allData = []
    for f in xrange(100):
        file = openpbm.fileNameFrom(fstruct, number, f)
        pixels = openpbm.read_pbm(file)
        data = getattributeArray.getAttrArr(pixels)
        allData.append(data)
    return allData

def writeToFile(fileName, allData):
    file = open(fileName, "w")
    for row in allData:
        strRow = str(row)[:-1][1:] + "\n"
        file.write(strRow)
    file.close()

if __name__ == "__main__":
    for i in xrange(10):
        print "Start Loading: " + str(i)
        data = getData(i)
        outfile = 'digit-feature-data/' + str(i) + '.csv'
        writeToFile(outfile, data)
        print "Done Writing: " + str(i)