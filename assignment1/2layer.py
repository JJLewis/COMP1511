import numpy as np
import openpbm

class NeuralNet():

    def pMatrixDim(self, m1, n1, m2, n2):
        print n1 + " width: " + str(len(m1[0]))
        print n1 + "height: " + str(len(m1))

        print n2 + " width: " + str(len(m2[0]))
        print n2 + " height: " + str(len(m2))

    def makeGuess(self, input):
        # layers
        l0 = input
        l1 = self.nonlin(np.dot(l0, self.syn0))
        l2 = self.nonlin(np.dot(l1, self.syn1))

        return l2

    # sigmoid function
    def nonlin(self, x, deriv=False):
        if deriv:
            return x * (1 - x)
        return 1 / (1 + np.exp(-x))

    def train(self, numtimes, filenameFormat, numnum, maxPerNum):
        for t in xrange(numtimes):
            for n in xrange(numnum):
                expected = [0] * 10
                expected[n] = 1
                expected = np.array(expected)
                for f in xrange(maxPerNum + 1):
                    file = openpbm.fileNameFrom(filenameFormat, n, f)

                    # open file
                    pixels = openpbm.read_pbm(file)
                    pixels = np.array(pixels)

                    # layers
                    l0 = pixels
                    l1 = self.nonlin(np.dot(l0, self.syn0))
                    l2 = self.nonlin(np.dot(l1, self.syn1))

                    # backpropagation
                    l2_error = expected - l2
                    if (t % numtimes / 10) == 0:
                        print 'Error: ' + str(np.mean(np.abs(l2_error)))

                    # calculate deltas
                    l2_delta = l2_error * self.nonlin(l2, deriv=True)
                    l1_error = l2_delta.dot(self.syn1.T)
                    l1_delta = l1_error * self.nonlin(l1, deriv=True)

                    # update synapses
                    self.syn1 += l1.T.dot(l2_delta)
                    self.syn0 += l0.T.dot(l1_delta)

    def __init__(self, inputW, inputH, numOutputNodes):
        self._inputW = inputW
        self._inputH = inputH

        np.random.seed(1)

        self.syn0 = 2 * np.random.random((inputW, inputH)) - 1
        self.syn1 = 2 * np.random.random((numOutputNodes, 1)) - 1