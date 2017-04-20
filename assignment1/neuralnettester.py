from netclass import NeuralNet
import openpbm

class NetTester():
    def userTest(self):
        while True:
            n = input("Number: ")
            f = input("File Numer: ")
            pixels = openpbm.read_pbm(openpbm.fileNameFrom(self.fstruct, n, f))
            guesses = self.net.makeGuess(pixels)
            print guesses
            maxG = max(guesses)
            index = guesses.index(maxG)
            print "Guessing: " + str(index) + " with probability of " + str(maxG)

    def __init__(self, numTrainingCycles, uptoandincnum, uptofile):
        self.fstruct = 'pbms/digit/*N_*F.pbm'
        afile = openpbm.fileNameFrom(self.fstruct, 0, 0)
        dimensions = openpbm.get_dimensions(afile)
        self.net = NeuralNet(dimensions[0], dimensions[1], 10)
        print "Starting training..."
        self.net.train(numTrainingCycles, self.fstruct, uptoandincnum + 1, uptofile)
        print "Done training."
        print "You may now test the neural net."
        self.userTest()


if __name__ == '__main__':
    NetTester(1, 0, 50)