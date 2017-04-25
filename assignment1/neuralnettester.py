from netclass import NeuralNet
import openpbm
import getattributeArray

class NetTester():

    def getGuess(self, n, f):
        pixels = openpbm.read_pbm(openpbm.fileNameFrom(self.fstruct, n, f))
        inputData = getattributeArray.getAttrArr(pixels)
        guesses = self.net.makeGuess(inputData)
        maxG = max(guesses)
        index = guesses.index(maxG)
        return (index, maxG)

    def testAll(self, uptoandinc):
        numErrors = 0
        for n in xrange(uptoandinc + 1):
            for f in xrange(100):
                (index, probability) = self.getGuess(n, f)
                if index != n:
                    numErrors += 1
                    print str(n) + " failed. NN guessed: " + str(index) + " with probability of " + str(probability)
        print "Done Testing All"
        print "Made " + str(numErrors) + " mistakes. Accuracy of " + str(1 - (numErrors/((uptoandinc+1) * 100.0)))

    def userTest(self):
        while True:
            n = input("Number: ")
            f = input("File Numer: ")
            (index, prob) = self.getGuess(n, f)
            print "Guessing: " + str(index) + " with probability of " + str(prob)

    def __init__(self, numTrainingCycles, uptoandincnum, uptofile):
        self.fstruct = 'pbms/digit/*N_*F.pbm'

        self.net = NeuralNet(8, 10)

        print "Loading training data..."
        (training, expected) = self.net.loadTrainingData(self.fstruct, uptoandincnum + 1, uptofile)
        print "Loaded training data."

        print "Starting training..."
        self.net.train(numTrainingCycles, training, expected)
        print "Done training."

        print "You may now test the neural net."
        #self.userTest()
        self.testAll(uptoandincnum)

if __name__ == '__main__':
    NetTester(1000, 2, 20)
